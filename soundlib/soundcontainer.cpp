#include <alsa/asoundlib.h>
#include <thread>
#include <mutex>
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "soundcontainer.h"

SoundContainer::SoundContainer()
    :buffer(nullptr)
{
}

const char *SoundContainer::getFilename(){
	return filename.data();
}

PCM_INFO SoundContainer::getPcmInfo(){
	//return 0;
}

int SoundContainer::read(char *buf, size_t sample_num){
	return 0;
}

void SoundContainer::reload(){

}

void SoundContainer::setParam(){

}
