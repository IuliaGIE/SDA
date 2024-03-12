#include <stdio.h>
int putere(int a, int n) {
    if(n == 0) return 1;
    if(n == 1) return a;
    if(n % 2 == 0)
        return putere(a, n / 2) * putere(a, n / 2);
    else
        return a * putere(a, n / 2) * putere(a, n / 2);
}
int main() {
  int a, n;
  scanf("%d %d", &a, &n);
  printf("%d\n", putere(a, n));
  return 0;
}