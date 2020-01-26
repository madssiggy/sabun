
#include "sprite.h"
#include "input.h"
#include "scene.h"
#include "texture.h"
#include "fade.h"
#include"RankSystem.h"
#include "score.h"


#define  SCORE_TEXTURE_POS_X (320.0f)
#define  SCORE_TEXTURE_POS_Y (321.0f)
#define SCORE_MARGIN (50.0f)



#define SCORE_SIZE_X (860.0f)
#define SCORE_SIZE_Y (170.0f)
#define  SCORE_RATIO (0.2)
#define RANKING_RATIO (0.2f)
#define APPEAR_SCORE_COUNT (4)

#define OLD_SCORE_SIZE_X (300.0f)
#define OLD_SCORE_SIZE_Y (100.0f)
#define OLD_SCORE_MARGIN_Y (140.0f)
#define OLD_SCORE_MARGIN_X (50.0f)
#define SCORE_POS_X (90.0f)
#define SCORE_POS_Y (20.0f)

static float point[6] = { 0,0,0,0,0,0 };

static float ranking[10][6] = { 0 };




//(get_score+i)

void Result_Initialize(void)
{
	Fade_Start(false, 90, D3DCOLOR_RGBA(0, 0, 0, 0));
}

void Result_Finalize(void)
{
}

void Result_Update(void)
{
	if (Keyboard_IsRelease(DIK_SPACE))
	{
		Scene_Change(SCENE_INDEX_TITLE);
	}

	if (Keyboard_IsTrigger(DIK_G))
	{
		Scene_Change(SCENE_INDEX_GAME);
	}

	BainariRead();

	point[0] = GetScore() % 10;//---1�̈ʂ𒊏o
	point[1] = GetScore() / 10 % 10;//---10�̈ʂ𒊏o
	point[2] = GetScore() / 100 % 10;//---�S�̈ʂ𒊏o
	point[3] = GetScore() / 1000 % 10;//---��̈ʂ𒊏o
	point[4] = GetScore() / 10000 % 10;//---���̈ʂ𒊏o
	point[5] = GetScore() / 100000 % 10;//---�\���̈ʂ𒊏o



	for (int f = 0; f <= APPEAR_SCORE_COUNT; f++)//--------�����L���O���e�A�ʂ��Ƃɒ��o������
	{

		ranking[f][0] = (Getprevious(f)) % 10;//---1�̈ʂ𒊏o
		ranking[f][1] = (Getprevious(f)) / 10 % 10;//---10�̈ʂ𒊏o
		ranking[f][2] = (Getprevious(f)) / 100 % 10;//---�S�̈ʂ𒊏o
		ranking[f][3] = (Getprevious(f)) / 1000 % 10;//---��̈ʂ𒊏o
		ranking[f][4] = (Getprevious(f)) / 10000 % 10;//---���̈ʂ𒊏o
		ranking[f][5] = (Getprevious(f)) / 100000 % 10;//---�\���̈ʂ𒊏o



	}




}

