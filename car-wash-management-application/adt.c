/* file   : adt.c
	author : Gilang Surya Gumilar (121511011)
				M. Dimas Dewantara   (121511020)
				M. Taufiq Ismail     (121511021)
	tanggal: 02-06-2013
*/

#ifndef adt_C
#define adt_C

#include "adt.h"

#define jeda 10


double dif_sec,cleartime;
Tipe tipe[4];         //  represestasi penampung untuk tipe-tipe mobil
time_t time1,time2;   // variable untuk menampung waktu
T Tanggal,tanggal[10];

J pukul, jam[10];

Jam tunggu;     //  menampung waktu yang paling sebentar dari parkiran
Jam tunggu2;
Jam kosong;
Jam tampung;

int catat;

/* jam untuk menentukan waktu selesai pada mobil di parkiran*/
Jam kesatu; //  Jam selesai dari tempat cuci ke 1
Jam kedua;  //  Jam selesai dari tempat cuci ke 2
Jam ketiga; //  Jam selesai dari tempat cuci ke 3

/* jam untuk melakukan pop dari tempat cuci, dan push dari tempat parkir ketempat cuci
 bila parkiran sudah penuh*/
Jam ke1_pop; //  Jam selesai dari tempat cuci ke 1
Jam ke2_pop;  //  Jam selesai dari tempat cuci ke 2
Jam ke3_pop; //  Jam selesai dari tempat cuci ke 3


void isidatatipe()
{ /*
	I.S. 	: variabel untuk tipe masih kosong
	F.S	: variabel untuk tipe sudah terisi dengan tipe-tipe yang sudah ditentukan
	*/

  //tipe A
	tipe[0].golongan = 'A';
	tipe[0].Durasi.Hour = 1;
	tipe[0].Durasi.Minute = 30;
	tipe[0].Durasi.Second = 0;
	strcpy(tipe[0].Biaya,"50000");

	//tipe B
	tipe[1].golongan = 'B';
	tipe[1].Durasi.Hour = 1;
	tipe[1].Durasi.Minute = 10;
	tipe[1].Durasi.Second = 0;
	strcpy(tipe[1].Biaya,"45000");

	//tipe C
	tipe[2].golongan = 'C';
	tipe[2].Durasi.Hour = 0;
	tipe[2].Durasi.Minute = 50;
	tipe[2].Durasi.Second = 0;
	strcpy(tipe[2].Biaya,"30000");

  //tipe B
	tipe[3].golongan = 'D';
	tipe[3].Durasi.Hour = 0;
	tipe[3].Durasi.Minute = 40;
	tipe[3].Durasi.Second = 0;
	strcpy(tipe[3].Biaya,"22000");

	tipe[4].golongan = ' ';
	tipe[4].Durasi.Hour = 0;
	tipe[4].Durasi.Minute = 0;
	tipe[4].Durasi.Second = 0;
	strcpy(tipe[4].Biaya,"0");
}

int tipemobil(char nama[])
{
  /*
	I.S. 	: nama mobil yang dimasukan menjadi acuan untuk mendapatkan tipenya
	F.S   : mengembalikan nilai urutan tipe mobil sesuai dengan nama mobil yang diinput
  */
		FILE *f;
		char tampung[20];
		int urutan=4;
		int kembali;

		if((f = fopen("data.TXT","rt+")) !=NULL)
				{
					while(!feof(f))
					{
						fscanf(f,"%s %d",&tampung,&kembali);
						if(strcmp(nama,tampung)==0)
							{
								urutan = kembali;
							}

					}
				}
		return urutan;
}

void FindLast(Queue Q,address *P)
{  //mendapatkan address terakhir dari Queue
	(*P) = Front(Q);

	while(Next(*P)!= Nil)
	{
		(*P)=Next(*P);
	}
}

void getwaktutunggu(Queue Q,address *P,Mobil M,Jam *J,Jam *J2)
{
	/*mendapatkan waktu tunggu dari tempat cuci dan menyimpan data mobil kedalam file*/

		(*P) = Front(Q);

	 FindLast(Q,&(*P));
	(*J) = Durasi(*P);
	(*J2) = Durasi(*P);

}

