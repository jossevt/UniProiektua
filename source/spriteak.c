/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		// NDS-rako garatuta dagoen liburutegia
#include <stdio.h>		// C-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		// C-ko liburutegi estandarra memoria erreserbak eta zenbaki bihurketak egiteko
#include <unistd.h>		// Sistema eragileen arteko bateragarritasuna ziurtatzeko liburutegia
#include "spriteak.h"
#include "definizioak.h"

u16* gfxpj;
u16* gfxpjUP;
u16* gfxpjDOWN;
u16* gfxdragon;
u16* gfxdragonF;

/* Pantailan erakutsi nahi den sprite bakoitzeko memoria erreserbatu.*/
void memoriaErreserbatu()
{
	/* Pantaila nagusian gehitu nahi den sprite bakoitzarentzako horrelako bat egin behar da. */
	gfxpj= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxpjUP= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxpjDOWN= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdragon= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxdragonF= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
}

/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu PANTAILA NAGUSIAN. 0 balioa gardena da 
   eta definitu gabeko balioak beltzak. SPRITEARI KOLOREAK ESLEITZEKO ALDATU*/
void PaletaNagusiaEzarri() {
	SPRITE_PALETTE[1] = RGB15(31,0,0); // 1 baliodun pixelak gorriak izango dira.
	SPRITE_PALETTE[2] = RGB15(31,31,0); // 2 baliodun pixelak horiak izango dira.
	SPRITE_PALETTE[3] = RGB15(0,0,0); // 3 baliodun pixelak beltzak izango dira.
	SPRITE_PALETTE[4] = RGB15(19,0,4); // 3 baliodun pixelak granateak izango dira.
	SPRITE_PALETTE[5] = RGB15(25,0,0); // 3 baliodun pixelak marroiak izango dira.
	SPRITE_PALETTE[6] = RGB15(31,19,25); // 3 baliodun pixelak arrosak izango dira.
	SPRITE_PALETTE[7] = RGB15(31,31,19); // 3 baliodun pixelak hori argiak izango dira.
	SPRITE_PALETTE[8] = RGB15(16,16,16); // 3 baliodun pixelak grisak izango dira.
	SPRITE_PALETTE[9] = RGB15(25,25,25); // 3 baliodun pixelak gris argiak izango dira.
	SPRITE_PALETTE[10] = RGB15(8,8,8); // 3 baliodun pixelak gris ilunak izango dira.
	SPRITE_PALETTE[11] = RGB15(0,16,16); // 3 baliodun pixelak berde urdinxkak izango dira.
	}

/* 16x16 pixeleko Sprite baten definizioa erronbo bat marrazteko */
/* Memoriako bankuek duten lan egiteko modua dela eta, lehenengo lau lerroak goiko
   ezkerreko koadrantean erakusten dira, hurrengo lauak goiko eskuineko kuadrantean,
   hurrengo lauak beheko ezkerreko koadrantean eta azkeneko lauak beheko eskuineko koadrantean. 
   Alboko irudian ikusten den bezala. */

