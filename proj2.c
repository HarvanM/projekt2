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

bool checkForInput(int argc, char *argv[], double *u0, double *r, double *eps);

double diodeEquation(double *u0, double *r, double *up);

double diode(double u0, double r, double eps);

void printResults(double *u0, double *r, double up);

int main(int argc, char *argv[]){
    double u0 = 0;
    double r = 0;
    double eps = 0;
    //check for correct input
    if (checkForInput(argc, argv, &u0, &r, &eps) == true){
        //calculate and print results
        printResults(&u0, &r, diode(u0, r, eps));
        return 1;
    }
    return 0;
}

bool checkForInput(int argc, char *argv[], double *u0, double *r, double *eps){
    //function checks if all inputs are correct, then writes them to variabiles
    //argc = number of passing arguments
    //argv = array of passing arguments
    //u0 = pointer to variabile where we want to store U0
    //r = pointer to variabile where we want to store R
    //eps = pointer to variabile where we want to store eps
    //function returns true when all inputs are correct, else it returns false
    
    bool wrongInput = false;
    if (argc != 4){
        wrongInput = true;
    }
    //if input is correct, save it to variabiles
    if (wrongInput == false){
        char *err;
        *u0 = strtod(argv[1], &err);
        if (*err != '\0'){wrongInput = true;}
        *r = strtod(argv[2], &err);
        if (*err != '\0'){wrongInput = true;}
        *eps = strtod(argv[3], &err);
        if (*err != '\0'){wrongInput = true;}
        if (r == 0 || eps == 0){wrongInput = true;}
    }
    //print error if input is wrong
    if (wrongInput == true){
        fprintf(stderr, "Wrong input\n");
        return false;
    }
    else {
        return true;
    }
}

double diodeEquation(double *u0, double *r, double *up){
    //function calculates voltage on diode from input parameters
    //u0 = pointer to voltage on power source
    //r = pointer to resistatnce R
    //up = pointer to voltage up
    //returns voltae on diode from input parameters
    
    //constants
    const double I0 = pow(10, -12);
    const double UT = 0.0258563;
    //return result of equation
    return (I0 * (exp(*up/UT) - 1) - ((*u0 - *up) / *r));
}

double diode(double u0, double r, double eps){
    //functions calculates voltage on diode with inputed precision 
    //u0= voltage on power source
    //r= resistance R
    //eps= epsilon, or precision with which we want to calculate
    
    double intervalLower = 0;
    double intervalHigher = u0;
    double result = 0;
    double average = 0;
    //calculate until desired precision is achieved
    while((intervalHigher - intervalLower) >= eps){
        average = (intervalLower + intervalHigher) / 2;
        result = diodeEquation(&u0, &r, &average);
        //if last result was higher than 0
        if (result > 0){
            //save last result to higher value of interval
            intervalHigher = average;
        }
        //if last result was lower than 0
        if (result < 0){
            //save last result to lower value of interval
            intervalLower = average;
        }
    }
    //return voltage after calculations are done
    return average;
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