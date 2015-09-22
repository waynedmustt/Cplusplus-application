/*
Program 		: NEW_ATM_Grup12.cpp
Deskripsi 		: Program Simulasi Sistem ATM
I.S 			: Fasilitas ATM belum terbentuk
F.S				: Fasilitas ATM sudah terbentuk dan dapat memberikan pelayanan perbankan kepada nasabah
Authors 		: Kelompok 12 
Tanggal/Versi 	: 24 Desember 2012 / versi 0.2
Requirement     : Menggunakan Compiler Dev-C++ 
*/

#include <iostream.h>
#include <string.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

/*---------------------- VARIABEL GLOBAL -----------------------*/

FILE *file;
/*Type data Record of Nasabah*/
typedef struct {
        int saldo;
        char nama[250];
        char pin[7], no_rek[14], blokir[10];
        }Nasabah;
        
        /*Deklarasi Variabel of Nasabah*/
        Nasabah N[100], N_aktif, N_transfer;
         
        int i, x;
        /*Variabel penampung namafile(.txt) dan mode file*/
        char namafile[256], mode[2];
        
        /*Variabel penampung password dan no rekening yang diinput*/
        string password, noRek;
        
        /*Variabel penampung nominal, saldo awal, saldo yang tersedia di mesin, dan nominal transfer*/
        int nominal, awal, saldo_mesin, nominal_transfer;
        
        /*Variabel penampung no rek tujuan yang diinput*/
        char no_rek_tujuan[14];

/*-------------------- END VARIABEL GLOBAL ----------------------*/

void Banner();
void Tunggu();
void Selesai();

void InfoSaldo(Nasabah N_aktif);
void InfoAkun(Nasabah N_aktif);

/*----------------------- MODUL MENU ----------------------------*/

void MainMenu();
void Tampil_MainMenu();
int Switch_MainMenu(int menu);

void MenuTransaksiLain();
void Tampil_MenuTransaksiLain();
int Switch_MenuTransaksiLain(int menu);

void MenuPembayaran();
void Tampil_MenuPembayaran();
int Switch_MenuPembayaran(int menu);

void MenuTanya();
void Tampil_MenuTanya();

int Input_pilihan();
bool MenuUlangi();
bool BenarAtauSalah();
void Tunggu();
/*--------------------- END MODUL MENU ----------------------------*/

/*------------------ 1. DEKLARASI MODUL UNTUK MANIPULASI FILE -------------------*/
void OpenFile(char namafile[256], char mode[2]);
bool CekBalance(int nominal);
bool CekSaldo(int nominal);
int update_balance(int nominal);
void isi_saldo_baru(char no_rek[14] ,int saldo_baru);
void update_Nasabah(int i);
void update_rekening();
/*------------------- END DEKLARASI MODUL UNTUK MANIPULASI FILE -----------------*/


/*-------------------- 2. DEKLARASI MODUL UNTUK SISTEM LOGIN --------------------*/

void SistemLogin();

string InputNorek();
bool CekNorek(string noRek);
void ValidasiNorek(int count);

string InputPin();
bool CekPin(string password,string noRek);
void ValidasiPin(int count);

bool Blokir(string noRek);
bool CekBlokir(char pin[7], char blokir[10]);
void ValidasiBlokir(string noRek);

/*--------------------- END DEKLARASI MODUL UNTUK SISTEM LOGIN ------------------*/


/*-------------------- 3. DEKLARASI MODUL PENARIKAN UANG TUNAI ------------------*/
void Proses_TarikUangTunai(int nominal);
bool Validasi_AmbilUang();

void JumlahLain();
int Input_JumlahLain();
bool Validasi_JumlahLain(int nominal);

void StrukSaldo();
/*-------------------- END DEKLARASI MODUL PENARIKAN UANG TUNAI -----------------*/


/*------------------------- 4. DEKLARASI MODUL TRANSFER -------------------------*/
void Transfer(); 
bool Proses_Transfer();

bool Input_NoRekTujuan();
bool CekNoRekTujuan(char no_rek_tujuan[14]);
void ValidasiNorekTujuan();

bool Input_NominalTransfer();
bool Konfirmasi_Transfer();
/*------------------------- END DEKLARASI MODUL TRANSFER ------------------------*/


/*-------------------------- 5. DEKLARASI MODUL UBAH PIN ------------------------*/
char pin_baru[7] , pin_lama[7];

int UbahPin();
void Input_PinLama();
bool Validasi_PinLama(char pin_aktif[7] , char pin_lama[7]);
void Input_PinBaru();
int Proses_UbahPin();
void Perhatian();

/*-------------------------- END DEKLARASI MODUL UBAH PIN -----------------------*/


/*---------------- 6. DEKLARASI MODUL PEMBAYARAN REKENING LISTRIK ---------------*/
typedef struct {
        char no_pelanggan[11], nama[255], bln[20], tahun[5], status[3];
        int jumlah_tagihan;
        }RekeningListrik;
        
RekeningListrik Listrik[255], Listrik_aktif ;
char no_pelanggan[11];
bool cek_status;

void Pembayaran(); 
bool Input_NoPelanggan();
bool Cek_NoPelanggan(char no_pelanggan[11]);
bool Konfirmasi_Pembayaran();
bool Proses_Pembayaran_Listrik();
bool Validasi_Pembayaran(char no_pelanggan[11]);

/*----------------- END DEKLARASI MODUL PEMBAYARAN REKENING LISTRIK -------------*/


/*------------------ 7. DEKLARASI MODUL PEMBELIAN VOUCHER PULSA -----------------*/
string id_voucher;
int id;
char nama_provider[20];
int nilai_voucher;

int VoucherPulsa();
bool Proses_VoucherPulsa();
string Random_IdVoucher(char kode[3]);

void Menu_TypeVoucher();
void Tampil_MenuTypeVoucher();
int Switch_MenuTypeVoucher(int menu);

void Menu_NilaiVoucher();
void Tampil_MenuNilaiVoucher();
int Switch_MenuNilaiVoucher(int menu);

bool Konfirmasi_Pembelian();

/*------------------- END DEKLARASI MODUL PEMBELIAN VOUCHER PULSA ---------------*/
#include "LaporanTransaksi.cpp"
#include "LaporanTransfer.cpp"
#include "LaporanTransaksiLain.cpp"


