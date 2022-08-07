/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#ifndef __AUDIO_H__
#define __AUDIO_H__

//#include <FMOD/fmod.h>

#ifndef _3DS
#ifdef OGS_SDL2
#include <SDL2/SDL_mixer.h>
#else
#include <SDL/SDL_mixer.h>
#endif

#define FSOUND_FREE 1
#endif
class Audio {
    public :
        static Audio* getInstance();
#ifdef _3DS
        void init();
#endif
        void playSound(int id, int chl = FSOUND_FREE);
        void stopSound();
        void playMusic(int id);
        void stopMusic();
        void replayMusic();
        void setVolume(int vol);
        void setVolson(int volson);
    private :
        Audio();
        ~Audio();
        static Audio instance;
        void loadSounds();
        void freeSounds();
#ifdef _3DS
        FMUSIC_MODULE* choixMusique(int id);
        
        bool SOUND;
#endif
        int previous_volume;
        int previous_volson;
        int volume;
        int musiqueId;
        bool playing;
#ifdef _3DS
        FSOUND_SAMPLE** sons;
        FMUSIC_MODULE* music;
#endif

};

#endif  // Audio.h
