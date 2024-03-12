#include <stdio.h>
int recursiv(int n, int k){
    if (n < k) { 
        return 1;
    }
    if(k == 0 || k == 1 || k == 2)
        return 1;
    return recursiv(n, k - 2) + recursiv(n, k - 1);
}
int main() {
  int n, k;
  scanf("%d%d",&n ,&k);
  printf("%d\n", recursiv(n, k));
  return 0;
}