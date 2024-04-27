/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"


int tekla; // Sakatutako tekla gordetzeko aldagaia; baloratu ea behar den

int TeklaDetektatu() {
	// TRUE itzultzen du teklaren bat sakatu dela detektatzen badu
	if ((~TEKLAK_DAT & 0x03ff)!=0) return 1;
	else return 0;
}

int SakatutakoTekla() {
	// Sakatutako teklaren balioa itzultzen du: A=0;B=1;Select=2;Start=3;Esk=4;Ezk=5;
	// Gora=6;Behera=7;R=8;L=9;
	if ((~TEKLAK_DAT & 0x4001)==0x4001) return A; // A tekla 
	else if ((~TEKLAK_DAT & 0x4002)==0x4002) return B; // B tekla
	else if ((~TEKLAK_DAT & 0x4004)==0x4004) return SELECT; // SELECT tekla
	else if ((~TEKLAK_DAT & 0x4008)==0x4008) return START; // START tekla
	else if ((~TEKLAK_DAT & 0x4010)==0x4010) return ESKUBI; // ESKUBI noranzko tekla
	else if ((~TEKLAK_DAT & 0x4020)==0x4020) return EZKER; // EZKER noranzko tekla
	else if ((~TEKLAK_DAT & 0x4040)==0x4040) return GORA; // GORA noranzko tekla
	else if ((~TEKLAK_DAT & 0x4080)==0x4080) return BEHERA; // BEHERA noranzko tekla
	else if ((~TEKLAK_DAT & 0x4100)==0x4100) return R; // R tekla
	else if ((~TEKLAK_DAT & 0x4200)==0x4200) return L; // L tekla
}

// |= ????????
void konfiguratuTeklatua(int TEK_konf){
	// Teklatuaren konfigurazioa bere S/I erregistroak aldatuz
	TEKLAK_KNT |= TEK_konf;
}

void konfiguratuTenporizadorea(int Latch, int TENP_konf){
	// Tenporizadorearen konfigurazioa bere S/I erregistroak aldatuz
	DENB0_KNT |= TENP_konf; // 0000 0000 1100 0010
	DENB0_DAT = Latch;
}

void TekEtenBaimendu(){
	// Teklatuaren etenak baimendu
	// Lan hau burutzeko hasieran eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	IE |= 0x00001000; // 12 bitari 1 balioa eman
	IME=1;
}

void TekEtenGalarazi(){

	// Teklatuaren etenak galarazi
	// Lan hau burutzeko hasieran eten guztiak galarazi behar dira eta bukaeran baimendu 
	IME=0;
	IE &= 0xFFFFEFFF; // 12 bitari 0 balioa eman
	IME=1;
}  

void DenbEtenBaimendu(){

// Tenporizadore baten etenak baimendu (Timer0)
// Horretarako hasieran eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	IE |= 0x00000008; // 3 bitari 1 balioa eman	
	IME=1;
}

void DenbEtenGalarazi(){

// Tenporizadore baten etenak galarazi (Timer0)
// Horretarako hasieran eten guztiak galarazi eta bukaeran berriro baimendu
	IME=0;
	IE &= 0xFFFFFFF7; // 3 bitari 0 balioa eman
	IME=1;

}

void ErlojuaMartxanJarri(){
	DENB0_KNT |= 0x0080; // 7 bitari 1 balioa eman
}

void ErlojuaGelditu(){
	DENB0_KNT &= 0xFF7F; // 7 bitari 0 balioa eman
}

//Taktila noiz sakatzen den jakiteko prozedura
int TaktilaSakatuta(){
	touchPosition = pos_pantaila; // aldagaiaren definizioa
	touchRead(&pos_pantaila); // posizioaren irakurketa
	while(pos_pantaila.px==0 && pos_pantaila.py==0){
		touchRead(&pos_pantaila);
	}
	if (pos_pantaila.px!=0 && pos_pantaila.py!=0){
		return 1;
	}
}