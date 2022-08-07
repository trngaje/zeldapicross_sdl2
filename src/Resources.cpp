/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include "Common.h"
#include "Resources.h"

Resources Resources::instance=Resources();

Resources::Resources() {
    for (int i = 0; i < 10; i++) {;
        theme[i] = 0;
        map[i] = 0;
        icon[i] = 0;
    }
    for (int i = 0; i < 15; i++) {
        background[i] = 0;
        picrossBG[i] = 0;
    }
    for (int i = 0; i < NB_PICROSS; i++) {
        picross[i] = 0;
    }
    chiffres = 0;
    font = 0;
    link = 0;
    status = 0;
    cadre = 0;
    boss = 0;
    logo = 0;
    titreBG = 0;
    titreLogo = 0;
    linkMenu = 0;
    feeMenu = 0;
    mouse = 0;
    for (int i = 0; i < 3; i++) {
        step[i] = 0;
    }
    introFond1 = 0;
    introFond2 = 0;
    endingFond = 0;
    treeFond = 0;
}

Resources::~Resources() {
    for (int i = 0; i < 10; i++) {
        SDL_FreeSurface(theme[i]);
        SDL_FreeSurface(map[i]);
        SDL_FreeSurface(icon[i]);
    }
    for (int i = 0; i < 15; i++) {
        SDL_FreeSurface(background[i]);
        SDL_FreeSurface(picrossBG[i]);
    }
    for (int i = 0; i < NB_PICROSS; i++) {
        SDL_FreeSurface(picross[i]);
    }
    SDL_FreeSurface(chiffres);
    SDL_FreeSurface(font);
    SDL_FreeSurface(link);
    SDL_FreeSurface(status);
    SDL_FreeSurface(cadre);
    SDL_FreeSurface(boss);
    SDL_FreeSurface(logo);
    SDL_FreeSurface(titreBG);
    SDL_FreeSurface(titreLogo);
    SDL_FreeSurface(mouse);
    for (int i = 0; i < 3; i++) {
        SDL_FreeSurface(step[i]);
    }
    SDL_FreeSurface(introFond1);
    SDL_FreeSurface(introFond2);
    SDL_FreeSurface(endingFond);
    SDL_FreeSurface(treeFond);
}

Resources* Resources::getInstance() {
    return &instance;
}

#ifdef OGS_SDL2
extern SDL_Window* sdlWindow;
#endif

SDL_Surface* Resources::convertImage(SDL_Surface* tmp) {
    if (tmp == NULL) return NULL;
#ifdef _3DS
    return tmp;
#else
#ifdef OGS_SDL2
    SDL_Surface* im = SDL_ConvertSurfaceFormat(tmp,  SDL_GetWindowPixelFormat(sdlWindow), 0);
#elif defined(MIYOO_MINI)
    SDL_Surface* im = SDL_DisplayFormatAlpha(tmp);
#else
    SDL_Surface* im = SDL_DisplayFormat(tmp);
#endif
    SDL_FreeSurface(tmp);
    return im;
#endif
}

SDL_Surface* Resources::getTheme(int i) {
    if (i == 0 || i > 10) {
        return 0;
    }
    if (theme[i-1] == 0) {
        ostringstream im;
        im << i;
        theme[i-1] = IMG_Load(
#ifdef _3DS
            ("romfs:/images/theme/theme" + im.str() + ".png").c_str());
#else
            ("data/images/theme/theme" + im.str() + ".png").c_str());
#endif
        theme[i-1] = convertImage(theme[i-1]);
    }
    return theme[i-1];
}

SDL_Surface* Resources::getChiffres() {
    if (chiffres == 0) {
#ifdef _3DS
        chiffres = IMG_Load("romfs:/images/font/chiffres.png");
#else
        chiffres = IMG_Load("data/images/font/chiffres.png");
#endif
        if (chiffres) {
            SDL_SetColorKey(chiffres,
#ifdef OGS_SDL2
                SDL_TRUE,SDL_MapRGB(chiffres->format,0,0,255));
#else
                SDL_SRCCOLORKEY,SDL_MapRGB(chiffres->format,0,0,255));
#endif
        }
        chiffres = convertImage(chiffres);
    }
    return chiffres;
}

