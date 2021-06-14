#include <stdio.h>
#include <math.h>

int main(){
    double x, y, power;
    if(scanf("%lf %lf", &x, &y) == 2){
        power = pow(x, y);
        printf("%lf\n", power);
    }
    else{
        //smth about error
    }
    return 0;
}
