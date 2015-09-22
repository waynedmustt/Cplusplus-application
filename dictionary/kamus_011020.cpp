/*
    Nama File   : kamus_011020.cpp
    Deskripsi   : Membandingkan kata yang ada di artikel dengan kata yang ada di kamus dan menampilkan 
                  kata-kata yang tidak ada di kamus. Selain itu dapat menghitung jumlah kata pada art-
                  ikel, pencarian kata pada kamus dan memasukkan kata yang tidak ada di kamus pada fi-
                  le lain. 
   Author       : Gilang Surya Gumilar     (121511011)
                  Muhammad Dimas Dewantara (121511020)
   Tanggal      : 21-12-2012
*/

#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#define PANJANG 10000 //menentukan isi array 10000 dengan variabel PANJANG
#define JUM_BLOK 1 // jumlah blok sama dengan 1

//variabel komposit untuk menampung kata yang tidak ada di kamus
typedef struct{
	char kata[30];
	int jml;
}data;
data nonkamus[PANJANG];

//variabel komposit untuk menyimpan kata lain ke file katalain.txt
typedef struct {
                  char kata_lain[30];
               } data_lain;
data_lain daftar;

//variabel global 
char string[PANJANG];
FILE *artikel;
FILE *kamus;
FILE *f_bkkamus;
FILE *f_teks;
FILE *f_teks1;

//modul-modul untuk pembuatan program
void menu();
int cek_kamus(char kata[30]);
void pindah(char kata[30]);
void tampil_nonkamus();
void tampil_artikel();
int cek_artikel(int jumlah);
int kata(int spasi);
int banding(char a[65],char b[65]);
void carikata();
void kamus_lain(char word2[30]);
void tampil_kamus_lain();

//program utama
main()
{
    //memanggil modul menu
    menu();
    getch();
}  

//deklarasi modul menu
void menu()
{
		int pil=0;
          printf("\t=========================================================\n");
		  printf("\t\t|| PROGRAM KAMUS BESAR BAHASA INDONESIA ||\n");
          printf("\t=========================================================\n\n");
		  printf("\t 1. Tampil Artikel \n");
         /*untuk menampilkan statistik kata yang tidak ada di kamus, 
           harus menunggu beberapa detik karena proses pencarian kata yang tidak ada di kamus.*/
		  printf("\t 2. Statistik kata yang tidak ada di kamus\n"); 
		  printf("\t 3. Cari isi kamus \n");
          printf("\t 4. Lihat isi file katalain.txt \n");
          printf("\t 5. Exit \n\n");
		  printf("\tP I L I H A N :  "); scanf("%d",&pil);
		  switch (pil)
			 {
					case 1 : {tampil_artikel();
                              break ; }
                    /*untuk menampilkan statistik kata yang tidak ada di kamus, 
                     harus menunggu beberapa detik karena proses pencarian kata yang tidak ada di kamus.*/           
					case 2 : {tampil_nonkamus();  
					          break ; }
					case 3 : {carikata();
					          break ; }                   
                    case 4 : {tampil_kamus_lain();
                              break;}
                    case 5 : {exit(1);
                              break;}
			 }
}

/*memeriksa apakah kata-kata di artikel ada di kamus, 
jika tidak, maka jumlah kata yang tidak ada pada kamus bertambah*/
int cek_artikel(int jumlah)
{
       char teks[30];
       jumlah=0;
       system("cls");
       if((artikel=fopen("artikel.txt","rt"))!=NULL)
    {
          while(!feof(artikel)){
          fscanf(artikel,"%s",&teks);
            if(cek_kamus(teks)==0){
            jumlah++;
            pindah(teks);                   
            }
                             
          }          
    }
    fclose(artikel);
    return jumlah;
}

//modul menampilkan artikel
void tampil_artikel()
{
  int space;
  int nolsatu;
  system("cls");   
  if((f_teks=fopen("artikel.txt","rt"))== NULL)
	    {
           printf("File tak dapat dibuka!\r\n");
		   exit(1);
	    }
        printf("Artikel :\n\n"); 
        while ((fgets(string, PANJANG, f_teks)) != NULL)
	    printf("%s\n\n", string);
	    printf("jumlah kata dalam artikel     : %d\n\n",kata(space));
	    printf("kembali ke menu(0) :");
	    scanf("%d",&nolsatu);
   if (nolsatu == 0)
	{
	  system("cls");
	  menu();
	}
}

/*fungsi untuk memeriksa apakah kata 
yang di kamus ada yang sama atau tidak di artikel */
int cek_kamus(char kata[30]){
    FILE *kamus;
    char teks[30];
    int cek=0;
    if((kamus=fopen("kbbi.txt","rt"))!=NULL)
    {
          while(!feof(kamus)&&cek ==0){
          fscanf(kamus,"%s",&teks);
             if(strcmp(kata,teks)==0)cek=1;
          }
          
    }
    fclose(kamus);
    return cek;
}

