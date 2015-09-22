#include <iostream.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

int id_transaksi, jumlah;
char tgl[255];
//char  no_rek[7];
time_t ambil_waktu;
    
/*
void OpenFile(char namafile[256], char mode[2])
{
     if((file = fopen(namafile , mode)) == NULL)
      {
                    cout << "File Tidak Dapat Dibuka";
                    system("pause");
      }
}*/

void W_transaksi();
int Ambil_idTransaksi(char no_rek[14], int jumlah);

int TulisTransaksi(char no_rek[14] , int jumlah)
{   
  time(&ambil_waktu);  

  if(Ambil_idTransaksi(no_rek , jumlah)!= 0)
    { id_transaksi = Ambil_idTransaksi(no_rek , jumlah) + 1; }
  else { id_transaksi = 12001; }
  /*cout << id_transaksi << "\n ";
  cout << "no rekening = " ; cin >> no_rek;
  cout << "jumlah = " ; cin >> jumlah;
  */
  OpenFile("FILE/transaksi.txt", "a+");
  fprintf(file, "%d | %s | %d | %s", id_transaksi, no_rek, jumlah, ctime (&ambil_waktu));
  fclose(file);
  //cout << "transaksi berhasil di tulis di file";
  //system("pause");  
}

int Ambil_idTransaksi(char no_rek[14], int jumlah)
{   
    int id;
    char day[255], moon[255], date[255], jam[255], year[255];
    OpenFile("FILE/transaksi.txt", "rt");
    while(!feof(file))      
    {                           
          fscanf(file, "%d | %s | %d | %s %s %s %s %s", &id, &no_rek, &jumlah, &day , &moon , &date , &jam , &year);
    
    }
    fclose(file);
    return id;
}
