#include <stdio.h>
#include <stdlib.h>
#include "scope.h"
#include "symtab.h"

/*
- scope : symbol table의  stack 구조
- symbol table을 push & pop
- search_scope_stack : 같은 name의 symbol table 있는지 알기 위해 scope 탐색 (top-down 방식)
- 같은 식별자가 사용될 수 있는데 가장 위에 있는게 첫번째로 return
*/

/* upper bound(=max_size(10)) 의 크기로 스택 초기화 */
scope_elem *scope_init(int max_size) {
  scope_elem *stack = (scope_elem *) malloc(sizeof(scope_elem));

  symtable **content;
  int i;

  content = (symtable **) malloc(sizeof(symtable*) * max_size);
  for (i = 0; i < max_size; i++)
    content[i] = (symtable *) malloc(sizeof(symtable));

  stack->content = content;
  stack->max_size = max_size;
  stack->top = -1;

  return stack;
}

void scope_push(scope_elem *stack, symtable *st) {
  stack->content[++stack->top] = st;
}

symtable *scope_pop(scope_elem *stack) {
  return stack->content[stack->top--];
}

/* top-down 방식 stack 탐색 */
st_node_t *search_scope_stack(scope_elem *stack, char * name) {
  symtable *current;
  st_node_t *n;
  int i;

  for (i = stack->top; i >= 0; --i) {
     current = stack->content[i];
     n = symtab_lookup(current, name);

     if (n != NULL) return n;
  }

  return NULL;
}
