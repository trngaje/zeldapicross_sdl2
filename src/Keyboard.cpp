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

#include "Keyboard.h"
#include "Common.h"

#ifdef OGS_SDL2
#define CONFIRM_BUTTON SDL_SCANCODE_LCTRL
#else
#define CONFIRM_BUTTON SDLK_LCTRL
#endif

Keyboard::Keyboard() : tmpDirUp(0), tmpDirDown(0), tmpDirLeft(0), tmpDirRight(0), 
tmpAction(0), tmpReturn(0), tmpHypo(0), tmpMouse(0), tmpEscap(0), tmpMusic(0), 
startTime(0), running(false) {
    event = new Event();
}

Keyboard::~Keyboard() {
    delete event;
}

void Keyboard::pollEvent() {
    
    event->MOUSE_ACTION = false;
    event->MOUSE_FLAG = false;
    event->MOUSE_CANCEL_ACTION = false;
    event->MOUSE_CANCEL_FLAG = false;
    
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT : 
                event->QUIT=true;
                return;
            case SDL_KEYDOWN :
                pollKey(sdlEvent);
                break;
            case SDL_MOUSEBUTTONDOWN :
                if (sdlEvent.button.button == SDL_BUTTON_LEFT 
                && !event->MOUSE_HOLD_ACTION) {
                    if (event->MOUSE_HOLD_FLAG) {
                        event->MOUSE_HOLD_FLAG = false;
                        event->MOUSE_CANCEL_FLAG = true;
                    } else {
                        event->MOUSE_HOLD_ACTION = true;
                    }
                } else if (sdlEvent.button.button == SDL_BUTTON_RIGHT 
                && !event->MOUSE_HOLD_FLAG) {
                    if (event->MOUSE_HOLD_ACTION) {
                        event->MOUSE_HOLD_ACTION = false;
                        event->MOUSE_CANCEL_ACTION = true;
                    } else {
                        event->MOUSE_HOLD_FLAG = true;
                    }
                }
                break;
            case SDL_MOUSEBUTTONUP :
                if (event->MOUSE_HOLD_ACTION && !event->MOUSE_HOLD_FLAG) {
                    event->MOUSE_HOLD_ACTION = false;
                    event->MOUSE_ACTION = true;
                } else if (event->MOUSE_HOLD_FLAG && !event->MOUSE_HOLD_ACTION) {
                    event->MOUSE_HOLD_FLAG = false;
                    event->MOUSE_FLAG = true;
                }
                break;
        }
    }
#if defined(_3DS)
    int keys = SDL_GetKeyState(NULL);
#elif defined(OGS_SDL2)
    Uint8* keys = (Uint8*)SDL_GetKeyboardState(NULL);
#else    
    Uint8* keys = SDL_GetKeyState(NULL);
#endif
    pollKeys(keys);
    
}

void Keyboard::pollKey(SDL_Event sdlEvent) {
    event->QUIT = false;
    event->ESCAPE = false;
    event->FULLSCREEN = false;
    switch (sdlEvent.key.keysym.sym) {
        case SDLK_ESCAPE :
            event->QUIT=true;
            event->ESCAPE=true;
            break;
        case SDLK_F4 :
            if (sdlEvent.key.keysym.mod & KMOD_ALT) event->QUIT=true;
            break;
#ifdef _3DS
        case SDLK_RETURN :
#else
        case CONFIRM_BUTTON :
#endif
            if (sdlEvent.key.keysym.mod & KMOD_CTRL) event->FULLSCREEN=true;
            break;
        default : break;
    }
}

