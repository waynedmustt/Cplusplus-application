#include <iostream.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
int id_transfer; 

int Ambil_idTransfer(char no_rek[14], int jumlah, char no_rek_tujuan[14]);

int TulisTransaksi(char no_rek[14] , int jumlah, char no_rek_tujuan[14])
{  
  time(&ambil_waktu);  

  if(Ambil_idTransfer(no_rek , jumlah, no_rek_tujuan)!= 0)
    { id_transfer = Ambil_idTransfer(no_rek , jumlah, no_rek_tujuan) + 1; }
  else { id_transfer = 13001; }
  /*cout << id_transaksi << "\n ";
  
  cout << "no rekening = " ; cin >> no_rek;
  cout << "jumlah = " ; cin >> jumlah;
  cout << "no rekening Tujuan= " ; cin >> no_rek_tujuan;
  */
  OpenFile("FILE/transfer.txt", "a+");
  fprintf(file, "%d | %s | %d | %s | %s", id_transfer, no_rek, jumlah, no_rek_tujuan, ctime (&ambil_waktu));
  fclose(file);
  //cout << "transaksi berhasil di tulis di file";
  //system("pause");  
}

int Ambil_idTransfer(char no_rek[14], int jumlah, char no_rek_tujuan[14])
{   
    int id;
    char day[255], moon[255], date[255], jam[255], year[255];
    OpenFile("FILE/transfer.txt", "rt");
    while(!feof(file))      
    {                           
          fscanf(file, "%d | %s | %d | %s | %s %s %s %s %s", &id, &no_rek, &jumlah, &no_rek_tujuan, &day , &moon , &date , &jam , &year);
    
    }
    fclose(file);
    return id;
}
