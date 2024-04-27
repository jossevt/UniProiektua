/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"
#include "periferikoak.h"
#include "fondoak.h"
#include "spriteak.h"



void tekEten (){ // tekla

	if(EGOERA == ISTORIOA && SakatutakoTekla() == A){
			my_hp=4;
			my_dmg=2;
			boss_hp=2000;
			t4seg=0;
			EGOERA=ERASOA;	
		 	erasoEgoera();	
	
	}
	
	if(EGOERA == EKIDIN){ // ????? 
		if(beharrezkoTeklaSakatu() == false){ //HAY QUE IMPLEMENTAR
			ekidin_attacks=false;
		}else{kont=kont+1;}
	}
}	

void tenpEten(){ // tenporizadorearen zerbitzu  errutina

	if (EGOERA==ISTORIOA){
		t4seg++; 
		if (t4seg==4*15){
			erakutsiFondoBat();
			t4seg=0;
			ekidin_attacks=true;
			EGOERA=3;
		}
	}		
}

void etenZerbErrutEzarri(){

	irqSet(IRQ_KEYS,tekEten); // teklatuaren etenak baimendu 
	irqSet(IRQ_TIMER0,tenpEten);  // tenporizadorearen etenak baimendu
}

