
#include "efx/CaveSound.h"
void CaveSound::SoundInitialize()
{

	ALFWInit();
	ALFWprintf("OpenAL Now Available\n");

	if (!ALFWInitOpenAL())
	{
		ALFWprintf("Failed to initialize OpenAL\n");
		ALFWShutdown();
	}
	
	alGenBuffers(128, caveBuffer);
	if (alGetError() != NO_ERROR)
		exit(1);

	alGenSources(128, caveSource);
	if (alGetError() != NO_ERROR)
	{
		ALFWprintf("Failed to generate a source\n");
		alDeleteBuffers(1, caveBuffer);
		ALFWShutdownOpenAL();
		ALFWShutdown();
		exit(1);
	}
	
	if (alGetError() != AL_NO_ERROR)
	{
		ALFWprintf("Failed to set the source attributes.\n");
		alDeleteBuffers(1, caveBuffer);
		alDeleteSources(1, caveSource);
		ALFWShutdownOpenAL();
		ALFWShutdown();
		exit(1);
	}
}

void CaveSound::SoundExtension()
{
	

	/*pDevice = alcOpenDevice(NULL); // ����Ʈ OpenAL device�� �����Ѵ�.
	if (!pDevice) return;
	// Effect Extension ����� �����Ǵ� ��ġ���� Ȯ���Ѵ�.
	if (alcIsExtensionPresent(pDevice, "ALC_EXT_EFX") == AL_FALSE) return;
	printf("EFX Extension found!\n");
	// Context ����. �����ϸ鼭 source �� �ִ� 4���� Auxiliary Send�� ����ϰڴٰ� ������.
	attribs[0] = ALC_MAX_AUXILIARY_SENDS;
	attribs[1] = 1;
	pContext = alcCreateContext(pDevice, attribs);
	if (!pContext) return;
	alcMakeContextCurrent(pContext); // ������ context�� Ȱ��ȭ
// �� Source �� ���� ��� ������ Aux. Send ������ ��´�.
	alcGetIntegerv(pDevice, ALC_MAX_AUXILIARY_SENDS, 1, &iSends);
	printf("Device supports %d Aux Sends per Source\n", iSends);*/
	// Effect Extension �Լ� �����͸� ��´�.
	// �߿�!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	alGenAuxiliaryEffectSlots = (LPALGENEFFECTS)alGetProcAddress("alGenAuxiliaryEffectSlots");
	alGenEffects = (LPALGENEFFECTS)alGetProcAddress("alGenEffects");
	alDeleteEffects = (LPALDELETEEFFECTS)alGetProcAddress("alDeleteEffects");
	alIsEffect = (LPALISEFFECT)alGetProcAddress("alIsEffect");
	alEffecti = (LPALEFFECTI)alGetProcAddress("alEffecti");
	alEffectf = (LPALEFFECTF)alGetProcAddress("alEffectf");

	alGenFilters = (LPALGENFILTERS)alGetProcAddress("alGenFilters");
	alIsFilter = (LPALISFILTER)alGetProcAddress("alIsFilter");
	alFilteri = (LPALFILTERI)alGetProcAddress("alFilteri");
	alFilterf = (LPALFILTERF)alGetProcAddress("alFilterf");
	alAuxiliaryEffectSloti = (LPALAUXILIARYEFFECTSLOTI)alGetProcAddress("alAuxiliaryEffectSloti");
	
	// �ʿ��� ��� Effect Extension �Լ����� �����͸� ��´�.
	// ���� function pointer���� ��ȿ���� �˻��Ѵ�.
	if (!(alGenEffects && alDeleteEffects && alIsEffect)) std::cout << "fuck its not working!";
	// EFX �ʱ�ȭ�� �Ϸ�Ǿ� �������� EFX ���α׷����� ����������!!!!
}

void CaveSound::AddSound(const ALchar* wavFile)
{

	// ����ü���� ���̺��̸��̶� ���°�� �����ߴ���
	// 
	if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(wavFile), caveBuffer[0]))
	{
		ALFWprintf("Failed to load or attach %s\n", ALFWaddMediaPath(wavFile));
		alDeleteBuffers(1, caveBuffer);
		ALFWShutdownOpenAL(); ALFWShutdown();
		exit(1);
	}
}


void CaveSound::SoundToSource(const ALchar* wavFile)
{
	alSourcei(caveSource[0], AL_BUFFER, caveBuffer[0]);
}

void CaveSound::SetLoop(bool b)
{
	if (b == true)
		alSourcei(caveSource[0], AL_LOOPING, AL_TRUE);
	else if(b == false)
		alSourcei(caveSource[0], AL_LOOPING, AL_FALSE);
}

void CaveSound::SetMaxDistance(ALfloat maxDis)
{
	alSourcef(caveSource[0], AL_MAX_DISTANCE, maxDis);
}

void CaveSound::SetRefDistance(ALfloat refDis)
{
	alSourcef(caveSource[0], AL_REFERENCE_DISTANCE, refDis);
}


void CaveSound::SetListenerPos()
{
	//���ӿ��� ������(�÷��̾� ĳ����)�� ���� ������
	
	//�����ʿ� �� ����
	alListenerfv(AL_POSITION, ListenerPos);
	alListenerfv(AL_VELOCITY, ListenerVel);
	alListenerfv(AL_ORIENTATION, ListenerOri);
}

void CaveSound::SoundPlay()
{
	alSourcePlay(caveSource[0]);
	
}

void CaveSound::SetVolume(ALfloat *gain)
{
	alSourcefv(caveSource[0], AL_GAIN, gain);
}

void CaveSound::SetPitch(ALfloat *pitch)
{
	alSourcefv(caveSource[0], AL_PITCH, pitch);
}

void CaveSound::SetSourcePos()
{
	alSourcefv(caveSource[0], AL_POSITION, SourcePos);
}

void CaveSound::SetRolloff(ALfloat rolloff)
{
	alSourcef(caveSource[0], AL_ROLLOFF_FACTOR, rolloff);
}