u8 pj[256] = 
{
	0	,	0	,	6	,	6	,	6	,	0	,	6	,	6	,	6	,	6	,	1	,	1	,	6	,	6	,	9	,	11	,	//	0	0	6	6	6	0	6	6	6	6	6	6	0	0	0	0
6	,	6	,	1	,	6	,	6	,	9	,	9	,	11	,	6	,	6	,	6	,	6	,	6	,	6	,	9	,	9	,	//	6	6	1	1	6	6	9	11	10	11	10	11	6	0	0	0
6	,	6	,	0	,	6	,	6	,	9	,	6	,	6	,	0	,	0	,	0	,	6	,	9	,	10	,	24	,	24	,	//	6	6	1	6	6	9	9	11	9	11	10	11	6	0	0	0
0	,	0	,	0	,	6	,	9	,	10	,	24	,	6	,	0	,	0	,	0	,	6	,	6	,	9	,	24	,	6	,	//	6	6	6	6	6	6	9	9	9	10	10	6	6	0	6	0
6	,	6	,	6	,	6	,	0	,	0	,	0	,	0	,	10	,	11	,	10	,	11	,	6	,	0	,	0	,	0	,	//	6	6	0	6	6	9	6	6	6	6	6	6	0	6	9	6
9	,	11	,	10	,	11	,	6	,	0	,	0	,	0	,	9	,	10	,	10	,	6	,	6	,	0	,	6	,	0	,	//	0	0	0	6	9	10	24	24	24	24	24	9	0	6	10	6
6	,	6	,	6	,	6	,	0	,	6	,	9	,	6	,	24	,	24	,	24	,	9	,	0	,	6	,	10	,	6	,	//	0	0	0	6	9	10	24	6	24	24	6	9	0	6	9	6
24	,	24	,	6	,	9	,	0	,	6	,	9	,	6	,	24	,	24	,	6	,	9	,	0	,	6	,	9	,	6	,	//	0	0	0	6	6	9	24	6	24	24	6	9	0	6	9	6
0	,	0	,	0	,	0	,	6	,	9	,	24	,	24	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	//	0	0	0	0	6	9	24	24	24	24	24	9	0	6	10	6
6	,	6	,	9	,	10	,	10	,	6	,	9	,	10	,	0	,	0	,	6	,	11	,	6	,	6	,	9	,	9	,	//	6	6	6	6	6	6	6	6	9	9	6	6	6	6	9	6
6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	24	,	24	,	6	,	6	,	9	,	9	,	//	6	6	9	10	10	6	9	10	10	9	10	6	6	20	20	20
6	,	6	,	24	,	24	,	6	,	6	,	20	,	20	,	0	,	0	,	6	,	6	,	0	,	6	,	9	,	9	,	//	0	0	6	11	6	6	9	9	10	6	10	6	11	6	24	6
24	,	24	,	24	,	9	,	0	,	6	,	10	,	6	,	9	,	9	,	6	,	6	,	6	,	6	,	9	,	6	,	//	6	6	6	6	6	6	6	6	6	6	6	11	6	11	20	6
10	,	9	,	10	,	6	,	6	,	20	,	20	,	20	,	10	,	6	,	10	,	6	,	11	,	6	,	24	,	6	,	//	6	6	24	24	6	6	9	9	10	10	10	6	0	6	6	0
6	,	6	,	6	,	11	,	6	,	11	,	20	,	6	,	10	,	10	,	10	,	6	,	0	,	6	,	6	,	0	,	//	6	6	24	24	6	6	20	20	6	6	20	6	0	0	0	0
6	,	6	,	20	,	6	,	0	,	0	,	0	,	0	,	6	,	6	,	9	,	9	,	6	,	0	,	0	,	0	,	//	0	0	6	6	0	6	9	9	6	6	9	9	6	0	0	0
};

