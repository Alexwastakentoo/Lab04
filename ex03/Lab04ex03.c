//
// Created by skyle on 10/11/2021.
//

#include "Lab04ex03Fn.h"
#include <string.h>


#define ERR_ATH_NUM -1;
#define ERR_MALLOC -2;

#define MAX_CMD_LEN 6;

#define DEBUG 1;

int main(int argc, char** argv){

    athlete_t *athlete;
    int athCount = 0, bestAvgIndex;
    float bestAvg;

    char tempName[MAX_NAME_SIZE + 1], cmd[MAX_NAME_SIZE + 1];
    char stop = 0;

    checkargc(argc, 2, argv[0]);

    FILE* inputFile = fopen(argv[1], "r");

    fscanf(inputFile, "%d\n", &athCount);
    if(athCount <= 0){
        fprintf(stderr, "%s: Invalid number of athletes (%d)\n", argv[0], athCount);
        return ERR_ATH_NUM;
    }

    athlete = malloc(athCount * sizeof(athlete_t));
    if(athlete == NULL){
        fprintf(stderr,"%s: Error allocating memory\n", argv[0]);
        freeMemAth(&athlete, athCount);
        return ERR_MALLOC;
    }


    for(int i = 0; i < athCount; i++){
        fscanf(inputFile, "%s %d %d\n", athlete[i].name, &athlete[i].id, &athlete[i].nlaps);
        athlete[i].laps = NULL;

#ifdef DEBUG
        printf("athlete[%d] | name: %s | id: %d| nlaps: %d \n", i, athlete[i].name, athlete[i].id, athlete[i].nlaps);
        fflush(stdout);
#endif

        athlete[i].laps = realloc(athlete[i].laps, athlete[i].nlaps * sizeof(float));
        if(athlete[i].laps == NULL){
            fprintf(stderr,"%s: Error allocating memory\n", argv[0]);
            freeMemAth(&athlete, athCount);
            return ERR_MALLOC;
        }

        printf("\n");

        for(int j = 0; j < athlete[i].nlaps; j++){

            fscanf(inputFile, "%f", &athlete[i].laps[j]);

#ifdef DEBUG
            printf("athlete[%d].laps[%d] : %f\n", i, j, athlete[i].laps[j]);
            fflush(stdout);
#endif

        }

        athlete[i].laps = realloc(athlete[i].laps, athlete[i].nlaps * sizeof(float));
    }

    fclose(inputFile);

    avglap(athlete, athCount, &bestAvg, &bestAvgIndex);

#ifdef DEBUG
    printf("\n");
    for(int i = 0; i < athCount; i++){
        printf("athlete[%d].bestLap : %f\n", i, athlete[i].bestLap);
    }

    printf("\n best avg lap by athlete[%d] with avg lap : %f\n", bestAvgIndex, bestAvg);
#endif

    // Console interaction

    while(stop != 1){
        printf("Input a command or help: ");
        scanf("%6s", cmd);

        if(stricmp(cmd, "Help") == 0){

            printf("\nCommand list:\n\n List: the program prints-out the number of athletes, their names, identifiers, and number of laps "
                   "performed.\n\n Detail 'Name': given an athlete name, the program prints-out his/her identifier, and all lap times."
                   "\n\n Best: the program prints-out the name, identifier, all lap times and the average lap time for the athlete "
                   "whose average lap time is smaller. \n\n Stop: end the program. \n");

        } else if(stricmp(cmd, "List") == 0){
            printf("Number of athletes: %d\n", athCount);
            for(int i = 0; i < athCount; i++){
                printf("Name: %s | id: %d | Number of laps: %d\n", athlete[i].name, athlete[i].id, athlete[i].nlaps);
            }

        } else if(stricmp(cmd, "Detail") == 0){
            scanf("%s", tempName);
            for(int i = 0; i < athCount; i++){
                if(stricmp(tempName, athlete[i].name) == 0){
                    printf("id: %d\n", athlete[i].id);
                    for(int j = 0; j < athlete[i].nlaps; j++) {
                        printf("lap[%d]: %f\n", j, athlete[i].laps[j]);
                    }
                    i = athCount;
                }
            }

        } else if(stricmp(cmd, "Best") == 0){
            printf("Best avg lap by athlete[%d] Name: %s with avg lap : %f\n", bestAvgIndex, athlete[bestAvgIndex].name, bestAvg);

        } else if(stricmp(cmd, "Stop") == 0){
            stop = 1;
        } else{
            printf("Invalid command, type Help for the command list.\n");
        }
    }



    return 0;
}
