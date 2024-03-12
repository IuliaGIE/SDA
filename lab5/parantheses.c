#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LEN 256

typedef char Item;
#include "Stack.h"

int isBalanced(const char *str, int length){
  Stack *stack = createStack(length); // Cream stiva cu capacitatea data de lungimea sirului
  int i;
  char ch;
  for (i = 0; i < length; i++) {
    ch = str[i];
    if (ch == '(' || ch == '{' || ch == '[') {
      push(stack, ch); // Adaugam paranteza deschisa pe stiva
    }
    else if (ch == ')' || ch == '}' || ch == ']') {
      if (isEmpty(stack)) {
        freeStack(stack); // Eliberam memoria folosita de stiva
        return 0; // Nu exista o paranteza deschisa corespunzatoare, sirul nu este balansat
      }
      char top = pop(stack); // Scoatem paranteza deschisa de pe varful stivei
      if ((ch == ')' && top != '(') || (ch == '}' && top != '{') || (ch == ']' && top != '[')) {
        freeStack(stack); // Eliberam memoria folosita de stiva
        return 0; // Paranteza inchisa nu are o paranteza deschisa corespunzatoare, sirul nu este balansat
      }
    }
  }
  int ret = isEmpty(stack); // Verificam daca stiva este goala, caz in care sirul este balansat
  freeStack(stack); // Eliberam memoria folosita de stiva
  return ret;
}

int main(){
    int len;
    char buffer[MAX_INPUT_LEN];
    FILE* inputFile = fopen("input-parantheses.txt","r");
    if(inputFile == NULL) return 1;


    while(fgets(buffer, MAX_INPUT_LEN, inputFile) != NULL){
      buffer[strcspn(buffer, "\r\n")] = 0;
      len = strlen(buffer);
      if(len == 0) break;

      if(isBalanced(buffer, len))
        printf("%s ---> is balanced.\n", buffer);
      else
        printf("%s ---> not balanced.\n", buffer);
    }

    fclose(inputFile);

    return 0;
}