u8 pjUP[256] = 
{
	0	,	0	,	6	,	6	,	6	,	0	,	6	,	6	,	6	,	6	,	1	,	1	,	6	,	6	,	9	,	11	,	//	0	0	6	6	6	0	6	6	6	6	0	0	0	0	0	0
6	,	6	,	1	,	6	,	6	,	9	,	9	,	11	,	6	,	6	,	6	,	6	,	6	,	6	,	9	,	9	,	//	6	6	1	1	6	6	9	11	6	6	6	6	0	0	0	0
6	,	6	,	0	,	6	,	6	,	9	,	6	,	6	,	0	,	0	,	0	,	6	,	9	,	10	,	24	,	24	,	//	6	6	1	6	6	9	9	11	6	9	6	6	0	0	0	0
0	,	0	,	0	,	6	,	9	,	10	,	24	,	6	,	0	,	0	,	0	,	6	,	6	,	9	,	24	,	6	,	//	6	6	6	6	6	6	9	9	9	6	9	6	0	0	0	0
6	,	6	,	0	,	0	,	0	,	0	,	0	,	0	,	6	,	6	,	6	,	6	,	0	,	0	,	0	,	0	,	//	6	6	0	6	6	9	6	6	6	6	6	9	6	0	0	0
6	,	9	,	6	,	6	,	0	,	0	,	0	,	0	,	9	,	6	,	9	,	6	,	0	,	0	,	0	,	0	,	//	0	0	0	6	9	10	24	24	24	24	24	6	9	6	0	0
6	,	6	,	6	,	9	,	6	,	0	,	0	,	0	,	24	,	24	,	24	,	6	,	9	,	6	,	0	,	0	,	//	0	0	0	6	9	10	24	6	24	24	6	9	6	9	6	0
24	,	24	,	6	,	9	,	6	,	9	,	6	,	0	,	24	,	24	,	6	,	9	,	0	,	6	,	9	,	6	,	//	0	0	0	6	6	9	24	6	24	24	6	9	0	6	9	6
0	,	0	,	0	,	0	,	6	,	9	,	24	,	24	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	//	0	0	0	0	6	9	24	24	24	24	24	9	6	6	6	20
6	,	6	,	9	,	10	,	10	,	6	,	9	,	10	,	6	,	6	,	6	,	11	,	6	,	6	,	9	,	9	,	//	6	6	6	6	6	6	6	6	9	9	6	6	6	9	20	24
6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	24	,	24	,	6	,	6	,	9	,	9	,	//	6	6	9	10	10	6	9	10	10	9	10	6	6	9	6	6
6	,	6	,	24	,	24	,	6	,	6	,	20	,	20	,	0	,	0	,	6	,	6	,	0	,	6	,	9	,	9	,	//	6	6	6	11	6	6	9	9	10	6	10	6	11	6	0	0
24	,	24	,	24	,	9	,	6	,	6	,	6	,	20	,	9	,	9	,	6	,	6	,	6	,	9	,	20	,	24	,	//	6	6	6	6	6	6	6	6	6	6	6	11	6	0	0	0
10	,	9	,	10	,	6	,	6	,	9	,	6	,	6	,	10	,	6	,	10	,	6	,	11	,	6	,	0	,	0	,	//	6	6	24	24	6	6	9	9	10	10	10	6	0	0	0	0
6	,	6	,	6	,	11	,	6	,	0	,	0	,	0	,	10	,	10	,	10	,	6	,	0	,	0	,	0	,	0	,	//	6	6	24	24	6	6	20	20	6	6	20	6	0	0	0	0
6	,	6	,	20	,	6	,	0	,	0	,	0	,	0	,	6	,	6	,	9	,	9	,	6	,	0	,	0	,	0	,	//	0	0	6	6	0	6	9	9	6	6	9	9	6	0	0	0	
};

