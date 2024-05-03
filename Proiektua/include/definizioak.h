// 2023-2024 ikasturtea

/*-------------------------------------
definizioak.h
-------------------------------------*/

#include <nds.h>		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

#define IME		(*(vuint32*)0x04000208) // Interrupt Master Enable -- Eten guztiak baimendu-galarazi
#define IE		(*(vuint32*)0x04000210) // Interrupt Enable -- Etenak banaka baimendu-galarazi
#define IF		(*(vuint32*)0x04000214) // Interrupt Flag -- Eten eskaeren erregistroa

// Etenak tratatzeko funtzioak
#define EtenakBaimendu() IME=1 // Eten guztiak baimendu
#define EtenakGalarazi() IME=0 // Eten guztiak galarazi

// Teklatuaren erregistroak
#define TEKLAK_DAT	(*(vu16*)0x4000130) // Teklatuaren datu-erregistroa
#define TEKLAK_KNT	(*(vu16*)0x4000132) // Teklatuaren kontrol-erregistroa

// Tenporizadorearen (Timer0) erregistroak
#define DENB0_KNT   (*(vuint16*)0x04000102) // Kontrol-erregistroa
#define DENB0_DAT    (*(vuint16*)0x04000100) // Datu-erregistroa



// Ukimen-pantailaren erregistroak
touchPosition PANT_DAT;

// Teklei izena eman diegu zenbakiak nahasgarriak izan daitezkeelako

#define A			0 
#define B			1
#define SELECT			2 
#define START			3
#define ESKUBI			4 
#define EZKER			5
#define GORA			6 
#define BEHERA			7
#define R			8 
#define L			9


extern int EGOERA;
#define MENU  1
#define ISTORIOA 2
#define ERASOA 3
#define EKIDIN 4
#define IRABAZI 5
#define GALDU 6

extern int my_hp; // Pertsonaiaren bizitza finkatzen duen aldagaia
extern int my_dmg; // Pertsonaiaren eraso balioa finkatzen duen aldagaia
extern int boss_hp; // Nagusiaren bizitza finkatzen duen aldagaia
extern int t4seg;   // Lau segundo pasatzen ote diren ikusten joateko
extern bool ekidinAttacks; //Erasoa ekiditea lortu duen edo ez finkatzen duen aldagaia
