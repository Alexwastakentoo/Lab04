#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_WORD_SIZE 20 + 2 // +2 due to \n and \0 chars
#define MAX_LINE_SIZE 100 + 2
#define MAX_WORD_NUM 100

#define ERR_INVALID_ARG -1
#define ERR_READ_FILE   -2
#define ERR_MALLOC_FAIL -3

typedef struct {
    char word[MAX_WORD_SIZE];
    int occurrences;
} keyword_t;

//int myStrcmp(char * string1, char * string2);
void addNewline(char ** string, char ** string_n/*, char ** argv*/);
void freeAllMem(char ** ptr1, char ** ptr2, keyword_t ** ptr3, int ptr3_elements);


int main(int argc, char** argv) {

    keyword_t* keyword = NULL;
    char* token = NULL, *token_n = NULL;
    char linebufferW[MAX_WORD_SIZE], linebufferL[MAX_LINE_SIZE];
    int wordsStored = 0;


    if(argc != 3){
        fprintf(stderr, "%s: Error invalid number of arguments (%d instead of 3)",argv[0], argc);
        return ERR_INVALID_ARG;
    }


    FILE *listFile = fopen(argv[1], "r");

   fscanf(listFile, "%d\n", &wordsStored);

    keyword = (keyword_t *) malloc(wordsStored * sizeof(keyword_t));
    if(keyword == NULL){
        fprintf(stderr,"%s: Error allocating memory", argv[0]);
        free(keyword);
        keyword = NULL;
        return ERR_MALLOC_FAIL;
    }

    int i = 0;
    while(fgets(linebufferW, MAX_WORD_SIZE, listFile) != NULL){

        strcpy(keyword[i].word, linebufferW);

        wordsStored++;
        i++;
    }

    for(int j = 0; j < wordsStored; j++){
        keyword[j].occurrences = 0;
    }

    fprintf(stdout,"\n");
    for(int j = 0; j < wordsStored; j++){
        fprintf(stdout,"list[%d]: %s at address %p\n",j , keyword[j].word, &keyword[j]);
    }

    fclose(listFile);



    FILE *textFile = fopen(argv[2], "r");
    // read file line by line and use strtok to look for keywords saved in list

    token_n = malloc(MAX_WORD_SIZE * sizeof(char));
    if(token_n == NULL){
        fprintf(stderr, "%s: Error allocating memory", argv[0]);
        freeAllMem(&token, &token_n, &keyword, wordsStored);
        return ERR_MALLOC_FAIL;
    }

    while(fgets(linebufferL, MAX_LINE_SIZE, textFile)){

        token = strtok(linebufferL, " ");
        addNewline(&token, &token_n/*, argv*/);
        if(token_n == NULL){
            freeAllMem(&token, &token_n, &keyword, wordsStored);
            return ERR_MALLOC_FAIL;
        }

        while(token != NULL){
            for(int j = 0; j < wordsStored; j++) {
                // printf("list[j]: %p\n", list[j]);
                // printf("token: %s, list[j]: %s\n", token, list[j]);
                if (stricmp(token, keyword[j].word) == 0 || stricmp(token_n, keyword[j].word) == 0) {
                    keyword[j].occurrences++;
                    //  printf("found[%d]: %d\n", j, found[j]);
                }
            }
            token = strtok(NULL, " ");
            addNewline(&token, &token_n/*, argv*/);
            if(token_n == NULL){
                freeAllMem(&token, &token_n, &keyword, wordsStored);
                return ERR_MALLOC_FAIL;
            }
        }
    }
    fclose(textFile);

    printf("\n\n\n");

    for(int k = 0; k < wordsStored; k++){
        printf("%s was found %d times.\n", keyword[k].word, keyword[k].occurrences);
    }

    freeAllMem(&token, &token_n, &keyword, wordsStored);
    return 0;
}

/*
int myStrcmp(char* string1, char* string2){ // case insensitive strncmp returns 0 if equal, >0 if string1>string2, <0 otherwise
    int result = 0;

    // convert everything to lowercase then compare
    // check that string1[i] is an uppercase letter
    for(int i = 0; (string1[i] != '\0') && (isupper(string1[i]) != 0) && (string1[i]>= 65 && string1[i] <= 90); i++){
        string1[i] += 32; // uppercase to lower case "distance" is 32 in ascii
    }

    // do the same for string2, to save time we can also compare in this loop
    for(int i = 0; (string2[i] != '\0') && (isupper(string2[i]) != 0) && (string2[i]>= 65 && string2[i] <= 90); i++){
        string2[i] += 32; // uppercase to lower case "distance" is 32 in ascii
        result = string1[i] - string2[i]; // if all char are equal this will be == 0
    }

    return result;
}*/

void addNewline(char ** string, char ** string_n/*, char ** argv*/){
    /* alloc new memory to string_n only if needed
        *string_n = (char* ) realloc(*string_n, strlen(*string) * sizeof(char));
        if(*string_n == NULL){
            fprintf(stderr,"%s: Error reallocating memory", argv[0]);
            return; // go back to main to free the memory
        }
    */

    if(*string != NULL) {
        strcpy(*string_n, *string);
        strcat(*string_n, "\n");
    }
}

void freeAllMem(char** ptr1, char** ptr2, keyword_t ** ptr3, int ptr3_elements){
    if(*ptr1 != NULL){
        free(*ptr1);
        *ptr1 = NULL;
    }

    if(*ptr2 != NULL){
        free(*ptr2);
        *ptr2 = NULL;
    }

    if(*ptr3 != NULL){
        for(int i = 0; i < ptr3_elements; i++){
            free(ptr3[i]);
            ptr3[i] = NULL;
        }
    }
}