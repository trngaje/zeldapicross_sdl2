/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <sstream>
#include <fstream>
#include <iostream>
#ifdef OGS_SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#endif
#include "Audio.h"

Mix_Music* music;
Mix_Chunk* sfx_id[16];

Audio Audio::instance=Audio();

static Mix_Music* choixMusique(int id) 
{
    switch (id) {
        case 1 : return Mix_LoadMUS("data/music/Plaine.ogg");
        case 2 : return Mix_LoadMUS("data/music/Home.ogg");
        case 3 : return Mix_LoadMUS("data/music/Lac.ogg");
        case 4 : return Mix_LoadMUS("data/music/Cocorico.ogg");
        case 5 : return Mix_LoadMUS("data/music/Mont.ogg");
        case 6 : return Mix_LoadMUS("data/music/BoisPerdus.ogg");
        case 7 : return Mix_LoadMUS("data/music/Jeu.ogg");
        case 8 : return Mix_LoadMUS("data/music/Chateau.ogg");
        case 9 : return Mix_LoadMUS("data/music/Boss.ogg");
        case 10 : return Mix_LoadMUS("data/music/DFinal.ogg");
        case 11 : return Mix_LoadMUS("data/music/BossF.ogg");
        case 12 : return Mix_LoadMUS("data/music/Zelda.ogg");
        case 190 : return Mix_LoadMUS("data/music/Selection.ogg");
        case 195 : return Mix_LoadMUS("data/music/Magasin.ogg");
        case 200 : return Mix_LoadMUS("data/music/Titre.ogg");
        case 210 : return Mix_LoadMUS("data/music/Debut.ogg");
        case 220 : return Mix_LoadMUS("data/music/Mort.ogg");
        case 230 : return Mix_LoadMUS("data/music/Fin.ogg");
        default : return Mix_LoadMUS("data/music/Plaine.ogg");
    }
}

Audio::Audio() : volume(0), musiqueId(0), playing(false) 
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) 
	{
		printf("Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
	Mix_AllocateChannels(16);
    music = NULL;
	loadSounds();

}

Audio::~Audio() {
	freeSounds();
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	Mix_CloseAudio();
}

Audio* Audio::getInstance() {
    return &instance;
}

void Audio::setVolume(int vol) 
{
}

void Audio::setVolson(int volson) 
{
}

void Audio::loadSounds() {
    sfx_id[0] = Mix_LoadWAV("data/sound/text.ogg"); // lettres
    sfx_id[1] = Mix_LoadWAV("data/sound/menu1.ogg"); // menu 1
    sfx_id[2] = Mix_LoadWAV("data/sound/menu2.ogg"); // menu 2
    sfx_id[3] = Mix_LoadWAV("data/sound/menu3.ogg"); // menu 3
    sfx_id[4] = Mix_LoadWAV("data/sound/surprise.ogg"); // surprise
    sfx_id[5] = Mix_LoadWAV("data/sound/monte.ogg"); // monte
    sfx_id[6] = Mix_LoadWAV("data/sound/descend.ogg"); // descend
    sfx_id[7] = Mix_LoadWAV("data/sound/bomb.ogg"); // bombe
    sfx_id[8] = Mix_LoadWAV("data/sound/textnext.ogg"); // suite texte
    sfx_id[9] = Mix_LoadWAV("data/sound/textend.ogg"); // fin texte
    sfx_id[10] = Mix_LoadWAV("data/sound/happy.ogg"); // trouve objet
    sfx_id[11] = Mix_LoadWAV("data/sound/sword.ogg"); // ??
    sfx_id[12] = Mix_LoadWAV("data/sound/Sword360.ogg"); // spin
    sfx_id[13] = Mix_LoadWAV("data/sound/stamp.ogg"); // pose bombe
    sfx_id[14] = Mix_LoadWAV("data/sound/danger.ogg"); // danger
    sfx_id[15] = Mix_LoadWAV("data/sound/hurt.ogg"); // link se blesse
    Mix_PlayChannel(-1, sfx_id[0], 0);
    
}

void Audio::freeSounds() {
	unsigned char i;
	for (i=0;i<16;i++)
	{
		if (sfx_id[i])
		{
			Mix_FreeChunk(sfx_id[i]);
			sfx_id[i] = NULL;
		}
	}
}

void Audio::playSound(int id, int chl) 
{
	Mix_PlayChannel(-1, sfx_id[id], 0) ;
}

void Audio::stopSound() 
{
	Mix_HaltChannel(-1);
	musiqueId=0;
}

void Audio::playMusic(int id) 
{
	if (musiqueId != id || !playing) 
	{
		musiqueId = id;
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = choixMusique(id);
		Mix_PlayMusic(music, -1);
		playing = true;
	}
}

void Audio::stopMusic() {
	 Mix_HaltMusic();
	 playing = false;
}

void Audio::replayMusic() {
	 Mix_PlayMusic(music, -1);
	 playing = true;
}
