
// Sprite: Mapa de bits que va a ser representado en pantalla
// Como puede ser un jugador o cualquier enemigo.
// Un sprite se compone de una serie de imagenes que representan distintos frames
// Cada frame se representa en un orden para formar una animación.
// En megadrive los sprites tienen su propio plano.
// La posición de los Sprites va en Píxeles y no en Tiles
// Podemos tener un total de 80 sprites por pantalla
// Solo se pueden tener 20 sprites por línea horizontal
// Un sprite siempre debe ser divisible por 8.
// El tamañó máximo de sprites que SGDK permite es de 16x16 tiles (128x128 píxlee)
// Se permiten 16 animaciones por sprite


/** Ejemplo5: Ejemplo de planos con Mega Drive **/
//Incluir libreria
#include <genesis.h>

// Incluir los recursos
#include "gfx.h"
#include "sprt.h"

//animaciones
#define ANIM_RIGTH 1
#define ANIM_LEFT 3
#define ANIM_DOWN 2
#define ANIM_UP 0
#define ANIM_STAY 4

//Esta funcion nos ayudara a leer los controles
void readcontrollers();

//Sprite Principal
Sprite* mainsprt;
//Sprite Secundario
Sprite* secondsprt;
u32 posx = 45;
u32 posy = 155;
//Funcion Principal
int main()
{
    //array donde se almacenara las paletas
    u16 palette[32];



   //Para evitar problemas, se deshabilitan las interrupciones durante la carga
    SYS_disableInts();
    // initializacion a 320 de ancho
    VDP_setScreenWidth320();

     // se establecen los colores de la paleta a negro
    VDP_setPaletteColors(0, (u16*) palette_black, 32);

    //Indice para pdoer saber la carga
    u16 ind = TILE_USERINDEX;

    //dibuja un plano a partir de un recurso
    VDP_drawImageEx(BG_B, &bga_image, TILE_ATTR_FULL(PAL1, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += bga_image.tileset->numTile;
    VDP_drawImageEx(BG_A, &bgb_image, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += bgb_image.tileset->numTile;



     //Se vuelven a activar las interrupciones
    SYS_enableInts();
     //Inicializa motor de sprites con los parámetros por defecto
    SPR_init(0, 0, 0);

    mainsprt = SPR_addSprite(&main_sprt, 15, 125, TILE_ATTR_FULL(PAL2, TRUE, FALSE, FALSE,ind));
    secondsprt= SPR_addSprite(&elli_sprt, 45, 155, TILE_ATTR(PAL3,TRUE,FALSE,FALSE));
    // prepare palettes
    memcpy(&palette[0], bgb_image.palette->data, 16 * 2);
    memcpy(&palette[16], bga_image.palette->data, 16 * 2);
    VDP_setPalette(PAL2,main_sprt.palette->data);
    VDP_setPalette(PAL3, elli_sprt.palette->data);
    SPR_setAnim(mainsprt, ANIM_STAY);
    SPR_setAnim(secondsprt, ANIM_STAY);
     // fade in
    VDP_fadeIn(0, (2 * 16) - 1, palette, 20, FALSE);
    // bucle infinito
    while(1)
    {

        readcontrollers();
        //actualiza el VDP
        SPR_update();
        //Esperar refresco
        SYS_doVBlankProcess();
    }

}

void readcontrollers()
{
    //Se lee el estado del joistick en el puerto 1
    int value = JOY_readJoypad(JOY_1);

    if(value & BUTTON_RIGHT){
        SPR_setPosition(secondsprt, posx++, posy);
        SPR_setAnim(secondsprt,ANIM_RIGTH);
    }

    if(value & BUTTON_LEFT){
        SPR_setPosition(secondsprt, posx--, posy);
        SPR_setAnim(secondsprt,ANIM_LEFT);
    }

    if(value & BUTTON_DOWN)
    {
        SPR_setPosition(secondsprt, posx, posy++);
        SPR_setAnim(secondsprt,ANIM_DOWN);
    }

    if(value & BUTTON_UP)
    {
        SPR_setPosition(secondsprt, posx, posy--);
        SPR_setAnim(secondsprt,ANIM_UP);
    }
    if(((!(value & BUTTON_RIGHT)) && (!(value & BUTTON_LEFT))) && ((!(value & BUTTON_DOWN)) && (!(value & BUTTON_UP))))
    {
        SPR_setAnim(secondsprt,ANIM_STAY);
    }
}




