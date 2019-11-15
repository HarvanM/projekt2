#include <stdio.h>
#include <stdlib.h>
#include <math.h>


unsigned long int factorial(unsigned long int number);

long double diode(double u0, double r, long double eps);

int main(int argc, char *argv[]){
    printf("%0.10Lf", diode(5, 10e3, 1e-10));
}

unsigned long int factorial(unsigned long int number){
    if (number == 0){
        return 1;
    }
    for (int i = number - 1; i > 0; i--){
        number = number * i;
    }
    return number;
}

long double diode(double u0, double r, long double eps){
    const double I0 = pow(10, -12);
    const double UT = 0.0258563;
    long double ID = 0;
    long double ID_last = 0;
    long double delta = 1000;
    long double interval[2] = {0, u0};
    long double stred = 0;
    for (int i = 0; delta > eps; i++){
        stred = ((interval[0] + interval[1]) / 2);
        ID = I0 * (exp(stred/UT) - 1) - ((u0 - stred) / r);
        if (ID > 0){
            interval[1] = stred;
            if ((ID - ID_last) > 0){
                delta = ID - ID_last;
            }
            else
            {
                delta = ID_last - ID;
            }
            ID_last = ID;
        }
        if (ID < 0){
            interval[0] = stred;
            if ((ID - ID_last) > 0){
                delta = ID - ID_last;
            }
            else
            {
                delta = ID_last - ID;
            }
            ID_last = ID;
        }
        if (ID == 0){
            
            return stred;
        }
    }
    return stred;
}