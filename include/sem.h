#ifndef SEM_H
#define SEM_H

/*Set of semaphores*/
typedef struct{
    int id;
    int count;
} SemSet;

/*Allocate set of semaphores with size (semCount) and generate key at path (p_keyPath) with program id (program)*/
SemSet* InitSemSet(int semCount, char *p_keyPath, char program);

/*P Operation on semaphores with index (indices)*/
void P(SemSet *p_semSet, int indices[], int indiceCount);

/*V Operation on semaphores with index (indices)*/
void V(SemSet *p_semSet, int indices[], int indiceCount);

/*Deallocate SemSet*/
void DisposeSemSet(SemSet *p_semSet);

#endif