void Insert(Mobil mobil,Queue *parkir,Queue *cuci1,Queue *cuci2,Queue *cuci3)
{
	/*
	I.S.	: Queue dari parkir,cuci1,cuci2,dan cuci3 boleh kosong ataupun tidak
	F.S.	: Queue dari parkir,cuci1,cuci2,atau cuci3 terisi

	 apabila semua tempat cuci telah terisi maka, mobil akan dimasukan kedalam parkir
	 apabila parkir sudah penuh, maka akan dilakukan pencarian waktu durasi paling sebentar dari tempat cuci
	 kemudian mobil dari parkir akan dimasukan kedalam tempat cuci
	*/
	address P,P2,P3;

		if( ListEmpty(*cuci1) && ListEmpty(*cuci2) && ListEmpty(*cuci3))
			{ Push(&(*cuci1),mobil,tunggu);
			  if( !ListEmpty(*cuci1))
				{getwaktutunggu((*cuci1),&P,mobil,&kesatu,&ke1_pop);}
			  struck((*cuci1));
			  }

			else if( !ListEmpty(*cuci1) && ListEmpty(*cuci2) && ListEmpty(*cuci3))
			  { Push(&(*cuci2),mobil,tunggu);
				  if( !ListEmpty(*cuci2)){
				 getwaktutunggu((*cuci2),&P2,mobil,&kedua,&ke2_pop);}
				 struck((*cuci2));
					}
			else if( ListEmpty(*cuci3) && !ListEmpty(*cuci2) && !ListEmpty(*cuci1))
			  { Push(&(*cuci3),mobil,tunggu);
				  if( !ListEmpty(*cuci3)){
				 getwaktutunggu((*cuci3),&P3,mobil,&ketiga,&ke3_pop);}
				 struck((*cuci3));
				 }
			else if( !ListEmpty(*cuci3) && !ListEmpty(*cuci2) && !ListEmpty(*cuci1))
			{
				tunggu = bandingDurasi(kesatu,kedua,ketiga);
				tunggu2 = penambahanJam(tunggu,tunggu2,kosong);
				Push(&(*parkir),mobil,tunggu2);
				struck((*parkir));
				//mengeluarkan struk
				if(catat != 4){
				isiwaktu(&kesatu,&kedua,&ketiga,tunggu,(*parkir));}
			}
}

void PopPenuh(Queue *parkir,Queue *cuci1,Queue *cuci2,Queue *cuci3)
{
	address P,P2;

	tunggu = bandingDurasi(ke1_pop,ke2_pop,ke3_pop);
		if(tunggu.Hour == ke1_pop.Hour &&tunggu.Minute == ke1_pop.Minute )
		{
			Pop(&(*cuci1));
			P = Front(*parkir);
			P2 = Front(*parkir);
			InsertFirst(&(*cuci1),P);
			P2 = Next(P2);
			Front(*parkir) = P2;
			Next(P) = Nil;
		}
		 else	if(tunggu.Hour == ke2_pop.Hour &&tunggu.Minute == ke2_pop.Minute )
		{
			Pop(&(*cuci2));
			P = Front(*parkir);
			P2 = Front(*parkir);
			InsertFirst(&(*cuci2),P);
			P2 = Next(P2);
			Front(*parkir) = P2;
			Next(P) = Nil;
		}
		  else if(tunggu.Hour == ke3_pop.Hour &&tunggu.Minute == ke3_pop.Minute )
		{
			Pop(&(*cuci3));
			P = Front(*parkir);
			P2 = Front(*parkir);
			InsertFirst(&(*cuci3),P);
			P2 = Next(P2);
			Front(*parkir) = P2;
			Next(P) = Nil;
		}
}

boolean caridata(Queue *parkir,Queue *cuci1,Queue *cuci2,Queue *cuci3)
{
	address P1,P2,P3,P4;

	P1 = search(*parkir);
	P2 = search(*cuci1);
	P3 = search(*cuci2);
	P4 = search(*cuci3);

	if(P1 != Nil)
	{
	 DelLast(&(*parkir));
	 return true;
	}

	if(P2 != Nil)
	{
	 DelLast(&(*cuci1));
	 return true;
	}

	if(P3 != Nil)
	{
	 DelLast(&(*cuci2));
	 return true;
	}

	if(P4 != Nil)
	{
	 DelLast(&(*cuci3));
	 return true;
	}

 return false;
}