/*modul untuk menampung kata-kata artikel yang tidak sama di kamus.
*/  
void pindah(char kata[30]){
	int x,cek;
	char jawab;
	x=0;
	cek = 0;
	while(nonkamus[x].jml != NULL && cek == 0){
		if(strcmp(nonkamus[x].kata,kata)==0){
			nonkamus[x].jml++;
			cek = 1;
		}
		x++;
	}
	if(cek==0){
	strcpy(nonkamus[x].kata,kata);
		nonkamus[x].jml = 1;
	}
}

//menampilkan kata-kata yang tidak ada di artikel beserta jumlah kata-kata tersebut
/*untuk menampilkan statistik kata yang tidak ada di kamus, 
harus menunggu beberapa detik karena proses pencarian kata yang tidak ada di kamus.*/
void tampil_nonkamus(){
    int x;
	x=0;
	system("cls");
	int amount;    
    int nolsatu;   
    printf("Jumlah kata pada artikel yang tidak ada di kamus        : %d\n\n",cek_artikel(amount));
	while(nonkamus[x].jml != NULL){
		printf("%s : %d\n\n\n",nonkamus[x].kata, nonkamus[x].jml);
		x++;
	}
   printf("kembali ke menu(0) :");
   scanf("%d",&nolsatu);
   if (nolsatu == 0)
	{
	  system("cls");
	  menu();
	} 
}

//menghitung jumlah kata pada artikel dan mengembalikan nilai variabel spasi
int kata(int spasi)
{
    spasi=0;
    FILE *f_teks;
	char string1[PANJANG];
	if((f_teks=fopen("artikel.txt","rt"))== NULL)
	{
		printf("File tak dapat dibuka!\r\n");
		exit(1);
	}
	 while ((fgets(string1, PANJANG, f_teks)) != NULL){
    for (int index = 0; index <= strlen(string1); index++)
	{
		if(isspace (string1[index]) || ispunct (string1[index]))
				{
						spasi++;
				} if (string1[index] == '.' || string1[index] == ',' || string1[index] == '?' || string1[index] == '!')
					{
						spasi--;
					}
     }
     }fclose(f_teks);
     return spasi+1;     
}

//fungsi membandingkan kata-kata yang dicari lewat inputan pada kamus dan bernilai benar jika sama
int banding(char a[65],char b[65])
{


		if(strcmp(a,b)==0)
							{
								return 1;
							}
							else
							{
							return 0;
							}
	}

//modul untuk mencari kata lewat inputan pada kamus
void carikata()
{
  char word[65];
  char word1[65];
	int a;
	int b=0;
	char jawab;
	int nolsatu;
	system("cls");
	kamus=fopen("kbbi.txt","r");
	
    printf("\n masukan kata yang anda cari : ");
	scanf("%s",&word1);
	  while(!feof(kamus))
	{

	  fscanf(kamus,"%s",&word);
	  a=banding(word,word1);
			  if(a==1)
				{b=1;}
	}
 	if(b==1){printf("\n Kata Ada di kamus!\n");}
 	else{
         printf("\n Kata tidak ada di kamus!\n");
         printf("\n Kata sudah disimpan di file katalain.txt!\n");
         kamus_lain(word1);
         
         }
	fclose(kamus);
	printf("\n");
	printf("kembali ke menu(0) :");
	scanf("%d",&nolsatu);
   if (nolsatu == 0)
	{
	  system("cls");
	  menu();
	} 
}

//modul untuk menampung dan menyimpan kata-kata ke file katalain.txt
void kamus_lain(char word2[30])
{
   strcpy(daftar.kata_lain,word2); 
      if ((f_bkkamus=fopen("katalain.txt","ab+")) == NULL)
	    {
		   printf("File tidak dapat dibuat!\r\n");
		   exit(1);
	    }
        fwrite(&daftar, sizeof(daftar),JUM_BLOK,f_bkkamus);
        fclose(f_bkkamus);
}

//menampilkan kata-kata yang ada di file katalain.txt
void tampil_kamus_lain()
{ 
        int nolsatu;
        system("cls");          
          if ((f_bkkamus=fopen("katalain.txt","rb")) == NULL)
	      {
		    printf("File tidak dapat dibuat!\r\n");
		    exit(1);
          }
          printf("\nISI FILE katalain.txt ADALAH : \n\n");
            while((fread(&daftar, sizeof(daftar),JUM_BLOK,f_bkkamus))==JUM_BLOK)
	        printf("%s \r\n", daftar.kata_lain);
            fclose(f_bkkamus);
            printf("\n");
       	    printf("kembali ke menu(0) :");
       	    scanf("%d",&nolsatu);
   if (nolsatu == 0)
	{
	  system("cls");
	  menu();
	} 
}