int main()
{
    
    system("color f9"); // set backgorund 
    
    Banner();
	SistemLogin();	
    
	MainMenu();
	   
    system("pause");

}
void Banner() {
    cout << "\n\n"; 
    cout << "\t\t\t+--------------------------------+" << endl; Sleep (250);
	cout << "\t\t\t|   AAAAAA TTTTTT MMMMM   MMMMM  |" << endl; Sleep (250);
	cout << "\t\t\t|   AA  AA   TT   MM   MMM   MM  |" << endl; Sleep (250);
	cout << "\t\t\t|   AAAAAA   TT   MM    M    MM  |" << endl; Sleep (250);
	cout << "\t\t\t|   AA  AA   TT   MM         MM  |" << endl; Sleep (250);
	cout << "\t\t\t|   AA  AA   TT   MM         MM  |" << endl; Sleep (250);
	cout << "\t\t\t+--------------------------------+" << endl; Sleep (250);
	cout << "\t\t\t|              ATM 12            |" << endl;
	cout << "\t\t\t+--------------------------------+" << endl << endl;
	
}

void Selesai() {
     char copyright=184;
     system("cls");
     cout << "\n\n\n\n\n\n\n\n";
     cout << "\t    +-----------------------------------------------------+\n\n";
     cout << "\t        TERIMA KASIH TELAH MENGGUNAKAN LAYANAN ATM KAMI    \n\n";
     cout << "\t\t\t    ATM COPYRIGHT " << copyright << " BY GROUP 12      \n\n";
     cout << "\t\t\t\t D3 - JTK POLBAN                                     \n\n";
     cout << "\t    +-----------------------------------------------------+\n\n";
     Sleep(3000);
     exit(0);
}

void InfoSaldo(Nasabah N_aktif) {
     system("cls");
     				
     cout << "\n\n";
     cout << "\t\t\t+-----------------------------------+"<<endl;
     cout << "\t\t\t|     INFORMASI SALDO REKENING      |"<<endl;
     cout << "\t\t\t+-----------------------------------+"<<endl;
     cout << "\n";   
     cout << "\t\t\t     JUMLAH SALDO   = Rp."<< N_aktif.saldo  << endl;
     cout << "\n";
     cout << "\t\t\t+-----------------------------------+"<< endl;
     cout << "\n\n\n";
}

void InfoAkun(Nasabah N_aktif) {
     system("cls");
     				
     cout << "\n\n";
     cout << "\t\t\t+-----------------------------------+"<<endl;
     cout << "\t\t\t|       INFORMASI AKUN NASABAH      |"<<endl;
     cout << "\t\t\t+-----------------------------------+"<<endl;
     cout << "\n\t\t\t\t NO REKENING    : "<< N_aktif.no_rek  << endl;
     cout << "\n\t\t\t\t NAMA NASABAH   : "<< N_aktif.nama    << endl;
     cout << "\n\t\t\t\t PIN            : "<< N_aktif.pin     << endl;   
     cout << "\n\t\t\t\t SISA SALDO     : Rp."<< N_aktif.saldo << endl;
     cout << "\n\t\t\t+-----------------------------------+"   << endl;
     cout << "\n\n\n";
}

/*----------------------------------------- MODUL MENU -----------------------------------------*/
void MainMenu() {   
    int menu;
    system("cls");
    Tampil_MainMenu();
    Switch_MainMenu(Input_pilihan());    
}

void Tampil_MainMenu() {
   
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\t\t |                  MENU UTAMA                  |"<< endl;
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\n";
    cout << "\t\t +-----+";                     cout << "\t\t\t          +-----+" << endl;
    cout << "\t\t |  1  | Rp. 100.000";     cout << "\t     Rp. 500.000  |  2  | " << endl;
    cout << "\t\t +-----+";                     cout << "\t\t\t          +-----+" << endl;
    cout << "\n";
    cout << "\t\t +-----+";                     cout << "\t\t\t          +-----+" << endl;
    cout << "\t\t |  3  | Rp. 1.000.000";   cout << "\t   Rp. 5.000.000  |  4  | " << endl;
    cout << "\t\t +-----+";                     cout << "\t\t\t          +-----+" << endl;
    cout << "\n";
    cout << "\t\t +-----+";                     cout << "\t\t\t          +-----+" << endl;
    cout << "\t\t |  5  | JUMLAH LAIN";     cout << "\t      INFO SALDO  |  6  | " << endl;
    cout << "\t\t +-----+";                     cout << "\t\t\t          +-----+" << endl;
    cout << "\n";
    cout << "\t\t +-----+";                     cout << "\t\t\t          +-----+" << endl;
    cout << "\t\t |  7  | TRANSAKSI LAIN";        cout << "\t\t  KELUAR  |  8  | " << endl;
    cout << "\t\t +-----+";                     cout << "\t\t\t          +-----+" << endl;
    cout << "\n";

} 

int Switch_MainMenu(int menu)
{
    switch(menu)
    {
          case 1 : nominal = 100000 ; Proses_TarikUangTunai(nominal);  break;
          case 2 : nominal = 500000 ; Proses_TarikUangTunai(nominal);  break;
          case 3 : nominal = 1000000; Proses_TarikUangTunai(nominal);  break;
          case 4 : nominal = 5000000; Proses_TarikUangTunai(nominal);  break;
          case 5 : JumlahLain();  break;
          case 6 : InfoSaldo(N_aktif); break;
          case 7 : MenuTransaksiLain(); break;
          case 8 : Selesai();          
    }
    MenuTanya();
}

void MenuTransaksiLain() {   
    system("cls");
    Tampil_MenuTransaksiLain();
    Switch_MenuTransaksiLain(Input_pilihan());     
}

void Tampil_MenuTransaksiLain() {
   
    cout << "\n";
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\t\t |               TRANSAKSI LAINNYA              |"<< endl;
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\n\n";
    cout << "\t\t +-----+";                     cout << "\t\t\t          +-----+" << endl;
    cout << "\t\t |  1  | INFORMASI AKUN";        cout << "\t\tTRANSFER  |  2  | " << endl ;
    cout << "\t\t +-----+";                     cout << "\t\t\t          +-----+" << endl;
    cout << "\n";
    cout << "\t\t +-----+";                     cout << "\t\t\t          +-----+" << endl;
    cout << "\t\t |  3  | PEMBAYARAN /";          cout << "\t\tUBAH PIN  |  4  | " << endl ;
    cout << "\t\t +-----+";                     cout << "\t\t\t          +-----+" << endl;
    cout << "\t\t         PEMEBELIAN";
    cout << "\n\n\n";
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\t\t |         TEKAN 0 UNTUK BATAL [CANCEL]         |"<< endl;
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\n\n";

}

