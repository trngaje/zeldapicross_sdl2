/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#if defined(_3DS)
#include "3ds/SDL_3ds.h"
#elif defined(OGS_SDL2)
#include <SDL2/SDL.h>
#else
#include <SDL/SDL.h>
#endif

#include "Logo.h"
#include "Resources.h"
#include "Game.h"
#include "Audio.h"

Logo Logo::instance=Logo();

Logo::Logo() {
}

Logo::~Logo() {
}

void Logo::init() {
    image = Resources::getInstance()->getLogo();
}

Logo* Logo::getInstance() {
    return &instance;
}

void Logo::handleEvent(Event* event) {
#ifdef _3DS
    if (event->RETURN) {
		bMenuSelected = true;

    }
	else {
		if (bMenuSelected) {
			bMenuSelected = false;
			Audio::getInstance()->playSound(1);
			Game::getInstance()->setMode(TITLE);
		}
	}
#else    
    if (event->RETURN) {
        Audio::getInstance()->playSound(1);
        Game::getInstance()->setMode(TITLE);
    }
#endif

}

void Logo::draw(SDL_Surface* gpScreen) {
    SDL_Rect src;
    SDL_Rect dst;
    src.x = 0;
    src.y = 0;
    src.w = 320; 
    src.h = 240;
    dst.x = 0;
    dst.y = 0;
    SDL_BlitSurface(image, &src, gpScreen, &dst);
}
