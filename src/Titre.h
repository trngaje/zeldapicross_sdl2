/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __TITRE_H__
#define __TITRE_H__

#ifdef OGS_SDL2
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include "Event.h"

class Titre {
    public :
        static Titre* getInstance();
        
        void init();
        void start();
        void handleEvent(Event* event);
        void draw(SDL_Surface* gpScreen);
    private :
        static Titre instance;
        
        Titre();
        ~Titre();
        
        SDL_Surface* imageBackground;
        SDL_Surface* imageLogo;
};

#endif  // Titre.h
