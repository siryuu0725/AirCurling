#include "SystemController.h"
#include "Window.h"
#include "DirectGraphics.h"
#include "Inputter.h"

//システム初期化関数
bool InitEngine(int width_, int height_, const char* title_name_)
{
	//Window作成
	if (MakeWindow(width_, height_, title_name_) == false)
	{
		return false;
	}

	//テクスチャ描画情報初期化
	if (Graphics::Instance()->InitGraphics() == false)
	{
		return false;
	}
	//入力情報初期化
	if (Inputter::Instance()->InitInput() == false)
	{
		return false;
	}


	return true;
}

//システム解放関数
void EndEngine()
{
	//テクスチャ描画情報解放
	Graphics::Instance()->ReleaseGraphics();

	//入力情報解放
	Inputter::Instance()->EndInput();

	Graphics::Instance()->ReleaseInstance();
	Inputter::Instance()->ReleaseInstance();
}