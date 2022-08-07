/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <cstdlib>
#include <ctime>
#ifdef _3DS
#include <sys/stat.h>
#endif

#include "Window.h"

int main(int argc, char** argv) {
    if (argc && argv); //pour ?iter un warning.....
    
    std::srand(std::time(NULL));

#ifdef _3DS
	mkdir("/3ds", 0777);
	mkdir("/3ds/ZeldaPicross", 0777);
	mkdir("/3ds/ZeldaPicross/save", 0777);
	mkdir("/3ds/ZeldaPicross//zpicross", 0777);
#endif   
    Window* window = new Window(true);
    
    window->loop();
    
    delete window;
    
    return 0;
}
