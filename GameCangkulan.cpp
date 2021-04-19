#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

typedef struct {
	char card_type;
	int card_number;
} cangkulan;
	
cangkulan kartu[53];
cangkulan player[53];
cangkulan computer[53];
int totalKartuPlayer, totalKartuComputer, sisaCangkulan;
int kartuTerakhirCangkulan, kartuAwalCangkulan = 15;
char playerName[10];
	
void menu(); 
void PengocokanKartu(); 
void ShowMenuWelcome(); 
void PembagianKartu(); 
void ShowKocokanCangkulan();
void ShowSisaCangkulan(); 
void ShowKartuPlayerComputer(); 
void ShowKartuAwalCangkulan();
void ValidasiKartuPlayer (const char ket[15]); 
int ValidasiKartuPilihanPlayer (const char ket[15]);
int GetPilihanKartuPlayer(); 
void ShowKalimatWrongCard(); 
void PreparationPlayerCard (const char ket[15]); 
int GetPilihanKartuComputer (const char ket[15]); 
void PreparationComputerCard (const char ket[15]); 
void Battle_Stage(); 
void ShowPlayerFightCard(); 
void ShowComputerFightCard(); 
void ShowKalimatVersus(); 
void WinnerLoserCondition(); 
void ShowConditionDisplay (const char ket[5]); 
void ComparingCards (const char ket[15]); 
void ShowDisplay(); 
void help(); 
void gotoxy(int x, int y);
void SetColor (int ForgC);

int main() {
	srand(time(0));
	menu();  
}

void menu() {
    int pilihan;

	system ("cls");
	printf ("======================================================\n");
	SetColor(3);
	printf ("                  PERMAINAN CANGKULAN\n");
	SetColor(15); 
	printf ("======================================================\n");
	printf ("  1. Play Game\n");
	printf ("  2. Informasi Tentang Program\n");
	printf ("  3. Menampilkan History Permainan\n");
	printf ("  4. Exit Game\n");
	printf ("======================================================\n");
	printf (" Input menu: ");
    scanf("%d", &pilihan); 
    SetColor(15);
    
    switch (pilihan) {
    	case 1:
    		{
	    		system("cls");
			    totalKartuPlayer = 7, totalKartuComputer = 7;
				kartuTerakhirCangkulan = 1, sisaCangkulan = 16,
			    printf ("\n\n\n\t\t\tMasukkan Nama Pemain (MAX 9 Huruf): ");
			    scanf("%s", &playerName);
			    
			    PengocokanKartu();
			    ShowMenuWelcome();
				getch();
				PembagianKartu();
				system("cls");
				ShowDisplay();
				ShowKartuAwalCangkulan();
				
				ValidasiKartuPlayer ("VSCangkulan"); 
				PreparationPlayerCard ("VSCangkulan"); 
				
				PreparationComputerCard ("VSCangkulan");
			    Battle_Stage();
			}
			break;
			
    	case 2:
    		{
    			help();
	   			menu();	
			}
    		break;
    		
    	case 3:
    		{
	    		struct data_cangkulan {
					char nama[10];
					char status[10];
				} cangkulan;
		
				system("cls");
				FILE *f_DataCangkulan;
				f_DataCangkulan = fopen ("CANGKULAN.DAT","rb");
				printf ("\n");
				printf ("\n\n\t\tRECORDS\n\n\n\n\n");
				printf ("\tNama Pemain \t\t      Status\n\n");
				
				while ((fread(&cangkulan, sizeof(cangkulan), 1, f_DataCangkulan)) == 1) { 
		           printf ("\t%-30s %-30s \n", cangkulan.nama, cangkulan.status);
		    	}
				
				printf ("\n\n\n\n\n\n\n\nPress ENTER to main menu\n");
			    fclose (f_DataCangkulan);
			    getch();
			    menu();	
			}
		    break;
		    
		case 4:
			exit(0);
			break;
			
		default:
			printf ("Inputan tidak benar!"); 	
			break;
	}
}
	
void PengocokanKartu() {
	int noIndexArray = 1, maximumCardNumber = 14, desimalCardType = 65, totalCardType = 4;
	int totalShuffle = rand () %30000 + 162; // Pengocokan min. = 162; max. = 30162 
	
	for (int i = 1; i <= totalCardType; i++) { // Input setiap number dan type kartu ke array kartu
		for (int cardNumber = 2; cardNumber <= maximumCardNumber; cardNumber++) {
			kartu[noIndexArray].card_type = desimalCardType;
			kartu[noIndexArray].card_number = cardNumber;
			noIndexArray++;
		}
		desimalCardType++;
	}
	
	for (int i = 1; i <= totalShuffle; i++) {
		int index1 = rand () %52 + 1; // Random sebanyak total kartu, tetapi ditulis 52 + 1 != 53
		int index2 = rand () %52 + 1; // karena supaya tidak dapat angka 0, minim: 1
		
		char temporary_type = kartu[index1].card_type; // Swapping
		kartu[index1].card_type = kartu[index2].card_type;
		kartu[index2].card_type = temporary_type;
		
		int temporary_number = kartu[index1].card_number; // Swapping
		kartu[index1].card_number = kartu[index2].card_number;
		kartu[index2].card_number = temporary_number;
	}
}