address search(Queue Q)
{
	Jam cek;
	address P = Front(Q);

	while(P!=Nil)
	{
	 cek = Selesai(P);
	 if(cek.Hour > 17 || cek.Hour < 8)
		{
		 break;
		}
	 P = Next(P);
	}
	return P;

}

void isiwaktu(Jam *J1,Jam *J2,Jam *J3,Jam Banding,Queue Q)
{
  /*
	  I.S.	: variabel J1,J2,J3 masih belum berubah (waktu yang dimiliki masih terisi dengan input sebelumnya)
	  F.S.	: varibel yang sama dengan banding akan diisi dengan waktu dari Durasi mobil
				  dan sebelumnya waktu yang lainnya dikurangi dengan variabel tersebut
  */

  address P = Front(Q);

  while(Next(P)!=NULL)
  {
		P = Next(P);
  }

  if((*J1).Hour ==Banding.Hour && (*J1).Minute ==Banding.Minute )
  {
	  (*J2) = penguranganJam((*J2),(*J1));
	  (*J3) = penguranganJam((*J3),(*J1));
	  (*J1) = Durasi(P);
  }
	else if((*J2).Hour ==Banding.Hour && (*J2).Minute ==Banding.Minute )
  {
	  (*J1) = penguranganJam((*J1),(*J2));
	  (*J3) = penguranganJam((*J3),(*J2));
	  (*J2) = Durasi(P);
  }
  else if((*J3).Hour ==Banding.Hour && (*J3).Minute ==Banding.Minute )
  {
	  (*J1) = penguranganJam((*J1),(*J3));
	  (*J2) = penguranganJam((*J2),(*J3));
	  (*J3) = Durasi(P);
  }
}

Jam bandingDurasi(Jam ke1,Jam ke2,Jam ke3)
  {
	  // modul untuk mencari jam paling sebentar diantara ke1,ke2,dan ke3
	 int a,b,c,d;


	 if(ke1.Hour>0)
	 { d = ke1.Hour;
		a = 60 + (60*d);}
		else{ a = 0; }	a = a + ke1.Minute;

	if(ke2.Hour>0)
	 { d = ke1.Hour;
		b = 60 + (60*d);}
		else{ b = 0; } 	b = b + ke2.Minute;

		if(ke3.Hour>0)
	 { d = ke3.Hour;
		c = 60 + (60*d);}
		else{ c = 0; }   	c = c + ke3.Minute;

	  if(a<b)
	  {
		 if(a<c)
		 {
			return ke1;
		 }else{
			return ke3;
		 }
	  }else{
		 if(b<c){
			return ke2;
		 }else{
			return ke3;
		 }
	  }
  }

Jam penguranganJam(Jam ke1,Jam ke2)
{
	// mengurangi Jam ke1 dengan Jam ke2
	  Jam t;
	  t.Minute =0;
	  t.Hour =0;

		if(ke1.Hour>0)
		{ ke1.Minute = (60*ke1.Hour)+ ke1.Minute;}
		if(ke2.Hour>0)
		{ ke2.Minute = (60*ke2.Hour)+ke2.Minute;}

		t.Minute = ke1.Minute - ke2.Minute;
	  t = convertmin(t);
	 return t;
 }

Jam convertmin(Jam J)
{ // mengkonversi waktu menit ke dalam jam bila lebih dari 60
  while(J.Minute>60){
	 J.Minute-=60;
	 J.Hour = 1 + J.Hour;
  }
  return J;
}

Jam penambahanJam(Jam ke1,Jam ke2,Jam ke3)
  {
	 // nilai kembalian dari pengurangan jam berupa integer dimaksudkan untuk memudahkan
	 // perbandingan
	 Jam J;
	 J.Minute = 0;
	 J.Hour = 0;

	  J.Minute = ke1.Minute + ke2.Minute+ke3.Minute;
	  J.Hour = ke1.Hour + ke2.Hour + ke3.Hour;

	  J = convertmin(J);
	 return J;
  }

