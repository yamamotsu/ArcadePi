#include <iostream>
#include <alsa/asoundlib.h>
#include <time.h>
#include <fstream>
#include <stdint.h>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
using namespace std;

#include "soundcontainer.h"
#include "wavecontainer.h"
#include "soundplayer.h"

void SP_routine_start(SoundPlayer *ptr);

static double sound_level = 0.1;

SoundPlayer::SoundPlayer()
{
    int i;
    int errf = 0;
    soundcnt = 0;
    enable = 0;
    deathf = 0;

    for(i=0;i<DEF_SND_CONTAINS;i++){
        info[i].status = empty;
        info[i].internal_created_flag = 0;
        info[i].loopf = 0;
    }

    device = DEF_ALSA_DEVICE;

    errf = snd_pcm_open(&handle,device.data(),SND_PCM_STREAM_PLAYBACK,0);
    if(errf){
        cout << "Unable to open pcm" << endl;
    }else{
        errf = snd_pcm_set_params(handle,
                                  DEF_PCM_FORMAT,
                                  SND_PCM_ACCESS_RW_INTERLEAVED,
                                  DEF_CHANNELS,
                                  DEF_SAMPLEPERSEC,
                                  0,
                                  DEF_LATENCY);
        if(errf){
            cout << "Unable to set params" << endl;
        }else{
            hnd = new thread(SP_routine_start,this);
            mtx = new mutex();
            cout << "ready" << endl;
        }
    }
}

void SoundPlayer::routine(){
    int i,j;
    int mixnum=0,emptys;
    int eof;
    timespec ts;
    //long max_sleep = (long)(DEF_SAMPLES*1000000000/(DEF_SAMPLEPERSEC*2));
    ts.tv_sec = 0;
    //ts.tv_nsec = (max_sleep > 1000000) ? 1000000 : max_sleep;
    ts.tv_nsec = 1000000;
	
    //現在はsigned 16bitのみで対応..
    vector<short> temp[DEF_SND_MIXNUM];
    //vector<char> temp(DEF_CHANNELS*DEF_SAMPLES*2);
    vector<short> buf(DEF_SAMPLES*DEF_CHANNELS);
    for(i=0;i<DEF_SND_MIXNUM;i++){
            temp[i].resize(DEF_SAMPLES*DEF_CHANNELS);
    }
    //buf = new vector<short>(DEF_SAMPLES*DEF_CHANNELS);

    while(1){
        mixnum = 0;
        emptys = 0;
        for(i=0;i<DEF_SAMPLES*DEF_CHANNELS;i++){
           buf[i] = 0;
        }

        mtx->lock();
		for(i=0;i<soundcnt;i++){
			if(info[i].status == playing){
				if(mixnum < DEF_SND_MIXNUM){
					for(j=0;j<DEF_SAMPLES*DEF_CHANNELS;j++){
						temp[mixnum][j] = 0;
					}
					eof = container[i]->read((char *)temp[mixnum].data(),DEF_SAMPLES);
					if(eof){
						if(info[i].loopf){
							container[i]->reload();
						}else{
							cout << container[i]->getFilename() << " is stopped." << endl;
							info[i].status = stopped;
						}
						
					}
					mixnum++;
				}
			}
			
			if(info[i].status == stopped || info[i].status == contained){
				emptys++;
			}
			
		}

		if(mixnum){
			for(i=0;i<mixnum;i++){
				//今度Vectorクラスを新しく作ってoperator +を定義
				for(j=0;j<DEF_SAMPLES*DEF_CHANNELS;j++){
					buf[j] += (short)((temp[i])[j]*sound_level);
				}
			}
		}

		
		if(emptys == soundcnt){
			//cout << "end" << endl;
			enable = 0;
			
		}

	//container[0]->read((char *)temp[0].data(),DEF_SAMPLES);
	//cout << "read:" << to_string(container[0]->read((char *)temp.data(),DEF_SAMPLES)) << endl;
	//snd_pcm_writei(handle,(const void*)temp[0].data(),DEF_SAMPLES);
	snd_pcm_writei(handle,(const void*)buf.data(),DEF_SAMPLES);

	if(deathf){
		mtx->unlock();
		cout << "pcm stream closing..." << endl;
		break;
	}
	mtx->unlock();
	nanosleep(&ts,nullptr);
    }
    snd_pcm_close(handle);
    
}

