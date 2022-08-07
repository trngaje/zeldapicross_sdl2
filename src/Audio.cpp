/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <sstream>
#include <fstream>
#include <iostream>

#if defined(_3DS)
#include "3ds/SDL_3ds.h"
#include <3ds.h>
#elif defined(OGS_SDL2)
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#else
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#endif
#include "Audio.h"

#ifndef _3DS
Mix_Music* music;
Mix_Chunk* sfx_id[16];
#endif

Audio Audio::instance=Audio();

#ifdef _3DS
FMUSIC_MODULE* Audio::choixMusique(int id) {
    switch (id) {
        case 1 : return FMUSIC_LoadSong("romfs:/music/Plaine.raw");
        case 2 : return FMUSIC_LoadSong("romfs:/music/Home.raw");
        case 3 : return FMUSIC_LoadSong("romfs:/music/Lac.raw");
        case 4 : return FMUSIC_LoadSong("romfs:/music/Cocorico.raw");
        case 5 : return FMUSIC_LoadSong("romfs:/music/Mont.raw");
        case 6 : return FMUSIC_LoadSong("romfs:/music/BoisPerdus.raw");
        case 7 : return FMUSIC_LoadSong("romfs:/music/Jeu.raw");
        case 8 : return FMUSIC_LoadSong("romfs:/music/Chateau.raw");
        case 9 : return FMUSIC_LoadSong("romfs:/music/Boss.raw");
        case 10 : return FMUSIC_LoadSong("romfs:/music/DFinal.raw");
        case 11 : return FMUSIC_LoadSong("romfs:/music/BossF.raw");
        case 12 : return FMUSIC_LoadSong("romfs:/music/Zelda.raw");
        case 190 : return FMUSIC_LoadSong("romfs:/music/Selection.raw");
        case 195 : return FMUSIC_LoadSong("romfs:/music/Magasin.raw");
        case 200 : return FMUSIC_LoadSong("romfs:/music/Titre.raw");
        case 210 : return FMUSIC_LoadSong("romfs:/music/Debut.raw");
        case 220 : return FMUSIC_LoadSong("romfs:/music/Mort.raw");
        case 230 : return FMUSIC_LoadSong("romfs:/music/Fin.raw");
        default : return FMUSIC_LoadSong("romfs:/music/Plaine.raw");
    }
}
#else
static Mix_Music* choixMusique(int id) 
{
    switch (id) {
#ifdef MIYOO_MINI
	// ogg files are not supported in miyoo sdl mixer
        case 1 : return Mix_LoadMUS("data/music/Plaine.mp3");
        case 2 : return Mix_LoadMUS("data/music/Home.mp3");
        case 3 : return Mix_LoadMUS("data/music/Lac.mp3");
        case 4 : return Mix_LoadMUS("data/music/Cocorico.mp3");
        case 5 : return Mix_LoadMUS("data/music/Mont.mp3");
        case 6 : return Mix_LoadMUS("data/music/BoisPerdus.mp3");
        case 7 : return Mix_LoadMUS("data/music/Jeu.mp3");
        case 8 : return Mix_LoadMUS("data/music/Chateau.mp3");
        case 9 : return Mix_LoadMUS("data/music/Boss.mp3");
        case 10 : return Mix_LoadMUS("data/music/DFinal.mp3");
        case 11 : return Mix_LoadMUS("data/music/BossF.mp3");
        case 12 : return Mix_LoadMUS("data/music/Zelda.mp3");
        case 190 : return Mix_LoadMUS("data/music/Selection.mp3");
        case 195 : return Mix_LoadMUS("data/music/Magasin.mp3");
        case 200 : return Mix_LoadMUS("data/music/Titre.mp3");
        case 210 : return Mix_LoadMUS("data/music/Debut.mp3");
        case 220 : return Mix_LoadMUS("data/music/Mort.mp3");
        case 230 : return Mix_LoadMUS("data/music/Fin.mp3");
        default : return Mix_LoadMUS("data/music/Plaine.mp3");	
#else		
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
#endif
    }
}
#endif

