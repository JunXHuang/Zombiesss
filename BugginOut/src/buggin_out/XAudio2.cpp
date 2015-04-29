//by Jay Tennant 3/4/12
//A Brief Look at XAudio2: Playing a Sound
//win32developer.com
//this code provided free, as in public domain; score!
#include<buggin_out\XAudio2.h>

int XAudio2::initXAudio(){

	IXAudio2 *g_engine;
	IXAudio2SourceVoice *g_source;
	IXAudio2MasteringVoice *g_master;

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

	//helper class to load wave files; trust me, this makes it MUCH easier
	Wave buffer;

	//load a wave file
	if (!buffer.load("data/Sound/ah.wav"))
	{
		g_engine->Release();
		CoUninitialize();
		return -3;
	}

	//create the source voice, based on loaded wave format
	if (FAILED(g_engine->CreateSourceVoice(&g_source, buffer.wf())))
	{
		g_engine->Release();
		CoUninitialize();
		return -4;
	}

	//start consuming audio in the source voice
	g_source->Start();
	
	//simple message loop
	while (MessageBox(0, TEXT("Do you want to play the sound?"), TEXT("ABLAX: PAS"), MB_YESNO) == IDYES)
	{
		//play the sound
		g_source->SubmitSourceBuffer(buffer.xaBuffer());
	}
	
		//release the engine, NOT the voices!
			g_engine->Release();
		//again, for COM
			CoUninitialize();

}
XAudio2::XAudio2(){

}
XAudio2::~XAudio2(){
}
void XAudio2::TurnOffAudio(){
	
}