void History(Mobil mobil)
{    // modul untuk menyimpan catatan mobil yang melakukan pencucian di dalam file
		FILE *FWaktu;
		time_t t = time(NULL);
		struct tm * now = localtime(&t);

				Tanggal.tgl = now->tm_mday;
				Tanggal.bln = now->tm_mon + 1;
				Tanggal.thn = now->tm_year + 1900;

				pukul.jam = now->tm_hour;
				pukul.menit = now->tm_min;
				pukul.detik = now->tm_sec;

		  if ((FWaktu = fopen("LOG.TXT", "ab")) != NULL)
				{
				 fprintf(FWaktu, "%s %s %d/%d/%d %d:%d:%d\n",mobil.nama,mobil.nomor,Tanggal.tgl, Tanggal.bln, Tanggal.thn, pukul.jam, pukul.menit, pukul.detik);
				}
	  fclose(FWaktu);
}


void struck(Queue Q)
{
  int hitung;
  int awal=0,akhir=13;
  char Terbilang[10]="123456789";
  char *A[]={"SATU","DUA","TIGA","EMPAT","LIMA","ENAM","TUJUH","DELAPAN","SEMBILAN"};
  char *B[]={"SE","BELAS"," PULUH ","RATUS"," RIBU "};
  char rupiah[7] = "RUPIAH";
  char angka2[30];
  char angka_fix1, angka_fix2;
  char angka3[50] = " ";
  address P=Front(Q);
  int i;
  time_t t = time(NULL);
  struct tm * now = localtime(&t);

  Tanggal.tgl = now->tm_mday;
  Tanggal.bln = now->tm_mon + 1;
  Tanggal.thn = now->tm_year + 1900;
	hitung = NbElmt(Q);
		if(hitung>1)
		{
			  while(Next(P)!=NULL)
			 {
				P = Next(P);
				}
		}
	if(!ListEmpty(Q)){
	//print struck
	printf("\n\n\t\t\t====================================\n");
	printf("\t\t\t||            CAR WASH            ||\n");
	printf("\t\t\t||           KELOMPOK 9           ||\n");
	printf("\t\t\t||                                ||\n");
	printf("\t\t\t||           %d/%d/%d             ||\n",Tanggal.tgl,Tanggal.bln,Tanggal.thn);
	printf("\t\t\t||                                ||\n");
	awal = strlen(Nama(P));
	printf("\t\t\t||    NAMA MOBIL  : %s",Nama(P));
	while(awal<=akhir)
	{
	printf(" ");
	awal++;
	}
	printf("||\n");
	awal = strlen(Nomor(P));
	printf("\t\t\t||    NOMOR MOBIL : %s",Nomor(P));
	while(awal<=akhir)
	{
	printf(" ");
	awal++;
	}
	printf("||\n");
	printf("\t\t\t||    JAM MASUK   : %02i:%02i\t  ||\n",Datang(P).Hour,Datang(P).Minute);
	printf("\t\t\t||    JAM CUCI    : %02i:%02i\t  ||\n",Mulai(P).Hour,Mulai(P).Minute);
	printf("\t\t\t||    JAM SELESAI : %02i:%02i\t  ||\n",Selesai(P).Hour,Selesai(P).Minute);
	awal = strlen(Biaya(P));
	printf("\t\t\t||    BIAYA       : %s",Biaya(P));

	strcpy(angka2,Biaya(P));
	while(awal<=akhir)
	{
	printf(" ");
	awal++;
	}
	printf("||\n");
	angka_fix1 = angka2[0];
	angka_fix2 = angka2[1];

  printf("\t\t\t||    TERBILANG   :               ||\n");
  for(i=0;i<10;i++){
	  if(angka_fix1 == Terbilang[i]){
		 strcat(angka3,A[i]);
		 strcat(angka3,B[2]);
	  }
		if(angka_fix2 == Terbilang[i]){
					strcat(angka3,A[i]);
					strcat(angka3,B[4]);
					strcat(angka3,rupiah);
					printf("\t\t\t||  %s",angka3);
					awal = strlen(angka3);
					while(awal<30)
					{
					  printf(" ");
					  awal++;
					}
					printf("||\n");
					break;
	  }
  }
	  if(angka_fix2 == '0'){
				  strcat(angka3,B[4]);
				  strcat(angka3,rupiah);
				  printf("\t\t\t||  %s",angka3);
				  awal = strlen(angka3);
					while(awal<30)
					{
					  printf(" ");
					  awal++;
					}
					printf("||\n");
			  }
	printf("\t\t\t||                                ||\n");
	printf("\t\t\t||                                ||\n");
	printf("\t\t\t||         |TERIMA KASIH|         ||\n");
	printf("\t\t\t||  ----------------------------  ||\n");
	printf("\t\t\t|| |KEPUASAN ANDA PRIORITAS KAMI| ||\n");
	printf("\t\t\t||  ----------------------------  ||\n");
	printf("\t\t\t====================================\n");
	}
	else
	{
		clrscr();
		printf("\t\t     ===========================================\n");
		printf("\t\t     || maaf mobil belum terdaftar dalam list ||\n");
		printf("\t\t     ===========================================\n");

	}

}


