#ifndef SEM_H
#define SEM_H

typedef struct{
    int id;
    int count;
} SemSet;

SemSet* InitSemSet(int semCount);

void P(SemSet *p_semSet, int indices[], int indiceCount);

void V(SemSet *p_semSet, int indices[], int indiceCount);

void DisposeSemSet(SemSet *p_semSet);

#endif