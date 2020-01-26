#include <d3dx9.h>
//#include "debugPrintf.h"
#include "mydirect3d.h"
#include "texture.h"
#include "main.h"

#define TEXTURE_FILENAME_MAX (64)


typedef struct TextureFile_tag
{
	char filename[TEXTURE_FILENAME_MAX];
	int width;
	int height;
} TextureFile;

static const TextureFile g_TextureFiles[] = {
	{ "asset/texture/TITLE_BG.png", SCREEN_WIDTH, SCREEN_HEIGHT },//---1
	{ "asset/texture/TITLE_Title.png", 256, 64 },//---2
	{ "asset/texture/TITLE_Press.png", 256, 64 },//---3
	{ "asset/texture/meter.png", 256, 256 },//---4
	{ "asset/texture/needle.png", 20, 100 },//---5
	{ "asset/texture/number004.png", 25, 30 },//---6
	{ "asset/texture/RESULT.jpg", SCREEN_WIDTH, SCREEN_HEIGHT },//---7
	{ "asset/texture/road.jpg", 500, 500 },//---8
	{ "asset/texture/field000.jpg", 500, 500 },//---9
	{ "asset/texture/number.png", 3200, 321 },//---10
	{ "asset/texture/SABCD001.png", 2000, 800 },//---11
	{ "asset/texture/frame-l.png", 3366, 3257 },//---12
	{ "asset/texture/frame-s.png", 2154, 3257 },//---13

{ "asset/texture/1st.png", 308, 267 },//---14
{ "asset/texture/2nd.png", 302, 209 },//---15
{ "asset/texture/3rd.png", 295, 210 },//---16
{ "asset/texture/4th.png", 288, 219 },//---17
{"asset/texture/pe-0123.png",1602,400},//18ペダル画像
{"asset/texture/CheckTutorial.png",430,299},//19確認ボード
{"asset/texture/Yes.png",473,194},//20選択肢:Yes
{"asset/texture/No.png",341,181},//21選択肢:No

	{ "asset/texture/temporaryTexture.png", 235, 183 },//---Temporary
	{ "asset/texture/temporaryTexture2.png", 235, 183 },//---Temporary2
};

static const int TEXTURE_FILE_COUNT = sizeof(g_TextureFiles) / sizeof(g_TextureFiles[0]);

static_assert(TEXTURE_INDEX_MAX == TEXTURE_FILE_COUNT, "TEXTURE_INDEX_MAX != TEXTURE_FILE_COUNT");

static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_FILE_COUNT] = {};

int Texture_Load(void)
{   
    LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	if( !pDevice ) {
		return TEXTURE_FILE_COUNT;
	}

	int failed_count = 0;

	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( FAILED(D3DXCreateTextureFromFile(pDevice, g_TextureFiles[i].filename, &g_pTextures[i])) ) {
            // DebugPrintf("テクスチャの読み込みに失敗 ... %s\n", g_TextureFiles[i].filename);
			failed_count++;
		}
	}

	return failed_count;
}

void Texture_Release(void)
{
	for( int i = 0; i < TEXTURE_FILE_COUNT; i++ ) {
		
		if( g_pTextures[i] ) {
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

LPDIRECT3DTEXTURE9 Texture_GetTexture(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_pTextures[index];
}

int Texture_GetWidth(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_TextureFiles[index].width;
}

int Texture_GetHeight(TextureIndex index)
{
    if( index < 0 || index >= TEXTURE_INDEX_MAX ) {
        return NULL;
    }

	return g_TextureFiles[index].height;
}
