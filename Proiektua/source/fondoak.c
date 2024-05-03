/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia

/* Fondo desberdinak erakutsi nahi izango baditugu, hemen fondo bakoitzaren burukoa (.h fitxategia) gehitu behar da. Buruko horiek
automatikoki sortzen dira, konpilatzerako garaian, baina horretarako gogoratu behar da */

#include "fondoak.h"
#include "grafikoak.h"
#include "batalla.h"
#include "IrabaziFondoa.h"
#include "GalduFondoa.h"
#include "Menu.h"
#include "Istorioa.h"

/* Irudiak memorian kopiatzeko DMA kanala aukeratu (3.a) */
static const int DMA_CHANNEL = 3;

/* Pantailaratu nahi den grafiko bakoitzerako horrelako prozedura bat idatzi behar da */

void erakutsiBatalla() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     batallaBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *)BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     batallaBitmapLen); /* Luzera (bytetan); automatikoki sortzen den aldagaia */
}
void erakutsiIrabaziFondoa() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     IrabaziFondoaBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *)BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     IrabaziFondoaBitmapLen); /* Luzera (bytetan); automatikoki sortzen den aldagaia */
}
void erakutsiGalduFondoa() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     GalduFondoaBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *)BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     GalduFondoaBitmapLen); /* Luzera (bytetan); automatikoki sortzen den aldagaia */
}
void erakutsiMenu() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     MenuBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *)BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     MenuBitmapLen); /* Luzera (bytetan); automatikoki sortzen den aldagaia */
}
void erakutsiIstorioa() {
		
    dmaCopyHalfWords(DMA_CHANNEL,
                     IstorioaBitmap, /* Automatikoki sortzen den aldagaia */
                     (uint16 *)BG_BMP_RAM(0), /* Fondo nagusiaren helbidea */
                     IstorioaBitmapLen); /* Luzera (bytetan); automatikoki sortzen den aldagaia */
}