u8 pjDOWN[256]{
	6	,	6	,	6	,	0	,	6	,	6	,	6	,	6	,	1	,	1	,	6	,	6	,	9	,	11	,	10	,	11	,	//	6	6	6	0	6	6	6	6	6	6	0	0	0	0	0	0
6	,	6	,	6	,	9	,	9	,	11	,	9	,	11	,	6	,	6	,	6	,	6	,	9	,	9	,	9	,	10	,	//	1	1	6	6	9	11	10	11	10	11	6	0	0	9	0	0
6	,	6	,	6	,	9	,	6	,	6	,	6	,	6	,	6	,	6	,	9	,	10	,	24	,	24	,	24	,	24	,	//	6	6	6	9	9	11	9	11	10	11	6	0	0	0	9	0
6	,	6	,	9	,	10	,	24	,	6	,	24	,	24	,	6	,	6	,	6	,	9	,	24	,	6	,	24	,	24	,	//	6	6	6	6	9	9	9	10	10	6	6	0	9	0	0	0
6	,	6	,	0	,	0	,	0	,	0	,	0	,	0	,	10	,	11	,	6	,	0	,	0	,	9	,	0	,	0	,	//	6	6	6	9	6	6	6	6	6	6	0	0	0	9	0	0
10	,	11	,	6	,	0	,	0	,	0	,	9	,	0	,	10	,	6	,	6	,	0	,	9	,	0	,	0	,	0	,	//	6	6	9	10	24	24	24	24	24	9	0	0	0	0	0	9
6	,	6	,	0	,	0	,	0	,	9	,	0	,	0	,	24	,	9	,	0	,	0	,	0	,	0	,	0	,	9	,	//	6	6	9	10	24	6	24	24	6	9	6	6	6	6	6	0
6	,	9	,	6	,	6	,	6	,	6	,	6	,	0	,	6	,	9	,	6	,	20	,	24	,	20	,	6	,	0	,	//	6	6	6	9	24	6	24	24	6	9	6	20	24	20	6	0
0	,	0	,	6	,	9	,	24	,	24	,	24	,	24	,	6	,	6	,	6	,	6	,	6	,	6	,	9	,	9	,	//	0	0	6	9	24	24	24	24	24	9	6	24	20	6	0	0
10	,	10	,	10	,	6	,	9	,	10	,	10	,	9	,	11	,	11	,	6	,	6	,	9	,	9	,	10	,	6	,	//	6	6	6	6	6	6	9	9	6	6	6	20	6	9	6	0
6	,	6	,	6	,	6	,	6	,	6	,	6	,	6	,	24	,	24	,	6	,	6	,	9	,	9	,	10	,	10	,	//	10	10	10	6	9	10	10	9	10	6	6	6	0	6	9	6
24	,	24	,	6	,	6	,	20	,	20	,	6	,	6	,	6	,	6	,	0	,	6	,	9	,	9	,	6	,	6	,	//	11	11	6	6	9	9	10	6	10	6	11	0	0	0	6	9
24	,	9	,	6	,	24	,	20	,	6	,	0	,	0	,	6	,	6	,	6	,	20	,	6	,	9	,	6	,	0	,	//	6	6	6	6	6	6	6	6	6	11	6	0	0	0	0	6
10	,	6	,	6	,	6	,	0	,	6	,	9	,	6	,	10	,	6	,	11	,	0	,	0	,	0	,	6	,	9	,	//	24	24	6	6	9	9	10	10	10	6	0	0	0	0	0	0
6	,	11	,	6	,	0	,	0	,	0	,	0	,	6	,	10	,	6	,	0	,	0	,	0	,	0	,	0	,	0	,	//	24	24	6	6	20	20	6	6	20	6	0	0	0	0	0	0
20	,	6	,	0	,	0	,	0	,	0	,	0	,	0	,	9	,	9	,	6	,	0	,	0	,	0	,	0	,	0	,	//	6	6	0	6	9	9	6	6	9	9	6	0	0	0	0	0

};

u8 dragon[256]{
	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	6	,	6	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	6	,	1	,	14	,	6	,	0	,	0	,	0	,	6	,	1	,	14	,	6	,	0	,	0	,	 //	0	0	0	0	6	6	0	0	0	0	6	6	0	0	0	0
0	,	6	,	1	,	14	,	6	,	1	,	6	,	0	,	6	,	1	,	13	,	6	,	1	,	6	,	0	,	0	,	 //	0	0	0	6	1	14	6	0	0	6	14	1	6	0	0	0
6	,	1	,	13	,	6	,	14	,	6	,	6	,	6	,	6	,	1	,	13	,	1	,	6	,	14	,	17	,	17	,	 //	0	0	6	1	14	6	0	0	0	0	6	14	1	6	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	6	,	6	,	0	,	0	,	0	,	0	,	 //	0	6	1	14	6	1	6	0	0	6	1	6	14	1	6	0
0	,	6	,	14	,	1	,	6	,	0	,	0	,	0	,	0	,	0	,	6	,	14	,	1	,	6	,	0	,	0	,	 //	6	1	13	6	1	6	0	0	0	0	6	1	6	13	1	6
0	,	6	,	1	,	6	,	14	,	1	,	6	,	0	,	0	,	0	,	6	,	1	,	6	,	13	,	1	,	6	,	 //	6	1	13	6	14	6	6	6	6	6	6	14	6	13	1	6
6	,	6	,	6	,	14	,	6	,	13	,	1	,	6	,	17	,	17	,	14	,	6	,	1	,	13	,	1	,	6	,	 //	6	1	13	1	6	14	17	17	17	17	14	6	1	13	1	6
6	,	1	,	14	,	13	,	1	,	6	,	1	,	2	,	6	,	1	,	6	,	14	,	13	,	6	,	13	,	1	,	 //	6	1	14	13	1	6	1	2	17	2	6	1	13	14	1	6
6	,	6	,	0	,	6	,	14	,	1	,	6	,	13	,	6	,	0	,	6	,	1	,	6	,	1	,	14	,	6	,	 //	6	1	6	14	13	6	13	1	17	17	17	6	14	6	13	6
0	,	6	,	1	,	6	,	14	,	1	,	1	,	14	,	6	,	1	,	13	,	6	,	14	,	1	,	1	,	24	,	 //	6	6	0	6	14	1	6	13	14	1	14	6	6	0	6	6
6	,	13	,	6	,	13	,	6	,	1	,	1	,	24	,	0	,	6	,	14	,	6	,	14	,	6	,	14	,	6	,	 //	6	0	6	1	6	1	14	6	13	13	13	6	0	0	0	6
17	,	2	,	6	,	1	,	13	,	14	,	1	,	6	,	17	,	17	,	17	,	6	,	14	,	6	,	13	,	6	,	 //	0	6	1	6	14	1	1	14	6	6	6	14	6	0	0	0
14	,	1	,	14	,	6	,	6	,	0	,	6	,	6	,	13	,	13	,	13	,	6	,	0	,	0	,	0	,	6	,	 //	6	1	13	6	14	1	1	24	24	13	1	14	6	0	0	0
6	,	6	,	6	,	14	,	6	,	0	,	0	,	0	,	24	,	13	,	1	,	14	,	6	,	0	,	0	,	0	,	 //	6	13	6	13	6	1	1	24	6	13	1	6	13	6	0	0
6	,	13	,	1	,	6	,	13	,	6	,	0	,	0	,	6	,	14	,	6	,	14	,	6	,	14	,	6	,	0	,	 //	0	6	14	6	14	6	14	6	6	14	6	14	6	14	6	0

}

