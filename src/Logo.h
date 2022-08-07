/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __LOGO_H__
#define __LOGO_H__

#if defined(_3DS)
#include "3ds/SDL_3ds.h"
#elif defined(OGS_SDL2)
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include "Event.h"

class Logo {
    public :
        static Logo* getInstance();
        
        void init();
        void handleEvent(Event* event);
        void draw(SDL_Surface* gpScreen);
    private :
        static Logo instance;
        
        Logo();
        ~Logo();
        
        SDL_Surface* image;
#ifdef _3DS
		bool bMenuSelected;
#endif
};

#endif  // Logo.h