int Switch_MenuTransaksiLain(int menu)
{
    switch(menu)
    {
          case 0 : MainMenu(); break;
          case 1 : InfoAkun(N_aktif); break;
          case 2 : Transfer();  break;
          case 3 : MenuPembayaran();  break;
          case 4 : UbahPin(); break;    
    }
    MenuTanya();
}

void MenuPembayaran() {   
    system("cls");
    Tampil_MenuPembayaran();
    Switch_MenuPembayaran(Input_pilihan());      
}

void Tampil_MenuPembayaran() {
   
    cout << "\n";
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\t\t |       TRANSAKSI PEMBAYARAN / PEMBELIAN       |"<< endl;
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\n\n";
    cout << "\t\t +-----+";                 cout << "\t\t\t          +-----+" << endl;
    cout << "\t\t |  1  | LISTRIK";     cout << "\t   VOUCHER PULSA  |  2  | " << endl ;
    cout << "\t\t +-----+";                 cout << "\t\t\t          +-----+" << endl;                     
    cout << "\n\n\n";
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\t\t |         TEKAN 0 UNTUK BATAL [CANCEL]         |"<< endl;
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\n\n";

}

int Switch_MenuPembayaran(int menu)
{
    switch(menu)
    {
          case 0 : MainMenu(); break;
          case 1 : Pembayaran(); break; 
          case 2 : VoucherPulsa(); break;          
    }
    
    MenuTanya();
}

void MenuTanya() {
    Tampil_MenuTanya(); 
    switch(Input_pilihan()) {
          case 1 : MainMenu(); break;
          case 2 : Selesai(); break;
    }
}

void Tampil_MenuTanya()
{
     Sleep (350);
     cout << "\t\t APAKAH ANDA INGIN MELAKUKAN TRANSAKSI LAINNYA ? \n\n";
     cout<<"\t\t\t\t+-----------------+"<<endl;
     cout<<"\t\t\t\t|  1. MENU UTAMA  |"<<endl;
     cout<<"\t\t\t\t|  2. SELESAI     |"<<endl;
     cout<<"\t\t\t\t+-----------------+"<<endl;
} 

int Input_pilihan() {   
    int menu;
    
    cout << "\n\t\t\t Pilihan Anda : "; cin >> menu;
    
    return menu;
}
     
bool MenuUlangi()
{    
     bool cek_ulangi = false;
     cout<<"\t\t\t\t+-----------------+"<<endl;
     cout<<"\t\t\t\t|  1. ULANGI      |"<<endl;
     cout<<"\t\t\t\t|  2. MENU UTAMA  |"<<endl;
     cout<<"\t\t\t\t+-----------------+"<<endl;
     
     if(Input_pilihan() == 1 ) { cek_ulangi = true; } 
     else { MainMenu(); } 
     
     return cek_ulangi;
}

bool BenarAtauSalah()
{    bool cek_bool = false;
     cout << "\n\n\n";
     cout<<"\t\t\t  +-----------------------------+"<<endl;
     cout<<"\t\t\t  |  TEKAN 1 UNTUK MELANJUTKAN  |"<<endl;
     cout<<"\t\t\t  |                             |"<<endl;
     cout<<"\t\t\t  |     TEKAN 2 UNTUK BATAL     |"<<endl;
     cout<<"\t\t\t  +-----------------------------+"<<endl;
     cout << "\t";
     
     if(Input_pilihan() == 1 ) { cek_bool = true; } 
     else { MainMenu(); } 
     
     return cek_bool;
}

