#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

double diodeEquation(double *u0, double *r, double intervalLower, double intervalHigher);

double diode(double u0, double r, double eps, double result, double *intervalLower, double *intervalHigher);

int main(int argc, char *argv[]){
    bool wrongInput = false;
    double u0 = 0;
    double r = 0;
    double eps = 0;
    int stringLength = 0;
    //check for correct input
    if (argc != 4){
        wrongInput = true;
    }
    printf("%d", stringLength);
    for (int i = 1; i <= argc; i++){
        stringLength = strlen(argv[i]);
        printf("%d", stringLength);
        for (int j = 0; j < stringLength; j++){
            if((argv[i][j] > '9' && argv[i][j] < '0') || argv[i][j] != '-' || argv[i][j] != '.'){
                wrongInput = true;
            } 
        }
    }
    if (wrongInput == false) {
        //if input is correct, save it to variabiles
        u0 = atof(argv[1]);
        r = atof(argv[2]);
        eps = atof(argv[3]);
    }
    if (wrongInput == true){
        fprintf(stderr, "Wrong Input");
        return 0;
    }
    double intervalLower = 0;
    double intervalHigher = u0;
    double Up = diode(u0, r, eps, diodeEquation(&u0, &r, intervalLower, intervalHigher), &intervalLower, &intervalHigher);
    double Ip = (u0 - Up) / r;
    printf("Up=%g V\nIp=%g A\n", Up, Ip);
}

double diodeEquation(double *u0, double *r, double intervalLower, double intervalHigher){
    const double I0 = pow(10, -12);
    const double UT = 0.0258563;
    double middle = (intervalLower + intervalHigher) / 2;
    return (I0 * (exp(middle/UT) - 1) - ((*u0 - middle) / *r));
}

double diode(double u0, double r, double eps, double result, double *intervalLower, double *intervalHigher){
    if ((*intervalHigher - *intervalLower) < eps){
        return (*intervalLower + *intervalHigher) / 2;
    }
    if (result == 0){
        return (*intervalLower + *intervalHigher) / 2;
    }
    if (result > 0){
        *intervalHigher = (*intervalLower + *intervalHigher) / 2;
    }
    if (result < 0){
        *intervalLower = (*intervalLower + *intervalHigher) / 2;
    }
    return diode(u0, r, eps, diodeEquation(&u0, &r, *intervalLower, *intervalHigher), intervalLower, intervalHigher);
}