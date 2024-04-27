// 2023-2024 ikasturtea

extern u16* gfx;
extern u16* gfx2;
extern u16* gfx3;
extern u16* gfxSub;

extern void memoriaErreserbatu();

/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu pantaila nagusian. 0 balioa gardena da 
   eta definitu gabeko balioak beltzak. */
extern void PaletaNagusiaEzarri();

/* Pixel bakoitzak har ditzakeen 256 balioetako bakoitzari kolore bat esleitu bigarren pantailan. 0 balioa 
   gardena da eta definitu gabeko balioak beltzak. */
extern void BigarrenPaletaEzarri();

/* Irudikatutako Spriteak memorian kargatzen ditu.*/
extern void SpriteakMemorianGorde();

/* Funtzio honek erronbo bat irudikatzen du pantailako x,y posizioan. Pantailan ateratzea nahi den erronbo 
   bakoitzari indize desberdin bat esleitu behar zaio, 0 eta 126 balioen arteko indizea izan daiteke. */

/* Funtzio honek erronbo baten indizea pasata pantailatik ezabatzen du */
extern void Erakutsipj(int indizea, int x, int y);
extern void Ezabatupj(int indizea, int x, int y);
extern void ErakutsipjUP(int indizea, int x, int y);
extern void EzabatupjUP(int indizea, int x, int y);
extern void ErakutsipjDOWN(int indizea, int x, int y);
extern void EzabatupjDOWN(int indizea, int x, int y);
extern void ErakutsiDragon(int indizea, int x, int y);
extern void EzabatuDragon(int indizea, int x, int y);
extern void ErakutsidragonF(int indizea, int x, int y);
extern void EzabatuDragonF(int indizea, int x, int y);




