#include "sem.h"
#include "lib.h"
#include <sys/sem.h>
#include "stdlib.h"
#include <stdio.h>

int GenerateKey(char *p_keyPath, char program){
    int key;
    if((key = ftok(p_keyPath, program)) < 0){
        perror("Error in ftok");
        exit(ERROR);
    }
    return key;
}

SemSet* InitSemSet(int semCount, char *p_keyPath, char program){
    SemSet *p_semSet = malloc(sizeof(SemSet));
    p_semSet->count = semCount;
    int key = GenerateKey(p_keyPath, program);
    // Get Semaphoren
    if ((p_semSet->id = semget(key, semCount, IPC_CREAT|0666))<0){
        perror("Error in semget");
        exit(ERROR);
    }
    // Activate Semaphoren
    for(int i = 0; i < semCount; i++){
        if(semctl(p_semSet->id, i, SETVAL, 1)<0){
            perror("Error in semctl");
            exit(ERROR);
        }
    }
    return p_semSet;
}

void P(SemSet *p_semSet, int indices[], int indiceCount){
    struct sembuf semaphore[indiceCount];

    for(int i = 0; i < indiceCount; i++){
        semaphore[i].sem_flg=~(IPC_NOWAIT|SEM_UNDO);
        semaphore[i].sem_op=-1;
        semaphore[i].sem_num=indices[i];
        if(semop(p_semSet->id,&semaphore,indiceCount)){
            perror("Error in semop P()");
            exit(ERROR);
        }
    }
}

void V(SemSet *p_semSet, int indices[], int indiceCount){
    struct sembuf semaphore[indiceCount];

    for(int i = 0; i < indiceCount; i++){
        semaphore[i].sem_flg=~(IPC_NOWAIT|SEM_UNDO);
        semaphore[i].sem_op=1;
        semaphore[i].sem_num=indices[i];
        if(semop(p_semSet->id,&semaphore,indiceCount)){
            perror("Error in semop V()");
            exit(ERROR);
        }
    }
}

void DisposeSemSet(SemSet *p_semSet){
    free(p_semSet);
}