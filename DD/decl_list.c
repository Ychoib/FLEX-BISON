#include <stdio.h>
#include <stdlib.h>
#include "decl_list.h"
/* Declaration Linked list : 선언된 변수들 노드로 저장 */

void decl_destroy(decl_elem *head) {
  if (head == NULL)
    return;

  decl_elem *curr, *tmp;

  curr = head->next;
  head->next = NULL;

  while (curr != NULL) {
    tmp = curr->next;
    free(curr);
    curr = tmp;
  }
}

/* list 에 변수 이름 추가 */
decl_elem *decl_append(decl_elem *head, char *name) { 
  decl_elem *tmp;

  if (head == NULL) {	
    if ((head = (decl_elem *) malloc(sizeof(decl_elem))) == NULL) { //malloc error
      printf("could not malloc\n");
      exit(1);
    }
    head->name = name;
    head->next = head;
  }
  else {
    tmp = head;

    while (tmp->next != head)
      tmp = tmp->next;

    if ((tmp->next = (decl_elem *)malloc(sizeof(decl_elem))) == NULL) { //malloc error
      printf("coul not malloc\n");
      exit(1);
    }

    tmp = tmp->next;
    tmp->name = name;
    tmp->next = head;
  }

  return head;
}