void Tunggu() {
  printf("\n\n");
  printf("\t\t\t\t  HARAP TUNGGU\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  printf("\t\t\t\t ATM BY GROUP 12");Sleep(1000);
  system("cls");   
}
/*-------------------------------------- END MODUL MENU -----------------------------------------*/

/*------------------------------ 1.MODUL UNTUK MANIPULASI FILE ----------------------------------*/

void OpenFile(char namafile[256], char mode[2])
// Prosedur Membuka suatu File 
// I.S                     : File belum dibuka
// F.S                     : File telah terbuka
// Modul yang dipanggil    : -
// Modul yang memanggil    : CekBalance(),
{
     //Jika fIle tidak dapat dibuka akan muncul error
     if((file = fopen(namafile , mode)) == NULL)
      {
                    cout << "File Tidak Dapat Dibuka";
                    system("pause");
      }
}

bool CekBalance(int nominal)
// Fungsi untuk mengecek balance jumlah saldo yang tersedia  
// di mesin (saldo_mesinATM.txt) dengan nominal yang diinput
// Input       : int nominal
// Output      : cekBalance : boolean
// Modul yang dipanggil    : OpenFile()
// Modul yang memanggil    : 
{
     bool cekBalance;
     cekBalance = true;
     
     OpenFile("FILE/saldo_mesinATM.txt", "r+");
     fscanf(file, "%d", &saldo_mesin); 
     
     //nominal tidak boleh melebihi saldo_mesin dan batas minimal jumlah saldo_mesin adalah 1000000 
     if((nominal > saldo_mesin) && saldo_mesin <= 1000000) 
     {  
        cekBalance = false;
        system("cls");
        cout << "\n\n\n\n";
        cout << "\t\tMAAF !! UNTUK SEMENTARA TIDAK DAPAT DILAKUKAN TRANSAKSI\n\n\n\n";
          
     }   
     fclose(file); 
      
     return cekBalance;
}

bool CekSaldo(int nominal)
// Fungsi untuk mengecek saldo nasabah yang aktif  
// dan membandingkan dengan nominal yang di input
// Input       : int nominal
// Output      : cek_saldo : boolean
// Modul yang dipanggil    : -
// Modul yang memanggil    : 
{   
     bool cek_saldo;
     cek_saldo = true;
     
     //nominal tidak boleh melebihi nasabah yg aktif dan batas minimal saldo nasabah yg aktif adalah 100000 
     if(nominal > N_aktif.saldo && N_aktif.saldo <= 100000)
     {          cek_saldo= false;
                system("cls");
                cout << "\n\n\n\n";
                cout << "\t\t\tMAAF !! NOMINAL MELEBIHI SALDO ANDA\n\n\n\n";
                    
     }
         return cek_saldo;     
}

int update_balance(int nominal)
{    saldo_mesin = saldo_mesin - nominal;
     OpenFile("FILE/saldo_mesinATM.txt", "r+");
     fprintf(file, "%d", saldo_mesin); 
     fclose(file);  
}

void isi_saldo_baru(char no_rek[14] , int saldo_baru)
{
     int i; i=1;
     
     OpenFile("FILE/nasabah.txt", "rt+");
     while(!feof(file)) 
     {          
          fscanf(file, "%s , %s , %s , %d , %s", &N[i].no_rek , &N[i].nama , &N[i].pin, &N[i].saldo, &N[i].blokir);
          
          if(strcmp(no_rek ,N[i].no_rek)==0)
          {  
             N[i].saldo = saldo_baru; 
          }
         
          i++;
     }

     update_Nasabah(i);
                                    			 
}

void update_Nasabah(int i)
{    
    OpenFile("FILE/nasabah.txt", "w+"); 
    int y=1;
    while(y<i-1)
    {
         fprintf(file, "%s , %s , %s , %d , %s \n", N[y].no_rek , N[y].nama , N[y].pin, N[y].saldo, &N[y].blokir);
         y++;
    }    
 
    fclose(file);    
}

void update_rekening()
{
     int i; i=1;
     
     OpenFile("FILE/RekeningListrik.txt", "rt+");
     while(!feof(file)) 
     {          
          fscanf(file, "%s | %s | %s | %s | %d | %s", &Listrik[i].no_pelanggan, &Listrik[i].nama, &Listrik[i].bln, &Listrik[i].tahun,  &Listrik[i].jumlah_tagihan,  &Listrik[i].status);
          
          if( strcmp ( no_pelanggan, Listrik[i].no_pelanggan ) ==0)
          { 
             strcpy(Listrik[i].status, "L");  
          }
         
          i++;
     }

     OpenFile("FILE/RekeningListrik.txt", "w+"); 
     int y=1;
     
     while(y<i-1)
     {
          fprintf(file, "%s | %s | %s | %s | %d | %s \n", Listrik[y].no_pelanggan, Listrik[y].nama, Listrik[y].bln, Listrik[y].tahun,  Listrik[y].jumlah_tagihan, Listrik[y].status);
          y++;
     }    
     
     fclose(file);                                                 			 
}


/*----------------------------- END MODUL UNTUK MANIPULASI FILE --------------------------------*/


/*------------------------------- 2. MODUL UNTUK SISTEM LOGIN ----------------------------------*/
void SistemLogin()
{   bool cek;
    int count;

    cek= false;
    count=3;
    while ((cek == false) && (count>=1))
    {     
          InputNorek();
          system("cls");
          if(CekNorek(noRek)== false)
          {                   
             count--;
             ValidasiNorek(count); 
             noRek = "";
          }
          
          else  
          { 
            cek = true ; 
          }                            
    }
    
    
    cek= false;
    count=3;
    while ((cek == false) && (count>=1))
    {     
          InputPin();
          system("cls");
          if(CekPin(password, noRek)== false)
          {                   
             count--;
             ValidasiPin(count); 
             password = "";
          }
          
          else  
          { 
            cek = true ; 
          }                            
    }
    
}

string InputNorek()
{      
    char no[14];
    cout << "\n\n";   
    cout<<"\t\t\t SILAHKAN MASUKAN NO REKENING ANDA"<<endl;
    cout<<"\n\t\t\t\t UNTUK PELAYANAN " <<endl;
    cout<<"\n\t\t\t---------------------------------- "<<endl;
    cout<<"\n\t\t\t    No Rekening : ";
       
    for(int i=0;i<13;i++)
    {   no[i]=getch(); cout << no[i];      
        noRek += no[i];
    } 
       return noRek;
         
}

bool CekNorek(string noRek)
{
     OpenFile("FILE/nasabah.txt", "r");
     bool cek;
     cek =  false;
     
     i=1;
      
      while(!feof(file) && cek == false )
      {             
           fscanf(file, "%s , %s , %s , %d , %s", &N[i].no_rek , &N[i].nama , &N[i].pin, &N[i].saldo, &N[i].blokir);
                    
           if(noRek == N[i].no_rek)
           {
              cek = true;
                             
              if(CekBlokir(N[i].pin, N[i].blokir) == true)
              {
                  ValidasiBlokir(N[i].no_rek);
              }
           }         
           
           i++;                            
      }
                              
      fclose(file);
      return cek;
}
void ValidasiNorek(int count)
{    
     if(count<1)
     {
        cout << "\n\n\n\n\n\n\n\n\n\n\t\t MAAF !! NO REKENING TIDAK TERDAFTAR DI ATM 12\n";
        Sleep(3000);
        Selesai();
        exit(0);
     }
     
     else 
     {          
        cout << "\n\n\t\t\t     NO REKENING TIDAK VALID";
        cout << "\n\n\t\t\t\t  Silahkan Ulangi";
        cout << "\n\t\t     ( Anda mempunyai " << count << " kali kesempatan lagi )\n\n"; 
     }  
        
}



string InputPin()
{
     char pass[10];
     //Banner();
     cout << "\n\n";
     cout<<"\t\t\t     SILAHKAN MASUKAN PIN ANDA  "<<endl;
     cout<<"\n\t\t\t----------------------------------- "<<endl;
     cout<<"\n\t\t\t    PIN         : ";
     
     for(int i=0;i<6;i++)
     {   pass[i]=getch(); cout << "*";      
         password += pass[i];
     }
    
     return password;                                    
}

bool CekPin(string password, string noRek)
{
     OpenFile("FILE/nasabah.txt", "r");
     bool cek;
     cek = false;
     i=1;
      
      while(!feof(file) && cek == false )
      {     
            fscanf(file, "%s , %s , %s , %d , %s", &N[i].no_rek , &N[i].nama , &N[i].pin, &N[i].saldo, &N[i].blokir);
            
            if(password == N[i].pin && noRek == N[i].no_rek)
            {
               N_aktif = N[i];
               cek = true;
            }
            i++;                            
      }                        
      fclose(file);
      return cek;
}

void ValidasiPin(int count)
{    string temp;
     temp = "";
     if(count<1 && Blokir(noRek)==true)
     {
         cout << "\n\n\n\n\t\t\tMAAF !! No rekening anda telah diblokir\n"; Sleep(3000);
         Selesai();
         exit(0);
     }
     else 
     {          
         cout << "\n\n\t\t\t\t  PIN TIDAK VALID";
         cout << "\n\n\t\t\t\t  Silahkan Ulangi";
         cout << "\n\t\t     ( Anda mempunyai " << count << " kali kesempatan lagi )\n\n"; 
     }    
}


bool Blokir(string noRek)
{
     bool blokir;
     OpenFile("FILE/nasabah.txt", "r+"); 
     int i =1;
     
     while(!feof(file))
     {    
          fscanf(file, "%s , %s , %s , %d , %s", &N[i].no_rek , &N[i].nama , &N[i].pin, &N[i].saldo, &N[i].blokir);
          
          if(N[i].no_rek == noRek)
          {
              strcpy(N[i].pin, "******");
              strcpy(N[i].blokir, "YES");
          }
          
          i++;
     }

     update_Nasabah(i); 
     blokir = true;
     return blokir; 
}

bool CekBlokir(char pin[7], char blokir[5])
{
     bool cekBlokir;
     cekBlokir =  false;
     
     if((strcmp(pin , "******")==0) || (strcmp(blokir, "YES")==0))
     {
        cekBlokir =  true;           
     }
     
     return cekBlokir;
}

void ValidasiBlokir(string noRek)
{
     cout << "\n\n\n\n\n\n\n\n\n\n\t\tMAAF !! No rekening \"" << noRek << " \" Masih Di BLOKIR\n";Sleep(3000);
     Selesai();
     exit(0);
}

/*------------------------------- END MODUL UNTUK SISTEM LOGIN ----------------------------------*/
 
 
 
/*---------------------------------- 3. MODUL PENARIKAN UANG TUNAI ------------------------------*/

void Proses_TarikUangTunai(int nominal)
{    if(CekBalance(nominal) == true) 
     {
                 if(CekSaldo(nominal)==true)
                 { 
                        
                        if(Validasi_AmbilUang()==true)
                        { 
              		        awal = N_aktif.saldo;
                            N_aktif.saldo = N_aktif.saldo - nominal;
                    		isi_saldo_baru(N_aktif.no_rek, N_aktif.saldo);
                    		update_balance(nominal);
                    		TulisTransaksi(N_aktif.no_rek , nominal);
                    		StrukSaldo();
                        }
                 }
     }
}

bool Validasi_AmbilUang()
{   bool cek_ambiluang;
    cek_ambiluang = false;
    system("cls");
    Tunggu();

    cout << "\n\n\n\n";
    cout<<"\t\t\t+-----------------------------------+"<<endl;
    cout<<"\t\t\t|     SILAHKAN AMBIL UANG ANDA      |"<<endl;
    cout<<"\t\t\t+-----------------------------------+"<<endl;
    if(BenarAtauSalah()==true) { cek_ambiluang = true; }
    
    return cek_ambiluang;
}

void JumlahLain()
{    int nominal_JumlahLain;
     nominal_JumlahLain = Input_JumlahLain();
     system("cls");
     Tunggu();  
     
     if(Validasi_JumlahLain(nominal_JumlahLain) == true) 
     {    
          Proses_TarikUangTunai(nominal_JumlahLain);
     }
 
}

int Input_JumlahLain()
{
  system("cls");  
  cout << "\n\n\n";
  cout << "\t\t\t+----------------------------------+" << endl;
  cout << "\t\t\t|  MASUKAN JUMLAH TRANSAKSI TUNAI  |" << endl;
  cout << "\t\t\t|       KELIPATAN RP 100.000       |" << endl; 
  cout << "\t\t\t+----------------------------------+" << endl; 
  cout << "\n\n\n\t\t\t\t    Rp. "; 
  cin >> nominal;
  
  return nominal;  
}

bool Validasi_JumlahLain(int nominal)
{
     bool cek_nominal;
     cek_nominal = true;
     if(nominal % 100000 != 0 ||  nominal < 100000 || nominal > 5000000) {
     if(nominal < 100000 || nominal > 5000000)
	 { 
        printf("\n\n\n");
		printf("\t .::  BATAS NOMINAL : MIN = Rp 100.000 dan MAX Rp 5.000.000  ::.\n");
		printf("\n\n\n");	
	 } 
     
     if(nominal % 100000 != 0)
     {
        printf("\n\n\n");
		printf("\t\t .:: NOMINAL HARUS DALAM KELIPATAN RP 100.000 ::.\n");
		printf("\n\n\n");        
     }
     if(MenuUlangi() == true) { Switch_MainMenu(5); }
     cek_nominal = false;  
     }
     
     return cek_nominal;
     
}



void StrukSaldo()
{
	    system("cls");
        cout <<"\n\t\t\tTRANSAKSI TARIK TUNAI BERHASIL\n\n";
        cout << "\t\t.:: Penarikan Uang Tunai Nominal Rp."<< nominal << " ::." <<endl;      

        cout <<"\t\t\t+----------------------------+"<<endl;
        cout <<"\t\t\t| STRUK PENARIKAN UANG TUNAI |"<<endl;
        cout <<"\t\t\t+----------------------------+"<<endl;
        
        cout << "\t\t\t   NO REKENING \t= "<< N_aktif.no_rek << endl;
        cout << "\t\t\t   NAMA  \t= "<< N_aktif.nama<< endl;    
        cout << "\t\t\t   SALDO AWAL \t= Rp."<< awal << endl;
        cout << "\t\t\t   SISA SALDO \t= Rp."<< N_aktif.saldo << endl;
        cout << "\t\t\t   ID TRANSAKSI : "<< id_transaksi << endl;
        cout << "\t\t\t   " << ctime (&ambil_waktu);
        cout <<"\t\t\t+------------------------------+\n"<<endl;
        cout << "\n";

}

/*--------------------------------  END MODUL PENARIKAN UANG TUNAI -----------------------------*/
 
 
/*------------------------------------- 4. MODUL TRANSFER ---------------------------------------*/

void Transfer()
{  
   if(Proses_Transfer() == true )
   {   
       system("cls");
       cout <<"\n\n\n\t\t\      .:: TRANSAKSI TRANSFER BERHASIL ::.\n\n\n\n\n";
   }
}
 
bool Proses_Transfer()
{  bool transfer;
   transfer = false;
   if( Input_NoRekTujuan() == true )
   {   
       if (CekNoRekTujuan(no_rek_tujuan) == true) 
       {
          if( Input_NominalTransfer() == true )
          {  
             if(Konfirmasi_Transfer() == true )
             {
                if(CekSaldo(nominal_transfer) == true )
                {
                   N_aktif.saldo = N_aktif.saldo - nominal_transfer;
                   isi_saldo_baru(N_aktif.no_rek , N_aktif.saldo);
               
                   N_transfer.saldo = N_transfer.saldo + nominal_transfer;
                   isi_saldo_baru(N_transfer.no_rek ,N_transfer.saldo); 
                 
                   transfer = true;
                   TulisTransaksi(N_aktif.no_rek, nominal_transfer, N_transfer.no_rek);
                }
             }
          }
       }
       else { ValidasiNorekTujuan(); }
   }
   
   return transfer;
}


bool Input_NoRekTujuan()
{   bool input_no_rek_tujuan;
    input_no_rek_tujuan = false;
    system("cls");
    cout << "\n";
    cout << "\t\t     +-----------------------------------------+" << endl;
    cout << "\t\t     |            SILAHKAN MASUKAN             |" << endl;
    cout << "\t\t     |                                         |" << endl;
    cout << "\t\t     |  NO REKENING TUJUAN TRANSFER (13 DIGIT) |" << endl; 
    cout << "\t\t     |                                         |" << endl;
    cout << "\t\t     |  (HANYA UNTUK TRANSFER KE SESAMA BANK)  |" << endl; 
    cout << "\t\t     +-----------------------------------------+" << endl; 
    cout << "\n\n\n\t\t\t\t\t";
    for(int i=0;i<13;i++) { no_rek_tujuan[i]=getch(); cout << no_rek_tujuan[i]; }
    if (BenarAtauSalah()==true) { input_no_rek_tujuan = true; }
    
    return input_no_rek_tujuan;
}


bool CekNoRekTujuan(char no_rek_tujuan[7])
{
     OpenFile("FILE/nasabah.txt", "r");
     bool cek;
     cek = false;
     i=1;
      
      while(!feof(file) && cek == false )
      
      {             
                    fscanf(file, "%s , %s , %s , %d , %s", &N[i].no_rek , &N[i].nama , &N[i].pin, &N[i].saldo, &N[i].blokir);
                    if((strcmp(no_rek_tujuan ,N[i].no_rek)==0) && strcmp(no_rek_tujuan ,N_aktif.no_rek)!=0)
                    {               
                                N_transfer = N[i];
                                cek = true;
                    }
                     
                    i++;                            
      }                        
      fclose(file);
      return cek;
}

void ValidasiNorekTujuan()
{      system("cls");
       printf("\n\n");
        
       if(strcmp(no_rek_tujuan ,N_aktif.no_rek) ==0)
       { 
          cout << "\n\n\n\t\tMAAF !! TRANSFER TIDAK BISA KE NO REKENING SENDIRI\n\n\n\n\n"; 
       }
       else
       { 
          cout << "\n\n\n\t     MAAF !! NO REKENING TUJUAN TIDAK TERDAFTAR DI ATM 12\n\n\n\n\n"; 
       }
       
       if(MenuUlangi() == true) { Switch_MenuTransaksiLain(2); }        
}

bool Input_NominalTransfer()
{   bool input_nominal_transfer;
    input_nominal_transfer = false;
    system("cls");
    cout << "\n";
    cout << "\t\t\t     +------------------------+" << endl;
    cout << "\t\t\t     |    SILAHKAN MASUKAN    |" << endl;
    cout << "\t\t\t     |                        |" << endl; 
    cout << "\t\t\t     |     JUMLAH TRANSFER    |" << endl; 
    cout << "\t\t\t     +------------------------+" << endl; 
    cout << "\n\n\n\t\t\t\t    Rp. ";
    cin >> nominal_transfer;
    if (BenarAtauSalah()==true) { input_nominal_transfer = true; }
    
    return input_nominal_transfer;
}

bool Konfirmasi_Transfer()
{    bool konfirm;
     konfirm =false;
 	 system("cls");
		printf("\n\n");
		cout << "\t\t\t+-----------------------------------+"<<endl;
		cout << "\t\t\t|        KONFIRMASI TRANSFER        |"<<endl;
		cout << "\t\t\t+-----------------------------------+"<<endl;
        printf("\n");
		cout << "\n\t\t\t     NO REKENING TUJUAN = "<< N_transfer.no_rek << endl;
		cout << "\n\t\t\t     NAMA \t\t= "<< N_transfer.nama << endl;    
		cout << "\n\t\t\t     JUMLAH TRANSFER \t= Rp."<< nominal_transfer << endl;
		cout << "\n\t\t\t     NO REKENING ASAL   = "<< N_aktif.no_rek << endl;
		cout << "\n\t\t\t+-----------------------------------+"<< endl;
		
		if (BenarAtauSalah()==true) { konfirm = true; }
    
    return konfirm;
}
/*------------------------------------ END MODUL TRANSFER ---------------------------------------*/


/*------------------------------------- 5. MODUL UBAH PIN ---------------------------------------*/

int UbahPin()
{
    Input_PinLama();
    Input_PinBaru();
    Proses_UbahPin(); 
}    


void Input_PinLama()
{
    system("cls");
    cout << "\n\n\n";
    cout << "\t\t\t      +----------------------+" << endl;
    cout << "\t\t\t      |   SILAHKAN MASUKAN   |" << endl;
    cout << "\t\t\t      |                      |" << endl;
    cout << "\t\t\t      |      KEMBALI PIN     |" << endl; 
    cout << "\t\t\t      |                      |" << endl;
    cout << "\t\t\t      |       ATM ANDA       |" << endl; 
    cout << "\t\t\t      +----------------------+";
    cout << "\n\n\n\t\t\t\t        ";
    
    for(int i=0;i<6;i++) { pin_lama[i]=getch(); cout << pin_lama[i]; }
      
}

bool Validasi_PinLama(char pin_aktif[7] , char pin_lama[7])
{    
     bool cek_PinLama = true;
     if(strcmp(pin_aktif , pin_lama)!=0)
     {
        system("cls");
        cout<<"\n\n\t\t\t  PIN LAMA ATM ANDA TIDAK VALID\n\n\n"<<endl; 
        if(MenuUlangi() == true) { Switch_MenuTransaksiLain(4); }                      
        cek_PinLama = false;
     }
     
     else 
     { 
        system("cls");
        cout<<"\n\n\t\t\t.:: PIN ATM ANDA BERHASIL DIUBAH ::.\n"<<endl;
        Perhatian();  
     }
     
     return cek_PinLama;
}

void Input_PinBaru()
{   
    for(int i =1 ; i<=2 ; i++)
    { 
                  system("cls");
                  cout << "\n\n\n";
                  cout << "\t\t\t      +-----------------------+" << endl;
                  cout << "\t\t\t      |    SILAHKAN MASUKAN   |" << endl;
                  if(i==2) { 
                  cout << "\t\t\t      |                       |" << endl;
                  cout << "\t\t\t      |      SEKALI LAGI      |" << endl; }
                  cout << "\t\t\t      |                       |" << endl;
                  cout << "\t\t\t      |     PIN BARU ANDA     |" << endl; 
                  cout << "\t\t\t      |                       |" << endl;
                  cout << "\t\t\t      |    SEBANYAK 6 DIGIT   |" << endl; 
                  cout << "\t\t\t      +-----------------------+";
                  cout << "\n\n\n\t\t\t\t        ";
                   
                  for(int i=0;i<6;i++) { pin_baru[i]=getch(); cout << pin_baru[i]; }
    } 
      
}

int Proses_UbahPin()
{
    OpenFile("FILE/nasabah.txt", "r");
    int i=1;          
    while(!feof(file))
    {             
         fscanf(file, "%s , %s , %s , %d , %s", &N[i].no_rek , &N[i].nama , &N[i].pin, &N[i].saldo, &N[i].blokir);
      
         if(strcmp(N_aktif.no_rek ,N[i].no_rek)==0)
         {  
            if((Validasi_PinLama(N[i].pin , pin_lama)) == true) 
            {
               strcpy( N[i].pin, pin_baru);
            } 
            N_aktif = N[i];
         }
         i++;
    }
 
    fclose(file);
    update_Nasabah(i);

}

void Perhatian()
{   
    cout << "\n";
    cout << "\t\t\t      +-----------------------+" << endl;
    cout << "\t\t\t      | JANGAN MEMBERITAHUKAN |" << endl;
    cout << "\t\t\t      |        PIN ANDA       |" << endl; 
    cout << "\t\t\t      |    KEPADA SIAPAPUN    |" << endl; 
    cout << "\t\t\t      +-----------------------+" << endl; 
    cout << "\n\n\n";
}

/*------------------------------------- END MODUL UBAH PIN --------------------------------------*/


/*---------------------------- 6. MODUL PEMBAYARAN REKENING LISTRIK -----------------------------*/


void Pembayaran()
{  
   if(Proses_Pembayaran_Listrik() == true )
   {   
       system("cls");
       cout <<"\n\n\n\t\t\.:: TRANSAKSI Pembayaran Rekening Listrik BERHASIL ::.\n\n\n\n";
   }
}

bool Input_NoPelanggan()
{   bool input_no_pelanggan;
    input_no_pelanggan = false;
    
    system("cls");
    cout << "\n";
    cout << "\t\t     +-----------------------------------------+" << endl;
    cout << "\t\t     |            SILAHKAN MASUKAN             |" << endl;
    cout << "\t\t     |                                         |" << endl;
    cout << "\t\t     | NO PELANGGAN REKENING LISTRIK (10 DIGIT)|" << endl; 
    cout << "\t\t     +-----------------------------------------+" << endl; 
    cout << "\n\n\n\t\t\t\t\t";
    
    for(int i=0;i<10;i++) { no_pelanggan[i]=getch(); cout << no_pelanggan[i]; }
    
    if (BenarAtauSalah()==true) { input_no_pelanggan = true; }
    
    return input_no_pelanggan;
}

bool Cek_NoPelanggan(char no_pelanggan[11])
{   
    
    bool cek;
    cek =  false;
    cek_status = false;
    
    OpenFile("FILE/RekeningListrik.txt", "r");
    int i=1;

    while(!feof(file) && cek == false )      
    {                           
          fscanf(file, "%s | %s | %s | %s | %d | %s", &Listrik[i].no_pelanggan, &Listrik[i].nama, &Listrik[i].bln, &Listrik[i].tahun, &Listrik[i].jumlah_tagihan, &Listrik[i].status);
          
           if(strcmp ( no_pelanggan, Listrik[i].no_pelanggan ) ==0)
          {   cek = true;
              if(strcmp(Listrik[i].status , "BL") == 0)
              {
                 Listrik_aktif = Listrik[i];
                  
                 cek_status = true;
              }
          } 

          i++;
    }
    fclose(file);
    return cek;
}


bool Konfirmasi_Pembayaran()
{    bool konfirm;
     konfirm =false;
 	    
        system("cls");
		printf("\n\n");
		cout << "\t\t\t+-----------------------------------+"<<endl;
		cout << "\t\t\t|        Konfirmasi Pembayaran      |"<<endl;
		cout << "\t\t\t+-----------------------------------+"<<endl;
        printf("\n");
		cout << "\n\t\t\t     NO PELANGGAN \t: "<< Listrik_aktif.no_pelanggan << endl;
		cout << "\n\t\t\t     NAMA \t\t: "<< Listrik_aktif.nama << endl;    
		cout << "\n\t\t\t     BULAN\TAHUN \t: "<< Listrik_aktif.bln << "/" << Listrik_aktif.tahun << endl;
		cout << "\n\t\t\t     JUMLAH TAGIHAN     : Rp."<< Listrik_aktif.jumlah_tagihan << endl;
		cout << "\n\t\t\t+-----------------------------------+"<< endl;
		
		if (BenarAtauSalah()==true) { konfirm = true; }
    
    return konfirm;
}


 
bool Proses_Pembayaran_Listrik()
{  bool pembayaran;
   pembayaran = false;
   
   if( Input_NoPelanggan() == true )
   {   
       if (Validasi_Pembayaran(no_pelanggan) == true) 
       { 
         if(Konfirmasi_Pembayaran() == true )
         {   
             if(CekSaldo(Listrik_aktif.jumlah_tagihan) == true  )
             {
                N_aktif.saldo = N_aktif.saldo - Listrik_aktif.jumlah_tagihan;
                isi_saldo_baru(N_aktif.no_rek , N_aktif.saldo);
                update_rekening();
                TulisTransaksiLain(N_aktif.no_rek, Listrik_aktif.no_pelanggan, Listrik_aktif.jumlah_tagihan, 1) ;
                pembayaran = true;
             }
          }
       }
   }
   
   return pembayaran;
}

bool Validasi_Pembayaran(char no_pelanggan[11])
{    bool cek_Pembayaran = true;
     
     if((Cek_NoPelanggan(no_pelanggan) == false ) || (cek_status == false))
     {   
         system("cls");
         
         if( Cek_NoPelanggan(no_pelanggan) == false )
         { 
             cout <<"\n\n\n\n\t\t\t.:: NO PELANGGAN TIDAK TERDAFTAR ::.\n\n\n\n\n"; 
         }
         
         else 
         {   
              if( cek_status == false )
              { cout <<"\n\n\n\n\t   .:: TAGIHAN UNTUK NO PELANGGAN \"" << no_pelanggan << "\" SUDAH LUNAS ::.\n\n\n\n\n"; }
         }
         
         if(MenuUlangi() == true) { Switch_MenuPembayaran(1); }
     }
     return cek_Pembayaran;
}

/*--------------------------- END MODUL PEMBAYARAN REKENING LISTRIK -----------------------------*/



/*-------------------------------- 7. MODUL PEMBELIAN VOUCHER PULSA -----------------------------*/

int VoucherPulsa()
{
    if(Proses_VoucherPulsa()==true)
    {
        system("cls");
        cout << "\n\n";
        cout <<"\n\t\t\      .:: TRANSAKSI PEMBELIAN VOUCHER BERHASIL ::.\n\n"; 
        cout <<"\n\t\t\       .:: BERIKUT ID VOUCHER PEMBELIAN ANDA ::.\n\n";
		cout << "\t\t\t+-----------------------------------+"        <<endl;
		cout << "\t\t\t|             "<< id_voucher <<"            |"<<endl;
		cout << "\t\t\t+-----------------------------------+"        <<endl; 
		cout << "\n\n";
    }
}

bool Proses_VoucherPulsa()
{    bool pembelian = false;
     Menu_TypeVoucher();
     Menu_NilaiVoucher(); 
     if(Konfirmasi_Pembelian()==true)
     {
         if(CekSaldo(nilai_voucher) == true)
             {
                
                N_aktif.saldo = N_aktif.saldo - nilai_voucher;
                isi_saldo_baru(N_aktif.no_rek , N_aktif.saldo);
                
                TulisTransaksiLain(N_aktif.no_rek, nama_provider, nilai_voucher, 2);
                pembelian = true;
             }
     }  
     return pembelian;
}

string Random_IdVoucher(char kode[3])
{   char c[1];
    string id_voucher;
    int x;
    id_voucher += kode;
    for(int i =0 ; i<=6 ; i++)
    {     
          x = rand()%10;
          id_voucher += itoa(x, c, 10);
    } 
    return id_voucher;  
}

void Menu_TypeVoucher() {   
    system("cls");
    Tampil_MenuTypeVoucher();
    Switch_MenuTypeVoucher(Input_pilihan());      
}

void Tampil_MenuTypeVoucher()
{   
    system("cls");
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\t\t |          SILAHKAN PILIH TYPE VOUCHER         |"<< endl;
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\n\n";
    cout << "\t\t +-----+";              cout << "\t\t\t          +-----+" << endl;
    cout << "\t\t |  1  | TELKOMSEL";      cout << "\t\t INDOSAT  |  2  | " << endl ;
    cout << "\t\t +-----+";              cout << "\t\t\t          +-----+" << endl;
    cout << "\n";
    cout << "\t\t +-----+";              cout << "\t\t\t          +-----+" << endl;
    cout << "\t\t |  3  | THREE 3";        cout << "\t\t      XL  |  4  | " << endl ;
    cout << "\t\t +-----+";              cout << "\t\t\t          +-----+" << endl;
    cout << "\n"; 
    cout << "\t\t +-----+";              cout << "\t\t\t          +-----+" << endl;
    cout << "\t\t |  5  | ESIA";         cout << "\t\t\t    FREN  |  6  | " << endl ;
    cout << "\t\t +-----+";              cout << "\t\t\t          +-----+" << endl;
    cout << "\n\n"; 
}


int Switch_MenuTypeVoucher(int menu)
{   char kode[3];
    string id;
    switch(menu)
    {
          case 1 : strcpy(kode ,"111");strcpy(nama_provider ,"TELKOMSEL"); break;
          case 2 : strcpy(kode ,"222");strcpy(nama_provider ,"INDOSAT"); break;
          case 3 : strcpy(kode ,"333");strcpy(nama_provider ,"THREE(3)"); break;
          case 4 : strcpy(kode ,"444");strcpy(nama_provider ,"XL"); break;
          case 5 : strcpy(kode ,"555");strcpy(nama_provider ,"ESIA"); break;
          case 6 : strcpy(kode ,"666");strcpy(nama_provider ,"FREN"); break;       
    }
    
    id_voucher = Random_IdVoucher(kode);  
}

void Menu_NilaiVoucher() {   
    system("cls");
    Tampil_MenuNilaiVoucher();
    Switch_MenuNilaiVoucher(Input_pilihan());      
}

void Tampil_MenuNilaiVoucher()
{   
    system("cls");
    cout << "\n";
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\t\t |         SILAHKAN PILIH NILAI VOUCHER         |"<< endl;
    cout << "\t\t +----------------------------------------------+"<< endl;
    cout << "\n";
    cout << "\t\t +-----+";            cout << "\t\t\t          +-----+" << endl;
    cout << "\t\t |  1  | 50.000";     cout << "\t\t\t 100.000  |  2  | " << endl;
    cout << "\t\t +-----+";            cout << "\t\t\t          +-----+" << endl;
    cout << "\n";
    cout << "\t\t +-----+";            cout << "\t\t\t          +-----+" << endl;
    cout << "\t\t |  3  | 200.000";      cout << "\t\t 300.000  |  4  | " << endl;
    cout << "\t\t +-----+";            cout << "\t\t\t          +-----+" << endl;
    cout << "\n";
    cout << "\n";
    cout << "\t\t +-----+" << endl;
    cout << "\t\t |  5  | 500.000" << endl ;
    cout << "\t\t +-----+" << endl;
    cout << "\n\n"; 
}

int Switch_MenuNilaiVoucher(int menu)
{   
    switch(menu)
    {
          case 1 : nilai_voucher = 50000; break;
          case 2 : nilai_voucher = 100000; break;
          case 3 : nilai_voucher = 200000; break;
          case 4 : nilai_voucher = 300000; break;
          case 5 : nilai_voucher = 500000; break;      
    }
}

bool Konfirmasi_Pembelian()
{     bool konfirm;
      konfirm =false;
 	  
        system("cls");
		printf("\n\n");
		cout << "\t\t\t+-----------------------------------+"<<endl;
		cout << "\t\t\t|    Konfirmasi Pembelian Voucher   |"<<endl;
		cout << "\t\t\t+-----------------------------------+"<<endl;
        printf("\n");
		cout << "\n\t\t\t     Nama Provider \t: "<< nama_provider << endl;
		cout << "\n\t\t\t     Nilai Voucher \t: "<< nilai_voucher << endl;    
        cout << "\n\t\t\t+-----------------------------------+"<< endl;
		printf("\n\n");
		
		if (BenarAtauSalah()==true) { konfirm = true; }
    
      return konfirm;
}

/*------------------------------ END MODUL PEMBELIAN VOUCHER PULSA -----------------------------*/
