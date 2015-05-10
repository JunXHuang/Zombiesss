//by Jay Tennant 3/4/12
//A Brief Look at XAudio2: Playing a Sound
//win32developer.com
//this code provided free, as in public domain; score!
#include "sssf\XAudio2\XAudio2.h"

int XAudio2::initXAudio(){

	//must call this for COM
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//create the engine
	if (FAILED(XAudio2Create(&g_engine, 0, XAUDIO2_DEFAULT_PROCESSOR)))
	{
		CoUninitialize();
		return -1;
	}

	//create the mastering voice
	if (FAILED(g_engine->CreateMasteringVoice(&g_master)))
	{
		g_engine->Release();
		CoUninitialize();
		return -2;
	}

}
XAudio2::XAudio2(){
}
XAudio2::~XAudio2(){
}
void XAudio2::TurnOffAudio(){
	g_source->Stop();
}
void XAudio2::FreeAudioEngine(){
	//release the engine, NOT the voices!
	g_engine->Release();
	//again, for COM
	CoUninitialize();
}
void XAudio2::playAudio(){
	g_source->Stop();
	g_source->FlushSourceBuffers();
	g_source->Start();
	//play the sound
	g_source->SubmitSourceBuffer(buffer.xaBuffer());
}
int XAudio2::loadWavFile(char *str){
	//load a wave file
	if (!buffer.load(str))
	{
		g_engine->Release();
		CoUninitialize();
		return -3;
	}
}

int XAudio2::createSource(){
	//create the source voice, based on loaded wave format
	if (FAILED(g_engine->CreateSourceVoice(&g_source, buffer.wf())))
	{
		g_engine->Release();
		CoUninitialize();
		return -4;
	}
}