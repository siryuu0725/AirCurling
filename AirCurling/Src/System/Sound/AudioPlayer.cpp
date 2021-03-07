#include "AudioPlayer.h"

//ウェブファイル読み込み関数
bool AudioPlayer::LoadAudioFail(std::string alias_, std::string file_name_) {

	//まだ読み込んでいないサウンドデータである場合
	if (m_SoundData.count(alias_) == 0) {
		m_SoundData.emplace(alias_, m_Sound->LoadWaveFile(file_name_));
		return true;
	}
	return false;
}

//再生
void AudioPlayer::Play(
	std::string alias_,
	int volume_,
	bool is_loop_
) {

	IDirectSoundBuffer8* sound = Find(alias_);
	if (sound == nullptr) {
		return;//サウンドデータがなかった
	}

	if (is_loop_) {
		sound->SetVolume(volume_);
		sound->Play(0, 0, DSBPLAY_LOOPING);
	}
	else {
		sound->SetVolume(volume_);
		sound->Play(0, 0, 0);
		sound->SetCurrentPosition(0);
	}
}

//停止
void AudioPlayer::Stop(std::string alias_) {

	IDirectSoundBuffer8* sound = Find(alias_);
	if (sound == nullptr) {
		return;//サウンドデータがなかった
	}
	sound->Stop();
}


// ボリューム調整
void AudioPlayer::SetVolume(std::string alias_, int volume_) {

	IDirectSoundBuffer8* sound = Find(alias_);
	if (sound == nullptr) {
		return;//サウンドデータがなかった
	}
	sound->SetVolume(volume_);
}

//解放処理
void AudioPlayer::Release(std::string alias_) {

	IDirectSoundBuffer8* sound = Find(alias_);
	if (sound == nullptr) {
		return;//サウンドデータがなかった
	}

	if (sound) {
		sound->Release();
		sound = nullptr;
		m_SoundData.erase(alias_);//要素削除
	}
}

//サウンドファイル検索関数
IDirectSoundBuffer8* AudioPlayer::Find(std::string alias_) {

	//サウンドデータをキーで検索
	auto data = m_SoundData.find(alias_);
	//サウンドデータがみつかった場合
	if (data != m_SoundData.end()) {
		return data->second;
	}
	return nullptr;//見つからなかったのでnullを渡す
}

AudioPlayer::~AudioPlayer() {

	if (m_SoundData.empty()) {
		//要素の削除がすべて完了している場合はクリア
		m_SoundData.clear();
	}
	//解放漏れがある場合
	for (auto data : m_SoundData) {
		IDirectSoundBuffer8* sound = data.second;
		if (sound == nullptr) {
			continue;
		}
		sound->Release();
		//m_SoundData.erase(data.first);
	}
	m_SoundData.clear();

	if (m_Sound) {
		delete m_Sound;
	}
}

