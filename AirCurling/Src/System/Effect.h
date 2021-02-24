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
*@clss  エフェクトクラス
*/
class Effect
{
private:
	Effect() {}
	~Effect() {}

public:

	/**
　　* @brief  インスタンス化関数
　　* @detail 初回のみインスタンス化し、それ以外は実態を呼ぶ
　　*/
	static Effect* Instance();

	/**
　　* @brief  初期化関数
　　* @detail Effecseerの初期化など
　　*/
	void InitEffect();

	/**
　　* @brief  エフェクト読み込み関数
　　* @detail 必要なefkファイルを読み込む
　　*/
	void LoadEffect();

	/**
　　* @brief  描画関数
　　*/
	void DrawEffect();

	/**
　　* @brief  エフェクト再生関数
	* @param (type_)  再生するエフェクトの種類
	* @param (x_)  表示するX座標
	* @param (y_)  表示するY座標
	* @param (z_)  表示するZ座標
　　* @detail 呼び出し時にmanagerに再生するよう問い合わせる
　　*/
	void PlayEffect(EffectType type_, float x_, float y_, float z_);

	/**
　　* @brief  エフェクト描画開始関数
　　* @detail エフェクトの描画開始処理を行う。
　　*/
	void StartEffect();

	/**
　　* @brief  エフェクト停止関数
　　* @detail 必要なefkファイルを読み込む
　　*/
	void StopEffect();

	/**
　　* @brief  エフェクト終了関数
　　* @detail エフェクトの描画終了処理を行う。
　　*/
	void EndEffect();

	/**
　　* @brief  エフェクト更新関数
    * @param (camera_)  カメラのアドレス
　　* @detail エフェクトのカメラ設定やmanagerの更新を行う
　　*/
	void UpdateEffect(Camera* camera_);

	/**
　　* @brief  エフェクト解放関数
　　*/
	void ReleaseEffect();
private:
	static Effect* p_instance;
	Camera* m_camera;

	::Effekseer::Manager* e_manager = NULL;
	::EffekseerRendererDX9::Renderer* e_renderer = NULL;

	::Effekseer::Effect* hit_efc = NULL;    //!衝突時エフェクト
	::Effekseer::Effect* fall_efc = NULL;	//!落下時エフェクト
	::Effekseer::Effect* reset_efc = NULL;	//!反射時エフェクト
	::Effekseer::Effect* goal_efc = NULL;	//!ゴール時エフェクト


	::Effekseer::Handle	e_handle = -1;
	::Effekseer::Vector3D e_position;
	LPDIRECT3DDEVICE9	e_device = NULL;

	D3DXVECTOR2 window_size;

	
	::Effekseer::Vector3D e_camera_pos; //!カメラの位置 

	::Effekseer::Vector3D e_eye_pos; //!注視点

	::Effekseer::Vector3D e_camera_up; //!カメラの上向きのベクトル

};

#endif