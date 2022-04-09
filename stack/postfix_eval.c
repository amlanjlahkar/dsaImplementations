// evaluate postfix expressions using stack
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define STACKSIZE 20
typedef struct {
  int topindex;
  int members[STACKSIZE];
} stackrec;
stackrec stack = {.topindex = -1};

int isEmpty(stackrec *ptr) { return ((ptr->topindex) == -1 ? 1 : 0); }

void push(stackrec *ptr, int topelement) {
  if (!(ptr->topindex == (STACKSIZE - 1))) {
    ptr->topindex += 1;
    ptr->members[ptr->topindex] = topelement;
  }
}

int pop(stackrec *ptr) {
  if (!isEmpty(ptr))
    return (ptr->members[ptr->topindex--]);
  return 0;
}

int eval_postfix(const char expr[]) {
  for (long i = 0; i < strlen(expr); i++) {
    if (isdigit(expr[i]))
      push(&stack, expr[i] - '0');
    else {
      long operand1 = pop(&stack);
      long operand2 = pop(&stack);
      switch (expr[i]) {
      case '+':
        push(&stack, operand2 + operand1);
        break;
      case '-':
        push(&stack, operand2 - operand1);
        break;
      case '*':
        push(&stack, operand2 * operand1);
        break;
      case '/':
        push(&stack, operand2 / operand1);
        break;
      }
    }
  }
  return pop(&stack);
}

int main(void) {
  const char expression[STACKSIZE] = "19+5/4*";
  printf("Result of postfix evaluation of \"%s\" : %d\n", expression,
         eval_postfix(expression));
  return 0;
}
