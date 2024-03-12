#include <stdio.h>
int recursiv(int v[], int i, int n, int nr) {
  if (i < n) {
    if (v[i] >= nr)
      return 1 + recursiv(v, i + 1, n, nr);
    else
      return recursiv(v, i + 1, n, nr);
  }
  return 0;
}
int main() {
  int v[100], n, nr, i;
  scanf("%d%d", &n, &nr);
  for (i = 0; i < n; i++) 
        scanf("%d", &v[i]);
  printf("%d\n", recursiv(v, 0, n, nr));
  return 0;
}