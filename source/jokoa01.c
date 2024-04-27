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

int denb; // denbora neurtzen joateko; baloratu ea beharrezkoa den



void jokoa01(){ 	
	// Aldagai baten definizioa
	int i = 9; //Proba bat egiteko
	int tekla = 0;
	EGOERA=0;

	EtenakBaimendu();
	konfiguratuTeklatua(0x4001); //Teklatua konfiguratu behar da, 0x4001 = 0100 0000 0000 0001, 14. etena eta lehenengoa
	konfiguratuTenporizadorea(30583,0x00C1); // latch = 65536-(1/15)*(33554432/64) = 30583 (15tik segunduko)(33MHz/64, zenbaki negatiborik ezin da atera kenketa egiterakoan)
						 // Tenporizadorea konfiguratu behar da.
	etenZerbErrutEzarri();	// Etenen zerbitzu errutinak ezarri behar dira.
	TekEtenBaimendu(); // Teklatuaren etenak baimendu behar dira.
	DenbEtenBaimendu(); // Tenporizadorearen etenak baimendu behar dira.


	iprintf("\x1b[22;5HTestu pantaila probatzen");	// Hau 22 lerroan eta 5 zutabean hasiko da idazten.
							//Aldagai baten idatzi nahi izanez gero, %d komatxoen barruan eta 
							//komatxoen kanpoan aldagaiaren balioa.
	iprintf("\x1b[23;5HAldagai proba, 9 izan beharko luke balioa. Balioa=%d", i);
	erakutsiFondoBat(); // erakutsi menu fondoa

	while(1){
		erakutsiFondoBat();
		if (EGOERA == MENU && (TaktilaSakatuta() == 1 || SakatutakoTekla()==SELECT)){
			EGOERA =ISTORIOA;
			istorioEgoera(); //CON ESTA FUNCION, SE METE DE MANERA RECURSIVA A LA SIGUIENTE EGOERA.
		}
	}
}

void istorioEgoera(){//FALTAN IMPLEMENTAR LOS SPRITES Y HACER LA HISTORIA + ETENA

		while (EGOERA == ISTORIOA){ // ESTA EGOERA VA POR ETENAS, ASI QUE HAY QUE CONFIGURAR LOS ETENSERBITZUAK PARA PASAR A LA SIGUIENTE EGOERA.
			erakutsibatalla();
			tekEten(); //????????
		}
}

//boss_hp -= my_dmg;
void erasoEgoera(){

	int aurrekoPultsazio==L;
	while(EGOERA == ERASOA){// HAY QUE CONFIGURAR EL TEMPORIZADOR PARA QUE VAYA SUMANDO TIEMPO
		
		while (t4seg<=4){
			if (TeklaDetektatu() == 1){
				switch(aurrekoPultsazio){
					case L: 
						if (L_R_Detektatu()==R){
							aurrekoPultsazio==R;
							boss_hp -= my_dmg;
						}
						break;				
					case R:
						aurrekoPultsazio=erasoDetektatu();
						if (aurrekoPultsazio==L){
							boss_hp -= my_dmg;
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
			t4seg++;//????????
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
	
	while (t4seg < 4){ // NO ESTA HECHO EL TIMER (ES UN COPIA PEGA DEL DE ERASOA)
		int beharrezkoTekla = rand() % 2; //HAY QUE DEFINIR ZERBITZU ERRUTINAK. RAND % 2 ES UNA FUNCION PARA ELEGIR UN NUMERO RANDOM ENTRE 0 Y 1, A ES 0 Y B ES 1.
		//falta configurar los etenak en esta egoera.
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