SDL_Surface* Resources::getBackground(int i) {
    if (i < 0 || i > 10) {
        return 0;
    }
    if (background[i] == 0) {
        ostringstream im;
        im << i;
        background[i] = IMG_Load(
#ifdef _3DS
            ("romfs:/images/background/background" + im.str() + ".png").c_str());
#else
            ("data/images/background/background" + im.str() + ".png").c_str());
#endif
        background[i] = convertImage(background[i]);
    }
    return background[i];
}

SDL_Surface* Resources::getPicross(int i) {
    if (i == 0 || i > NB_PICROSS) {
        return 0;
    }
    if (picross[i-1] == 0) {
        ostringstream im;
        im << i;
        picross[i-1] = IMG_Load(
#ifdef _3DS
            ("romfs:/images/picross/picross" + im.str() + ".png").c_str());
#else
            ("data/images/picross/picross" + im.str() + ".bmp").c_str());
#endif
        picross[i-1] = convertImage(picross[i-1]);
    }
    return picross[i-1];
}

SDL_Surface* Resources::getMap(int i) {
    if (i == 0 || i > 10) {
        return 0;
    }
    if (map[i-1] == 0) {
        ostringstream im;
        im << i;
        map[i-1] = IMG_Load(
#ifdef _3DS
            ("romfs:/images/map/map" + im.str() + ".png").c_str());
#else
            ("data/images/map/map" + im.str() + ".png").c_str());
#endif
        if (map[i-1]) {
            SDL_SetColorKey(map[i-1],
#ifdef OGS_SDL2
                SDL_TRUE,SDL_MapRGB(map[i-1]->format,0,0,255));
#else
                SDL_SRCCOLORKEY,SDL_MapRGB(map[i-1]->format,0,0,255));
#endif
        }
        map[i-1] = convertImage(map[i-1]);
    }
    return map[i-1];
}

SDL_Surface* Resources::getIcon(int i) {
    if (i < 0 || i > 10) {
        return 0;
    }
    if (icon[i] == 0) {
        ostringstream im;
        im << i;
        icon[i] = IMG_Load(
#ifdef _3DS
            ("romfs:/images/icon/icon" + im.str() + ".png").c_str());
#else
            ("data/images/icon/icon" + im.str() + ".png").c_str());
#endif
        if (icon[i]) {
            SDL_SetColorKey(icon[i],
#ifdef OGS_SDL2
                SDL_TRUE,SDL_MapRGB(icon[i]->format,0,0,255));
#else
                SDL_SRCCOLORKEY,SDL_MapRGB(icon[i]->format,0,0,255));
#endif
        }
        icon[i] = convertImage(icon[i]);
    }
    return icon[i];
}

SDL_Surface* Resources::getPicrossBG(int i) {
    if (i == 0 || i > 15) {
        return 0;
    }
    if (picrossBG[i-1] == 0) {
        ostringstream im;
        im << i;
        picrossBG[i-1] = IMG_Load(
#ifdef _3DS
            ("romfs:/images/background/picross" + im.str() + ".png").c_str());
#else
            ("data/images/background/picross" + im.str() + ".png").c_str());
#endif
        picrossBG[i-1] = convertImage(picrossBG[i-1]);
    }
    return picrossBG[i-1];
}

