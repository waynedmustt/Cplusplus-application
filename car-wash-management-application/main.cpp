/* file   : main.cpp
	author : Gilang Surya Gumilar (121511011)
				M. Dimas Dewantara   (121511020)
				M. Taufiq Ismail     (121511021)
	tanggal: 02-06-2013
*/

#include "adt.c"

main()
{
  /*Deklarasi */

	Queue parkir,cuci1,cuci2,cuci3;
	Mobil M;
	int jmlh_mobil_di_parkir=0;
	time_t t = time(NULL);
	struct tm * now = localtime(&t);

	/*program */

	/*membuat Queue untuk parkir,tempat cuci 1 ,cuci 2, dan cuci 3*/

	CreateList(&parkir);
	CreateList(&cuci1);
	CreateList(&cuci2);
	CreateList(&cuci3);

	// proses : mengisi tempat cuci , dan parkir selama tempat parkir tidak penuh ,
	// dan mobil yang mendaftar waktu selesainya lebih dari jam 17.00

	int n;
		isidatatipe();

		do
		{
		  clrscr();
		  printf("\t\t      ________   __________   _________ \n");
		  printf("\t\t     /_______/| /_________/| /________/|\n");
		  printf("\t\t    |  _____|/  |   ___   || |   ___  ||\n");
		  printf("\t\t    | ||        |  ||__|  || |  ||__| //\n");
		  printf("\t\t    | ||______  |   ___   || |   ___  ||\n");
		  printf("\t\t    | |/_____/| |  ||  |  || |  ||  | ||\n");
		  printf("\t\t    |_______|/  |__|/  |__|/ |__|/  |_|/\n");

		  printf("\t     ___        ___   __________    ________  ___     ___ \n");
		  printf("\t    /__/|      /__/| /_________/|  /_______/ /__/|   /__/|\n");
		  printf("\t    |  ||      |  || |   ___   || | ______|| |  ||   |  ||\n");
		  printf("\t    |  ||  _   |  || |  ||__|  || | ||____   |  ||___|  ||\n");
		  printf("\t    |  ||_/ \\__|  || |   ___   || |_____  || |   ____   ||\n");
		  printf("\t    |      _      || |  ||  |  ||  /____| || |  ||   |  ||\n");
		  printf("\t    |_____//\\_____|/ |__|/  |__|/ |_______// |__||   |__|/\n");
		  printf("\n\n\t\t\t     ||   1. Input     ||\n");
		  printf("\t\t\t     ||   2. Histori   ||\n ");
		  printf("\t\t\t     ||   3. Tentang   ||\n ");
		  printf("\t\t\t     ||   4. Keluar    ||\n ");
		  printf("\n\t\t\t     Pilihan : "); scanf("%d", &n); printf("\n\n");

		switch(n)
		  {
			case 1 :    clrscr();
							printf("\t\t      ====================================\n");
							printf("\t\t      ||             Car Wash           ||\n");
							printf("\t\t      ||            Kelompok 9          ||\n");
							printf("\t\t      ====================================\n");
							printf("\n\t\tMasukan Nama Mobil  : ");
							scanf("%s",&M.nama);
							printf("\n\t\tMasukan Nomor Mobil : ");
							scanf("%s",&M.nomor);
							M.datang.Hour = now->tm_hour;
							M.datang.Minute = now->tm_min;

							if((jmlh_mobil_di_parkir = NbElmt(parkir))>=6)
							  {
								  clrscr();
								  PopPenuh(&parkir,&cuci1,&cuci2,&cuci3);
									  printf("\t\t      ==========================================\n");
									  printf("\t\t      || Maaf Tempat Cuci kami Sudah Penuh    ||\n");
									  printf("\t\t      || Silakan Tunggu %d jam : %d menit lagi ||\n",tunggu2.Hour,tunggu2.Minute);
									  printf("\t\t      ==========================================\n");

								  printf("\n\n\n\n\tTekan ENTER untuk kembali ke menu...");getch();
								  break;
								}else{
									clrscr();
									Insert(M,&parkir,&cuci1,&cuci2,&cuci3);
									if(caridata(&parkir,&cuci1,&cuci2,&cuci3)==true)
									{
									  clrscr();
									  printf("\t\t        =================================\n");
									  printf("\t\t        || maaf tempat pencucian tutup ||\n");
									  printf("\t\t        =================================\n");

								  printf("\n\n\n\n\tTekan ENTER untuk kembali ke menu...");getch();
								  break;
									}else{
									  if(catat != 4)
									  {
										History(M);
										}
								  }
								}

						printf("\n\n\n\tTekan ENTER untuk kembali ke menu...");getch();
						break;

			 case 2 :  FILE *f;
						  clrscr();
						  if ((f = fopen("LOG.TXT", "rt+")) != NULL)
							 {
								printf("\tNama\tNomor Mobil\t Tanggal\t  Jam\n\n");
								int j = 0;
						 while (!feof(f))
								{
									fscanf(f,"\t%s %s %d/%d/%d %d:%d:%d\n",&M.nama,&M.nomor, &tanggal[j].tgl, &tanggal[j].bln, &tanggal[j].thn, &jam[j].jam, &jam[j].menit, &jam[j].detik,&cleartime);
									printf("\t%s\t %s \t%d/%d/%d\t%02d:%02d:%02d\n",M.nama,M.nomor, tanggal[j].tgl, tanggal[j].bln, tanggal[j].thn, jam[j].jam, jam[j].menit, jam[j].detik,cleartime);
									j++;
								}
							}
								else printf("Gagal membuka file LOG.TXT !\n");
								fclose(f);
								printf("\n\n\n\n\tTekan ENTER untuk kembali ke menu...");getch();
								break;

			case 3  :  clrscr();
						  printf("\t\t\t=================================\n");
						  printf("\t\t\t||           AUTHOR            ||\n");
						  printf("\t\t\t=================================\n");
						  printf("\t\t\t     Gilang Surya Gumilar        \n");
						  printf("\t\t\t     Muhammad Dimas Dewantara    \n");
						  printf("\t\t\t     Muhammad Taufiq Ismail      \n");

						  printf("\n\n\n\n\tTekan ENTER untuk kembali ke menu...");getch();
						  break;

			case 4  :  clrscr();
						  exit(1);

			default :  clrscr();
						  printf("\t\t\t=================================\n");
						  printf("\t\t\t||      maaf pilihan salah     ||\n");
						  printf("\t\t\t=================================\n");
						  printf("\n\n\n\n\tTekan ENTER untuk kembali ke menu...");getch();
						  break;
			}

	  }while(n!=4);

	return 0;
}
