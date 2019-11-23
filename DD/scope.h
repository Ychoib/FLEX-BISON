#ifndef SCOPE_H
#define SCOPE_H

#include "symtab.h"

typedef struct scope_elem_s {
  symtable **content;
  int max_size;
  int top;
} scope_elem;

scope_elem *scope_init(int max_size);
void scope_push(scope_elem *stack, symtable *st);
symtable *scope_pop(scope_elem *stack);
st_node_t *search_scope_stack(scope_elem *stack, char * name);

#endif
