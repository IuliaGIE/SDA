#include <stdio.h>
#include <math.h>
int radacina_k(double nr, int k){
    double left = 0, right = nr, error = 0.001;
    double mij = (left + right) / 2;
    double poz = 1;
    while(fabs(poz - mij) > error){
        poz = mij;
        mij = pow(mij, k);
        if(mij > nr)
            right = poz;
        else 
            left = poz;
        mij = (left + right) / 2;
    }
    return mij;
}
int main()
{
    double nr = 27;
    int k = 3;
    double rez = radacina_k(nr, k);
    printf("Radicalul de ordin %d al lui %.3f este %.3f\n", k, nr, rez);
    return 0;
}