void ShowMenuWelcome() {
	system("cls");
 	printf ("                                                                               \n");
 	printf ("                                                                               \n");
 	printf ("                                                                               \n");
 	printf ("         xxxxxxxxxx        xxxx       xxx             xxx  xxxxxxxxx           \n");
 	printf ("         xxx    xxx       xx  xx      xxx xxx     xxx xxx  xxx                 \n");
	printf ("         xxx            xxx    xxx    xxx  xxx   xxx  xxx  xxx                 \n");
 	printf ("         xxx  xxxxx    xxx      xxx   xxx   xxx xxx   xxx  xxx xxxxx           \n");
 	printf ("         xxx    xxx   xxx xxxxxx xxx  xxx     xxx     xxx  xxx                 \n");
 	printf ("         xxx    xxx   xxx        xxx  xxx             xxx  xxx                 \n");
 	printf ("         xxxxxxxxxx   xxx        xxx  xxx             xxx  xxxxxxxxx           \n");
 	printf ("                                                                               \n");
 	printf ("                                                                               \n");
 	printf ("    xxxxx    xx    xx    x  xxxxxx  x   x  x     x  x         xx    xx    x    \n");
 	printf ("    x      x    x  x x   x  x       x  x   x     x  x       x    x  x x   x    \n");
 	printf ("    x      x    x  x  x  x  x xxxx  xxx    x     x  x       x    x  x  x  x    \n");
 	printf ("    x      xxxxxx  x   x x  x    x  x  x   x     x  x       xxxxxx  x   x x    \n");
 	printf ("    xxxxx  x    x  x    xx  xxxxxx  x   x  xxxxxxx  xxxxxx  x    x  x    xx    \n");
 	printf ("                                                                               \n");
 	printf ("                                                                               \n");
 	printf ("                                                                               \n");
 	printf ("                  PRESS ENTER TO PLAY THE GAME........                         \n");
}

void PembagianKartu () {
	int totalKartuAwalMain = 7;
	
	for (int index1 = 1; index1 <= totalKartuAwalMain ; index1++) {
		sisaCangkulan--;
		computer[index1].card_type	= kartu[kartuTerakhirCangkulan].card_type;
		computer[index1].card_number = kartu[kartuTerakhirCangkulan].card_number;
		kartuTerakhirCangkulan++;
		sisaCangkulan--;
		player[index1].card_type	= kartu[kartuTerakhirCangkulan].card_type;
		player[index1].card_number	= kartu[kartuTerakhirCangkulan].card_number;
		kartuTerakhirCangkulan++;
	}
}

void ShowKocokanCangkulan () {
	    ShowSisaCangkulan ();
	    gotoxy (75,9);
		printf ("CANGKULAN");
	    gotoxy (75,10);
		printf (" _______ ");
		gotoxy (75,11);
		printf ("|NO.XXX |");
		gotoxy (75,12);
		printf ("|       |");
		gotoxy (75,13);
		printf ("| XXXXX |");
		gotoxy (75,14);
		printf ("|       |");
		gotoxy (75,15);
		printf ("| XXXXX |");
		gotoxy (75,16);
		printf ("|_______|");
}

void ShowSisaCangkulan() {
     gotoxy (76,17);
     printf ("sisa %2d", sisaCangkulan);
}