SDL_Surface* Resources::getFont() {
    if (font == 0) {
    	/* add korean font */
#ifdef _3DS
        font = IMG_Load("romfs:/images/font/font.png");
#else
        font = IMG_Load("data/images/font/font_kor.png");
        //font = IMG_Load("data/images/font/font.png");
#endif
        if (font) {
#ifdef OGS_SDL2
            SDL_SetColorKey(font,SDL_TRUE,
#else
            SDL_SetColorKey(font,SDL_SRCCOLORKEY,
#endif
                SDL_MapRGB(font->format,0,0,255));
        }
        font = convertImage(font);
    }
    return font;
}

SDL_Surface* Resources::getLink() {
    if (link == 0) {
#ifdef _3DS
        link = IMG_Load("romfs:/images/link/link.png");
#else
        link = IMG_Load("data/images/link/link.png");
#endif
        if (link) {
#ifdef OGS_SDL2
            SDL_SetColorKey(link,SDL_TRUE,
#else
            SDL_SetColorKey(link,SDL_SRCCOLORKEY,
#endif
                SDL_MapRGB(link->format,0,0,255));
        }
        link = convertImage(link);
    }
    return link;
}

SDL_Surface* Resources::getStatus() {
    if (status == 0) {
#ifdef _3DS
        status = IMG_Load("romfs:/images/icon/objets.png");
#else
        status = IMG_Load("data/images/icon/objets.png");
#endif
        if (status) {
            SDL_SetColorKey(status,
#ifdef OGS_SDL2
                SDL_TRUE,SDL_MapRGB(status->format,0,0,255));
#else
                SDL_SRCCOLORKEY,SDL_MapRGB(status->format,0,0,255));
#endif
        }
        status = convertImage(status);
    }
    return status;
}

SDL_Surface* Resources::getCadre() {
    if (cadre == 0) {
#ifdef _3DS
        cadre = IMG_Load("romfs:/images/menu/bord.png");
#else
        cadre = IMG_Load("data/images/menu/bord.png");
#endif
        if (cadre) {
            SDL_SetColorKey(cadre,
#ifdef OGS_SDL2
                SDL_TRUE,SDL_MapRGB(cadre->format,0,0,255));
#else
                SDL_SRCCOLORKEY,SDL_MapRGB(cadre->format,0,0,255));
#endif
        }
        cadre = convertImage(cadre);
    }
    return cadre;
}

SDL_Surface* Resources::getBoss() {
    if (boss == 0) {
#ifdef _3DS
        boss = IMG_Load("romfs:/images/map/boss.png");
#else
        boss = IMG_Load("data/images/map/boss.png");
#endif
        if (boss) {
            SDL_SetColorKey(boss,
#ifdef OGS_SDL2
                SDL_TRUE,SDL_MapRGB(boss->format,0,0,255));
#else
                SDL_SRCCOLORKEY,SDL_MapRGB(boss->format,0,0,255));
#endif
        }
        boss = convertImage(boss);
    }
    return boss;
}

SDL_Surface* Resources::getLogo() {
    if (logo == 0) {
#ifdef _3DS
        logo = IMG_Load("romfs:/images/logos/logo.png");
#else
        logo = IMG_Load("data/images/logos/logo.png");
#endif
        logo = convertImage(logo);
    }
    return logo;
}

SDL_Surface* Resources::getTitreBG() {
    if (titreBG == 0) {
#ifdef _3DS
        titreBG = IMG_Load("romfs:/images/logos/fond.png");
#else
        titreBG = IMG_Load("data/images/logos/fond.png");
#endif
        titreBG = convertImage(titreBG);
    }
    return titreBG;
}

SDL_Surface* Resources::getTitreLogo() {
    if (titreLogo == 0) {
#ifdef _3DS
        titreLogo = IMG_Load("romfs:/images/logos/titre.png");
#else
        titreLogo = IMG_Load("data/images/logos/titre.png");
#endif
        if (titreLogo) {
            SDL_SetColorKey(titreLogo,
#ifdef OGS_SDL2
                SDL_TRUE,SDL_MapRGB(titreLogo->format,0,0,255));
#else
                SDL_SRCCOLORKEY,SDL_MapRGB(titreLogo->format,0,0,255));
#endif
        }
        titreLogo = convertImage(titreLogo);
    }
    return titreLogo;
}

SDL_Surface* Resources::getCadreMenu() {
    if (cadreMenu == 0) {
#ifdef _3DS
        cadreMenu = IMG_Load("romfs:/images/menu/cadres.png");
#else
        cadreMenu = IMG_Load("data/images/menu/cadres.png");
#endif
        if (cadreMenu) {
            SDL_SetColorKey(cadreMenu,
#ifdef OGS_SDL2
                SDL_TRUE,SDL_MapRGB(cadreMenu->format,0,0,255));
#else
                SDL_SRCCOLORKEY,SDL_MapRGB(cadreMenu->format,0,0,255));
#endif
        }
        cadreMenu = convertImage(cadreMenu);
    }
    return cadreMenu;
}

