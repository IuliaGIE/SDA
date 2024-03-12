#include <stdio.h>
int recursiv(int n, int k){
    if (n <= k) { 
        return 1;
    }
    int s = 0, i;
    for(i = 1; i <= k; i++)
        s += recursiv(n - i, k);
    return s;
}
int main() {
  int n, k;
  scanf("%d%d",&n ,&k);
  printf("%d\n", recursiv(n, k));
  return 0;
}