void ShowKartuPlayerComputer() {
	gotoxy (1,16);
	printf ("%s's Card", playerName); 
	gotoxy (1,1);	
	printf ("Computer's Card"); 
	int koordinatX = 1, koordinatY = 0;
	
	for (int kartuPlayer = 1; kartuPlayer <= totalKartuPlayer; kartuPlayer++) {	
		gotoxy (koordinatX, 18 + koordinatY);
		printf  (" _______ ");
		
		if (kartuPlayer >= 10) {
			gotoxy (koordinatX, 19 + koordinatY);
	    	printf  ("|NO. %d |", kartuPlayer);
		}
		
		else {
			gotoxy (koordinatX, 19 + koordinatY);
	    	printf  ("|NO. %d  |", kartuPlayer);	
		}
		                
		gotoxy (koordinatX, 20 + koordinatY);
		printf  ("|       |");
		gotoxy (koordinatX, 21 + koordinatY);
		 
		if (player[kartuPlayer].card_number == 10) {
			printf ("|   10  |");
		} else {
			if (player[kartuPlayer].card_number == 11) {
				printf ("| Jack  |");
			} else {
				if (player[kartuPlayer].card_number == 12) {
					printf ("| Queen |");
				} else {
					if (player[kartuPlayer].card_number == 13) {
						printf ("|  King |");
					} else {
						if (player[kartuPlayer].card_number == 14) {
							printf ("|   AS  |");
						} else {
							printf ("|   %d   |", player[kartuPlayer].card_number);
						}
						
					}	
				}
			}
		}

	    gotoxy (koordinatX, 22 + koordinatY);
		printf  ("|       |");
		gotoxy (koordinatX, 23 + koordinatY);
		printf  ("|Type: %c|", player[kartuPlayer].card_type);
		gotoxy (koordinatX, 24 + koordinatY);
		printf  ("|_______|");
	
		if (koordinatX >= 60) { 
			koordinatY = koordinatY + 7;
			koordinatX = 1;
		}
		
		else { 
			koordinatX = koordinatX + 10;
		} 
	}
	
	koordinatX = 1;
	koordinatY = 0;
	
	if (totalKartuComputer > 7) {
		koordinatY = totalKartuComputer - 7;
		gotoxy (12,1);
		printf ("(Hidden Computer Cards = %d)", koordinatY); 
	}
	
	for (int kartuComputer = 1; kartuComputer <= totalKartuComputer - koordinatY; kartuComputer++) { 
		gotoxy (koordinatX, 2);
		printf (" _______ ");
		gotoxy (koordinatX, 3);
		printf ("|NO.XXX |");
		gotoxy (koordinatX, 4);
		printf ("|       |");
		gotoxy (koordinatX, 5);
		printf ("| XXXXX |");
		gotoxy (koordinatX, 6);
		printf ("|       |");
		gotoxy (koordinatX, 7);
		printf ("| XXXXX |");
		gotoxy (koordinatX, 8);
		printf ("|_______|");
		koordinatX = koordinatX + 10;
	}
}

void ShowKartuAwalCangkulan() {
	gotoxy (4,17);
	printf ("Press ENTER for the first card:    ");
	getch();
	sisaCangkulan = sisaCangkulan - 1;
	kartuTerakhirCangkulan = kartuTerakhirCangkulan + 1;
    ShowSisaCangkulan ();
    gotoxy (21,10);
	printf (" _______ ");
	gotoxy (21,11);
	printf ("|       |");
	gotoxy (21,12);
	
	if (kartu[kartuAwalCangkulan].card_number == 10) {
		printf ("|   10  |");
	} else {
		if (kartu[kartuAwalCangkulan].card_number == 11) {
			printf ("|  Jack |");
		} else {
			if (kartu[kartuAwalCangkulan].card_number == 12) {
				printf ("| Queen |");
			} else {
				if (kartu[kartuAwalCangkulan].card_number == 13) {
					printf ("|  King |");
				} else {
					if (kartu[kartuAwalCangkulan].card_number == 14) {
						printf ("|   AS  |");
					} else {
						printf ("|   %d   |", kartu[kartuAwalCangkulan].card_number);
					}
				}
			}
		} 
	}
	
	gotoxy (21,13);
	printf ("|       |");
	gotoxy (21,14);
	printf ("|Type: %c|", kartu[kartuAwalCangkulan].card_type);
	gotoxy (21,15);
	printf ("|_______|");	
}

void ValidasiKartuPlayer (const char ket[15]) {
	int kartuPlayer = 1;
			
	if ((strcmp (ket, "VSCangkulan")) == 0) {
		while ((player[kartuPlayer].card_type != kartu[kartuAwalCangkulan].card_type) && kartuPlayer <= totalKartuPlayer) {
			kartuPlayer = kartuPlayer + 1;
		}
		
		if (kartuPlayer > totalKartuPlayer) { 
			gotoxy (1,17);
			printf ("                                    ");
			gotoxy (1,17);
			printf ("You must 'Cangkul' (press ENTER).");
			getch ();
			gotoxy (1,17);
			printf ("                                    ");
			player[kartuPlayer].card_type = kartu[kartuTerakhirCangkulan].card_type;
			player[kartuPlayer].card_number = kartu[kartuTerakhirCangkulan].card_number;
			totalKartuPlayer = totalKartuPlayer + 1;
		    kartuTerakhirCangkulan = kartuTerakhirCangkulan + 1;
		    sisaCangkulan = sisaCangkulan - 1;
		    ShowSisaCangkulan ();
			ShowKartuPlayerComputer ();
			ValidasiKartuPlayer ("VSCangkulan");
		}
	}
	
	if ((strcmp (ket, "VSComputer")) == 0) {
		while ((player[kartuPlayer].card_type != computer[0].card_type) && (kartuPlayer <= totalKartuPlayer)) {
			kartuPlayer = kartuPlayer + 1;
		}
		
		if ((kartuPlayer > totalKartuPlayer) && (sisaCangkulan > 0)) {
			gotoxy (1,17);
			printf ("You must 'Cangkul' (press ENTER).");
			getch ();
			gotoxy (1,17);
			printf ("                                    ");
			player[kartuPlayer].card_type = kartu[kartuTerakhirCangkulan].card_type;
			player[kartuPlayer].card_number = kartu[kartuTerakhirCangkulan].card_number;
			totalKartuPlayer = totalKartuPlayer + 1;
		    kartuTerakhirCangkulan = kartuTerakhirCangkulan + 1;
		    sisaCangkulan = sisaCangkulan - 1;
			ShowSisaCangkulan();
			ShowKartuPlayerComputer();
			ValidasiKartuPlayer ("VSComputer");
		}
		
		if ((kartuPlayer > totalKartuPlayer) && (sisaCangkulan == 0)) {
			gotoxy (1,17);
			printf ("Cangkulan habis! ambil kartu computer!");
			getch();
			player[kartuPlayer].card_type = computer[0].card_type;
			player[kartuPlayer].card_number = computer[0].card_number;
			player[0].card_number = 0;
			computer[0].card_number = 0;
			totalKartuPlayer = totalKartuPlayer + 1;
			ShowKartuPlayerComputer();
			ComparingCards ("ComputerTurn");
		}
	}	
}

