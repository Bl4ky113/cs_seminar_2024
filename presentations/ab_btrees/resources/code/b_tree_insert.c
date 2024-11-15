int insert(tree_node_t *tree, key_t new_key, object_t *new_object) { 
    tree_node_t *current_node, *insert_pt;
    key_t insert_key;
    int finished;
    current_node = tree;
    if( tree->height == 0 && tree->degree == 0 ) {
        tree->key[0] = new_key;
        tree->next[0] = (tree_node_t *) new_object;
        tree->degree = 1;
        return(0); /* insert in empty tree */
    }

    create_stack();
    while( current_node->height > 0 ) { 
        int lower, upper;
        /* binary search among keys */
        push( current_node );
        lower = 0;
        upper = current_node->degree;
        while( upper > lower +1 ) { 
            if( new_key < current_node->key[(upper+lower)/2 ] )
                upper = (upper+lower)/2;
            else
                lower = (upper+lower)/2;
        }
        current_node = current_node->next[lower];
    } 
    /* now current_node is leaf node in which we insert */

    insert_pt = (tree_node_t *) new_object;
    insert_key = new_key;
    finished = 0;
    while( !finished ){ 
        int i, start;
        if( current_node->height > 0 )
            start = 1;
            /* insertion in non-leaf starts at 1 */
        else
            start = 0;
            /* insertion in non-leaf starts at 0 */
        /* node still has room */
        if( current_node->degree < 2 * ALPHA ) { 
            /* move everything up to create the insertion gap */
            i = current_node->degree;
            while( (i > start) && (current_node->key[i-1] > insert_key)) {
                current_node->key[i] =
                    current_node->key[i-1];
                current_node->next[i] =
                    current_node->next[i-1];
                i -= 1;
            }

            current_node->key[i] = insert_key;
            current_node->next[i] = insert_pt;
            current_node->degree +=1;
            finished = 1;
        } 

        /* end insert in non-full node */
        else {
            /* node is full, have to split the node*/
            tree_node_t *new_node;
            int j, insert_done = 0;
            new_node = get_node();
            i = B-1; 
            j = (B-1)/2;
            while( j >= 0 ) { 
                /* copy upper half to new node */
                if( insert_done || insert_key < current_node->key[i] ) {
                    new_node->next[j] =
                        current_node->next[i];
                    new_node->key[j--] =
                        current_node->key[i--];
                } else { 
                    new_node->next[j] = insert_pt;
                    new_node->key[j--] = insert_key;
                    insert_done = 1;
                }
            } 
            /* upper half done, insert in lower half, if necessary*/
            while( !insert_done) { 
                if( insert_key < current_node->key[i] && i >= start ) {
                    current_node->next[i+1] =
                        current_node->next[i];
                    current_node->key[i+1] =
                        current_node->key[i];
                    i -=1;
                } else {
                    current_node->next[i+1] =
                        insert_pt;
                    current_node->key[i+1] =
                        insert_key;
                    insert_done = 1;
                }
            } 
            /*finished insertion */

            current_node->degree = B+1 - ((B+1)/2);
            new_node->degree = (B+1)/2;
            new_node->height = current_node->height;
            /* split nodes complete, now insert the new node above */
            insert_pt = new_node;
            insert_key = new_node->key[0];
            if( ! stack_empty() ) { 
                /* not at root; move one level up*/
                current_node = pop();
            }
            else { 
                /* splitting root: needs copy to keep root address*/
                new_node = get_node();
                for( i=0; i < current_node->degree; i++ ) { 
                    new_node->next[i] =
                        current_node->next[i];
                    new_node->key[i] =
                        current_node->key[i];
                }
                new_node->height =
                    current_node->height;
                new_node->degree =
                    current_node->degree;
                current_node->height += 1;
                current_node->degree = 2;
                current_node->next[0] = new_node;
                current_node->next[1] = insert_pt;
                current_node->key[1] = insert_key;
                finished =1;
            } /* end splitting root */
        } /* end node splitting */
    } /* end of rebalancing */
    remove_stack();
    return( 0 );
}
