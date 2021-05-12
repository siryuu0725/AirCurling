/**
 * @file Effect.h
 * @brief エフェクトを管理する
 * @details 中身：エフェクトクラス、エフェクトの種類列挙体
**/
#ifndef EFFECT_H_
#define EFFECT_H_
#include <Effekseer.h>
#include <EffekseerRendererDX9.h>
#include <d3dx9.h>

#include "Window.h"
#include "../Object/Camera.h"

constexpr unsigned __int16 SpriteNum = 2000;     //!最大描画スプライト数
constexpr unsigned __int16 InstanceNum = 2000;   //!最大インスタンス数
constexpr __int8 EffectCameraAngleofView = 60;   //!カメラの画角


//!エフェクトの種類
enum EffectType
{
	HitEfc,   //!衝突
	ResetEfc, //!リセット
	FallEfc,  //!落下
	GoalEfc,  //!ゴール
	MaxNum	  //!エフェクト数
};

/**
* エフェクトクラス
*/
class Effect
{
private:
	Effect():
		e_manager(nullptr),
		e_renderer(nullptr),
		e_device(nullptr),
		e_handle(-1),
		e_camera_pos(::Effekseer::Vector3D(0.0f, 0.0f, 0.0f)),
		e_eye_pos(::Effekseer::Vector3D(0.0f, 0.0f, 0.0f)),
		e_camera_up(::Effekseer::Vector3D(0.0f, 0.0f, 0.0f))
	{}

	~Effect() {}

public:

	/**
　　* @brief  インスタンス化関数
　　* @details 初回のみインスタンス化し、それ以外は実態を呼ぶ
　　*/
	static Effect* Instance();

	/**
　　* @brief  初期化関数
　　* @details Effecseerの初期化など
　　*/
	void InitEffect();

	/**
　　* @brief  エフェクト読み込み関数
　　* @details 必要なefkファイルを読み込む
　　*/
	void LoadEffect();

	/**
　　* @brief  描画関数
　　*/
	void DrawEffect();

	/**
　　* @brief  エフェクト再生関数
	* @param[in] type_  再生するエフェクトの種類
	* @param[in] x_  表示するX座標
	* @param[in] y_  表示するY座標
	* @param[in] z_  表示するZ座標
　　* @details 呼び出し時にmanagerに再生するよう問い合わせる
　　*/
	void PlayEffect(EffectType type_, float x_, float y_, float z_);

	/**
　　* @brief  エフェクト描画開始関数
　　* @details エフェクトの描画開始処理を行う。
　　*/
	void StartEffect();

	/**
　　* @brief  エフェクト停止関数
　　* @details 必要なefkファイルを読み込む
　　*/
	void StopEffect();

	/**
　　* @brief  エフェクト終了関数
　　* @details エフェクトの描画終了処理を行う。
　　*/
	void EndEffect();

	/**
　　* @brief  エフェクト更新関数
    * @param[in] camera_  カメラのアドレス
　　* @details エフェクトのカメラ設定やmanagerの更新を行う
　　*/
	void UpdateEffect(Camera* camera_);

	/**
　　* @brief  エフェクト解放関数
　　*/
	void ReleaseEffect();

	/**
	*	@brief Instance解放関数(Debug用)
	*	@details 手動でインスタンスを解放する
	*/
	void ReleaseInstance();

private:
	static Effect* mp_instance;

	::Effekseer::Manager* e_manager;
	::EffekseerRendererDX9::Renderer* e_renderer;

	::Effekseer::Effect* efcs[EffectType::MaxNum];    //!エフェクト配列

	::Effekseer::Handle	e_handle;
	LPDIRECT3DDEVICE9 e_device;

	D3DXVECTOR2 window_size;

	::Effekseer::Vector3D e_camera_pos; //!カメラの位置 

	::Effekseer::Vector3D e_eye_pos;    //!注視点

	::Effekseer::Vector3D e_camera_up; //!カメラの上向きのベクトル

};

#endif