int ValidasiKartuPilihanPlayer (const char ket[15]) {
	int pilihanKartuPlayer = GetPilihanKartuPlayer();
	
	if ((strcmp (ket, "VSCangkulan")) == 0) {
		if (player[pilihanKartuPlayer].card_type != kartu[kartuAwalCangkulan].card_type) {
	    	ShowKalimatWrongCard();                            
			pilihanKartuPlayer = ValidasiKartuPilihanPlayer ("VSCangkulan");
		}	
	}
	
	if ((strcmp (ket, "VSComputer")) == 0) {
		if ((player[pilihanKartuPlayer].card_type) != (computer[0].card_type)) {
	    	ShowKalimatWrongCard();
			pilihanKartuPlayer = ValidasiKartuPilihanPlayer ("VSComputer");
		}	
	}
	return pilihanKartuPlayer;
}

int GetPilihanKartuPlayer() {
	int pilihanKartuPlayer;
	
	gotoxy (4,17);
	printf ("                                        ");
	gotoxy (4,17);
	printf ("Choose Card from (No. 1 to No. %d):    ", totalKartuPlayer);
	scanf ("%d", &pilihanKartuPlayer);
	
	if ((pilihanKartuPlayer > totalKartuPlayer) || (pilihanKartuPlayer < 1)) {
        ShowKalimatWrongCard();
        pilihanKartuPlayer = GetPilihanKartuPlayer();
	}
	
	return pilihanKartuPlayer;
}

void ShowKalimatWrongCard() {
    gotoxy (31,12);
    printf ("Salah Pilih type kartu! Pilih lagi!");
    gotoxy (31,13);
    printf ("Press ENTER to continue....");
    getch();
    gotoxy (31,12);
    printf ("                                       ");
    gotoxy (31,13);
    printf ("                                       ");
}

void PreparationPlayerCard (const char ket[15]) {
	int pilihanKartuPlayer;
	
	if ((strcmp (ket, "VSCangkulan") == 0) || (strcmp (ket, "VSComputer") == 0)) {
		pilihanKartuPlayer = ValidasiKartuPilihanPlayer (ket);	
	}
	
	if (strcmp (ket, "ChooseCard") == 0) {
		pilihanKartuPlayer = GetPilihanKartuPlayer();
	}
	
	player[0].card_type = player[pilihanKartuPlayer].card_type;
	player[0].card_number = player[pilihanKartuPlayer].card_number;
	
	for (int kartuPlayer = pilihanKartuPlayer + 1; kartuPlayer <= totalKartuPlayer; kartuPlayer++) { 
		player[kartuPlayer-1].card_type = player[kartuPlayer].card_type;
		player[kartuPlayer-1].card_number = player[kartuPlayer].card_number;
	}
	totalKartuPlayer = totalKartuPlayer - 1;
}