Audio::Audio() : volume(0), musiqueId(0), playing(false) 
{
#ifndef _3DS	
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) 
	{
		fprintf(stderr, "Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}
	
#ifdef MIYOO_MINI
	int flags = MIX_INIT_OGG | MIX_INIT_MOD;
	int initted = Mix_Init(flags);
	if ((initted & flags) != flags) {
		fprintf(stderr, "Mix_Init: Failed to init required ogg and mod support!\n");
		fprintf(stderr, "Mix_Init: %s\n", Mix_GetError());
		// handle error
	}
#endif

	Mix_AllocateChannels(16);
    music = NULL;
	loadSounds();

#endif
}

Audio::~Audio() {
#ifdef _3DS
    if (SOUND) {
        freeSounds();
        FMUSIC_StopSong(music);
        FMUSIC_SetMasterVolume(music, previous_volume);
        FMUSIC_FreeSong(music);
        FSOUND_SetSFXMasterVolume(previous_volson);
        FSOUND_Close();
    }
#else
	freeSounds();
	Mix_HaltMusic();
	Mix_FreeMusic(music);
	Mix_CloseAudio();
#endif
}

#ifdef _3DS
void Audio::init() {
   SOUND = FSOUND_Init(44100, 32, 0);
    music = NULL;
//SOUND=0; // to remove -> hack for no sound mode
//setVolume(32);
//setVolson(32);
    if (SOUND) {
        previous_volume = -1;
        previous_volson = FSOUND_GetSFXMasterVolume();
        loadSounds();
    }
}
#endif

Audio* Audio::getInstance() {
    return &instance;
}

void Audio::setVolume(int vol) 
{
#ifdef _3DS
	volume=vol*4;
    if (previous_volume == -1) previous_volume = FMUSIC_GetMasterVolume(music);
    FMUSIC_SetMasterVolume(music, volume);
#endif
}

void Audio::setVolson(int volson) 
{
#ifdef _3DS
	FSOUND_SetSFXMasterVolume(volson*4);
#endif
}

void Audio::loadSounds() {
#if defined(_3DS)	
    sons = new FSOUND_SAMPLE*[16];
    
    sons[0] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/text.ogg",0,0,0); // lettres
    sons[1] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/menu1.ogg",0,0,0); // menu 1
    sons[2] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/menu2.ogg",0,0,0); // menu 2
    sons[3] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/menu3.ogg",0,0,0); // menu 3
    sons[4] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/surprise.ogg",0,0,0); // surprise
    sons[5] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/monte.ogg",0,0,0); // monte
    sons[6] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/descend.ogg",0,0,0); // descend
    sons[7] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/bomb.ogg",0,0,0); // bombe
    sons[8] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/textnext.ogg",0,0,0); // suite texte
    sons[9] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/textend.ogg",0,0,0); // fin texte
    sons[10] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/happy.ogg",0,0,0); // trouve objet
    sons[11] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/sword.ogg",0,0,0); // ??
    sons[12] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/Sword360.ogg",0,0,0); // spin
    sons[13] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/stamp.ogg",0,0,0); // pose bombe
    sons[14] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/danger.ogg",0,0,0); // danger
    sons[15] = FSOUND_Sample_Load(FSOUND_FREE, "romfs:/sound/hurt.ogg",0,0,0); // link se blesse
 
#elif defined(MIYOO_MINI)
    sfx_id[0] = Mix_LoadWAV("data/sound/text.mp3"); // lettres
    sfx_id[1] = Mix_LoadWAV("data/sound/menu1.mp3"); // menu 1
    sfx_id[2] = Mix_LoadWAV("data/sound/menu2.mp3"); // menu 2
    sfx_id[3] = Mix_LoadWAV("data/sound/menu3.mp3"); // menu 3
    sfx_id[4] = Mix_LoadWAV("data/sound/surprise.mp3"); // surprise
    sfx_id[5] = Mix_LoadWAV("data/sound/monte.mp3"); // monte
    sfx_id[6] = Mix_LoadWAV("data/sound/descend.mp3"); // descend
    sfx_id[7] = Mix_LoadWAV("data/sound/bomb.mp3"); // bombe
    sfx_id[8] = Mix_LoadWAV("data/sound/textnext.mp3"); // suite texte
    sfx_id[9] = Mix_LoadWAV("data/sound/textend.mp3"); // fin texte
    sfx_id[10] = Mix_LoadWAV("data/sound/happy.mp3"); // trouve objet
    sfx_id[11] = Mix_LoadWAV("data/sound/sword.mp3"); // ??
    sfx_id[12] = Mix_LoadWAV("data/sound/Sword360.mp3"); // spin
    sfx_id[13] = Mix_LoadWAV("data/sound/stamp.mp3"); // pose bombe
    sfx_id[14] = Mix_LoadWAV("data/sound/danger.mp3"); // danger
    sfx_id[15] = Mix_LoadWAV("data/sound/hurt.mp3"); // link se blesse
#else
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
#endif

#ifndef _3DS
	for(int i=0; i<16; i++) {
		if (sfx_id[i] == NULL) {
			fprintf(stderr, "[trngaje] sfx_id[%d] is NULL\n", i);
		}
	}
	
    if(Mix_PlayChannel(-1, sfx_id[0], 0) < 0) {
		fprintf(stderr, "[trngaje] loadsounds : id=0 error\n");
	}
#endif    
}

void Audio::freeSounds() {
#ifdef _3DS
    if (SOUND) {
        for (int i = 0; i < 16; i++) FSOUND_Sample_Free(sons[i]);
        delete[] sons;
    }
#else
	unsigned char i;
	for (i=0;i<16;i++)
	{
		if (sfx_id[i])
		{
			Mix_FreeChunk(sfx_id[i]);
			sfx_id[i] = NULL;
		}
	}
#endif
}

void Audio::playSound(int id, int chl) 
{
#ifdef _3DS
    if (SOUND) FSOUND_PlaySound(chl, sons[id]);
#else
	if (Mix_PlayChannel(-1, sfx_id[id], 0) < 0) {
		fprintf(stderr, "[trngaje] playsound : id=%d error\n", id);
	}
#endif		
}

void Audio::stopSound() 
{
#ifdef _3DS
    if (SOUND) {
    	FSOUND_StopSound(FSOUND_ALL); 
    	musiqueId=0;
    }
#else
	Mix_HaltChannel(-1);
	musiqueId=0;
#endif
}

void Audio::playMusic(int id) 
{
#ifdef _3DS
    if (SOUND) {
        if (musiqueId != id || !playing) {
            musiqueId = id;
            FMUSIC_StopSong(music);
            FMUSIC_FreeSong(music);
            music = choixMusique(id);
            if (previous_volume == -1) previous_volume = FMUSIC_GetMasterVolume(music);
            FMUSIC_SetMasterVolume(music, volume);
            FMUSIC_SetLooping(music, 1);
            FMUSIC_PlaySong(music);
            playing = true;
        }
    }
#else
	if (musiqueId != id || !playing) 
	{
		musiqueId = id;
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = choixMusique(id);
		if (!music) {
			fprintf(stderr, "[trngaje] choixMusique : id=%d error\n", id);
		}
		else {
			if (Mix_PlayMusic(music, -1) < 0) {
				fprintf(stderr, "[trngaje] playMusic : id=%d error\n", id);
			}
		}
		playing = true;
	}
#endif
}

void Audio::stopMusic() {
#ifdef _3DS
    if (SOUND) FMUSIC_StopSong(music);
    playing = false;
#else
	 Mix_HaltMusic();
	 playing = false;
#endif
}

void Audio::replayMusic() {
#ifdef _3DS
    if (SOUND) FMUSIC_PlaySong(music);
    playing = true;
#else
	 Mix_PlayMusic(music, -1);
	 playing = true;
#endif
}