SoundPlayer::~SoundPlayer(){
    int i;

    cout << "SoundPlayer shutdown..." << endl;
    mtx->lock();
    deathf = 1;
    //cout << "SoundPlayer enable flag down" << endl;
    mtx->unlock();
    
    cout << "waiting SoundPlayer thread closed" << endl;
    hnd->join();

    cout << "deach WaveContent's Memory" << endl;
    for(i=0;i<soundcnt;i++){
        if(info[i].internal_created_flag){
            delete container[i];
        }
    }


    delete mtx;
    delete hnd;
    //delete handle;
}

void SoundPlayer::play(int id){
    this->play(id,0);
}

void SoundPlayer::play(int id,int is_loop){
	if(soundcnt <= id){
        cout << "invalid id" << endl;
        return;
    }

    mtx->lock();
    if(info[id].status != empty && info[id].status != playing){
        if(info[id].status == stopped){
            //cout << "id:" << to_string(id) << " is being stopped.\nreloading.." << endl;
            container[id]->reload();
        }
		
        //cout << "id:" << to_string(id) << " is now playing" << endl;
        info[id].status = playing;
        info[id].loopf = is_loop;
        
        if(!enable){
            enable = 1;
        }
    }
    mtx->unlock();
}

void SoundPlayer::replay(int id){
    stop(id);
    play(id);
}

void SoundPlayer::wait(){
    
    timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 1000000;
	
    while(1){
        mtx->lock();
        if(!enable){
            mtx->unlock();
            break;
        }
        mtx->unlock();
    	nanosleep(&ts,NULL);
    }
    
}

void SoundPlayer::pause(int id){
    if(soundcnt <= id){
        cout << "invalid id" << endl;
        return;
    }

    mtx->lock();
    if(info[id].status != empty){
        if(info[id].status == playing){
            info[id].status = paused;
        }
    }
    mtx->unlock();
}

void SoundPlayer::stop(int id){
    if(soundcnt <= id){
        cout << "invalid id" << endl;
        return;
    }

    mtx->lock();
    if(info[id].status != empty){
		info[id].status = stopped;
    }
    mtx->unlock();
}

void SP_routine_start(SoundPlayer *ptr){
    ptr->routine();
}


void SoundPlayer::setDevice(char *device_name){
	device = device_name;
}


int SoundPlayer::setSound(const char *wave_file_name){
    if(soundcnt < DEF_SND_CONTAINS){
        container[soundcnt] = new WaveContainer(wave_file_name);

        cout << "SoundPlayer: sound file:\"" << container[soundcnt]->getFilename()
                        << "\" has registered to Container as id:"
                        << to_string(soundcnt) << endl;

        info[soundcnt].internal_created_flag = 1;
        info[soundcnt].status = contained;
        return soundcnt++;
    }
    return -1;
}


int SoundPlayer::setSound(SoundContainer *container){
    if(soundcnt < DEF_SND_CONTAINS && container!=nullptr){
        this->container[soundcnt] = container;
        
        cout << "SoundPlayer: sound file:\"" << container->getFilename() 
                        << "\" has registered to Container as id:"
        		<< to_string(soundcnt) << endl;
        		
        info[soundcnt].status = contained;
        
        return soundcnt++;
    }
    return -1;
}

void SoundPlayer::setVolume(double volume)
{
	if(volume >=0 && volume<100)
	{
		sound_level = volume;
	}
}