#ifndef STCK1_C
#define STCK1_C 

#include "boolean.h"
#include "STCK1.h"
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

void CreateEmptyStack(Stack *S)
{
    Top(*S)=Nil; // instruksi membuat stack kosong …;
}

int IsEmptyStack(Stack S)
{
    return(Top(S)==Nil); // instruksi cek stack …;
}

address Alokasi(infotype x)
{
    address P;
    P=(Node*)malloc(sizeof (Node));
        if(P!=Nil)
        {
            Next(P)=Nil; Info(P)=x;
        }
    return(P);
}

void Dealokasi(address P)
{
    free(P);
}

void Push(Stack *S,address P)
{
    Next(P)=Top(*S);
    Top(*S)=P; // push node ke stack …;
}

void PushE(Stack *S,infotype x)
{
    address P=Alokasi(x); // push element ke stack …;
    Push(S,P); // (panggil) fungsi Push
    printf ("Pemasukan Data Berhasil \n\n");
}

void Pop(Stack *S, address *addr)
{

    if (!IsEmptyStack(*S)) // check stack kosong
    {
       address P=Top(*S);
       if(Next(Top(*S))==Nil) Top(*S)=Nil;
            else
            {
                Top(*S)=Next(Top(*S));
            }
                printf("Data Yang Akan Dihapus : %c",Info(P));
    }
    else
        printf("Data Kosong ");
        getch();
}

void PrintInfo (Stack *S)
{ 
    address P=Top(*S);
    if(!IsEmptyStack(*S))
    {
        do
        {
            printf("%c\t",Info(P));
            P=Next(P);
        }while(P!=Nil);
        printf("\n ^\n"); printf(" |\n"); printf("Data Masuk\n"); printf("Yang Terakhir\n");
    }
    else
    printf("Data Kosong \n\n\n");
    getch();
}
#endif