int GetPilihanKartuComputer (const char ket[15]) {
	int pilihanKartuComputer = 1;

	if ((strcmp (ket, "VSCangkulan")) == 0) {
		while ((computer[pilihanKartuComputer].card_type != kartu[kartuAwalCangkulan].card_type) && pilihanKartuComputer <= totalKartuComputer) {
			pilihanKartuComputer = pilihanKartuComputer + 1;
		}
	
		if (pilihanKartuComputer > totalKartuComputer) {
			computer[pilihanKartuComputer].card_type = kartu[kartuTerakhirCangkulan].card_type;
			computer[pilihanKartuComputer].card_number = kartu[kartuTerakhirCangkulan].card_number;
			totalKartuComputer = totalKartuComputer + 1;
		    kartuTerakhirCangkulan = kartuTerakhirCangkulan + 1;
		    sisaCangkulan = sisaCangkulan - 1;
		    ShowSisaCangkulan();
			ShowKartuPlayerComputer();
			pilihanKartuComputer = GetPilihanKartuComputer ("VSCangkulan");
		}	
	}
	
	if ((strcmp (ket, "VSPlayer")) == 0) {
		while ((computer[pilihanKartuComputer].card_type != player[0].card_type) && (pilihanKartuComputer <= totalKartuComputer)) {
			pilihanKartuComputer = pilihanKartuComputer + 1;
		}
		
		if ((pilihanKartuComputer > totalKartuComputer) && (sisaCangkulan > 0)) {
			computer[pilihanKartuComputer].card_type = kartu[kartuTerakhirCangkulan].card_type;
			computer[pilihanKartuComputer].card_number = kartu[kartuTerakhirCangkulan].card_number;
			totalKartuComputer = totalKartuComputer + 1;
		    kartuTerakhirCangkulan = kartuTerakhirCangkulan + 1;
		    sisaCangkulan = sisaCangkulan - 1;
		    ShowSisaCangkulan();
			ShowKartuPlayerComputer();
			pilihanKartuComputer = GetPilihanKartuComputer ("VSPlayer");
		}
		
		if ((pilihanKartuComputer > totalKartuComputer) && (sisaCangkulan == 0)) {
			gotoxy (1,17);
			printf ("Cangkulan habis! computer mengambil kartu player.");
			getch();
			computer[pilihanKartuComputer].card_type = player[0].card_type;
			computer[pilihanKartuComputer].card_number = player[0].card_number;
			player[0].card_number = 0;
			computer[0].card_number = 0;
			totalKartuComputer = totalKartuComputer + 1;
			ShowKartuPlayerComputer();
			ComparingCards ("PlayerTurn");
		}	
	}
	
	if ((strcmp (ket, "Random")) == 0) {
		pilihanKartuComputer = rand () %totalKartuComputer;	
		if (pilihanKartuComputer == 0) {
			pilihanKartuComputer = pilihanKartuComputer + 1;
		}
	}
	
	return pilihanKartuComputer;
}

void PreparationComputerCard (const char ket[15]) {
	int pilihanKartuComputer;
	
	if ((strcmp (ket, "VSCangkulan")) == 0) {
		pilihanKartuComputer = GetPilihanKartuComputer ("VSCangkulan");	
	}
	
	if ((strcmp (ket, "VSPlayer")) == 0) {
		pilihanKartuComputer = GetPilihanKartuComputer ("VSPlayer");	
	}
	
	if ((strcmp (ket, "Random")) == 0) {
		pilihanKartuComputer = GetPilihanKartuComputer ("Random");	
	}
	
	computer[0].card_type = computer[pilihanKartuComputer].card_type;
	computer[0].card_number = computer[pilihanKartuComputer].card_number;
	
	for (int kartuComputer = pilihanKartuComputer + 1; kartuComputer <= totalKartuComputer; kartuComputer++) { // penggeseran kartu untuk lokasi yang kosong akibat pemilihan kartu
		computer[kartuComputer-1].card_type = computer[kartuComputer].card_type;
		computer[kartuComputer-1].card_number = computer[kartuComputer].card_number;
	}
	totalKartuComputer = totalKartuComputer - 1;
}

void Battle_Stage() {
	system("cls");
	ShowDisplay();
	ShowPlayerFightCard();
	ShowComputerFightCard();
	ShowKalimatVersus();
	system("cls");
	ShowDisplay();
	ComparingCards("");	
}

void ShowComputerFightCard() {   
   	gotoxy (9,12);
	printf ("Computer's");   
	gotoxy (11,13);
   	printf ("CARD -->>");
    gotoxy (21,10);
	printf (" _______ ");
	gotoxy (21,11);
	printf ("|       |");
	gotoxy (21,12);
	
	if (computer[0].card_number == 10) {
		printf ("|   10  |");
	} else {
		if (computer[0].card_number == 11) {
			printf ("|  Jack |");
		} else {
			if (computer[0].card_number == 12) {
				printf ("|  Queen|");
			} else {
				if (computer[0].card_number == 13) {
					printf ("|  King |");
				} else {
					if (computer[0].card_number == 14) {
						printf ("|   AS  |");
					} else {
						printf ("|   %d   |", computer[0].card_number);
					}
				}
			}
		}	
	}
	
	gotoxy (21,13);
	printf ("|       |");
	gotoxy (21,14);
	printf  ("|Type: %c|",computer[0].card_type);
	gotoxy (21,15);
	printf ("|_______|");
}

