#include<stdio.h>
int fact(int i, int n){
    if(n == 0) 
        return 1;
    if(i < n) 
        return i * fact(i + 1, n);
}
int main(){
  int n;
  scanf("%d",&n);
  printf("%d\n", fact(1, n));
  return 0;
}