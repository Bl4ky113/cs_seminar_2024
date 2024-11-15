object_t *delete(tree_node_t *tree, key_t delete_key) { 
    tree_node_t *current, *tmp_node;
    int finished, i, j;
    current = tree;
    create_node_stack(); 
    create_index_stack();
    while( current->height > 0 ) { 
        /* not at leaf level */
        int lower, upper;
        /* binary search among keys */
        lower = 0;
        upper = current->degree;
        while( upper > lower +1 ) { 
            if( delete_key < current->key[ (upper+lower)/2 ] ) 
                upper = (upper+lower)/2;
            else
                lower = (upper+lower)/2;
        }

        push_index_stack( lower );
        push_node_stack( current );
        current = current->next[lower];
    } 
    /* now current is leaf node from which we delete */
    for ( i=0; i < current->degree ; i++ )
        if( current->key[i] == delete_key )
            break;
    if( i == current->degree ) { 
        /* delete failed; key does not exist */
        return( NULL ); 
    } else { 
        /* key exists, now delete from leaf node */
        object_t *del_object;
        del_object = (object_t *) current->next[i];
        current->degree -=1;
        while( i < current->degree ) { 
            current->next[i] = current->next[i+1];
            current->key[i] = current->key[i+1];
            i+=1;
        } 
        /* deleted from node, now rebalance */
        finished = 0;
        while( ! finished ) {
            if(current->degree >= A ) { 
                finished = 1; 
                /* node still full enough, can stop */
            }
            else { 
                /* node became underfull */
                if( stack_empty() ) {
                    /* current is root */
                    if(current->degree >= 2 )
                        /* root still necessary */
                        finished = 1; 
                    else if ( current->height == 0 )
                        /* deleting last keys from root */
                        finished = 1; 
                    else { 
                        /* delete root, copy to keep address */
                        tmp_node = current->next[0];
                        for( i=0; i< tmp_node->degree; i++ ) {
                            current->next[i] = tmp_node->next[i]; 
                            current->key[i] = tmp_node->key[i];
                        }
                        current->degree =
                            tmp_node->degree;
                        current->height =
                            tmp_node->height;
                        return_node( tmp_node );
                        finished = 1;
                    }
                    /* done with root */
                } else { 
                    /* delete from non-root node */
                    tree_node_t *upper, *neighbor;
                    int curr;
                    upper = pop_node_stack();
                    curr = pop_index_stack();
                    if( curr < upper->degree -1 ) { 
                        /* not last*/
                        neighbor = upper->next[curr+1];
                        if( neighbor->degree >A ) { 
                            /* sharing possible */
                            i = current->degree;
                            if( current->height > 0 )
                                current->key[i] =
                                    upper->key[curr+1];
                            else { 
                                /* on leaf level, take leaf key */
                                current->key[i] =
                                    neighbor->key[0];
                                neighbor->key[0] =
                                    neighbor->key[1];
                            }
                            current->next[i] =
                                neighbor->next[0];
                            upper->key[curr+1] =
                                neighbor->key[1];
                            neighbor->next[0] =
                                neighbor->next[1];
                            for( j = 2; j < neighbor->degree; j++) { 
                                neighbor->next[j-1] =
                                    neighbor->next[j];
                                neighbor->key[j-1] =
                                    neighbor->key[j];
                            }
                            neighbor->degree -=1;
                            current->degree+=1;
                            finished =1;
                        } /* sharing complete */
                        else { 
                            /* must join */
                            i = current->degree;
                            if( current->height > 0 )
                                current->key[i] =
                                    upper->key[curr+1];
                            else /* on leaf level, take leaf key */
                                current->key[i] =
                                    neighbor->key[0];
                            current->next[i] =
                                neighbor->next[0];
                            for( j = 1; j < neighbor->degree; j++) { 
                                current->next[++i] =
                                    neighbor->next[j];
                                current->key[i] =
                                    neighbor->key[j];
                            }
                            current->degree = i+1;
                            return_node( neighbor );
                            upper->degree -=1;
                            i = curr+1;
                            while( i < upper->degree ) { 
                                upper->next[i] =
                                    upper->next[i+1];
                                upper->key[i] =
                                    upper->key[i+1];
                                i +=1;
                            } 
                            /* deleted from upper, now propagate up */
                            current = upper;
                        } /* end of share/joining if-else*/
                    }
                    else { 
                        /* current is last entry in upper */
                        neighbor = upper->next[curr-1]
                            if( neighbor->degree >A ) { 
                                /* sharing possible */
                                for( j = current->degree; j > 1; j--) { 
                                    current->next[j] =
                                        current->next[j-1];
                                    current->key[j] =
                                        current->key[j-1];
                                }
                                current->next[1] =
                                    current->next[0];
                                i = neighbor->degree;
                                current->next[0] =
                                    neighbor->next[i-1];
                                if( current->height > 0 ) {
                                    current->key[1] =
                                        upper->key[curr];
                                }
                                else {
                                    /* on leaf level, take leaf key */
                                    current->key[1] =
                                        current->key[0];
                                    current->key[0] =
                                        neighbor->key[i-1];
                                }
                                upper->key[curr] =
                                    neighbor->key[i-1];
                                neighbor->degree -=1;
                                current->degree+=1;
                                finished =1;
                            } /* sharing complete */
                            else { 
                                /* must join */
                                i = neighbor->degree;
                                if( current->height > 0 )
                                    neighbor->key[i] =
                                        upper->key[curr];
                                else /* on leaf level, take leaf key */
                                    neighbor->key[i] =
                                        current->key[0];
                                neighbor->next[i] =
                                    current->next[0];
                                for( j = 1; j < current->degree; j++) { 
                                    neighbor->next[++i] =
                                        current->next[j];
                                    neighbor->key[i] =
                                        current->key[j];
                                }
                                neighbor->degree = i+1;
                                return_node( current );
                                upper->degree -=1;
                                /* deleted from upper, now propagate up */
                                current = upper;
                            } /* end of share/joining if-else */
                    } /* end of current is (not) last in upper if-else*/
                } /* end of delete root/non-root if-else */
            } /* end of full/underfull if-else */
        } /* end of while not finished */

        return( del_object );

    } /* end of delete object exists if-else */
}
