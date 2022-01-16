/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __CASEICON_H__
#define __CASEICON_H__

#ifdef OGS_SDL2
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include "Common.h"
#include "CaseMap.h"

class CaseIcon : public CaseMap {
    public :
        CaseIcon(int thm);
        ~CaseIcon();
        void draw(SDL_Surface* gpScreen, bool display, bool map, bool compas);
        void loadFromString(string line);
        int getDestLvl();
        int getDestCase();
        int getImageId();
    private :
        
        int destLvl;
        int destCase;
        int imageId;
        SDL_Surface* imageTheme;
        
};

#endif  // CaseIcon.h
