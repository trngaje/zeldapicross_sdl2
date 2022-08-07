/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __FREE_H__
#define __FREE_H__

#if defined(_3DS)
#include "3ds/SDL_3ds.h"
#elif defined(OGS_SDL2)
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include "Event.h"
#include "Joueur.h"

class Free {
    public :
        static Free* getInstance();
        
        void init();
        void start(Joueur* joueur);
        void handleEvent(Event* event);
        void loop();
        void draw(SDL_Surface* gpScreen);
    private :
        static Free instance;
        
        Free();
        ~Free();
        
        void cadre(int x, int y, int w, int h, SDL_Surface* im);
        void initPage();
        void launchPicross();
        int randomId();
        
        FreeMode mode;
        int lineOpt;
        int line;
        int page;
        int picrossId;
        bool quit;
        bool quitPicross;
        bool picrossVictory;
        Joueur* gpJoueur;
        Picross* gpPicross;
        SDL_Surface* image;
        SDL_Surface* imagePage;
        SDL_Surface* imageOptions;
        SDL_Surface* curseurLink;
        SDL_Surface* background;
};

#endif  // Free.h