void ShowPlayerFightCard() {
	gotoxy (50,13);
	printf  ("<<-- %s's card", &playerName);
    gotoxy (41,10);
	printf (" _______ ");
	gotoxy (41,11);
	printf ("|       |");
	gotoxy (41,12);
	
	if (player[0].card_number == 10) {
		printf ("|  10   |");
	} else {
		if (player[0].card_number == 11) {
			printf ("| Jack  |");
		} else {
			if (player[0].card_number == 12) {
				printf ("| Queen |");
			} else {
				if (player[0].card_number == 13) {
					printf ("| King  |");
				} else {
					if (player[0].card_number == 14) {
						printf ("|  AS   |");
					} else {
						printf ("|   %d   |", player[0].card_number);
					}
				}
			}	
		}	
	}
	
	gotoxy (41,13);
	printf  ("|       |");
	gotoxy (41,14);
	printf  ("|Type: %c|", player[0].card_type);
	gotoxy (41,15);
	printf ("|_______|");
}

void ShowKalimatVersus() {
	gotoxy (34,12);
	printf ("VS.");
	gotoxy (31,13);
	printf ("<--   -->");	
	
	gotoxy (1,17);
	printf ("                                                      ");
    gotoxy (1,17);
	printf ("    To continue please press ENTER.");
	getch();
	gotoxy (1,17);
	printf ("                                                      ");
}

void ComparingCards (const char ket[15]) {
	if ((player[0].card_number > computer[0].card_number) || (strcmp (ket, "PlayerTurn") == 0)) { // Player Win
		system("cls");
		ShowDisplay();
		PreparationPlayerCard ("ChooseCard");
		system("cls");
		ShowDisplay();
		ShowPlayerFightCard();
		
		if (totalKartuPlayer == 0) {
			getch();
			WinnerLoserCondition();
		}
		
        PreparationComputerCard ("VSPlayer");
        Battle_Stage();
	}
	
	if ((player[0].card_number < computer[0].card_number) || (strcmp (ket, "ComputerTurn") == 0)) { // Player Lose
		PreparationComputerCard ("Random");
		system("cls");
		ShowDisplay();
		ShowComputerFightCard();
		
		if (totalKartuComputer == 0) {
			getch();
			WinnerLoserCondition();
		}
		
		ValidasiKartuPlayer ("VSComputer");
		PreparationPlayerCard ("VSComputer"); 
		Battle_Stage();
	}		
}
       
void WinnerLoserCondition () {
	struct data_cangkulan {
		char nama[10];
		char status[10];
	} cangkulan;
	
	if (totalKartuPlayer == 0) { // Player Win (Game)
	    FILE *f_DataCangkulan; 
	    f_DataCangkulan = fopen("CANGKULAN.DAT","ab");
	    
		strcpy (cangkulan.nama, playerName);
	    strcpy (cangkulan.status, "Win");
	    fwrite (&cangkulan, sizeof(cangkulan), 1, f_DataCangkulan);
	    
	    fclose (f_DataCangkulan);
	    
	    getch();
	    ShowConditionDisplay ("Win");
        menu();
	}

    if (totalKartuComputer == 0) { // Player Lose (Game)
		FILE *f_DataCangkulan; 
	    f_DataCangkulan = fopen("CANGKULAN.DAT","ab");
	    
		strcpy (cangkulan.nama, playerName);
	    strcpy (cangkulan.status, "Lose");
	    fwrite (&cangkulan, sizeof(cangkulan), 1, f_DataCangkulan);
	    
	    fclose (f_DataCangkulan);
	    
	    getch();
	    ShowConditionDisplay ("Lose");
        menu();
	}
}

void ShowConditionDisplay (const char ket[5]) {
	if ((strcmp (ket, "Win")) == 0) {
		system("cls");
	 	printf ("                                                                                 \n");
	 	printf ("                                                                                 \n");
	 	printf ("               xxx       xxx    xxx xxx xxx   xxx     xxx                        \n");
	 	printf ("               xxx       xxx    xxx     xxx   xxx     xxx                        \n");
	 	printf ("                 xxx   xxx      xxx     xxx   xxx     xxx                        \n");
	 	printf ("                    xxx         xxx     xxx   xxx     xxx                        \n");
	 	printf ("                    xxx         xxx xxx xxx   xxx xxx xxx                        \n");
	 	printf ("                                                                                 \n");
	 	printf ("                                                                                 \n");
	 	printf ("               xxx         xxx    xxxxx   xxx xxx     xxx                        \n");
	 	printf ("               xxx   xxx   xxx    xxxxx   xxx  xxx    xxx                        \n");
	 	printf ("               xxx   xxx   xxx    xxxxx   xxx   xxx   xxx                        \n");
	 	printf ("                xxx  xxx  xxx     xxxxx   xxx    xxx  xxx                        \n");
	 	printf ("                  xxx   xxx       xxxxx   xxx     xxx xxx                        \n");
	 	printf ("                                                                                 \n");
	 	printf ("                                                                                 \n");
	 	printf ("                      PRESS ENTER TO MAIN MENU .....                             \n");
		getch ();
	}
	
	if ((strcmp (ket, "Lose")) == 0) {
		system("cls");
		printf ("                                                                                 \n");
		printf ("                                                                                 \n");
	 	printf ("               xxx     xxx    xxx xxx xxx    xxx     xxx                         \n");
	 	printf ("               xxx     xxx    xxx     xxx    xxx     xxx                         \n");
	 	printf ("                xxx   xxx     xxx     xxx    xxx     xxx                         \n");
	 	printf ("                   xxx        xxx     xxx    xxx     xxx                         \n");
	 	printf ("                   xxx        xxx xxx xxx    xxx xxx xxx                         \n");
	 	printf ("                                                                                 \n");
	 	printf ("                                                                                 \n");
	 	printf ("             xxx          xxx xxx xxx   xxxxxxx    xxxxxxxxx                     \n");
	 	printf ("             xxx          xxx     xxx   xxx        xxx                           \n");
	 	printf ("             xxx          xxx     xxx   xxxxxxx    xxx xxx                       \n");
	 	printf ("             xxx xxxxxx   xxx     xxx       xxx    xxx                           \n");
	 	printf ("             xxx xxxxxx   xxx xxx xxx   xxxxxxx    xxxxxxxxx                     \n");
	 	printf ("                                                                                 \n");
	 	printf ("                                                                                 \n");
	 	printf ("                      PRESS ENTER TO MAIN MENU .....                             \n");
		getch ();
	}
}

