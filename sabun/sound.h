//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#pragma once


#include <windows.h>
#include "xaudio2.h"						// �T�E���h�����ŕK�v


//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
SOUND_LABEL_BGM_TITLE,
SOUND_LABEL_BGM_GAME,
SOUND_LABEL_BGM_RESULT,
SOUND_LABEL_SE_DRIFT,
SOUND_LABEL_SE_GET_DRINK,
SOUND_LABEL_SE_POINTER,

	SOUND_LABEL_MAX,

} SOUND_LABEL;
const float VOLUME_WEIGHT[SOUND_LABEL_MAX] =
{0.05f,0.05f,0.05f,0.5f,0.5f,0.25f};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
bool InitSound(HWND hWnd);
void UninitSound(void);
void PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

void SetVolume(SOUND_LABEL label,float volume);