// ADT QUEUE

boolean ListEmpty(Queue  Q)
{  /*  Mengirim true jika List kosong  */

		return(Front(Q)==Nil && Rear(Q)==Nil);
}

/* Pembuatan  List Kosong  */
void CreateList(Queue *Q)
{  /* I.S  :  Sembarang    		*/
	/* F.S  :  Terbentuk  List kosong  	*/
	Front(*Q)=Nil;
	Rear(*Q)=Front(*Q);
}

/* ********  MANAJEMEN MEMORY  ********* */
address Alokasi(Mobil  X,Jam tunggu)
{/* Mengirimkan  address  hasil alokasi    sebuah elemen */
 /* Jika alokasi  berhasil, maka  address tidak nil, dan misalnya  */
 /* menghasilkan   P               */
 /* Jika alokasi  gagal,  mengirimkan  Nil 			   */
	address P;
	int urutan;
	P=(address)malloc(sizeof(Mobil));
	urutan= tipemobil(X.nama);
	catat = urutan;
	if(P!=Nil) {
	  if(urutan != 4){
		 Datang(P)	= X.datang;
		 strcpy(Nomor(P),X.nomor);
		 strcpy(Nama(P),X.nama);
		 Durasi(P)	= tipe[urutan].Durasi;
		 strcpy(Biaya(P),tipe[urutan].Biaya);
		 Golongan(P)= tipe[urutan].golongan;
		 Mulai(P)	= convertmin(penambahanJam(kosong,tunggu,X.datang));
		 Mulai(P).Minute = Mulai(P).Minute+jeda;
		 Mulai(P) = convertmin(Mulai(P));
		 Selesai(P) = convertmin(penambahanJam(tipe[urutan].Durasi,Mulai(P),kosong));
			 Next(P)=Nil;
		 }
		 else{
		  P = Nil;
		 }
	}
	return P;
}

void Dealokasi(address *P)
{ /* I.S  : P terdefinisi      				*/
  /* F.S  : P dikembalikan ke  sistem 			*/
  /*   	    Melakukan dealokasi, pengembalian address P */
	 Next(*P)=Nil;
	 (*P) = Nil;
	 free(*P);
}

void InsVLast(Queue *Q, Mobil X,Jam tunggu)
{ /* I.S  : L mungkin kosong          */
  /* F.S  : Melakukan alokasi sebuah elemen dan                */
  /*        menambahkan elemen list di akhir; elemen terakhir  */
  /*        yang baru bernilai X jika alokasi berhasil,        */
  /*	    Jika alokasi gagal: I.S = F.S		       */
	  //Jam cek;
	  int hitung;
	  address P=Alokasi(X,tunggu);
		  if(P!= Nil)
	  {
	  InsertLast(&(*Q),P);
		}else if(P==Nil){
			if((hitung=NbElmt(*Q))<2)
			{
				 Front(*Q) = Nil;
			}
		}

}

/* *** Penghapusan Elemen  ***  */

void InsVFirst(Queue *Q,Mobil X,Jam tunggu)
{  /* I.S  : L mungkin kosong          */
	/* F.S  : Melakukan alokasi sebuah elemen dan             */
	/*        menambahkan elemen pertama dengan nilai X jika  */
	/*        Alokasi berhasil 				     */
	address P=Alokasi(X,tunggu);
	if(P!=Nil) { /* Alokasi Berhasil */
		InsertFirst(&(*Q),P);
	 }
}