u8 dragonF[256]{
	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	6	,	6	,	0	,	0	,	 //	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0	0
0	,	0	,	0	,	6	,	1	,	14	,	6	,	0	,	0	,	0	,	6	,	1	,	14	,	6	,	0	,	0	,	 //	0	0	0	0	6	6	0	0	0	0	6	6	0	0	0	0
0	,	6	,	1	,	14	,	6	,	1	,	6	,	0	,	6	,	1	,	13	,	6	,	1	,	6	,	0	,	0	,	 //	0	0	0	6	1	14	6	0	0	6	14	1	6	0	0	0
6	,	1	,	13	,	6	,	14	,	6	,	6	,	6	,	6	,	1	,	13	,	1	,	6	,	14	,	17	,	17	,	 //	0	0	6	1	14	6	0	0	0	0	6	14	1	6	0	0
0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	0	,	6	,	6	,	0	,	0	,	0	,	0	,	 //	0	6	1	14	6	1	6	0	0	6	1	6	14	1	6	0
0	,	6	,	14	,	1	,	6	,	0	,	0	,	0	,	0	,	0	,	6	,	14	,	1	,	6	,	0	,	0	,	 //	6	1	13	6	1	6	0	0	0	0	6	1	6	13	1	6
0	,	6	,	1	,	6	,	14	,	1	,	6	,	0	,	0	,	0	,	6	,	1	,	6	,	13	,	1	,	6	,	 //	6	1	13	6	14	6	6	6	6	6	6	14	6	13	1	6
6	,	6	,	6	,	14	,	6	,	13	,	1	,	6	,	17	,	17	,	14	,	6	,	1	,	13	,	1	,	6	,	 //	6	1	13	1	6	14	17	17	17	17	14	6	1	13	1	6
6	,	1	,	14	,	13	,	1	,	6	,	1	,	2	,	6	,	1	,	6	,	14	,	13	,	6	,	13	,	1	,	 //	6	1	14	13	1	6	1	2	17	2	6	1	13	14	1	6
6	,	6	,	0	,	6	,	14	,	1	,	6	,	13	,	6	,	0	,	6	,	1	,	6	,	1	,	14	,	6	,	 //	6	1	6	14	13	6	13	1	17	17	17	6	14	6	13	6
0	,	6	,	1	,	6	,	14	,	1	,	1	,	14	,	6	,	1	,	13	,	6	,	14	,	1	,	1	,	24	,	 //	6	6	0	6	14	1	6	13	14	1	14	6	6	0	6	6
6	,	13	,	6	,	13	,	6	,	1	,	1	,	24	,	0	,	6	,	14	,	6	,	14	,	6	,	14	,	6	,	 //	6	0	6	1	6	1	14	6	13	13	13	12	12	0	0	6
17	,	2	,	6	,	1	,	13	,	14	,	1	,	6	,	17	,	17	,	17	,	6	,	14	,	6	,	13	,	6	,	 //	0	6	1	6	14	1	1	14	6	13	12	2	2	12	0	0
14	,	1	,	14	,	6	,	6	,	0	,	6	,	6	,	13	,	13	,	13	,	12	,	12	,	0	,	0	,	6	,	 //	6	1	13	6	14	1	1	24	24	13	1	12	2	2	12	0
6	,	13	,	12	,	2	,	2	,	12	,	0	,	0	,	24	,	13	,	1	,	12	,	2	,	2	,	12	,	0	,	 //	6	13	6	13	6	1	1	24	6	13	1	6	12	2	2	12
6	,	13	,	1	,	6	,	12	,	2	,	2	,	12	,	6	,	14	,	6	,	14	,	6	,	12	,	12	,	12	,	 //	0	6	14	6	14	6	14	6	6	14	6	14	6	12	12	12

}
/* Irudikatutako Spriteak memorian kargatzen ditu. SPRITE bat baino gehiago erakusteko
for bana egin behar da.*/

