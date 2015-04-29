#pragma once
#include "sssf\XAudio2\wave.h"

class XAudio2
{
public:
	XAudio2();
	~XAudio2();
	int initXAudio();
	void playAudio();
	int createSource();
	void FreeAudioEngine();
	void TurnOffAudio();
	int loadWavFile(char *str);
private:
	IXAudio2 *g_engine;
	IXAudio2SourceVoice *g_source;
	IXAudio2MasteringVoice *g_master;
	//helper class to load wave files; trust me, this makes it MUCH easier
	Wave buffer;
};