#ifndef DIRECTSOUND_H_
#define DIRECTSOUND_H_
#include <dsound.h>
#include <string>

/**
*@class  DXサウンドクラス
*/

class DirectSound {

public:


	DirectSound(HWND hwnd = nullptr);

	/*
	　
	 wavファイルの書き出しを行い、データを返す

	使用方法：
		DirectSound("hoge.wave");
	*/
	IDirectSoundBuffer8* LoadWaveFile(std::string file_name);

	~DirectSound();

private:

	IDirectSound8* m_DSound8;			//サウンドインターフェース
	IDirectSoundBuffer* m_PrimaryBuffer;//プライマリーバッファ―
	IDirectSoundBuffer8* m_SecBuffer;
};

#endif
