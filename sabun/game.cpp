#include <time.h>
#include "myDirect3D.h"
#include "main.h"
#include "input.h"
#include "camera.h"
#include "camera2.h"
#include "light.h"
#include "debugproc.h"
#include "texture.h"
#include "sprite.h"
#include "score.h"
#include "meter.h"
#include "ground.h"
#include "scene.h"
#include "fade.h"
#include "Player.h"
#include "grid.h"
#include "drink.h"
#include "particle.h"
#include "speedline.h"
#include "shadow.h"
#include "skydome.h"
#include "RankSystem.h"
#include "back_ground.h"
#include "sound.h"

typedef enum PHASE_INDEX
{
	PHASE_INDEX_FADE,
	PHASE_INDEX_PLAYER_IN,
	PHASE_INDEX_PLAYER_MUTEKI,
	PHASE_INDEX_PLAYER_NORMAL,
	PHASE_INDEX_STAGE_CLEAR,
	PHASE_INDEX_END,

	PHASE_INDEX_MAX
};

static PHASE_INDEX g_Phase;
ParticleManager particle;
SpeedlineManager line;

static int g_GameFrameCount;

static int g_Score = 0;// �_��
static int g_KillCount = 0;


static bool Game_EndCheck(void);



void Game_Initialize(void)
{
	// �J�����̏���������
	Camera_Initialize();
	//Camera2_Initialize();

	// ���C�g�̏���������
	Light_Initialize();

	//�O���b�h�̏���������
	//Grid_Initialize();

	// �X�J�C�h�[��
	Skydome_Initialize();

	// �o�b�N�O���E���h
	Back_Initialize();

	// �e
	Shadow_Initialize();

	// �v���C���[
	Player_Initialize();

	// �O���E���h
	Ground_Initialize();

	// �h�����N
	Drink_Initialize();

	// �X�R�A
	InitScore();

	// �p�[�e�B�N��
	particle.InitParticle();

	// �X�s�[�h���C��
	line.InitSpeedline();

	// ���[�^�[
	Meter_Initialize();

	PlaySound(SOUND_LABEL_BGM_GAME);
	SetVolume(SOUND_LABEL_BGM_GAME,VOLUME_WEIGHT[SOUND_LABEL_BGM_GAME]) ;
}

void Game_Finalize(void)
{
	StopSound(SOUND_LABEL_BGM_GAME);
	// �J�����̏I������
	Camera_Finalize();
	//Camera2_Finalize();

	// ���C�g�̏I������
	Light_Finalize();

	// �O���b�h�̏I��
	//Grid_Finalize();

	// �X�J�C�h�[��
	Skydome_Finalize();

	// �o�b�N�O���E���h
	Back_Finalize();

	// �e
	Shadow_Finalize();

	// �v���C���[
	Player_Finalize();

	// �O���E���h
	//Ground_Finalize();

	// �h�����N
	Drink_Finalize();

	// �X�R�A
	UninitScore();

	// �p�[�e�B�N��
	particle.UninitParticle();

	// �X�s�[�h���C��
	line.UninitSpeedline();

	// ���[�^�[
	Meter_Finalize();

	// �X�R�A��������
	BainariWrite();
}

void Game_Update(void)
{


	// �J�����̍X�V����
	Camera_Update();
	//Camera2_Update();

	// ���C�g�̍X�V����
	Light_Update();

	//�O���b�h��
	//Grid_Update();

	// �X�J�C�h�[��
	Skydome_Update();

	// �o�b�N�O���E���h
	Back_Update();

	// �e
	Shadow_Update();

	// �v���C���[
	Player_Update();

	// �O���E���h
	//Ground_Update();

	// �h�����N
	Drink_Update();

	// �X�R�A
	UpdateScore();	

	// �p�[�e�B�N��
	particle.UpdateParticle();

	// �X�s�[�h���C��
	line.UpdateSpeedline();

	// ���[�^�[
	Meter_Update();

	if (Keyboard_IsRelease(DIK_SPACE))
	{
		Scene_Change(SCENE_INDEX_RESULT);
	}

}

void Game_Draw(void)
{
	// �J�����̐ݒ�
	Camera_SetCamera();
	//Camera2_SetCamera();

	//�O���b�h�̕`��
	//Grid_Draw();

	// �X�J�C�h�[��
	Skydome_Draw();

	// �o�b�N�O���E���h
	Back_Draw();

	// �O���E���h
	Ground_Draw();

	// �e
	Shadow_Draw();

	// �v���C���[
	Player_Draw();

	// �h�����N
	Drink_Draw();

	// �X�R�A
	DrawScore();

	// �p�[�e�B�N��
	particle.DrawParticle();

	// �X�s�[�h���C��
	//line.DrawSpeedline();

	// ���[�^�[
	Meter_Draw();
}



bool Game_EndCheck(void)
{

}



void Game_AddScore(int score)
{
	//g_Score += score;
}

void Game_AddKillCount()
{
	//g_KillCount += 1;
}
