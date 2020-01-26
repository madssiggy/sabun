#include "input.h"
#include "main.h"
#include "scene.h"
#include "texture.h"
#include "fade.h"
#include <d3d9.h>
#include "sprite.h"
#include "RankSystem.h"
#include "sound.h"


static int color = 0;
static float size = 0.0f;
static bool size_flag = true;
static bool color_flag = true;
enum Decide {
	Y,N
};

static bool isTutorial;
static bool screen;
static int alpha[2];//[0]がYes,[1]がＮｏ
const int forAlpha[2] = {255,126};
static int fps;//演出用
const float DecideSize = 1.0f;
static float g_DecSize[2] = {0.5f,0.5f};

void Shrink(int index) {
	g_DecSize[index] = DecideSize;
}

void Title_Initialize(void)
{
	
	fps = 0;
	alpha[Y] = forAlpha[Y];
	alpha[N] = forAlpha[N];
	isTutorial = true;
	screen = false;
	PlaySound(SOUND_LABEL_BGM_TITLE);
	SetVolume(SOUND_LABEL_BGM_TITLE,
		VOLUME_WEIGHT[SOUND_LABEL_BGM_TITLE]);
}

void Title_Finalize(void)
{
	StopSound(SOUND_LABEL_BGM_TITLE);
}

void Title_Update(void)
{
	fps++;
	if (fps >= 150) {
		switch (isTutorial) {
		case true:
			Shrink(Y);
			break;
		case false:
			Shrink(N);
			break;
		default:
			Shrink(Y);
			break;
		}
		fps = 0;
	}
	else if (fps == 5) {
		g_DecSize[Y] = 0.5f;
		g_DecSize[N] = 0.5f;
	}
	if (screen == true) {
		if (Keyboard_IsRelease(DIK_LEFT)) {
			
			alpha[0] = forAlpha[0];
			alpha[1] = forAlpha[1];
			isTutorial = true;
			PlaySound(SOUND_LABEL_SE_POINTER);
		}
		if (Keyboard_IsRelease(DIK_RIGHT)) {
			alpha[0] = forAlpha[1];
			alpha[1] = forAlpha[0];
			PlaySound(SOUND_LABEL_SE_POINTER);
			isTutorial = false;
		}
		if (Keyboard_IsRelease(DIK_SPACE)) {
			switch (isTutorial) {
			case true:
				PlaySound(SOUND_LABEL_SE_GET_DRINK);
				Scene_Change(SCENE_INDEX_TUTORIAL);
				break;
			case false:
				PlaySound(SOUND_LABEL_SE_GET_DRINK);
				Scene_Change(SCENE_INDEX_GAME);
				break;
			default:
				PlaySound(SOUND_LABEL_SE_GET_DRINK);
				Scene_Change(SCENE_INDEX_TUTORIAL);
				break;
			}
		}
	}
	// 透明にする・元に戻す
	if(color_flag)color+=2;
	else color -= 2;
	if (color > 252) color_flag = false;
	if (color < 10) color_flag = true;

	// サイズの拡大縮小
	if(size_flag) size += 0.03f;
	else size -= 0.03f;
	if (size < 0.1f)size_flag = true;
	if (size > 0.3f)size_flag = false;

	if (Keyboard_IsRelease(DIK_SPACE)&&screen==false) {
		screen = true;
		PlaySound(SOUND_LABEL_SE_GET_DRINK);
//		Scene_Change(SCENE_INDEX_TUTORIAL);
	}

	
}

void Title_Draw(void)
{

	// タイトルBG
	Sprite_Draw(TEXTURE_INDEX_BG, 0.0f, 0.0f);
	// タイトル文字
	Sprite_Draw(TEXTURE_INDEX_TITLE, 700.0f, 250.0f, 0.0f, 0.0f, 256.0f, 64.0f, 128.0f, 32.0f, 3.5f+size, 3.5f + size, 0.0f);
	// 透過
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255-color));
	// スタートを押して
	Sprite_Draw(TEXTURE_INDEX_PRESS, 500.0f, 420.0f, 0.0f, 0.0f, 256.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
	// α値を戻す
	Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
	if (screen == true) {
		Sprite_Draw(TEXTURE_INDEX_CH_TUTORIAL,
			SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
			0.0f, 0.0f, Texture_GetWidth(TEXTURE_INDEX_CH_TUTORIAL), Texture_GetHeight(TEXTURE_INDEX_CH_TUTORIAL),
			Texture_GetWidth(TEXTURE_INDEX_CH_TUTORIAL) / 2, Texture_GetHeight(TEXTURE_INDEX_CH_TUTORIAL) / 2,
			3.0f, 3.0f, 0);
		Sprite_Draw(TEXTURE_INDEX_YES,
			SCREEN_WIDTH / 2- (SCREEN_WIDTH / 4), SCREEN_HEIGHT / 2+(SCREEN_HEIGHT/5),
			0.0f, 0.0f, Texture_GetWidth(TEXTURE_INDEX_YES), Texture_GetHeight(TEXTURE_INDEX_YES),
			Texture_GetWidth(TEXTURE_INDEX_YES) / 2, Texture_GetHeight(TEXTURE_INDEX_YES) / 2,
			g_DecSize[Y], g_DecSize[Y], 0,alpha[Y]);
		Sprite_Draw(TEXTURE_INDEX_NO,
			SCREEN_WIDTH / 2+ (SCREEN_WIDTH / 4), SCREEN_HEIGHT / 2 + (SCREEN_HEIGHT / 5),
			0.0f, 0.0f, Texture_GetWidth(TEXTURE_INDEX_NO), Texture_GetHeight(TEXTURE_INDEX_NO),
			Texture_GetWidth(TEXTURE_INDEX_NO) / 2, Texture_GetHeight(TEXTURE_INDEX_NO) / 2,
			g_DecSize[N], g_DecSize[N], 0,alpha[N]);
	}


}