#ifdef _3DS
void Keyboard::pollKeys(int keys) {
#else
void Keyboard::pollKeys(Uint8* keys) {
#endif

#if defined(_3DS)
    if (keys & SDLK_UP) {
#elif defined(OGS_SDL2)
    if (keys[SDL_SCANCODE_UP]) {
#else
    if (keys[SDLK_UP]) {
#endif    	
        if (tmpDirUp == 0) {
            event->UP = true;
            tmpDirUp = 1;
            currentDir = UP;
            running = false;
            startTime = SDL_GetTicks();
        } else {
            if (currentDir == UP) {
                if (running) {
                    if ((SDL_GetTicks() - startTime) > TIME_WHILE_RUNNING) {
                        startTime = SDL_GetTicks();
                        event->UP = true;
                    } else {
                        event->UP = false;
                    }
                } else {
                    if ((SDL_GetTicks() - startTime) > TIME_BEFORE_RUNNING) {
                        startTime = SDL_GetTicks();
                        running = true;
                        event->UP = true;
                    } else {
                        event->UP = false;
                    }
                }
            } else {
                event->UP = false;
            }
        }
    } else {
        tmpDirUp = 0;
        event->UP = false;
    }

#if defined(_3DS)
    if (keys&SDLK_DOWN) {
#elif defined(OGS_SDL2)
    if (keys[SDL_SCANCODE_DOWN]) {
#else    
    if (keys[SDLK_DOWN]) {
#endif
        if (tmpDirDown == 0) {
            event->DOWN = true;
            tmpDirDown = 1;
            currentDir = DOWN;
            running = false;
            startTime = SDL_GetTicks();
        } else {
            if (currentDir == DOWN) {
                if (running) {
                    if ((SDL_GetTicks() - startTime) > TIME_WHILE_RUNNING) {
                        startTime = SDL_GetTicks();
                        event->DOWN = true;
                    } else {
                        event->DOWN = false;
                    }
                } else {
                    if ((SDL_GetTicks() - startTime) > TIME_BEFORE_RUNNING) {
                        startTime = SDL_GetTicks();
                        running = true;
                        event->DOWN = true;
                    } else {
                        event->DOWN = false;
                    }
                }
            } else {
                event->DOWN = false;
            }
        }
    } else {
        tmpDirDown = 0;
        event->DOWN = false;
    }

#if defined(_3DS)
    if (keys&SDLK_LEFT) {
#elif defined(OGS_SDL2)
    if (keys[SDL_SCANCODE_LEFT]) {
#else    
    if (keys[SDLK_LEFT]) {
#endif
        if (tmpDirLeft == 0) {
            event->LEFT = true;
            tmpDirLeft = 1;
            currentDir = LEFT;
            running = false;
            startTime = SDL_GetTicks();
        } else {
            if (currentDir == LEFT) {
                if (running) {
                    if ((SDL_GetTicks() - startTime) > TIME_WHILE_RUNNING) {
                        startTime = SDL_GetTicks();
                        event->LEFT = true;
                    } else {
                        event->LEFT = false;
                    }
                } else {
                    if ((SDL_GetTicks() - startTime) > TIME_BEFORE_RUNNING) {
                        startTime = SDL_GetTicks();
                        running = true;
                        event->LEFT = true;
                    } else {
                        event->LEFT = false;
                    }
                }
            } else {
                event->LEFT = false;
            }
        }
    } else {
        tmpDirLeft = 0;
        event->LEFT = false;
    }

#if defined(_3DS)
    if (keys&SDLK_RIGHT) {
#elif defined(OGS_SDL2)
    if (keys[SDL_SCANCODE_RIGHT]) {
#else    
    if (keys[SDLK_RIGHT]) {
#endif
        if (tmpDirRight == 0) {
            event->RIGHT = true;
            tmpDirRight = 1;
            currentDir = RIGHT;
            running = false;
            startTime = SDL_GetTicks();
        } else {
            if (currentDir == RIGHT) {
                if (running) {
                    if ((SDL_GetTicks() - startTime) > TIME_WHILE_RUNNING) {
                        startTime = SDL_GetTicks();
                        event->RIGHT = true;
                    } else {
                        event->RIGHT = false;
                    }
                } else {
                    if ((SDL_GetTicks() - startTime) > TIME_BEFORE_RUNNING) {
                        startTime = SDL_GetTicks();
                        running = true;
                        event->RIGHT = true;
                    } else {
                        event->RIGHT = false;
                    }
                }
            } else {
                event->RIGHT = false;
            }
        }
    } else {
        tmpDirRight = 0;
        event->RIGHT = false;
    }
    
    
    event->ACTION = false;
#if defined(_3DS)
    if ((keys&SDLK_w || keys&SDLK_z) && !event->HOLD_ACTION 
#elif defined(OGS_SDL2)
    if ((keys[SDL_SCANCODE_LCTRL] || keys[SDL_SCANCODE_Z]) && !event->HOLD_ACTION  
#else    
    if ((keys[SDLK_LCTRL] || keys[SDLK_z]) && !event->HOLD_ACTION  
#endif    
    && !event->HOLD_FLAG && !tmpAction) {
        event->HOLD_ACTION = true;
        tmpAction = 1;
    }
#if defined(_3DS)
    if (!(keys&SDLK_w) && !(keys&SDLK_z) && event->HOLD_ACTION) {
#elif defined(OGS_SDL2)
    if (!keys[SDL_SCANCODE_LCTRL] && !keys[SDL_SCANCODE_Z] && event->HOLD_ACTION) {
#else    
    if (!keys[SDLK_LCTRL] && !keys[SDLK_z] && event->HOLD_ACTION) {
#endif
        event->HOLD_ACTION = false;
        event->ACTION = true;
        tmpAction = 0;
    }
    
    event->FLAG = false;
#if defined(_3DS)
    if (keys&SDLK_x && !event->HOLD_ACTION  && !event->HOLD_FLAG 
#elif defined(OGS_SDL2)
	if (keys[SDL_SCANCODE_LALT] && !event->HOLD_ACTION  && !event->HOLD_FLAG 
#else
    if (keys[SDLK_LALT] && !event->HOLD_ACTION  && !event->HOLD_FLAG 
#endif
    && !tmpAction) {
        event->HOLD_FLAG = true;
        tmpAction = 1;
    }
#if defined(_3DS)
    if (!(keys&SDLK_x) && event->HOLD_FLAG) {
#elif defined(OGS_SDL2)
    if (!keys[SDL_SCANCODE_LALT] && event->HOLD_FLAG) {
#else
    if (!keys[SDLK_LALT] && event->HOLD_FLAG) {
#endif    	
        event->HOLD_FLAG = false;
        event->FLAG = true;
        tmpAction = 0;
    }
    
    // cancel action
#if defined(_3DS)
    if ((keys&SDLK_x) && event->HOLD_ACTION  && !event->HOLD_FLAG) {
#elif defined(OGS_SDL2)
    if (keys[SDL_SCANCODE_LALT] && event->HOLD_ACTION  && !event->HOLD_FLAG) {
#else
    if (keys[SDLK_LALT] && event->HOLD_ACTION  && !event->HOLD_FLAG) {
#endif
        event->HOLD_ACTION = false;
        event->CANCEL_ACTION = true;
        tmpAction = 1;
    }
#if defined(_3DS)
    if (!(keys&SDLK_x) && !(keys&SDLK_w) && !(keys&SDLK_z)
#elif defined(OGS_SDL2)
    if (!keys[SDL_SCANCODE_LALT] && !keys[SDL_SCANCODE_LCTRL] && !keys[SDL_SCANCODE_Z] 
#else
    if (!keys[SDLK_LALT] && !keys[SDLK_LCTRL] && !keys[SDLK_z] 
#endif
    && event->CANCEL_ACTION) {
        event->CANCEL_ACTION = false;
        tmpAction = 0;
    }
    
    // cancel flag
#if defined(_3DS)
    if ((keys&SDLK_w || keys&SDLK_z) && !event->HOLD_ACTION  
#elif defined(OGS_SDL2)
    if ((keys[SDL_SCANCODE_LCTRL] || keys[SDL_SCANCODE_Z]) && !event->HOLD_ACTION
#else
    if ((keys[SDLK_LCTRL] || keys[SDLK_z]) && !event->HOLD_ACTION
#endif  
    && event->HOLD_FLAG) {
        event->HOLD_FLAG = false;
        event->CANCEL_FLAG = true;
        tmpAction = 1;
    }
#if defined(_3DS)
    if (!(keys&SDLK_x) && !(keys&SDLK_w) && !(keys&SDLK_z) && event->CANCEL_FLAG) {
#elif defined(OGS_SDL2)
    if (!keys[SDL_SCANCODE_LALT] && !keys[SDL_SCANCODE_LCTRL] && !keys[SDL_SCANCODE_Z] && event->CANCEL_FLAG) {
#else
    if (!keys[SDLK_LALT] && !keys[SDLK_LCTRL] && !keys[SDLK_z] && event->CANCEL_FLAG) {
#endif
        event->CANCEL_FLAG = false;
        tmpAction = 0;
    }
    
#ifdef _3DS
    if ((keys&SDLK_RETURN || keys&SDLK_KP_ENTER) && !tmpReturn) {
        event->RETURN = true;
        tmpReturn = 1;
    }
    if (!(keys&SDLK_RETURN) && !(keys&SDLK_KP_ENTER) && tmpReturn) {
		event->RETURN = false;		
        tmpReturn = 0;
    }
#else    
    event->RETURN = false;
#ifdef OGS_SDL2
    if ((keys[CONFIRM_BUTTON] || keys[SDL_SCANCODE_KP_ENTER]) && !tmpReturn) {
#else    
    if ((keys[CONFIRM_BUTTON] || keys[SDLK_KP_ENTER]) && !tmpReturn) {
#endif
        event->RETURN = true;
        tmpReturn = 1;
    }
#ifdef OGS_SDL2
    if (!keys[CONFIRM_BUTTON] && !keys[SDL_SCANCODE_KP_ENTER] && tmpReturn) {
#else
    if (!keys[CONFIRM_BUTTON] && !keys[SDLK_KP_ENTER] && tmpReturn) {
#endif
        tmpReturn = 0;
    }
#endif
    
    event->HYPOTHESE = false;
#if defined(_3DS)
    if (keys&SDLK_h && !event->HYPOTHESE && !tmpHypo) {
#elif defined(OGS_SDL2)
    if (keys[SDL_SCANCODE_LSHIFT] && !event->HYPOTHESE && !tmpHypo) {
#else
    if (keys[SDLK_LSHIFT] && !event->HYPOTHESE && !tmpHypo) {
#endif
        event->HYPOTHESE = true;
        tmpHypo = 1;
    }
#if defined(_3DS)
    if (!(keys&SDLK_h) && tmpHypo) {
#elif defined(OGS_SDL2)
    if (!keys[SDL_SCANCODE_LSHIFT] && tmpHypo) {
#else    
    if (!keys[SDLK_LSHIFT] && tmpHypo) {
#endif
        tmpHypo = 0;
    }
    
    event->MOUSE_ON_OFF = false;
#if defined(_3DS)
    if (keys&SDLK_TAB && !event->MOUSE_ON_OFF && !tmpMouse) {
#elif defined(OGS_SDL2)
    if (keys[SDL_SCANCODE_SPACE] && !event->MOUSE_ON_OFF && !tmpMouse) {
#else
    if (keys[SDLK_SPACE] && !event->MOUSE_ON_OFF && !tmpMouse) {
#endif
        event->MOUSE_ON_OFF = true;
        tmpMouse = 1;
    }
#if defined(_3DS)
    if (!(keys&SDLK_TAB) && tmpMouse) {
#elif defined(OGS_SDL2)
    if (!keys[SDL_SCANCODE_SPACE] && tmpMouse) {
#else
    if (!keys[SDLK_SPACE] && tmpMouse) {
#endif
        tmpMouse = 0;
    }
    
    
    event->MUSIC_ON_OFF = false;
#if defined(_3DS)
    if ((keys&SDLK_m || keys&SDLK_SEMICOLON) && !event->MUSIC_ON_OFF && !tmpMusic) {
#elif defined(OGS_SDL2)
    if ((keys[SDLK_m] || keys[SDL_SCANCODE_SEMICOLON]) && !event->MUSIC_ON_OFF && !tmpMusic) {
#else
    if ((keys[SDLK_m] || keys[SDLK_SEMICOLON]) && !event->MUSIC_ON_OFF && !tmpMusic) {
#endif
        event->MUSIC_ON_OFF = true;
        tmpMusic = 1;
    }
#if defined(_3DS)
    if (!(keys&SDLK_m) && !(keys&SDLK_SEMICOLON) && tmpMusic) {
#elif defined(OGS_SDL2)
    if (!keys[SDLK_m] && !keys[SDL_SCANCODE_SEMICOLON] && tmpMusic) {
#else
    if (!keys[SDLK_m] && !keys[SDLK_SEMICOLON] && tmpMusic) {
#endif
        tmpMusic = 0;
    }
    
    
    /*if ((keys[SDLK_LCTRL] || keys[SDLK_z]) && tmpAction == 0) {
        event->ACTION = true;
        tmpAction = 1;
    } else {
        event->ACTION = false;
    }
    if (!keys[SDLK_LCTRL] && !keys[SDLK_z]) {
        tmpAction = 0;
    }*/
    
}

Event* Keyboard::getEvent() {
    return event;
}

