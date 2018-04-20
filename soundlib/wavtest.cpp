#include <iostream>
#include <alsa/asoundlib.h>
#include <fstream>
#include <stdint.h>
#include <vector>
#include <thread>
#include <mutex>
#include <time.h>
using namespace std;

#include "soundcontainer.h"
#include "wavecontainer.h"
#include "soundplayer.h"

int main(void){
        WaveContainer bgm("kirby.wav");
        WaveContainer se("wav/cow_say3.wav");
        SoundPlayer sndplayer;
        sndplayer.setSound(&bgm);
        sndplayer.setSound(&se);
        sndplayer.play(0);
        sleep(2);
        sndplayer.play(1);

        sndplayer.wait();
}
