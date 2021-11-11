//
// Created by skyle on 10/11/2021.
//

#ifndef LAB04_LAB04EX03FN_H
#define LAB04_LAB04EX03FN_H



#define MAX_NAME_SIZE 30


#include <stdlib.h>
#include <stdio.h>

struct athlete_s{

    char name[MAX_NAME_SIZE + 1];
    int id;
    int nlaps;
    float* laps;
    float bestLap;

} typedef athlete_t;


void checkargc(int argc, int expected, char* argv0); // Checks if the number of expected arguments is equal to argc
void freeMemAth(athlete_t**, int athPtr_n);
void avglap(athlete_t*, int athNum, float *bestAvg, int *bestAvgIndex);


#endif //LAB04_LAB04EX03FN_H
