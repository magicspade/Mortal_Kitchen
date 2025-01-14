#include "common.h"

#include <al.h>
#include <alc.h>


#include <sndfile.h>

using namespace std;

ALuint LoadSound(const std::string& Filename)
{
  SF_INFO FileInfos;
  SNDFILE* File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
  if (!File)
    return 0;

  ALsizei NbSamples = static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
  ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);
  vector<ALshort> Samples(NbSamples);
  if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
    return 0;
  sf_close(File);
  ALenum Format;
  switch (FileInfos.channels)
  {
  case 1:  Format = AL_FORMAT_MONO16;   break;
  case 2:  Format = AL_FORMAT_STEREO16; break;
  default: return 0;
  }
  ALuint Buffer;
  alGenBuffers(1, &Buffer);
  alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);

  if (alGetError() != AL_NO_ERROR)
    return 0;

  return Buffer;
}

map < string, ALuint > sources;
list <string> sounds_src = {"boing.wav","1-up.wav","piece.wav","pipou.wav","travailler.wav","ouille.wav","aieaieaie.wav","mort.wav", "menu.wav","game.wav", "winner.wav","boss.wav","ha.wav"};
map < string , ALuint > sounds ;


void init_sound() {

  ALCdevice* Device = alcOpenDevice(NULL);
  ALCcontext* Context = alcCreateContext(Device, NULL);
  alcMakeContextCurrent(Context);

  for (list<string>::iterator srcs = sounds_src.begin(); srcs != sounds_src.end(); ++srcs)
  {
	  sounds[*srcs] = LoadSound(executablePath() + "/data/sound/" + *srcs);
	  alGenSources(1, &sources[*srcs]);
  }
}

void play_sound(string snd){
	ALint Status;
	alGetSourcei(sources[snd], AL_SOURCE_STATE, &Status);
	if (Status != AL_PLAYING) {
		alSourcei(sources[snd], AL_BUFFER, sounds[snd]);
		alSourcePlay(sources[snd]);
	}
}

void rewind_sound() {
  //alSourceRewind(Source);
}
