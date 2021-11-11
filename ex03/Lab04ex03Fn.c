//
// Created by skyle on 10/11/2021.
//

#include "Lab04ex03Fn.h"



void checkargc(int argc, int expected, char* argv0){

    if(argc != expected){
        fprintf(stderr,"%s: Error reading file, wrong number of arguments (%d)", argv0, argc);
        exit(EXIT_FAILURE);
    }
}

void freeMemAth(athlete_t** athlete, int athPtr_n){

    if(athlete != NULL){
        for(int i = 0; i < athPtr_n; i++){
            for(int j = athlete[i]->nlaps; j >= 0 ; j--){
                free(&athlete[i]->laps[j]);
            }
            free(&athlete[i]);
        }
        free(athlete);
    }

}


void avglap(athlete_t* athlete, int athNum, float *bestAvg, int *bestAvgIndex){

    *bestAvg = 100000;

    for(int i = 0; i < athNum; i++){
        athlete[i].bestLap = 0;
        for(int j = 0; j < athlete[i].nlaps; j++){
            athlete[i].bestLap += athlete[i].laps[j];
        }
        athlete[i].bestLap /= (float) athlete[i].nlaps;
        if(athlete[i].bestLap < *bestAvg){
            *bestAvg = athlete[i].bestLap;
            *bestAvgIndex = i;
        }
    }

}