void Result_Draw(void)
{
	Sprite_Draw(TEXTURE_INDEX_RESULT, 0.0f, 0.0f);



	Sprite_Draw(TEXTURE_INDEX_FLAME_S, 0.0f, 0.0f,

		0.0f, 0.0f,
		2154.0f, 3257.0f,

		0.0f, 0.0f, 0.2f, 0.2f, 0.0f);


	//10���̈�
	Sprite_Draw(TEXTURE_INDEX_SCORE002, SCORE_SIZE_X, SCORE_SIZE_Y,

		0.0f + (SCORE_TEXTURE_POS_X * point[5]), 0.0f,
		SCORE_TEXTURE_POS_X, SCORE_TEXTURE_POS_Y,

		SCORE_SIZE_X/2, SCORE_SIZE_Y/2, SCORE_RATIO, SCORE_RATIO, 0.0f);


	//���̈�
	Sprite_Draw(TEXTURE_INDEX_SCORE002, SCORE_SIZE_X + SCORE_MARGIN*1, SCORE_SIZE_Y,

		0.0f + (SCORE_TEXTURE_POS_X * point[4]), 0.0f,
		SCORE_TEXTURE_POS_X, SCORE_TEXTURE_POS_Y,

		SCORE_SIZE_X / 2, SCORE_SIZE_Y / 2, SCORE_RATIO, SCORE_RATIO, 0.0f);

	//��̈�
	Sprite_Draw(TEXTURE_INDEX_SCORE002, SCORE_SIZE_X + SCORE_MARGIN*2, SCORE_SIZE_Y,

		0.0f + (SCORE_TEXTURE_POS_X * point[3]), 0.0f,
		SCORE_TEXTURE_POS_X, SCORE_TEXTURE_POS_Y,

		SCORE_SIZE_X / 2, SCORE_SIZE_Y / 2, SCORE_RATIO, SCORE_RATIO, 0.0f);

	//�S�̈�
	Sprite_Draw(TEXTURE_INDEX_SCORE002, SCORE_SIZE_X + SCORE_MARGIN*3, SCORE_SIZE_Y,

		0.0f + (SCORE_TEXTURE_POS_X * point[2]), 0.0f,
		SCORE_TEXTURE_POS_X, SCORE_TEXTURE_POS_Y,

		SCORE_SIZE_X / 2, SCORE_SIZE_Y / 2, SCORE_RATIO, SCORE_RATIO, 0.0f);

	//�\�̈�
	Sprite_Draw(TEXTURE_INDEX_SCORE002, SCORE_SIZE_X + SCORE_MARGIN * 4, SCORE_SIZE_Y,

		0.0f + (SCORE_TEXTURE_POS_X * point[1]), 0.0f,
		SCORE_TEXTURE_POS_X, SCORE_TEXTURE_POS_Y,

		SCORE_SIZE_X / 2, SCORE_SIZE_Y / 2, SCORE_RATIO, SCORE_RATIO, 0.0f);

	//��̈�
	Sprite_Draw(TEXTURE_INDEX_SCORE002, SCORE_SIZE_X + SCORE_MARGIN * 5, SCORE_SIZE_Y,

		0.0f + (SCORE_TEXTURE_POS_X * point[0]), 0.0f,
		SCORE_TEXTURE_POS_X, SCORE_TEXTURE_POS_Y,

		SCORE_SIZE_X / 2, SCORE_SIZE_Y / 2, SCORE_RATIO, SCORE_RATIO, 0.0f);

	TextureIndex tmp;
	for (int u = 0; u <= APPEAR_SCORE_COUNT; u++)
	{
		switch (u) {
		case 0:
			tmp = TEXTURE_INDEX_1ST;
			break;
		case 1:
			tmp = TEXTURE_INDEX_2ND;
			break;
		case 2:
			tmp = TEXTURE_INDEX_3RD;
			break;
		case 3:
			tmp = TEXTURE_INDEX_4TH;
			break;
		default:
			tmp = TEXTURE_INDEX_1ST;
			break;
		}

		Sprite_Draw(tmp, 
			SCORE_POS_X +OLD_SCORE_MARGIN_X*-1, SCORE_POS_Y + OLD_SCORE_MARGIN_Y * u ,
			0.0f, 0.0f,
			Texture_GetWidth(tmp),Texture_GetHeight(tmp),
			OLD_SCORE_SIZE_X /2, OLD_SCORE_SIZE_Y /2,
			RANKING_RATIO, RANKING_RATIO, 0.0f);

		//10���̈�
		Sprite_Draw(TEXTURE_INDEX_SCORE002,
			SCORE_POS_X, SCORE_POS_Y + OLD_SCORE_MARGIN_Y * u,
			0.0f + (SCORE_TEXTURE_POS_X * ranking[u][5]), 0.0f,
			SCORE_TEXTURE_POS_X, SCORE_TEXTURE_POS_Y,

			OLD_SCORE_SIZE_X/2, OLD_SCORE_SIZE_Y/2, SCORE_RATIO, SCORE_RATIO, 0.0f);


		//���̈�
		Sprite_Draw(TEXTURE_INDEX_SCORE002,
			SCORE_POS_X +OLD_SCORE_MARGIN_X*1, SCORE_POS_Y + OLD_SCORE_MARGIN_Y * u,

			0.0f + (SCORE_TEXTURE_POS_X * ranking[u][4]), 0.0f,
			SCORE_TEXTURE_POS_X, SCORE_TEXTURE_POS_Y,

			OLD_SCORE_SIZE_X/2, OLD_SCORE_SIZE_Y/2 , SCORE_RATIO, SCORE_RATIO, 0.0f);

		//��̈�
		Sprite_Draw(TEXTURE_INDEX_SCORE002, 
			SCORE_POS_X + OLD_SCORE_MARGIN_X * 2, SCORE_POS_Y + OLD_SCORE_MARGIN_Y * u,


			0.0f + (SCORE_TEXTURE_POS_X * ranking[u][3]), 0.0f,
			SCORE_TEXTURE_POS_X, SCORE_TEXTURE_POS_Y,

			OLD_SCORE_SIZE_X / 2, OLD_SCORE_SIZE_Y / 2, SCORE_RATIO, SCORE_RATIO, 0.0f);

		//�S�̈�
		Sprite_Draw(TEXTURE_INDEX_SCORE002, 
			SCORE_POS_X + OLD_SCORE_MARGIN_X * 3, SCORE_POS_Y + OLD_SCORE_MARGIN_Y * u,

			0.0f + (SCORE_TEXTURE_POS_X * ranking[u][2]), 0.0f,
			SCORE_TEXTURE_POS_X, SCORE_TEXTURE_POS_Y,

			OLD_SCORE_SIZE_X / 2, OLD_SCORE_SIZE_Y / 2, SCORE_RATIO, SCORE_RATIO, 0.0f);

		//�\�̈�
		Sprite_Draw(TEXTURE_INDEX_SCORE002, 
			SCORE_POS_X + OLD_SCORE_MARGIN_X * 4, SCORE_POS_Y + OLD_SCORE_MARGIN_Y * u,
			0.0f + (SCORE_TEXTURE_POS_X * ranking[u][1]), 0.0f,
			SCORE_TEXTURE_POS_X, SCORE_TEXTURE_POS_Y,

			OLD_SCORE_SIZE_X / 2, OLD_SCORE_SIZE_Y / 2, SCORE_RATIO, SCORE_RATIO, 0.0f);

		//��̈�
		Sprite_Draw(TEXTURE_INDEX_SCORE002, 
			SCORE_POS_X + OLD_SCORE_MARGIN_X * 5, SCORE_POS_Y + OLD_SCORE_MARGIN_Y * u,


			0.0f + (SCORE_TEXTURE_POS_X * ranking[u][0]), 0.0f,
			SCORE_TEXTURE_POS_X, SCORE_TEXTURE_POS_Y,

			OLD_SCORE_SIZE_X / 2, OLD_SCORE_SIZE_Y / 2, SCORE_RATIO, SCORE_RATIO, 0.0f);
	}
}