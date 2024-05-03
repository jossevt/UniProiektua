/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

// Guk garatutako fitxategiak
	
#include "definizioak.h"
#include "periferikoak.h"
#include "zerbitzuErrutinak.h"
#include "fondoak.h"
#include "spriteak.h"


void jokoa01(){ 	
	// Aldagai baten definizioa
	EGOERA=MENU;

	EtenakBaimendu();
	konfiguratuTeklatua(0x4007); //Teklatua konfiguratu behar da, 0x4001 = 0100 0000 0000 0111, 14. etena eta A, B eta Select
	konfiguratuTenporizadorea(30583,0x00C1); // latch = 65536-(1/15)*(33554432/64) = 30583 (15tik segunduko)(33MHz/64, zenbaki negatiborik ezin da atera kenketa egiterakoan)

	etenZerbErrutEzarri();	// Etenen zerbitzu errutinak ezarri behar dira.
	TekEtenBaimendu(); // Teklatuaren etenak baimendu behar dira.
	DenbEtenBaimendu(); // Tenporizadorearen etenak baimendu behar dira.


	iprintf("\x1b[22;5HPartida hasteko sakatu Select tekla edo pantaila ukitu.");	// Hau 22 lerroan eta 5 zutabean hasiko da idazten.
							//Aldagai baten idatzi nahi izanez gero, %d komatxoen barruan eta 
							//komatxoen kanpoan aldagaiaren balioa.
	erakutsiMenu(); // erakutsi menu fondoa

	while(1){
		
		if (EGOERA == MENU && (TaktilaSakatuta() == 1)){
			erakutsiIstorioa();
			EGOERA = ISTORIOA;
		}
		
		if(EGOERA==ERASOA){//Erasotik L ra pasatzea l sakatuz eta etsaiari hp-a kendu
			if(TeklaDetektatu() == 1){
				if(SakatutakoTekla()==L){
					EGOERA=L;
					boss_hp-=my_dmg;
				}
			}
		}else if(EGOERA==L){// L egoeratik R egoerara pasatzea eta etsaiari hp-a kendu
			if(TeklaDetektatu()==1){
				if(SakatutakoTekla()==R){
					EGOERA=R;
					boss_hp-=my_dmg;
					if(boss_hp<=0){ //Boss-aren bizitza negatiboa bada irabazi egoerara aldatu 
						EGOERA == IRABAZI;
						erakutsiIrabaziFondoa();
					}
				}
			}
		}else if(EGOERA == R){//R egoeratik L egoerara pasatzea eta etsaiari hp-a kendu
			if(TeklaDetektatu() == 1){
				if(SakatutakoTekla()==L){
					EGOERA=L;
					boss_hp-=my_dmg;
					if(boss_hp<=0){ //Boss-aren bizitza negatiboa bada irabazi egoerara aldatu 
						EGOERA == IRABAZI;
						erakutsiIrabaziFondoa();
					}
				}
			}
		}
	}
}
