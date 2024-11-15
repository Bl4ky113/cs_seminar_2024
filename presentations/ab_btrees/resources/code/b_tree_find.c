object_t *find(tree_node_t *tree, key_t query_key) {
  tree_node_t *current_node;
  object_t *object;
  current_node = tree;

  while( current_node->height >= 0 ) { 
    /* binary search among keys */
    int lower, upper;
    lower = 0;
    upper = current_node->degree;

    while( upper > lower +1 ) {
      int med = (upper+lower)/2;
      if( query_key < current_node->key[med] )
        upper = med;
      else
        lower = med;
    }
    if( current_node->height > 0)
      current_node = current_node->next[lower];

    else {
      if( current_node->key[lower] == query_key )
        object = (object_t *) current_node->next[lower];
      else
        object = NULL;
      return( object );
    }
  }
}
