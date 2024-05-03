/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"
#include "periferikoak.h"
#include "fondoak.h"
#include "spriteak.h"

int t4seg;
int my_hp;
int boss_hp;
int my_dmg;
int boss_dmg;
int EGOERA;
bool ekidinAttacks = false;
 
void tekEten (){ // tekla
	
	if (EGOERA==MENU && SakatutakoTekla()==SELECT){
		erakutsiIstorioa();
		EGOERA=ISTORIOA;
	}

	if(EGOERA == ISTORIOA && SakatutakoTekla() == A){
			my_hp=4;
			my_dmg=2;
			boss_hp=2000;
			t4seg=0;
			EGOERA=ERASOA;
			erakutsiBatalla();	
			Erakutsipj(1,100,100);
			ErakutsiDragon(2,100,100);
	}
	if (EGOERA == IRABAZI || EGOERA == GALDU){
		if(TaktilaSakatuta() == 1 || SakatutakoTekla()==SELECT){
			EGOERA = MENU;
		}
	}
	if(EGOERA==EKIDIN){
		//erakutsiBeharrezkoTekla
		int beharrezkoTekla = rand() % 2; //HAY QUE DEFINIR ZERBITZU ERRUTINAK. RAND % 2 ES UNA FUNCION PARA ELEGIR UN NUMERO RANDOM ENTRE 0 Y 1, A ES 0 Y B ES 1.
		int tekla=SakatutakoTekla();
		switch (beharrezkoTekla){
		case 0:
			//erakutsiABotoia();
			tekla=A;
			
			break;
		case 1:
			//erakutsiBBotoia();
			tekla=B;
			
			break;
		}
		if(SakatutakoTekla()!=tekla){
			ekidinAttacks=false;
		}
	}
}	

void tenpEten(){ // tenporizadorearen zerbitzu  errutina
	if (EGOERA==ERASOA || EGOERA == L || EGOERA == R){
		t4seg++; 
		if (t4seg>=4*15 && EGOERA==ERASOA){
			t4seg=0;
			ekidinAttacks=true;
			EGOERA=EKIDIN;
		}else if(t4seg>=4*15 && (EGOERA==L || EGOERA==R) ){
			EGOERA==ERASOA;
		}
	}
	if(EGOERA == EKIDIN){
		t4seg++;
		if(t4seg == 4*15 && ekidinAttacks==true){
			t4seg = 0;
			EGOERA = ERASOA;
		}else if(t4seg == 4*15 && ekidinAttacks==false && my_hp > 1){
			my_hp--;
			t4seg=0;
			EGOERA == ERASOA;
		}
	}
}

void etenZerbErrutEzarri(){

	irqSet(IRQ_KEYS,tekEten); // teklatuaren etenak baimendu 
	irqSet(IRQ_TIMER0,tenpEten);  // tenporizadorearen etenak baimendu
}

