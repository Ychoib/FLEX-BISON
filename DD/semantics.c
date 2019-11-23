#include <stdio.h>
#include "semantics.h"
/* 여기에 정의된 함수들은 syntax tree를 만들고 올바르지 않은 tree 가 있으면 컴파일러를 종료하는 sem_error()를 호출 */

/* if_then : x */
void if_then_semantics(tree_t *t) {
  if (type_check(t) != BOOLEAN_TYPE)
    sem_error(TYPE_NON_BOOLEAN);
}

/* while : x */
void while_semantics(tree_t *t) {
  if (type_check(t) != BOOLEAN_TYPE)
    sem_error(TYPE_NON_BOOLEAN);
}

/* function : argument 숫자, 순서, 타입 확인 */
void function_semantics(st_node_t *st_node, tree_t *t) {
  arg_elem *head = NULL;
  head = expr_list_eval(head, t);
  if (st_node->num_of_args != arg_list_size(head))
    sem_error(WRONG_NUMBER_OF_ARGS);
  if (arg_list_compare(st_node->arg_type_list, head) != 0)
    sem_error(WRONG_ARG_TYPE);
}

/* procedure : argument 숫자, 순서, 타입 확인 */
void procedure_semantics(st_node_t *st_node, tree_t *t) {
  arg_elem *head = NULL;
  head = expr_list_eval(head, t);
  if (st_node->num_of_args != arg_list_size(head))
    sem_error(WRONG_NUMBER_OF_ARGS);

  // Compare arg_lists
  if (arg_list_compare(st_node->arg_type_list, head) != 0)
    sem_error(WRONG_ARG_TYPE);
}

/* 비교하기 쉽도록 트리를 linked list 로 변환 */
arg_elem *expr_list_eval(arg_elem *head, tree_t *t) {
  if (t == NULL) return head;

  if (t->type == EXPR_LIST) {
    head = expr_list_eval(head, t->left);
    head = expr_list_eval(head, t->right);
  }
  else
    head = arg_append(head, type_check(t));
}

/* array : 정수형 index 경계 확인 */
void array_semantics(st_node_t *st_node, tree_t *t) {
  int index, lb, ub;
  if (type_check(t) != INTEGER_TYPE) //index 정수형인지 확인
    sem_error(ARRAY_NON_INTEGER_BOUNDS);

  if (t->type == INUMBER) { 
    index = t->attr.ival;
    lb = st_node->type->lb;
    ub = st_node->type->ub;

    if (index < lb || index > ub)	//index 와 low bound, upper bound 비교확인
      sem_error(ARRAY_INDEX_OUT_OF_BOUNDS);
  }
}

/* 에러 메세지 case 분기 */
void sem_error(sem_error_id id) {
  char *msg;

  switch(id) {
    case VAR_UNDECLARED:
      msg = "Variable is undeclared"; break;
    case VAR_REDECLARED:
      msg = "Variable has been redeclared"; break;
    case WRONG_NUMBER_OF_ARGS:
      msg = "Wrong number of arguments"; break;
    case WRONG_ARG_TYPE:
      msg = "Wrong argument type"; break;
    case NO_RETURN_STMT:
      msg = "Function has no return statement"; break;
    case NON_LOCAL_MODIFICATION:
      msg = "Function tried to modify a non-local variable"; break;
    case BAD_RETURN_TYPE:
      msg = "Function did not return an integer or a real"; break;
    case ARRAY_INDEX_OUT_OF_BOUNDS:
      msg = "Array index is out of bounds"; break;
    case ARRAY_NON_INTEGER_BOUNDS:
      msg = "Array has non-integer bounds"; break;
    case TYPE_MISMATCH_EXPR:
      msg = "Type mismatch in expression"; break;
    case TYPE_MISMATCH_ASSN:
      msg = "Type mismatch in assignment"; break;
    case TYPE_NON_BOOLEAN:
      msg = "Expression is non-boolean"; break;
    default:
      msg = "UNKNOWN ERROR ID";
      fprintf(stderr, "code: %d\n", id);
  }

  fprintf(stderr, "[ERROR @ line: %d]: %s\n", yylineno, msg);
  exit(1);
}
