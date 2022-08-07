/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __INTRO_H__
#define __INTRO_H__

#if defined(_3DS)
#include "3ds/SDL_3ds.h"
#elif defined(OGS_SDL2)
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include "Event.h"

class Intro {
    public :
        static Intro* getInstance();
        
        void init();
        void start();
        void handleEvent(Event* event);
        void draw(SDL_Surface* gpScreen);
    private :
        static Intro instance;
        
        Intro();
        ~Intro();
        
        int anim;
        Uint32 lastAnimTime;
        SDL_Surface* imageStep[3];
        SDL_Surface* imageFond1;
        SDL_Surface* imageFond2;
};

#endif  // Intro.h
