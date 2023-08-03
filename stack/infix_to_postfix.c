// convert infix expression to postfix notation
#include <stdio.h>
#include <string.h>

#define STACKSIZE 20
typedef struct {
    int topindex;
    int members[STACKSIZE];
} stackrec;
stackrec stack = {.topindex = -1};

int isEmpty(stackrec* ptr) { return ((ptr->topindex) == -1 ? 1 : 0); }

// top of stack element
int tos(stackrec* ptr) {
    if (!isEmpty(ptr)) {
        return (ptr->members[ptr->topindex]);
    }
    return 0;
}

void push(stackrec* ptr, int topelement) {
    if (!(ptr->topindex == (STACKSIZE - 1))) {
        ptr->topindex += 1;
        ptr->members[ptr->topindex] = topelement;
    }
}

int pop(stackrec* ptr) {
    if (!isEmpty(ptr)) {
        return (ptr->members[ptr->topindex--]);
    }
    return 0;
}

int is_operand(const char ch) {
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') ? 1 : 0);
}

int precedence(const char ch) {
    switch (ch) {
        case '+':
        case '-': return 1;
        case '*':
        case '/':
        case '%': return 2;
    }
    return 0;
}

void inpo(char expr[]) {
    long i, j;
    for (i = 0, j = -1; i < strlen(expr); i++) {
        if (is_operand(expr[i])) {
            expr[++j] = expr[i];
        } else if (expr[i] == '(') {
            push(&stack, expr[i]);
        } else if (expr[i] == ')') {
            while (!isEmpty(&stack) && tos(&stack) != '(') {
                expr[++j] = pop(&stack);
            }
            // discard the opening parenthesis as well
            pop(&stack);
        } else {
            while (!isEmpty(&stack) &&
                   precedence(tos(&stack)) >= precedence(expr[i])) {
                expr[++j] = pop(&stack);
            }
            push(&stack, expr[i]);
        }
    }
    // append the remaining characters to the array
    while (!isEmpty(&stack)) {
        expr[++j] = pop(&stack);
    }
    expr[++j] = '\0';
}

int main(void) {
    char expression[STACKSIZE] = "A*(B*C)+(D*E)/F";
    inpo(expression);
    printf("After postfix conversion: %s.\n", expression);
    return 0;
}