void ShowDisplay() {
	ShowKocokanCangkulan(); 
	ShowKartuPlayerComputer();
}

void help() {
    int index1;
    
	system("cls");
    printf ("\n\n\n\t\t\tHELP Menu :\n");    
    printf ("\nTerdiri dari 4 daerah field yaitu:\n\n  a). Computer Deck\n\n");
    printf("  b). Player Deck\n\n  c). Battle field\n\n  d). Kocokan Field");
    printf ("\n\n\n Press ENTER to see SCREEN INFO");
    getch();
    system("cls");
    
    //membuat garis skema komputer deck
    for (index1=1;index1<=77;index1++) {
		gotoxy (index1,1);
		printf ("=");
	}
	
    for (index1=1;index1<=6;index1++) {
		gotoxy (1,index1);
		printf ("=");
	}
	
    for (index1=1;index1<=77;index1++) {
		gotoxy (index1,6);
		printf ("=");
	}
	
    for (index1=1;index1<=6;index1++) {
		gotoxy (77,index1);
		printf ("=");
	}
	
	gotoxy (2,4);
	printf ("\t\tC O M P U T E R - D E C K");
	
    //membuat garis skema player deck
    for (index1=1;index1<=77;index1++) {
		gotoxy (index1,19);
		printf ("=");
	}
	
    for (index1=19;index1<=24;index1++) {
		gotoxy (1,index1);
		printf ("=");
	}
	
    for (index1=1;index1<=77;index1++) {
		gotoxy (index1,24);
		printf ("=");
	}
	
    for (index1=19;index1<=24;index1++) {
		gotoxy (77,index1);
		printf ("=");
    }
    
    gotoxy (2,21);
	printf ("\t\tP L A Y E R - D E C K");	
	
    //membuat garis skema kocokan deck	
    for (index1=70;index1<=77;index1++) {
		gotoxy (index1,10);
		printf ("=");
	}
	
    for (index1=10;index1<=16;index1++) {
		gotoxy (70,index1);
		printf ("=");
	}
	
    for (index1=70;index1<=77;index1++) {
		gotoxy (index1,16);
		printf ("=");
	}
	
    for (index1=10;index1<=16;index1++) {
		gotoxy (77,index1);
		printf ("=");
    }	
    
    gotoxy (55,12);
	printf ("KOCOKAN DECK-->");

    //membuat garis skema untuk computer card
    for (index1=21;index1<=28;index1++) {
		gotoxy (index1,10);
		printf ("=");
	}
	
    for (index1=10;index1<=16;index1++) {
		gotoxy (21,index1);
		printf ("=");
	}
	
    for (index1=21;index1<=28;index1++) {
		gotoxy (index1,16);
		printf ("=");
	}
	
    for (index1=10;index1<=16;index1++) {
		gotoxy (28,index1);
		printf ("=");
    }	
    
    gotoxy (23,12);
	printf ("COMP.");
	gotoxy (23,14);
	printf ("CARD");  

    //membuat garis skema untuk player card    
    for (index1=41;index1<=48;index1++) {
		gotoxy (index1,10);
		printf ("=");
	}
	
    for (index1=10;index1<=16;index1++) {
		gotoxy (41,index1);
		printf ("=");
	}
	
    for (index1=41;index1<=48;index1++) {
		gotoxy (index1,16);
		printf ("=");
	}
	
    for (index1=10;index1<=16;index1++) {
		gotoxy (48,index1);
		printf ("=");
    }
    
    gotoxy (43,12);
	printf ("OUR");
	gotoxy (43,14);
	printf ("CARD");   
    
    //membuat garis skema battle field
    for (index1=18;index1<=51;index1++) {
		gotoxy (index1,9);
		printf ("=");
	}
	
    for (index1=9;index1<=17;index1++) {
		gotoxy (18,index1);
		printf ("=");
	}
	
    for (index1=18;index1<=51;index1++) {
		gotoxy (index1,17);
		printf ("=");
	}
	
    for (index1=9;index1<=17;index1++){
		gotoxy (51,index1);
		printf ("=");
    }
    
    gotoxy (2,13);
	printf ("BATTLE FIELD--->");
    
    gotoxy (2,25);
    printf ("Press ENTER to see CARD INFO");
    getch();
    system("cls");
    
    //Petunjuk/ Keterangn simbol kartu
	gotoxy (20,2);
	printf  (" _______ ");
    gotoxy (20,3);
	printf  ("|NO. 10 |");                  
	gotoxy (20,4);
	printf  ("|       |");
	gotoxy (20,5);
	printf ("| Jack  |");
	gotoxy (20,6);
	printf  ("|       |");
	gotoxy (20,7);
	printf  ("|Type: A|");
	gotoxy (20,8);
	printf  ("|_______|");

    printf ("\n\nKeterangan:\n");
    printf ("--- NO. 10 Menunjukkan 'POSISI KARTU'\n");
    printf ("           Fungsi : Agar Player tahu posisi kartu ketika \n");
    printf ("                    Player akan mengambil kartu dari deck\n\n");
    printf ("--- Jack   Menunjukkan 'NILAI KARTU'\n");
    printf ("           Fungsi : Ketika type kartu telah sama maka untuk\n");
    printf ("                    memenangkan 1x fase pertandingan syaratnya\n");
    printf ("                    dengan membandingkan siapa nilai kartu terbesar\n\n");
    printf ("--- Type:A Menunjukkan 'TYPE KARTU'\n");
    printf ("           Fungsi : Jika Player tidak mempunyai kartu yang sama\n");
    printf ("                    dengan type kartu yang ada di 'BATTLE FIELD'\n");
    printf ("                    maka Player harus mengambil kocokan dari 'KOCOKAN DECK'\n");
    gotoxy (2,25);
    printf ("Press ENTER to know 'HOW TO PLAY'");
    getch();
    system("cls");  
    
    printf ("\n\t\t\t'HOW TO PLAY'\n\n\n");
    printf ("1. Player akan dibagikan 7 buah kartu.\n\n");
    printf ("2. Kartu pertama dari kocokkan.\n\n"); 
    printf ("3. Lihat Jenis Kartu (A,B,C,D) pada kartu pertama, jika ada\n"); 
    printf ("   keluarkan Kartu jenis tersebut.\n\n");
    printf ("4. Jika Player/Komputer tidak mempunyai kartu tersebut maka\n"); 
    printf ("   Player/Komputer akan mencangkul hingga jenis kartu tersebut ada.\n\n");
    printf ("5. Bandingkan nilai kartu Player dengan kartu Komputer\n\n");
    printf ("   Jika nilai kartu Player lebih besar dengan nilai kartu\n"); 
    printf ("   Komputer maka Player akan memulai permainan terlebih\n"); 
    printf ("   dahulu di sesi selanjutnya.\n\n");
    printf ("6. Jika nilai Komputer lebih besar maka Komputer akan\n"); 
    printf ("   memulai permainan terlebih dahulu di sesi selanjutnya.\n\n");
    printf ("7. Jika salah satu pemain tidak mempunyai jenis kartu\n"); 
    printf ("   yang sama maka\n");
    printf ("   Player/Komputer akan melakukan seperti No.4.\n\n\n");

    printf ("PEMENANG DITENTUKAN DARI :\n\n");
    printf ("1. Ketika Player/Komputer sedang mencangkul dan kocokkan habis\n"); 
    printf ("   maka kartu yang lebih sedikit jumlahnya akan menjadi pemenang.\n\n"); 
    printf ("2. Jika jumlah kartu Player sama dengan jumlah kartu Komputer\n");
    printf ("   maka draw(tidak ada pemenang)\n\n");
    printf ("3. Pemain yang terlebih dahulu menghabiskan kartu maka\n"); 
    printf ("   pemain tersebut dikatakan memenangkan permainan.\n\n");
    
    printf ("Press ENTER to main menu");
    getch();
    system("cls"); 
}

void gotoxy(int x, int y) {
	HANDLE hConsoleOutput;  
	COORD dwCursorPosition;  
	dwCursorPosition.X = x;  
	dwCursorPosition.Y = y;  
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  
	SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);   
}

void SetColor (int ForgC) {	// Source code: "https://stackoverflow.com/questions/29574849/how-to-change-text-color-and-console-color-in-codeblocks"
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) {
    	wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
     }
}
