/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

// Guk garatutako fitxategiak

#include "grafikoak.h"		
#include "definizioak.h"
#include "spriteak.h"
#include "jokoa01.h"



// //---------------------------------------------------------------------------------
// void main {
// //---------------------------------------------------------------------------------


	
// 	EGOERA = 0;

// 	// Zuen jokoari dei egingo zaio hemendik
// 	while(1){
// 		if (EGOERA == 0 && (TaktilaSakatuta() == 1 || SakatutakoTekla()==SELECT)){
// 			EGOERA =1;
// 			jokoa01();
// 		}
// 	}
// }


//---------------------------------------------------------------------------------
int main(void) {
//---------------------------------------------------------------------------------

	HasieratuGrafikoakSpriteak();
	EtenakBaimendu();

	// Zuen jokoari dei egingo zaio hemendik
	jokoa01();

	return(0);

}