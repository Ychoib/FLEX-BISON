#ifndef TYPE_H
#define TYPE_H

#include "assert.h"

/* symbol table 의 class 정의에 사용되고, 만약 배열이면 bound 값도 저장 */

typedef enum symtab_type_e {
  ARRAY_TYPE_INT,
  ARRAY_TYPE_REAL,
  INTEGER_TYPE,
  FLOAT_TYPE,
  BOOLEAN_TYPE,
  VAR_CLASS,
  FUNCTION_CLASS,
  PROCEDURE_CLASS
} symtab_type;

typedef struct type_struct_t {
  symtab_type name;
  int lb;	//low bound
  int ub;	//upper bound
} type_struct;

#endif
