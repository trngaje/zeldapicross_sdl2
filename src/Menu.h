/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __MENU_H__
#define __MENU_H__

#if defined(_3DS)
#include "3ds/SDL_3ds.h"
#elif defined(OGS_SDL2)
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include "Common.h"
#include "Event.h"
#include "Joueur.h"

class Menu {
    public :
        static Menu* getInstance();
        
        void init(Joueur* j[]);
        void start();
        void handleEvent(Event* event);
        void draw(SDL_Surface* gpScreen);
    private :
        static Menu instance;
        
        Menu();
        ~Menu();
        
        void cadre(int x, int y, int w, int h, SDL_Surface* im);
        void initProfil();
        
        int line;
        int column;
        int lineFee;
        int lastProfil;
        MenuMode mode;
        bool loaded[3];
        Joueur* joueurs[3];
        SDL_Surface* image;
        SDL_Surface* imageMode;
        SDL_Surface* imageProfil;
        SDL_Surface* imageBaseProfil;
        SDL_Surface* imageDelete;
        SDL_Surface* curseurLink;
        SDL_Surface* curseurFee;
#ifdef _3DS
		bool bMenuSelected;
#endif
};

#endif  // Menu.h
