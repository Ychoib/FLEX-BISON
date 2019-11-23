#ifndef SEMANTICS_H
#define SEMANTICS_H

#include <stdlib.h>
#include "arg_list.h"
#include "tree.h"

/* flex에서 line counter를 사용하기 위해서 yylineno 변수 정의*/
extern int yylineno;

typedef enum sem_error_id_e {
  VAR_UNDECLARED,
  VAR_REDECLARED,
  WRONG_NUMBER_OF_ARGS,
  WRONG_ARG_TYPE,
  NO_RETURN_STMT,
  NON_LOCAL_MODIFICATION,
  BAD_RETURN_TYPE,
  ARRAY_INDEX_OUT_OF_BOUNDS,
  ARRAY_NON_INTEGER_BOUNDS,
  TYPE_MISMATCH_EXPR,
  TYPE_MISMATCH_ASSN,
  TYPE_NON_BOOLEAN
} sem_error_id;

void if_then_semantics(tree_t *t);
void while_semantics(tree_t *t);
void function_semantics(st_node_t *st_node, tree_t *t);
void procedure_semantics(st_node_t *st_node, tree_t *t);
arg_elem *expr_list_eval(arg_elem *head, tree_t *t);
void array_semantics(st_node_t *st_node, tree_t *t);

void sem_error(sem_error_id id);

#endif
