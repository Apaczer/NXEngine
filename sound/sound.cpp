/* SOUND.C
  PXT/SS/Org sound interface
*/

#include <stdio.h>
#include <string.h>

#ifdef _SDL_MIXER
#include <SDL_mixer.h>

Mix_Music *music_xm;
#endif

#include "../nx.h"
#include "../settings.h"
#include "pxt.h"
#include "sound.h"
#include "sound.fdh"

#define MUSIC_OFF		0
#define MUSIC_ON		1
#define MUSIC_BOSS_ONLY	2
static int lastsong = 0;		// this holds the previous song, for <RMU
static int cursong = 0;

// there are more than this around 9b; those are drums and are loaded by the org module
#define NUM_SOUNDS		0x75
#define ORG_VOLUME		75

const char *org_names[] =
{
    NULL,
    "wanpaku", "anzen", "gameover", "gravity", "weed", "mdown2", "fireeye",
    "vivi", "mura", "fanfale1", "ginsuke", "cemetery", "plant", "kodou", "fanfale3",
    "fanfale2", "dr", "escape", "jenka", "maze", "access", "ironh", "grand",
    "curly", "oside", "requiem", "wanpak2", "quiet", "lastcave", "balcony", "lastbtl",
    "lastbt3", "ending", "zonbie", "bdown", "hell", "jenka2", "marine", "ballos",
    "toroko", "white", "azarashi", NULL
};

static const char bossmusic[] = { 4, 7, 10, 11, 15, 16, 17, 18, 21, 22, 31, 33, 35, 0 };

static const char *pxt_dir = "./pxt/";

#ifndef _SDL_MIXER
static const char *org_dir = "./org/";
#else
static const char *xm_dir = "./xm/";
#endif

static const char *sndcache = "sndcache.pcm";
static const char *org_wavetable = "wavetable.dat";

bool sound_init(void)
{
    if (SSInit()) return 1;
    if (pxt_init()) return 1;
    if (pxt_LoadSoundFX(pxt_dir, sndcache, NUM_SOUNDS)) return 1;

    if (org_init(org_wavetable, pxt_dir, ORG_VOLUME))
    {
        staterr("Music failed to initialize");
        return 1;
    }

    return 0;
}

void sound_close(void)
{
    pxt_freeSoundFX();
    SSClose();
}

/*
void c------------------------------() {}
*/

void sound(int snd)
{
    if (!settings->sound_enabled)
        return;

    pxt_Stop(snd);
    pxt_Play(-1, snd, 0);
}

void sound_loop(int snd)
{
    if (!settings->sound_enabled)
        return;

    pxt_Play(-1, snd, -1);
}

void sound_stop(int snd)
{
    pxt_Stop(snd);
}

bool sound_is_playing(int snd)
{
    return pxt_IsPlaying(snd);
}


void StartStreamSound(int freq)
{
    // pxt_ChangePitch(SND_STREAM1, some_formula);
    // pxt_ChangePitch(SND_STREAM2, some_other_formula);
    sound_loop(SND_STREAM1);
    sound_loop(SND_STREAM2);
}

void StartPropSound(void)
{
    sound_loop(SND_PROPELLOR);
}

void StopLoopSounds(void)
{
    sound_stop(SND_STREAM1);
    sound_stop(SND_STREAM2);
    sound_stop(SND_PROPELLOR);
}

/*
void c------------------------------() {}
*/

void music(int songno)
{
    if (songno == cursong)
        return;

    lastsong = cursong;
    cursong = songno;

    stat(" >> music(%d)", songno);

    if (songno != 0 && !should_music_play(songno, settings->music_enabled))
    {
        stat("Not playing track %d because music_enabled is %d", songno, settings->music_enabled);
        org_stop();
        return;
    }

    start_track(songno);
}


bool should_music_play(int songno, int musicmode)
{

    /* if (game.mode == GM_TITLE || game.mode == GM_CREDITS)
        return true; */

    switch(musicmode)
    {
    case MUSIC_OFF: return false;
    case MUSIC_ON:  return true;
    case MUSIC_BOSS_ONLY:
        return music_is_boss(songno);
    }

    return false;
}

bool music_is_boss(int songno)
{
    if (strchr(bossmusic, songno))
        return true;
    else
        return false;
}

void music_set_enabled(int newstate)
{
    if (newstate != settings->music_enabled)
    {
        stat("music_set_enabled(%d)", newstate);

        settings->music_enabled = newstate;
        bool play = should_music_play(cursong, newstate);

        if (play != org_is_playing())
        {
            if (play)
                start_track(cursong);
            else
                org_stop();
        }
    }
}

static void start_track(int songno)
{
    char fname[MAXPATHLEN];

    if (songno == 0)
    {
        org_stop();
        return;
    }

#ifdef _SDL_MIXER
    if (music_xm) {
        music_free();
    }

    strcpy(fname, xm_dir);
    strcat(fname, org_names[songno]);
    strcat(fname, ".xm");

    if(music_xm=Mix_LoadMUS(fname)) {
        stat("openning %s file\n", fname);
    }

    bool qLooped = (songno == 3 || songno == 10 || songno == 15 || songno == 16);

    if(Mix_PlayMusic(music_xm, (qLooped) ? 0 : -1) == -1) {
        staterr("Error in Mix_PlayMusic!");
    }

    org_set_playing(true);

#else
    strcpy(fname, org_dir);
    strcat(fname, org_names[songno]);
    strcat(fname, ".org");

    if (!org_load(fname))
    {
        org_start(0);
    }
#endif
}

#ifdef _SDL_MIXER
void music_free()
{
    Mix_FreeMusic(music_xm);
#ifdef DEBUG
    stat("Music is free!");
#endif
}
#endif

int music_cursong()		{ return cursong; }
int music_lastsong() 	{ return lastsong; }


