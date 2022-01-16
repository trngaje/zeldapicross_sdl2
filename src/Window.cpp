/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifdef OGS_SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL2_rotozoom.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>
#endif

#include "Window.h"
#include "Keyboard.h"
#include "Event.h"
#include "Game.h"
#include "Audio.h"

SDL_Surface* init(bool* zoom);

Window::Window(bool full) : fullscreen(full), zoom(false) {
    gpScreen = init(&zoom);
}

Window::~Window() {
    SDL_ShowCursor(SDL_ENABLE);
    SDL_Quit();
}

#ifdef OGS_SDL2
SDL_Window* sdlWindow=NULL;
SDL_Surface* sdlSurface=NULL;
int lcd_width, lcd_height;
#endif
SDL_Surface* init(bool* zoom) // initialise SDL
{
    if(SDL_Init(SDL_INIT_VIDEO) == -1) 
    {
        printf("Could not load SDL : %s\n", SDL_GetError());
        return NULL;
    }
    
	if(SDL_Init(SDL_INIT_AUDIO)==-1) 
	{
		printf("SDL_Init: %s\n", SDL_GetError());
		exit(1);
	}
    
    atexit(SDL_Quit);

#ifdef OGS_SDL2
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
        lcd_width = DM.w;
        lcd_height = DM.h;

	//printf("[trngaje] detected resolution = %d x %d\n", DM.w, DM.h);
 
	sdlWindow = SDL_CreateWindow("Zelda Picross",
                              SDL_WINDOWPOS_UNDEFINED,  
                              SDL_WINDOWPOS_UNDEFINED,  
                              lcd_width, lcd_height,
                              SDL_WINDOW_OPENGL); 
#else
    SDL_WM_SetCaption("Zelda Picross",NULL);
    SDL_Surface* icon = SDL_LoadBMP("data/images/logos/crayon.ico");
    SDL_SetColorKey(icon,SDL_SRCCOLORKEY,SDL_MapRGB(icon->format,0,0,0));
    SDL_WM_SetIcon(icon,NULL);
#endif
    SDL_ShowCursor(SDL_DISABLE);


    /*SDL_Rect** modes;
    int gBpp = 0;
    
    modes = SDL_ListModes(NULL,SDL_FULLSCREEN|SDL_HWSURFACE);
    if (modes == (SDL_Rect**)-1) gBpp = 1;
    else {
        for (int i = 0; modes[i]; ++i) {
            if (modes[i]->w == 320 && modes[i]->h == 240) {
                gBpp = 1; break;
            }
        }
    }
    
    if(!gBpp) {
        *zoom = true;
        return SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
    } else {*/
    
#ifdef OGS_SDL2
    sdlSurface = SDL_GetWindowSurface(sdlWindow);
	return SDL_CreateRGBSurface(SDL_SWSURFACE, lcd_width, lcd_height, 32, 0, 0, 0, 0);
#else
        return SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
#endif
    /*}*/
}

void Window::loop() {
    
    if (gpScreen == NULL) {
        return;
    }
    
#ifdef OGS_SDL2
   SDL_Rect src;
    src.w=320; src.h=240; src.y=0; src.x=0;

    int scale_w, scale_h, scale;
    scale_w = (lcd_width / src.w);
    scale_h = (lcd_height / src.h);
    if (scale_w <= scale_h)
        scale = scale_w;
    else
        scale = scale_h;

    SDL_Rect dst;
    if (scale == 1) {
        dst.w=lcd_width;
        dst.h=lcd_height;
        dst.x=0;
        dst.y=0;
    }
    else {
        dst.w=src.w * scale;
        dst.h=src.h * scale;
        dst.x=(lcd_width - dst.w) / 2;
        dst.y=(lcd_height - dst.h) / 2;
    }
#endif
    /*SDL_Rect src;
    SDL_Rect dst;
    src.w=640; src.h=480; src.y=0;src.x=0;dst.x=0; dst.y=0;*/
    
    //SDL_Surface* gpScreen2 = SDL_CreateRGBSurface(SDL_SWSURFACE, 320, 240, 16, 0, 0, 0, 0);
    //SDL_Surface* gpScreen3 = NULL;
    
    Event* event;
    
    bool gLoop = true;
    
    Uint32 lastAnimTime = SDL_GetTicks();
    
    Keyboard* gpKeyboard = new Keyboard();
    Game* gpGame = Game::getInstance();
    gpGame->init();
    
    while (gLoop) {
        
        
        gpKeyboard->pollEvent();
        event = gpKeyboard->getEvent();
        
        gLoop = handleEvent(event, gpGame);
        
        gpGame->loop();
        
        gpGame->draw(gpScreen);
        
        
        /*if (zoom || !fullscreen) {
            SDL_FreeSurface(gpScreen3);
            gpScreen3 = zoomSurface(gpScreen2, 2, 2, 0);
            SDL_BlitSurface(gpScreen3, &src, gpScreen, &dst);
        } else {
            SDL_BlitSurface(gpScreen2, &src, gpScreen, &dst);
        }*/
#ifdef OGS_SDL2
		/* test routine */
		//SDL_FillRect(gpScreen, NULL, SDL_MapRGB(gpScreen->format, 255, 0, 0));
		SDL_BlitScaled(gpScreen, &src, sdlSurface, &dst);
		SDL_UpdateWindowSurface(sdlWindow);
#else        
        SDL_Flip(gpScreen);
#endif        
        if (SDL_GetTicks() < lastAnimTime + 20) {
            SDL_Delay(lastAnimTime+20-SDL_GetTicks());
        }
        lastAnimTime = SDL_GetTicks();
    
    }
    
    Audio::getInstance()->stopMusic();
    
    delete gpKeyboard;
    
   // SDL_FreeSurface(gpScreen2);
   // SDL_FreeSurface(gpScreen3);
    
}

bool Window::handleEvent(Event* event, Game* gpGame) {
    if (event->FULLSCREEN) {
        event->FULLSCREEN = false;
        toggleFullScreen();
        return true;
    }
    gpGame->handleEvent(event);
    return (!event->QUIT);
}

void Window::toggleFullScreen() {
#ifdef OGS_SDL2
	int gFullScreen = 0;
#else
    int gFullScreen = (fullscreen ? 0 : SDL_FULLSCREEN);
#endif
    gFullScreen ? SDL_ShowCursor(SDL_DISABLE) : SDL_ShowCursor(SDL_ENABLE);
    /*if (zoom || gFullScreen == 0) {
        gpScreen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE
                                    |SDL_DOUBLEBUF|gFullScreen);
    } else {*/
#ifdef OGS_SDL2
		gpScreen = SDL_CreateRGBSurface(SDL_SWSURFACE, lcd_width, lcd_height, 32, 0, 0, 0, 0);
#else
        gpScreen = SDL_SetVideoMode(320, 240, 16, SDL_SWSURFACE);
#endif
    /*}*/
    fullscreen = (gFullScreen != 0);
}

    
