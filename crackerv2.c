#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <pthread.h>
#include <ctype.h>  
#include "split.h"

#define MAX_NAME_LEN 30
#define MAX_LINE_LEN 300
#define MAX_THREADS 4

typedef struct {
    char name[MAX_NAME_LEN];
    char temp2[MAX_LINE_LEN];
    int match;
} ThreadData;

void *threadFunc(void *arg) {
    ThreadData *data = (ThreadData *) arg;

    FILE *daten = fopen("data.txt", "r"); //Name of your Database. Name:X:X:X Format.
    char temp2[MAX_LINE_LEN];
    char name2[MAX_NAME_LEN];
    char *eof2 = fgets(temp2, MAX_LINE_LEN, daten);
    while (eof2 != NULL) {
        int lang = split(temp2, name2, ':');
        
        
        for (int i = 0; i < strlen(data->name); i++) {
            data->name[i] = tolower(data->name[i]);
        }
        for (int i = 0; i < strlen(name2); i++) {
            name2[i] = tolower(name2[i]);
        }

        data->match = strcmp(data->name, name2);
        if (data->match == 0) {
            strncpy(data->temp2, temp2, MAX_LINE_LEN - 1);
            printf("%s", temp2);
            break;
        }
        eof2 = fgets(temp2, MAX_LINE_LEN, daten);
    }
    fclose(daten);

    return NULL;
}

int main() {
    FILE *namen = fopen("targets.txt", "r"); //Names of your Targets  Name: *enter* Name: *enter* Format
    FILE *write = fopen("cracked.txt", "w");

    if (namen == NULL) {
        printf("Die Datei konnte nicht geöffnet werden.\n");
        return 1;
    }

    printf("Attack initialized\n");
    fprintf(write, "Made by svanax#3777\nMuch love\nFuck all of you!\n\n\n");

    char temp[MAX_LINE_LEN];
    char name[MAX_NAME_LEN];
    char *eof = fgets(temp, MAX_LINE_LEN, namen);
    do {
        int lang = split(temp, name, ':');
    

        pthread_t threads[MAX_THREADS];
        ThreadData threadData[MAX_THREADS];
        int numThreads = 0;

        for (int i = 0; i < MAX_THREADS; i++) {
            eof = fgets(temp, MAX_LINE_LEN, namen);
            if (eof == NULL) {
                break;
            }

            lang = split(temp, name, ':');
            strncpy(threadData[numThreads].name, name, MAX_NAME_LEN - 1);
            strncpy(threadData[numThreads].temp2, temp, MAX_LINE_LEN - 1);
            threadData[numThreads].match = -1;

            pthread_create(&threads[numThreads], NULL, threadFunc, &threadData[numThreads]);
            numThreads++;
        }

            for (int i = 0; i < numThreads; i++) {
            pthread_join(threads[i], NULL);
            if (threadData[i].match == 0) {
                fprintf(write, "%s", threadData[i].temp2);
            }
        }
    } while (eof != NULL);

    fclose(namen);
    fclose(write);

    printf("\nDone\n");
    return 0;
}