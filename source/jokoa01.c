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

int denb; // denbora neurtzen joateko; baloratu ea beharrezkoa den

void jokoa01(){ 	
	// Aldagai baten definizioa
	int tekla = 0;
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

void erasoEgoera(){

	int aurrekoPultsazio==L;
	while(EGOERA == ERASOA){// HAY QUE CONFIGURAR EL TEMPORIZADOR PARA QUE VAYA SUMANDO TIEMPO
		t4seg++;
		while (t4seg<=4){
			if (TeklaDetektatu() == 1){

					case L: 
						if (L_R_Detektatu()==R){
							aurrekoPultsazio==R;
							boss_hp -= my_dmg;
										switch(aurrekoPultsazio){}
						break;				
					case R:
						aurrekoPultsazio=L_R_Detektatu();
						if (aurrekoPultsazio==L){
							
							boss_hp -= my_dmg;
							ezabatuDragon();
							ErakutsiDragon(4,100,100);
						}					
						break;	
					default:
						break;
				}
			}
			if (boss_hp<=0){
				EGOERA = IRABAZI;
				irabaziEgoera();
			}
		}
		EGOERA = EKIDIN;
		ekidinEgoera(); //LLAMADA RECURSIVA A LA EGOERA EKIDIN, CUANDO SALE DE ESTA FASE, VUELVE A EMPEZAR EL BUCLE, ASI NO SE METE INNECESARIAMENTE EN MAS LLAMADAS
	}
}

int L_R_Detektatu(){
	if (SakatutakoTekla() == L){	
		return L;

	}else if (SakatutakoTekla() == R) {
		return R;
	}
}


void ekidinEgoera(){
	
	while (t4seg < 4 && ekidinAttacks){ // NO ESTA HECHO EL TIMER (ES UN COPIA PEGA DEL DE ERASOA)
		int beharrezkoTekla = rand() % 2; //HAY QUE DEFINIR ZERBITZU ERRUTINAK. RAND % 2 ES UNA FUNCION PARA ELEGIR UN NUMERO RANDOM ENTRE 0 Y 1, A ES 0 Y B ES 1.
		switch (beharrezkoTekla){
		case 0:
			erakutsiABotoia();
			char tekla=A;
			
			break;
		case 1:
			erakutsiBBotoia();
			char tekla=B;
			
			break;
		}
		if(SakatutakoTekla()!=tekla){
			ekidinAttacks=false;
		}
	}
	if (!ekidin_attacks){
		my_hp--;
		if(my_hp==0){
			EGOERA=GALDU
			galduEgoera(); // LLAMADA RECURSIVA A LA SIGUIENTE EGOERA.
		}
	}
	EGOERA = ERASOA;
	t4seg = 0;
}




/*
void irabaziEgoera(){
	while (EGOERA== IRABAZI){	
		erakutsiIrabaziFondoa(); //POR DEFINIR
		if (TeklaDetektatu()==1 && (TaktilaSakatuta() == 1 || SakatutakoTekla()==SELECT)){
			EGOERA = MENU;
		}
	}
}

void galduEgoera(){
	while (EGOERA== IRABAZI){	
		erakutsiGalduFondoa(); //POR DEFINIR
		if (TeklaDetektatu()==1 && (TaktilaSakatuta() == 1 || SakatutakoTekla()==SELECT)){
			EGOERA = ISTORIOA; // VUELVE A LA FUNCION DE LA ISTORIA PARA VOLVER A EMPEZAR.
		}
	}

}
*/


// void erasoEgoera(){

// 	int aurrekoPultsazio==L;
// 	while(EGOERA == ERASOA){// HAY QUE CONFIGURAR EL TEMPORIZADOR PARA QUE VAYA SUMANDO TIEMPO
// 		t4seg++;
// 		while (t4seg<=4){
// 			if (TeklaDetektatu() == 1){
// 				switch(aurrekoPultsazio){
// 					case L: 
// 						if (L_R_Detektatu()==R){
// 							aurrekoPultsazio==R;
// 							boss_hp -= my_dmg;
// 						}
// 						break;				
// 					case R:
// 						aurrekoPultsazio=erasoDetektatu();
// 						if (aurrekoPultsazio==L){
// 							boss_hp -= my_dmg;
// 						}					
// 						break;	
// 					default:
// 						break;
// 				}
// 			}
// 			if (boss_hp<=0){
// 				EGOERA = IRABAZI;
// 				irabaziEgoera();
// 			}
// 		}
// 		EGOERA = EKIDIN;
// 		ekidinEgoera(); //LLAMADA RECURSIVA A LA EGOERA EKIDIN, CUANDO SALE DE ESTA FASE, VUELVE A EMPEZAR EL BUCLE, ASI NO SE METE INNECESARIAMENTE EN MAS LLAMADAS
// 	}
// }