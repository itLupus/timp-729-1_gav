#include <stdio.h>

int main(void){
double a, b, sum;
int temp = scanf("%lf %lf", &a, &b);
if(temp == 2){
sum = a + b;
printf("%lf", sum);
}
else{
    return 1;
}
return 0;
}
