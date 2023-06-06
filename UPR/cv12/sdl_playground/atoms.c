/**
 * Docs: http://wiki.libsdl.org/FrontPage
 * Tutorial: http://lazyfoo.net/tutorials/SDL/index.php
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

#include "sdl_playground.h"
#include "array.h"


#define WINDOW_WIDTH 800        // rozlišení okna
#define WINDOW_HEIGHT 600

// zasah 2)  - vytvoreni kulicek po kliknuti na obrazovku

typedef struct {
    int pos_x;
    int pos_y;
    int smer_x;
    int smer_y;
    int radius;
    int count;
} Kulicka;


int main() {

    Array kulicky;                              // 2) cast pro vlozeni vice kulicek
    array_init(&kulicky, 5, sizeof(Kulicka));
    Kulicka *prva_kulicka = array_push(&kulicky);
    prva_kulicka->pos_x = 50;
    prva_kulicka->pos_y = 50;
    prva_kulicka->smer_x = 1;
    prva_kulicka->smer_y = 1;
    prva_kulicka->radius = 50;


    SDL_Window * win = NULL;    // vztvoří plochu
    SDL_Renderer * ren = NULL;
    
    bool initialized = sdl_playground_init( &win, &ren, WINDOW_WIDTH, WINDOW_HEIGHT ); // vztvor okno

    if ( !initialized )  // pokud se to nepovede, tak to smaz
    {
        sdl_playground_destroy( win, ren );
        return -1;
    }


    // Zásah č1 - initializace textury
    SDL_Texture * tex =  IMG_LoadTexture(ren, "atom.svg"); // Vztvorili jsme ho v pameti, tak ho musim i nakonec zrusit





    int rect_x = 50;        // inicializace pozice X (kde se prve vykresli)
    int rect_y = 50;
    //int direction = 5;      // smer kam se hybe (pokud - tak zprava do leva | pokud +)
    int direction_x = 5;
    int direction_y = 5;

    SDL_Event e;
    bool quit = false;

    while ( !quit ) {               // odchyt udalosti v jakych dojde ke konci
        while ( SDL_PollEvent( &e ) ) {
            if ( e.type == SDL_QUIT ) {
                quit = true;
            }
            else if ( e.type == SDL_KEYDOWN ) { // key pressed down
                if ( e.key.keysym.sym == SDLK_r ) {         // cuklus skončí pokud zmačknu R
                    quit = true;
                }
            }
            // Zasah 3) generator kulicek
            else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) { // mouse button released || -> tato fce nám umožní získat pozici, na kterou jsme klikli na obrazovce levým tlačítkem myši
                // x: e.button.x
                // y: e.button.y
                Kulicka *nova_kul = array_push(&kulicky);
                nova_kul->pos_x = e.button.x;
                nova_kul->pos_y = e.button.y;
                nova_kul->smer_x = 1;
                nova_kul->smer_y = 1;
                nova_kul->radius = 50;
            }
            else if (e.type == SDL_MOUSEMOTION) { // mouse movement
                // x: e.motion.x
                // y: e.motion.y
            }
        }


    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);          //nastavime barvu pozadi na cernou 
    SDL_RenderClear(ren);

      for (int i = 0; i < kulicky.count; i++){
        
        Kulicka *kul = array_get(&kulicky, i);

       SDL_Rect rect;
       rect.x = kul->pos_x;
       rect.y = kul->pos_y;
       rect.w = kul->radius;
       rect.h = kul->radius;

        /*
        SDL_Rect rect;      // tady vytvorim ctverec
        rect.x = rect_x;    // tadz jsem si nadefinoval, ze se bude menit pouze pozice na x
        rect.y = rect_y;        // y je konstantni
        rect.w = 70;
        rect.h = 70;
        */

      /* Kulicka *kul = array_get(&kulicky, 0);
       SDL_Rect rect;
       rect.x = kul->pos_x;
       rect.y = kul->pos_y;
       rect.w = kul->radius;
       rect.h = kul->radius;*/

        SDL_SetRenderDrawColor(ren, 255, 0, 0, 255); // RGB
        //SDL_RenderFillRect(ren, &rect);  -> misto rectu vykreslim kulicku
        SDL_RenderCopy(ren, tex, NULL, &rect);
      }

        SDL_RenderPresent(ren); // aktualizace obrazovky

// tato cast se zabyva pouze pohzbem
      for (int i = 0; i < kulicky.count; i++){
        
        Kulicka *kul = array_get(&kulicky, i);
        //if ( rect_x + rect.w >= WINDOW_WIDTH || rect_x <= 0 ) { // pokud jsi dosahl na konec obrazovky, tak 
        if ( kul->pos_x + kul->radius >= WINDOW_WIDTH || kul->pos_x <= 0 ) {          
            //direction_x *= -1;
            kul->smer_x *= -1;
        }

        if ( kul->pos_y + kul->radius >= WINDOW_HEIGHT || kul->pos_y <= 0 ) { // pokud jsi dosahl na konec obrazovky, tak 
            //direction_y *= -1;            
            kul->smer_y *= -1;
        }

        kul->pos_x += kul->smer_x* 5; // posouvame rect o 3 (ted jen jeden) pixely aka rychlost
        kul->pos_y += kul->smer_y* 5;
        }
    }



    SDL_DestroyTexture(tex); // z casti 1)
    sdl_playground_destroy( win, ren );

    return 0;
}