SDL_Surface* Resources::getLinkMenu() {
    if (linkMenu == 0) {
#ifdef _3DS
        linkMenu = IMG_Load("romfs:/images/menu/curseur.png");
#else
        linkMenu = IMG_Load("data/images/menu/curseur.png");
#endif
        if (linkMenu) {
            SDL_SetColorKey(linkMenu,
#ifdef OGS_SDL2
                SDL_TRUE,SDL_MapRGB(linkMenu->format,0,0,255));
#else
                SDL_SRCCOLORKEY,SDL_MapRGB(linkMenu->format,0,0,255));
#endif
        }
        linkMenu = convertImage(linkMenu);
    }
    return linkMenu;
}

SDL_Surface* Resources::getFeeMenu() {
    if (feeMenu == 0) {
#ifdef _3DS
        feeMenu = IMG_Load("romfs:/images/menu/fee.png");
#else
        feeMenu = IMG_Load("data/images/menu/fee.png");
#endif
        feeMenu = convertImage(feeMenu);
    }
    return feeMenu;
}

SDL_Surface* Resources::getMouse() {
    if (mouse == 0) {
#ifdef _3DS
        mouse = IMG_Load("romfs:/images/icon/mouse.png");
#else
        mouse = IMG_Load("data/images/icon/mouse.png");
#endif
        if (mouse) {
            SDL_SetColorKey(mouse,
#ifdef OGS_SDL2
                SDL_TRUE,SDL_MapRGB(mouse->format,0,0,255));
#else
                SDL_SRCCOLORKEY,SDL_MapRGB(mouse->format,0,0,255));
#endif
        }
        mouse = convertImage(mouse);
    }
    return mouse;
}

SDL_Surface* Resources::getStep(int i) {
    if (i < 0 || i > 2) {
        return 0;
    }
    if (step[i] == 0) {
        ostringstream im;
        im << (i + 1);
        step[i] = IMG_Load(
#ifdef _3DS
            ("romfs:/images/logos/intro" + im.str() + ".png").c_str());
#else
            ("data/images/logos/intro" + im.str() + ".png").c_str());
#endif
        step[i] = convertImage(step[i]);
    }
    return step[i];
}

SDL_Surface* Resources::getIntroFond1() {
    if (introFond1 == 0) {
#ifdef _3DS
        introFond1 = IMG_Load("romfs:/images/logos/fond1.png");
#else
        introFond1 = IMG_Load("data/images/logos/fond1.png");
#endif
        if (introFond1) {
            SDL_SetColorKey(introFond1,
#ifdef OGS_SDL2
                SDL_TRUE,SDL_MapRGB(introFond1->format,0,0,255));
#else
                SDL_SRCCOLORKEY,SDL_MapRGB(introFond1->format,0,0,255));
#endif
        }
        introFond1 = convertImage(introFond1);
    }
    return introFond1;
}

SDL_Surface* Resources::getIntroFond2() {
    if (introFond2 == 0) {
#ifdef _3DS
        introFond2 = IMG_Load("romfs:/images/logos/fond2.png");
#else
        introFond2 = IMG_Load("data/images/logos/fond2.png");
#endif
        introFond2 = convertImage(introFond2);
    }
    return introFond2;
}

SDL_Surface* Resources::getEndingFond() {
    if (endingFond == 0) {
#ifdef _3DS
        endingFond = IMG_Load("romfs:/images/logos/fin.png");
#else
        endingFond = IMG_Load("data/images/logos/fin.png");
#endif
        endingFond = convertImage(endingFond);
    }
    return endingFond;
}

SDL_Surface* Resources::getTreeFond() {
    if (treeFond == 0) {
#ifdef _3DS
        treeFond = IMG_Load("romfs:/images/logos/arbre.png");
#else
        treeFond = IMG_Load("data/images/logos/arbre.png");
#endif
        treeFond = convertImage(treeFond);
    }
    return treeFond;
}

