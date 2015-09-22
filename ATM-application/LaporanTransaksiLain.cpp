#include <iostream.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

int id_TransaksiLain; 
int Ambil_id_TransaksiLain();


int TulisTransaksiLain(char no_rek[14],  char no_pelanggan[11] , int jumlah, int jenis)
{ 
    char jenis_transaksi[20];
    switch(jenis)
    {
         case 1 : strcpy(jenis_transaksi , "LISTRIK"); break;
         case 2 : strcpy(jenis_transaksi , "VOUCHER_PULSA"); break;
    }
      
    time(&ambil_waktu);  
  
    if(Ambil_id_TransaksiLain()!= 0)
    { id_TransaksiLain = Ambil_id_TransaksiLain() + 1; }
    else { id_TransaksiLain = 14001; }
  			
	
    OpenFile("FILE/TransaksiLain.txt", "a+");
    fprintf(file, "%d | %s | %s | %s | %d | %s \n", id_TransaksiLain, no_rek, jenis_transaksi, no_pelanggan, jumlah, ctime (&ambil_waktu));
    fclose(file);
  
}

int Ambil_id_TransaksiLain()
{   
    int id, jumlah;
    char jenis_transaksi[20], no_pelanggan[11], no_rek[14];
    char day[255], moon[255], date[255], jam[255], year[255];
    
    OpenFile("FILE/TransaksiLain.txt", "rt");
    while(!feof(file))      
    {                           
          fscanf(file, "%d | %s | %s | %s | %d | %s %s %s %s %s", &id, &no_rek, &jenis_transaksi, &no_pelanggan, &jumlah, &day , &moon , &date , &jam , &year);  
    }

    fclose(file);
    return id;
}
