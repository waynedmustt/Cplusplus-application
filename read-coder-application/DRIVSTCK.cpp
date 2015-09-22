/*
    Nama Program : DRIVSTCK.cpp
    Deskripsi    : Driver dari ADT Stack dinamis, 
                   menghitung karakter { dan } apakah sama jumlahnya
    Author       : Muhammad Dimas Dewantara
    Tanggal      : 28 Mei 2013
*/




#include "STCK1.h"
#include "STCK1.c"
#include <stdlib.h>
#include <stdio.h>
#include<string.h>
#include <conio.h>
#define PANJANG 10000

void check(Stack *S);

main()
{
    //kamus
    char pil;
    int amount;
    Stack S;
    address P;
    char x;
    //membuat stack kosong
    CreateEmptyStack(&S);
    
    do
    {
        printf("\n\t\tMENU \n ");
        printf("\n1. Input Data");
        printf("\n2. Hitung jumlah karakter '{' dan '}'");
        printf("\n3. Tampilkan Data");
        printf("\n\nPilihan (Masukkan Angka):");
        pil=getch();
            switch(pil)
            {
                case '1' :
                FILE *f_teks;
            	char string1[PANJANG];
            	if((f_teks=fopen("coding.txt","rt"))== NULL)
            	{
            		printf("File tak dapat dibuka!\r\n");
            		exit(1);
            	}
            	 while ((fgets(string1, PANJANG, f_teks)) != NULL){
                    for (int index = 0; index <= strlen(string1); index++)
                	{
                         if (string1[index] == '}' || string1[index] == '{')
                					{
                                        x = string1[index];
                						PushE(&S,x);
                					}
                     }
                 }fclose(f_teks);
                 //memasukkan data ke dalam stack
                break;
                case '2' : 
                check(&S); //memeriksa jumlah karakter '{' dan '}'
                break;
                case '3' : printf("\n");
                PrintInfo(&S); //menampilkan data
                break;
            }
    }while (pil!=99);
getch();
}

void check(Stack *S){

address P=Top(*S);
int jumlah1=0, jumlah2=0;
    if(!IsEmptyStack(*S)) //data tidak kosong
    {
        do
        {
           //pemeriksaan karakter
            if(Info(P) == '{'){
              jumlah1++; //penghitungan karakter '{'
            }else if(Info(P) == '}'){
                  jumlah2++; //penghitungan karakter '}'
            }
            P=Next(P); //ke node selanjutnya
        }while(P!=Nil);
    }
    else
    printf("Data Kosong… \n\n\n");
    //menampilkan jumlah karakter
    printf(" \njumlah karakter '{' = %d", jumlah1);
    printf(" \njumlah karakter '}' = %d\n\n\n", jumlah2);
    if(jumlah1 == jumlah2){//jumlah karakter '{' sama dengan '}'
               printf("jumlah karakter '{' dan '}' sama, yaitu : %d\n\n\n", jumlah1);
    }else printf("jumlah karakter '{' dan '}' tidak sama!\n\n\n");
}

