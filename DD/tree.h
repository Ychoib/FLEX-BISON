#ifndef TREE_H
#define TREE_H

#include "symtab.h"

typedef enum node_e {
  BEGIN_END,
  STMT_LIST,
  IF_THEN_ELSE_MATCHED,
  WHILE_DO,
  FOR_LOOP,
  IF_THEN_UNMATCHED,
  IF_THEN_ELSE_UNMATCHED,
  ASSIGN_STMT,
  IDENT,
  ID_ARRAY,
  PROC_CALL,
  FUNC_CALL,
  EXPR_LIST,
  RELOP_EXPR,
  SIGN_TERM,
  ADDOP_EXPR,
  MULOP_EXPR,
  RNUMBER,
  INUMBER,
  NOT_FACTOR
} node_type;

/*
 * the syntax tree + type checking code.
 * type: node type,(the node_type enum)
 * attr union: value 정보.  (타입에 따라 바뀜)
 * num_of_children: 특정 노드 child node 개수
 * left, right: 왼쪽노드,오른쪽노드 포인터
 * children: child node가 2보다 크면 더블포인터로 넣어줌
 */
typedef struct tree_s {
  node_type type;

  union {
    int ival;        /* attr.ival : INUMBER */
    float rval;      /* attr.rval : RNUMBER */
    st_node_t *sval; /* attr.sval : IDENTIFY */
    char *opval;      /* attr.opval : RELOP, ADDOP, MULOP */
  } attr;

  int num_of_children;

  struct tree_s *left, *right;
  struct tree_s **children;
} tree_t;


tree_t *mktree(node_type type, int count, ...);
void label_tree(tree_t *t, int left);

symtab_type type_check(tree_t *t);

#endif
