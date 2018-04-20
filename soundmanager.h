#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
#include "./gamesystem.h"
#include "./soundlib/soundplayer.h"


//==========================================================
//--------------------- SoundManager -----------------------
//==========================================================

class SoundManager
{
private:
    //vector<WaveContainer*> sounds;
    SoundPlayer *soundPlayer;

public:
    enum SoundName
    {
        BGM_game = 0,
        BGM_tfp,
        SE_stop,
        SE_move,
        SE_miss,
        SE_cut,
        SE_fanfare,
        SE_hayai,
        SE_hutuu,
        SE_osoi
    };
    SoundManager();
    ~SoundManager();
    static SoundManager *inst;
    void Play(SoundName name);
    void Play(SoundName name, bool loop);
    void PlayOverWrite(SoundName name);
    void Stop(SoundName name);
    void Pause(SoundName name);
};
#endif