/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#ifdef OGS_SDL2
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include "Event.h"
#include "Common.h"

class Keyboard {
    public :
        Keyboard();
        ~Keyboard();
        void pollEvent();
        Event* getEvent();
    private :
        void pollKey(SDL_Event event);
        void pollKeys(Uint8* keys);
        
        int tmpDirUp;
        int tmpDirDown;
        int tmpDirLeft;
        int tmpDirRight;
        int tmpAction;
        int tmpReturn;
        int tmpHypo;
        int tmpMouse;
        int tmpEscap;
        int tmpMusic;
        Event* event;
        
        // key repeating
        Direction currentDir;
        Uint32 startTime;
        bool running;
};

#endif  // Keyboard.h
