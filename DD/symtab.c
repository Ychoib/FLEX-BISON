#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "symtab.h"
#include "semantics.h"
#include "type.h"

/* symbol table lookup 함수 */
st_node_t *symtab_lookup(symtable *st, char *name) {
  int hash_index = hashpjw(name);
  st_node_t *n = st->Table[hash_index];

  while (n != NULL) {
    if (!strcmp(name, n->name))
      return n;
    n = n->next;
  }

  return NULL;
}

/* 기존 symbol table에 새 entry 추가 */
st_node_t *symtab_insert(symtable *st, char *name, symtab_type class,
                         type_struct *type, location_e location, int symtab_index) {
  int hash_index = hashpjw(name);
  st_node_t *head = st->Table[hash_index];
  st_node_t *n;

  if ((n = symtab_lookup(st, name)) != NULL)
    sem_error(VAR_REDECLARED);		//symbol table에 이미 존재하는 건 변수가 재선언 된 경우이므로 해당 오류 출력
  n = (st_node_t*) malloc(sizeof(st_node_t));

  assert(n != NULL);	//null 이면 프로그램 종료
  n->name = strdup(name);
  n->class = class;
  n->type = type;
  n->location = location;

  /* function class 인경우 나중에 할당될 argument type list 할당해둠 */
  if (class == FUNCTION_CLASS)
    n->arg_type_list = calloc(1, sizeof(arg_elem));
  else
    n->arg_type_list = NULL;

  n->index = symtab_index;
  n->next = NULL;

  if (head != NULL)
    n->next = head;
  st->Table[hash_index] = n;

  return n;
}

/* hash pjw 알고리즘 사용 */
int hashpjw(char *s) {
  char* p;
  unsigned h = 0, g;

  for (p = s; *p != EOS; p++) {
    h = (h << 4) + (*p);
    if (g = h & 0xf0000000) {
      h = h ^ (g >> 24);
      h = h ^ g;
    }
  }

  return h % PRIME;
}

/*
symbol table의 Var_class 수와 function / procedure의 class argument수를 계산하여 오프셋 설정
2 : the format argument , 1: the integer argument 
*/
int calculate_stack_offset(symtable *st) {
  st_node_t *n;
  int i, total = 0;

  for (i = 0; i < PRIME; i++) {
    n = st->Table[i];
    if (n != NULL) {
      if (n->class == VAR_CLASS)
        total++;
      else if (n->class == PROCEDURE_CLASS) {
          total += n->num_of_args;
      }
    }
  }

  return total;
}

/* symbol table 디버깅용.. */
void print_symtab(symtable *st) {
  st_node_t *n;
  int i;

  fprintf(stderr, "*** SYMBOL TABLE : %s ***\n", st->name);
  for (i = 0; i < PRIME; i++) {
    n = st->Table[i];
    if (n != NULL) {
      print_entry(n, i);
    }
  }
}

void print_entry(st_node_t *n, int hash_index) {
  fprintf(stderr, "[(hash) %i\t(name) %s\t(type) %d\t(location) %d\t(index) %d]\n",
          hash_index, n->name, n->type->name, n->location, n->index);

  if (n->class == FUNCTION_CLASS) {
    fprintf(stderr, "### Arg List Types for %s ###\n", n->name);
    if (n->arg_type_list != NULL)
      print_arg_list(n->arg_type_list);
    else
      fprintf(stderr, "problem!!\n");
  }

  if (n->next != NULL)
    print_entry(n->next, hash_index);
}