void InsertFirst(Queue *Q, address P)
{ /* I.S   : Sembarang, P sudah dialokasi		*/
  /* F.S   : Menambahkan elemen ber-address P, sebagai  */
  /*         elemen pertama				*/

	 Next(P)=Front(*Q);
	 Front(*Q)=P;
}


void DelVFirst(Queue *Q)
{ /* I.S    : List tidak kosong  		                 */
  /* F.S    : Elemen pertama List dihapus, nilai info disimpan   */
  /*	      pada X dan alamat elemen pertama  di-dealokasi 	 */
  /* Kamus */
  address  P;

  DelFirst(&(*Q),&P); /* Hapus elemem pertama, blm didealokasi */
		/* info dari First disimpan di X       */
  Dealokasi(&P);
}

/* *******  PRIMITIF BERDASARKAN ALAMAT ********	*/
/* Penambahan Elemen Berdasarkan Alamat 		*/

void InsertLast(Queue *Q, address P)
{ /* I.S   : Sembarang, P sudah dialokasi			*/
  /* F.S   : P ditambahkan  sebagai elemen terakhir yang baru	*/

		address Last;
		if(ListEmpty(*Q)) { /* Jika kosong, Insert elemen pertama */
		InsertFirst(&(*Q),P);
		}
		else { /* tdk kosong */
		 Last=Front(*Q);
		 while(Next(Last)!= Nil)
		  {	Last = Next(Last); }
		  Next(Last) = P;
		}
		Rear(*Q)=P;
}

/* ****** PENGHAPUSAN SEBUAH ELEMEN	*********   */
void DelFirst (Queue *Q, address *P)
{ /* I.S   : List tidak kosong 	*/
  /* F.S   : P adalah alamat elemen pertama list sebelum penghapusan */
  /*         Elemen List berkurang satu (mungkin menjadi kosong)     */
  /* First elemen yang baru adalah suksesor elemen pertama yang lama */

		*P=Front(*Q);
		Front(*Q)=Next(Front(*Q));
		Next(*P)=Nil;

 }

void DelLast (Queue *Q)
{ /* I.S   : List tidak kosong 	*/
  /* F.S   : P adalah alamat elemen terakhir list sebelum penghapusan */
  /*         Elemen List berkurang satu (mungkin menjadi kosong)     */
  /* Last elemen yang baru adalah suksesor elemen pertama yang lama */
  address P;

		P=Front(*Q);
		while(Next(P)!=Nil)
		{
			P=Next(P);
		}
		Dealokasi(&P);
 }


/* *************PROSES SEMUA ELEMEN ****************   */
void PrintInfo(Queue Q)
{ /* I.S   : List mungkin kosong 	*/
  /* F.S   : Jika list tidak kosong, semua info yang disimpan pada */
  /*         elemen list di-print			  	   */
  /*         Jika list kosong, hanya menuliskan "List Kosong"	   */
  address P=Front(Q);
  if( P==Nil) {
	  printf("List Kosong !\n");
  } else { /* List tidak kosong */
			 do {
		  printf("nomor :%s\n",Nomor(P));
		  printf("Nama :%s\n",Nama(P));
		  printf("datang :  %02i:%02i\n",Datang(P).Hour,Datang(P).Minute);
		  printf("selesai:  %02i:%02i\n",Selesai(P).Hour,Selesai(P).Minute);
		  printf("mulai:  %02i:%02i\n",Mulai(P).Hour,Mulai(P).Minute);
		  printf("durasi:  %02i:%02i\n",Durasi(P).Hour,Durasi(P).Minute);

		  P=Next(P);
		 } while(P!=Nil);
	 }
  printf("\n");
}

int NbElmt(Queue Q)
{ /* Mengirimkan banyaknya elemen list, mengirimkan Nol jika kosong */
  address P;
  int NbEl=0;
  if(ListEmpty(Q)){
	return 0;
  } else { /* Tidak kosong */
			P=Front(Q);
					do {
			 NbEl++;
			 P=Next(P);
			}while(P!=Nil);
	}
		 return NbEl;
}

void Push(Queue *Q, Mobil X,Jam tunggu){
/* Mengisi queue di last list*/
	InsVLast(&(*Q),X,tunggu);
}
void Pop(Queue *Q){
/* Mengisi queue di last list*/
	DelVFirst(&(*Q));
}
#endif
