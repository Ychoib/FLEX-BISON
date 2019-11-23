#include <stdio.h>
#include <stdlib.h>
#include "arg_list.h"
/* Argument Type List : symbol table 의 타입을 linked list 로 연결 */

void arg_destroy(arg_elem *head) {
  if (head == NULL)
    return;

  fprintf(stderr, "destroying arg_head\n");

  arg_elem *curr, *tmp;

  curr = head->next;
  head->next = NULL;

  while (curr != NULL) {
    tmp = curr->next;
    free(curr);
    curr = tmp;
  }
}

/* list 끝에 노드 추가, (즉 tail이 삽입지점) */
arg_elem *arg_append(arg_elem *head, symtab_type type) {
  arg_elem *tmp;

  if (head == NULL) {
    if ((head = (arg_elem *) malloc(sizeof(arg_elem))) == NULL) {
      printf("could not malloc\n");
      exit(1);
    }

    head->type = type;
    head->next = head;
  }
  else {
    tmp = head;

    while (tmp->next != head)
      tmp = tmp->next;

    if ((tmp->next = (arg_elem *)malloc(sizeof(arg_elem))) == NULL) {
      printf("coul not malloc\n");
      exit(1);
    }

    tmp = tmp->next;
    tmp->type = type;
    tmp->next = head;
  }

  return head;
}

/* list의 노드 수를 return
   (function,procedure semantic 체크에 쓰일 예정..) */
int arg_list_size(arg_elem *head) {
  arg_elem *data = head;
  int size = 0;

  if (data != NULL) {
    do {
      size++;

      data = data->next;
    }
    while (data != head);
  }
  else
    fprintf(stderr, "print_arg_list: data is null\n");

  return size;
}

/* 두개의 argument list에 차이가 없으면 0 return 
   (function,procedure semantic 체크에 쓰일 예정..) */
int arg_list_compare(arg_elem *one, arg_elem *two) {
  arg_elem *data_one = one, *data_two = two;
  int diff = 0;

  if (one == NULL || two == NULL)
    perror("arg_list_compare: null comparison"); //둘중 하나라도 null 일시 에러출력

  do {
    if (data_one->type != data_two->type)
      diff++;

    data_one = data_one->next;
    data_two = data_two->next;
  }
  while (data_one != one);

  return diff;
}

/* for debugging */
void print_arg_list(arg_elem *head) {
  arg_elem *data = head;

  if (data != NULL) {
    do {
      fprintf(stderr, "arg_list, type: %d\n", data->type);

      data = data->next;
    }
    while (data != head);
  }
  else
    fprintf(stderr, "print_arg_list: data is null\n");

}
