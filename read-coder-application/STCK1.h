#ifndef STCK1_H
#define STCK1_H 

#include<stdlib.h>
#include<stdio.h>
#define Nil NULL
#define Info(P) (P)->Info
#define Next(P) (P)->Next
#define Top(S) (S).Top

typedef char infotype;
typedef struct ref *address;
typedef struct ref {
infotype Info;
address Next;
} Node;

typedef struct {
address Top;
}Stack;

void CreateEmptyStack(Stack *S);
int IsEmpty(Stack S);
address Alokasi(infotype x);
void Dealokasi(address P);
void Push(Stack *S,address P);
void PushE(Stack *S,infotype x);
void Pop(Stack *S, address *P);
void PrintInfo (Stack *S);			   

#endif
