#include <stdio.h>
#include <math.h>

int main(){
    long int n, x, i, sum = 0;;
    if(scanf("%ld", &n) == 1){
        for(i = 1; i <= n; i++){
            if(scanf("%ld", &x) == 1){
                sum += (long int)pow((double)x, (double)2);
            }
        }

        printf("%ld", sum);
    }
    return 0;
}
