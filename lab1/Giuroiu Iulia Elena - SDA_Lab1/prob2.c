#include <stdio.h>
int recursiv(int v[], int n, int i) {
  if (i < n) {
    return v[i] * recursiv(v, n, i + 1);
  }
    return 1;
}

int main() {
  int v[100], n, i;
  scanf("%d", &n);
  for (i = 0; i < n; i++) 
        scanf("%d", &v[i]);
  printf("%d\n", recursiv(v, n, 0));
  return 0;
}