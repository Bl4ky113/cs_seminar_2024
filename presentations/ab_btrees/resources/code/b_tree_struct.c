int alpha = 2; /* any int >= 2 */
typedef struct tr_n_t {
  int degree;
  int height;
  key_t key[2 * alpha];
  struct tr_n_t *next[(2 * alpha) + 1];
  /* ... */
} tree_node_t;