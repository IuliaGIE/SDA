#include <stdio.h>
int r(int n){
    if(n == 1 || n == 2 || n == 3)
        return 1;
    else
        return r(n - 1) + r(n - 2) + r(n -3); // 
}
int main()
{
    int n, nr;
    scanf("%d", &n);
    nr = r(n);
    printf("%d\n", nr);
    return 0;
}