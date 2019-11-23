#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "tree.h"
#include "symtab.h"
#include "semantics.h"

/* 노드를 tree로 변환 , "..." : tree nodes의 count number */
tree_t *mktree(node_type type, int count, ...) {
  va_list ap;
  tree_t *t = (tree_t *) malloc(sizeof(tree_t));
  int i;

  t->left = t->right = NULL;
  t->type = type;
  t->num_of_children = count;

  if (count > 2)
    t->children = malloc(sizeof(*t->children) * count);

  va_start(ap, count);
  for (i = 0; i < count; i++) {
    if (i == 0)
      t->left = va_arg(ap, tree_t*);
    else if (i == count - 1)
      t->right = va_arg(ap, tree_t*);
    else
      t->children[i] = va_arg(ap, tree_t*);
  }
  va_end(ap);

  return t;
}

/* type check 함수 */
symtab_type type_check(tree_t *t) {
  symtab_type left_type, right_type;

  assert(t != NULL);	//null 이면 오류
  switch(t->type) {
    /* ID 나 Funcntion이면 symbol table 에서 type 얻어와 return */
    case IDENT:
    case FUNC_CALL:
      assert(t->attr.sval != NULL);
      return (t->attr.sval->type)->name;

    /* Array,  left child 가 ID */
    case ID_ARRAY:
      assert(t->attr.sval != NULL);
      left_type = type_check(t->left);

      if ((t->attr.sval->type)->name == ARRAY_TYPE_INT &&
          left_type == INTEGER_TYPE)
        return INTEGER_TYPE;
      else if ((t->attr.sval->type)->name == ARRAY_TYPE_REAL &&
               left_type == FLOAT_TYPE)
        return FLOAT_TYPE;
      sem_error(TYPE_MISMATCH_ASSN);

    /* Basic types */
    case RNUMBER:
      return FLOAT_TYPE;
    case INUMBER:
      return INTEGER_TYPE;

    /* Not, 왼쪽 expression이 boolean 인지 확인 */
    case NOT_FACTOR:
      left_type = type_check(t->left);

      if (left_type == BOOLEAN_TYPE)
        return BOOLEAN_TYPE;
      sem_error(TYPE_NON_BOOLEAN);

    /* Relational op, 양쪽 expression이 boolean인지 확인 */
    case RELOP_EXPR:
      left_type = type_check(t->left);
      right_type = type_check(t->right);

      if (left_type == right_type)
        return BOOLEAN_TYPE;
      sem_error(TYPE_NON_BOOLEAN);
    /* addop/mulop, type casting 오류 검출 */
    case ADDOP_EXPR:
    case MULOP_EXPR:
      left_type = type_check(t->left);
      right_type = type_check(t->right);

      if (left_type == right_type)
        return left_type;
      sem_error(TYPE_MISMATCH_EXPR);
  }
}

