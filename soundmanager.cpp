#include "soundmanager.h"

SoundManager *SoundManager::inst = new SoundManager();

SoundManager::SoundManager()
{
    //soundPlayer = new SoundPlayer();
    soundPlayer = GameSystem::soundplayer;
    cout << "SoundID:" << to_string(soundPlayer->setSound("soundlib/wav/BGM/game.wav")) << endl;
    soundPlayer->setSound("soundlib/wav/BGM/game.wav");
    soundPlayer->setSound("soundlib/wav/SE/enter.wav");
    soundPlayer->setSound("soundlib/wav/SE/move.wav");
    soundPlayer->setSound("soundlib/wav/SE/miss.wav");
    soundPlayer->setSound("soundlib/wav/SE/cut.wav");
    soundPlayer->setSound("soundlib/wav/SE/fanfare.wav");
    soundPlayer->setSound("soundlib/wav/SE/hayai.wav");
    soundPlayer->setSound("soundlib/wav/SE/hutuu.wav");
    soundPlayer->setSound("soundlib/wav/SE/osoi.wav");
}

SoundManager::~SoundManager()
{
    //int i;
    //for(i = 0; i < (int)sounds.size(); i++)
    //    delete sounds[i];
    delete this->inst;
}


void SoundManager::Play(SoundName name)
{
    soundPlayer->play((int)name);
}

void SoundManager::Play(SoundName name, bool loop)
{
    soundPlayer->play((int)name, loop);
}

void SoundManager::Stop(SoundName name)
{
    soundPlayer->stop((int)name);
}

void SoundManager::PlayOverWrite(SoundName name)
{
    Stop(name);
    Play(name);
}

void SoundManager::Pause(SoundName name)
{
    soundPlayer->pause((int)name);
}