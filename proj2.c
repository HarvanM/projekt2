/**
 * @name Projekt 2 - Iteracne vypocty
 * @author Mário Harvan 
 * login: xharva03
 * version: V1.2
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

#define I0 1e-12
#define UT 0.0258563

bool checkForInput(int argc, char *argv[], double *u0, double *r, double *eps);

double diodeEquation(double *u0, double *r, double *up);

double diode(double u0, double r, double eps);

void printResults(double up);

int main(int argc, char *argv[]){
    double u0 = 0;
    double r = 0;
    double eps = 0;
    //check for correct input
    if (checkForInput(argc, argv, &u0, &r, &eps) == true){
        //calculate and print results
        printResults(diode(u0, r, eps));
        return 1;
    }
    //if input is not correct, print error
    else {
        fprintf(stderr, "error: invalid arguments\n");
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
    
    if (argc != 4){
        return false;
    }
    //if input is correct, save it to variabiles
    char *err;
    *u0 = strtod(argv[1], &err);
    if (*err != '\0') return false;
    *r = strtod(argv[2], &err);
    if (*err != '\0') return false;
    *eps = strtod(argv[3], &err);
    if (*err != '\0') return false;
    //we cannot devide by zero and voltage cant be lower than zero
    if (*r == 0 || *u0 < 0) return false;
    
    return true;
}

double diodeEquation(double *u0, double *r, double *up){
    //function calculates voltage on diode from input parameters
    //u0 = pointer to voltage on power source
    //r = pointer to resistatnce R
    //up = pointer to voltage up
    //returns voltae on diode from input parameters
    
    //return result of equation
    return (I0 * (exp(*up/UT) - 1) - ((*u0 - *up) / *r));
}

double diode(double u0, double r, double eps){
    //functions calculates voltage on diode with inputed precision 
    //u0= voltage on power source
    //r= resistance R
    //eps= epsilon, or precision with which we want to calculate
    //function returns voltage on diode
    
    double intervalLower = 0;
    double intervalHigher = u0;
    double result = 0;
    double average = 0;
    double last_average = 0;
    //calculate until desired precision is achieved
    do {
        average = (intervalLower + intervalHigher) / 2;
        result = diodeEquation(&u0, &r, &average);
        //if result was higher than 0
        if (result > 0){
            //save result to higher value of interval
            intervalHigher = average;
        }
        //if result was lower than 0
        if (result < 0){
            //save result to lower value of interval
            intervalLower = average;
        }
        //if new average is same as last average, return average
        if (average-last_average == 0 || average-last_average == atof("inf")) return average;
        //set new average
        last_average = average;
    } while((intervalHigher - intervalLower) >= eps);
    //return voltage after calculations are done
    return average;
}

void printResults(double Up){
    //function calculates current from voltage on diode and prints results
    //Up = voltage on diode

    //calculate current in diode
    double Ip = I0*(exp(Up/UT) - 1);
    //print voltage and current on diode
    printf("Up=%g V\nIp=%g A\n", Up, Ip);
}