void SpriteakMemorianGorde(){ 
	
	int i;
	//16*16ko spriteentzako
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxpj[i] = pj[i*2] | (pj[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxpjUP[i] = pjUP[i*2] | (pjUP[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxpjDOWN[i] = pjDOWN[i*2] | (pjDOWN[(i*2)+1]<<8);				
	}
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxdragon[i] = dragon[i*2] | (dragon[(i*2)+1]<<8);				
	}

	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxdragonF[i] = dragonF[i*2] | (dragonF[(i*2)+1]<<8);				
	}
}

/* Funtzio honek erronbo bat irudikatzen du pantailako x,y posizioan. Pantailan ateratzea nahi den erronbo 
   bakoitzari indize desberdin bat esleitu behar zaio, 0 eta 126 balioen arteko indizea izan daiteke */

void Erakutsipj(int indizea, int x, int y)
{ 
 
oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpj,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/* Funtzio honek erronbo baten indizea pasata pantailatik ezabatzen du */
void Ezabatupj(int indizea, int x, int y)
{

oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpj,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
oamUpdate(&oamMain); 

}

void ErakutsipjUP(int indizea, int x, int y)
{ 
 
oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpjUP,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 

	  
oamUpdate(&oamMain);  
}

void EzabatupjUP(int indizea, int x, int y)
{

oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpjUP,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
oamUpdate(&oamMain); 

}
void ErakutsipjDOWN(int indizea, int x, int y)
{ 
 
oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpjDOWN,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 

	  
oamUpdate(&oamMain);  
}

void EzabatupjDOWN(int indizea, int x, int y)
{

oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxpjDOWN,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
oamUpdate(&oamMain); 

}
void ErakutsiDragon(int indizea, int x, int y)
{ 
 
oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdragon,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 

	  
oamUpdate(&oamMain);  
}

void EzabatuDragon(int indizea, int x, int y)
{

oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdragon,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
oamUpdate(&oamMain); 

}
void ErakutsidragonF(int indizea, int x, int y)
{ 
 
oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdragonF,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		false,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 

	  
oamUpdate(&oamMain);  
}

void EzabatuDragonF(int indizea, int x, int y)
{

oamSet(&oamMain, // main graphics engine context
		indizea,           // oam index (0 to 127)  
		x, y,   // x and y pixel location of the sprite
		0,                    // priority, lower renders last (on top)
		0,					  // this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxdragonF,//+16*16/2,                  // pointer to the loaded graphics
		-1,                  // sprite rotation data  
		false,               // double the size when rotating?
		true,			// hide the sprite?
		false, false, // vflip, hflip
		false	// apply mosaic
		); 
oamUpdate(&oamMain); 

}