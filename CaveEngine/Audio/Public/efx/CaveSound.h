#pragma once
#include <iostream>
#include <efx/Framework.h>
#include <AL\al.h>
#include <efx/al.h>
#include <math.h>
#include <efx/EFX-Util.h>

#define TEST_WAVE_FILE "Footsteps.wav"
#define VEHICLE_WAVE_FILE "Vehicle.wav"

class CaveSound 
{
public:
	//���忡 default ���� ��
	void SoundInitialize();
	void SoundExtension();

	//����(wav����)�� ����� �߰��� ��
	void AddSound(const ALchar* wavFile);
	//������۸� �ҽ��� ���� ��
	void SoundToSource(const ALchar* wavFile);
	
	//Ư�� ����(��ġ,����,�ǰ�,�̵�)�� �����ϸ� ���� ���
	void SoundPlay();//loop? 



	void SetVolume(ALfloat *gain);
	void SetPitch(ALfloat *pitch);
	void SetSourcePos();
	void SetRolloff(ALfloat rolloff);
	void SetLoop(bool b);
	void SetMaxDistance(ALfloat maxDis);
	void SetRefDistance(ALfloat refDis);
	void SetListenerPos();

	ALuint caveSource[128]; // Source ID
	ALuint caveBuffer[128]; // Buffer ID

	ALCdevice* pDevice = NULL;
	ALCcontext* pContext = NULL;
	ALint attribs[4] = { 0 };
	ALCint iSends = 0;
private:
	ALfloat ListenerPos[3] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerVel[3] = { 0.0, 0.0, 0.0 };
	ALfloat ListenerOri[6] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };
	ALfloat SourcePos[3] = { 0.0, 0.0, 0.0 };
	ALfloat SourceVel[3] = { 0.0, 0.0, 0.0 };

	
	ALubyte ch = ' ';
	ALfloat default_max_distance = (ALfloat)3.40282e+38;
	ALfloat default_ref_distance = (ALfloat)1;
	ALfloat default_doppler_factor = 1;
	ALfloat default_sound_speed = 343.3;
	ALfloat rolloff, maxDistance; // rollof ������ �ִ�Ÿ� ����
	ALfloat refDistance; // �����Ÿ�
	ALfloat dopplerFactor; //���÷�
	ALfloat soundSpeed; //�Ҹ��� �ӵ� ������ ����
};

