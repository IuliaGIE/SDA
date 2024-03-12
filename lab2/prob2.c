#include <stdio.h>
int r(int n, int *v){
    if(n == 1 || n == 2 || n == 3){
        return 1;
    }
    else if(v[n]){
        return v[n];
    }
    else{
        v[n] = r(n - 1, v) + r(n - 2, v) + r(n - 3, v);
        return v[n];
    }
}
int main()
{
    int n, nr, v[100], i;
    scanf("%d", &n);
    for(i = 1; i <= n; i++)
        v[i] = 0;
    nr = r(n, v);
    printf("%d\n", nr);
    return 0;
}