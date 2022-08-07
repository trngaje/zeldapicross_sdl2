/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __ENDING_H__
#define __ENDING_H__

#if defined(_3DS)
#include "3ds/SDL_3ds.h"
#elif defined(OGS_SDL2)
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include "Event.h"
#include "Common.h"
#include "Joueur.h"

class Ending {
    public :
        static Ending* getInstance();
        
        void init();
        void start(Joueur* joueur);
        void handleEvent(Event* event);
        void draw(SDL_Surface* gpScreen);
    private :
        static Ending instance;
        
        Ending();
        ~Ending();
        
        EndingMode mode;
        SDL_Surface* image;
        SDL_Surface* rank;
};

#endif  // Ending.h
