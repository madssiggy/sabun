#include "tutorial.h"

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

#include "tutboard.h"

static int fps;
static int g_Timer;


static ParticleManager particle;
static SpeedlineManager line;

static int g_GameFrameCount;

static int g_Score = 0;// 点数
static int g_KillCount = 0;


static bool Game_EndCheck(void);

void InitTutBoard();
void UninitTutBoard();
void UpdateTutBoard();
void DrawTutBoard();

void InitTutorial(void)
{
	InitTutBoard();

	Grid_Initialize();

	// カメラの初期化処理
	Camera_Initialize();
	//Camera2_Initialize();

	// ライトの初期化処理
	Light_Initialize();

	//グリッドの初期化処理
	//Grid_Initialize();





	// 影
	Shadow_Initialize();

	// プレイヤー
	Player_Initialize();

	// グラウンド
	Ground_Initialize();

	// ドリンク
	Drink_Initialize();

	// スコア
	InitScore();

	// パーティクル
	particle.InitParticle();

	// スピードライン
	line.InitSpeedline();

	// メーター
	Meter_Initialize();


	//PlaySound(SOUND_LABEL_BGM_GAME);
}

void UninitTutorial(void)
{
	UninitTutBoard();
	Grid_Finalize();
//	StopSound(SOUND_LABEL_BGM_GAME);
	// カメラの終了処理
	Camera_Finalize();
	//Camera2_Finalize();

	// ライトの終了処理
	Light_Finalize();

	// グリッドの終了
	//Grid_Finalize();



	// 影
	Shadow_Finalize();

	// プレイヤー
	Player_Finalize();

	// グラウンド
	//Ground_Finalize();

	// ドリンク
	Drink_Finalize();

	// スコア
	UninitScore();

	// パーティクル
	particle.UninitParticle();

	// スピードライン
	line.UninitSpeedline();

	// メーター
	Meter_Finalize();



}

void UpdateTutorial(void)
{
	UpdateTutBoard();

	// カメラの更新処理
	Camera_Update();
	//Camera2_Update();

	// ライトの更新処理
	Light_Update();

	//グリッド線
	//Grid_Update();



	// 影
	Shadow_Update();

	// プレイヤー
	Player_Update();

	// グラウンド
	//Ground_Update();
	Grid_Update();

	// ドリンク
	Drink_Update();

	// スコア
	UpdateScore();

	// パーティクル
	particle.UpdateParticle();

	// スピードライン
	line.UpdateSpeedline();

	// メーター
	Meter_Update();
	
	DebugProc_Print((char *)"\nfps:%d\ng_Timer:%d", fps,g_Timer);
	if (Keyboard_IsRelease(DIK_SPACE))
	{
		Scene_Change(SCENE_INDEX_GAME);
	}

}

void DrawTutorial(void)
{
	// カメラの設定
	Camera_SetCamera();
	//Camera2_SetCamera();

	//グリッドの描画
	Grid_Draw();



	// グラウンド
	Ground_Draw();


	Shadow_Draw();

	// プレイヤー
	Player_Draw();

	DrawTutBoard();
	// ドリンク
	Drink_Draw();
	//説明画面

	// 影
	// スコア
	DrawScore();

	// パーティクル
	particle.DrawParticle();

	// スピードライン
	//line.DrawSpeedline();

	// メーター
	Meter_Draw();

}
static bool phase=false;


static TextureIndex tut;
int phaseChecker;
static int alpha;
static int AddAlpha;
static int g_yPos;
const int AlphaSpeed = 1;
static float UV;

static int ResetTime = 100;


void InitTutBoard() {
	g_Timer = 91;
	fps = 0;
	g_yPos = 0;
	tut = TEXTURE_INDEX_PEDAL;
	phaseChecker = 0;
	alpha = 255;
	AddAlpha = 1;
	UV = 0;
}
void UninitTutBoard() {
	StopSound(SOUND_LABEL_SE_DRIFT);
	tut = TEXTURE_INDEX_TEMPORARY;
	phaseChecker = 0;
	alpha = 0;
	AddAlpha = 1;
}
void UpdateTutBoard() {
	fps += 1;
	if (fps % (ResetTime / 4) == 0) {
		UV += 0.25;
	}
	if (fps >= ResetTime) {

		UV = 0;
		fps = 0;

	}

	if (g_yPos < SCREEN_HEIGHT / 4)
		g_yPos += AlphaSpeed;
	if (phaseChecker == 0) {
		if (GetisMove() && (alpha > 1)) {
			alpha -= AddAlpha;
		}
		else if (!GetisMove() && (alpha > 1 && alpha < 255)) {
			alpha += AddAlpha;
		}
		if (alpha <= 1) {
			g_yPos = -50.0f;
			phaseChecker = 1;
			alpha = 255;
			tut = TEXTURE_INDEX_TEMPORARY2;
		}
	}
	else if (phaseChecker == 1) {
		if (GetisMove() && (alpha > 1)) {
			alpha -= AddAlpha;
		}
		else if (!GetisMove() && (alpha > 1 && alpha < 255)) {
			alpha += AddAlpha;
		}

		if (alpha <= 1) {
			g_yPos = 0.0f;
			alpha = 0;
			phaseChecker = 2;
			fps = 0;
			tut = TEXTURE_INDEX_TEMPORARY;
		}
	}
	else if (phaseChecker == 2) {
		if (fps >= 99) {
			g_Timer -= 1;
		}
		if (g_Timer <= 0) {
			Scene_Change(SCENE_INDEX_GAME);
		}


	}

}
const float SCORE_SIZE = Texture_GetWidth(TEXTURE_INDEX_SCORE002)/10.0f;
const float TextureWeight[10] = {0.1f,0.2f,0.3f,0.4f,0.5f,0.6f,0.7f,0.8f,0.9f};
void DrawTutBoard() {
	if (phaseChecker < 2) {
		Sprite_Draw(tut,
			SCREEN_WIDTH / 2, (g_yPos),
			0.0f + (Texture_GetWidth(tut)*UV), 0.0f,
			(Texture_GetWidth(tut)*0.25f), Texture_GetHeight(tut),
			Texture_GetWidth(tut) / 4, Texture_GetHeight(tut), 0.5f, 0.5f, 0.0f, alpha);
	}
	else if(phaseChecker==2){
		static int p_Count=g_Timer;
		for (int i = 0;i < 2;i++) {
			int use=p_Count / 10;
			Sprite_Draw(TEXTURE_INDEX_SCORE002, 
				SCREEN_WIDTH/2 + SCORE_SIZE*i, SCREEN_HEIGHT/2,
				0.0f+(Texture_GetWidth(TEXTURE_INDEX_SCORE002)*(TextureWeight[use]-0.1f)), 0.0f,
				SCORE_SIZE, Texture_GetHeight(TEXTURE_INDEX_SCORE002),
				SCORE_SIZE / 2, SCORE_SIZE / 2, 1.0f, 1.0f, 0.0f);
			p_Count %=10;
		}
		
	}

}

