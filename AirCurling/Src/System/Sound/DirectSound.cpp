#include "DirectSound.h"

#pragma comment(lib,"dxguid.lib")
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "winmm.lib")

//コンストラクタ
DirectSound::DirectSound(HWND hwnd_) {


	DirectSoundCreate8(nullptr, &m_DSound8, nullptr);
	m_DSound8->SetCooperativeLevel(hwnd_, DSSCL_NORMAL);

	DSBUFFERDESC desc = {};
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	desc.dwBufferBytes = 0;
	desc.dwReserved = 0;
	desc.lpwfxFormat = nullptr;
	desc.guid3DAlgorithm = GUID_NULL;
}

//　データ読み込み
IDirectSoundBuffer8* DirectSound::LoadWaveFile(std::string file_name_) {


	HMMIO hmmio = nullptr;
	MMIOINFO mminfo = {};
	hmmio = mmioOpen((LPSTR)file_name_.c_str(), &mminfo, MMIO_READ);

	//ファイルのオープンに失敗した場合
	if (!hmmio) {
		MessageBox(0, "waveファイルのオープンに失敗", 0, MB_OK);
		return nullptr;
	}

	MMRESULT result;
	MMCKINFO rif_chunk;
	rif_chunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	result = mmioDescend(hmmio, &rif_chunk, NULL, MMIO_FINDRIFF);

	//リフチャンクの検索に失敗した場合
	if (result != MMSYSERR_NOERROR) {
		mmioClose(hmmio, 0);
		return nullptr;
	}

	MMCKINFO fmt_chunk;
	fmt_chunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	result = mmioDescend(hmmio, &fmt_chunk, &rif_chunk, MMIO_FINDCHUNK);

	//フォーマットチャンクの検索に失敗した場合
	if (result != MMSYSERR_NOERROR) {
		mmioClose(hmmio, 0);
		return nullptr;
	}

	//音質やチャンネル数の情報を格納する
	WAVEFORMATEX format;
	DWORD fmsize = fmt_chunk.cksize;
	if (mmioRead(hmmio, (HPSTR)&format, fmsize) != fmsize) {
		mmioClose(hmmio, 0);
		return nullptr;
	}

	//データ検索の為一度戻る
	mmioAscend(hmmio, &fmt_chunk, 0);

	MMCKINFO data_chunk;
	data_chunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	result = mmioDescend(hmmio, &data_chunk, &rif_chunk, MMIO_FINDCHUNK);
	// データチャンクの検索に失敗した場合
	if (result != MMSYSERR_NOERROR) {
		mmioClose(hmmio, 0);
		return nullptr;
	}

	//波形データ
	DWORD data_size = data_chunk.cksize;
	BYTE* wav_data = new BYTE[data_chunk.cksize];
	if (mmioRead(hmmio, (HPSTR)wav_data, data_chunk.cksize) != data_chunk.cksize) {
		delete[] wav_data;
		return nullptr;
	}


	//正常読み込み
	mmioClose(hmmio, 0);

	// セカンダリバッファの設定
	DSBUFFERDESC desc = {};
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS |
		DSBCAPS_CTRLPAN | DSBCAPS_CTRLFREQUENCY;
	desc.dwBufferBytes = data_size;   //メモリサイズ
	desc.dwReserved = 0;			  //予約域
	desc.lpwfxFormat = &format;       //WAVEフォーマット
	desc.guid3DAlgorithm = GUID_NULL; //3Dエフェクトを使用しない

	IDirectSoundBuffer* buf = 0;
	m_DSound8->CreateSoundBuffer(&desc, &buf, nullptr);

	//戻り値がIDirectSoundBufferの為、IDirectSoundBuffer8に戻す
	buf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&m_SecBuffer);
	buf->Release();


	//WAVデータ書き込み
	LPVOID write_data;
	DWORD len;
	m_SecBuffer->Lock(
		0,		     	//ロック開始位置
		0,			    //メモリサイズ
		&write_data,	//ロック位置のポインタ
		&len,		    //大きさ
		NULL,	  	    //範囲を超えた場合のメモリ領域指定
		NULL,
		DSBLOCK_ENTIREBUFFER //指定の大きさだけロックする
	);

	memcpy(write_data, wav_data, len);
	m_SecBuffer->Unlock(write_data, len, nullptr, 0);
	//　元音源を削除
	delete[] wav_data;

	if (m_SecBuffer == nullptr) {
		MessageBox(0, "waveファイルの読み込みに失敗", 0, MB_OK);
	}

	return m_SecBuffer;
}


//　デストラクタ
DirectSound::~DirectSound() {

	m_DSound8->Release();
	//m_PrimaryBuffer->Release();
}

