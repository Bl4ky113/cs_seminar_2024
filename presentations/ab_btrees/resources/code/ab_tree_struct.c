#define ALPHA 2
#define BETA 4 /* any int >= (2 * ALPHA) - 1*/
typedef struct tr_n_t {
  int degree;
  int height;
  key_t key[BETA];
  struct tr_n_t *next[BETA];
  /* ... */
} tree_node_t;
