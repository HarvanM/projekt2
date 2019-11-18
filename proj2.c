/**
 * @name Projekt 2 - Iteracne vypocty
 * @author Mário Harvan 
 * login: xharva03
 * version: V1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

double diodeEquation(double *u0, double *r, double intervalLower, double intervalHigher);

double diode(double u0, double r, double eps, double result, double *intervalLower, double *intervalHigher);

void printResults(double *u0, double *r, double Up);

int main(int argc, char *argv[]){
    bool wrongInput = false;
    double u0 = 0;
    double r = 0;
    double eps = 0;
    //check for correct input
    if (argc != 4){
        wrongInput = true;
        return 0;
    }
    //if input is correct, save it to variabiles
    if (wrongInput == false){
        u0 = atof(argv[1]);
        r = atof(argv[2]);
        eps = atof(argv[3]);
        if (r == 0 || eps == 0){
            wrongInput = true;
        }
    }
    //print error if input is wrong
    if (wrongInput == true){
        fprintf(stderr, "Wrong input");
        return 0;
    }
    //set default values for interval
    double intervalLower = 0;
    double intervalHigher = u0;
    //calculate and print results
    printResults(&u0, &r, diode(u0, r, eps, diodeEquation(&u0, &r, intervalLower, intervalHigher), &intervalLower, &intervalHigher));
    return 1;
}

double diodeEquation(double *u0, double *r, double intervalLower, double intervalHigher){
    //function calculates voltage on diode from input parameters
    //u0 = pointer to voltage on power source
    //r = pointer to resistatnce R
    //intervalLower= lower value in interval, where we want to calculate
    //intervalHigher = higher value in interval, where we want to calculate
    //returns voltae on diode from input parameters
    
    //constants
    const double I0 = pow(10, -12);
    const double UT = 0.0258563;
    //calculates average from interval
    double average = (intervalLower + intervalHigher) / 2;
    return (I0 * (exp(average/UT) - 1) - ((*u0 - average) / *r));
}

double diode(double u0, double r, double eps, double result, double *intervalLower, double *intervalHigher){
    //functions recursively calculates voltage on diode with inputed precision 
    //u0= voltage on power source
    //r= resistance R
    //eps= epsilon, or precision with which we want to calculate
    //result= result from last called function
    //intervalLower= lower value of interval in which we are calculating
    //intervalHigher= higher value of interval in which we are calculating 
    
    //if we found result with demanded precision, return it
    if ((*intervalHigher - *intervalLower) < eps || result == 0){
        return (*intervalLower + *intervalHigher) / 2;
    }
    //if last result was higher than 0
    if (result > 0){
        //save last result to higher value of interval
        *intervalHigher = (*intervalLower + *intervalHigher) / 2;
    }
    //if last result was lower than 0
    if (result < 0){
        //save last result to lower value of interval
        *intervalLower = (*intervalLower + *intervalHigher) / 2;
    }
    //return same function with new result
    return diode(u0, r, eps, diodeEquation(&u0, &r, *intervalLower, *intervalHigher), intervalLower, intervalHigher);
}

void printResults(double *u0, double *r, double Up){
    //function calculates current from voltage on diode and prints results
    //u0 = pointer to voltage on power source
    //r = pointer to resistatnce R
    //Up = voltage on diode

    //calculate current in diode
    double Ip = (*u0 - Up) / *r;
    //print voltage and current on diode
    printf("Up=%g V\nIp=%g A\n", Up, Ip);
}