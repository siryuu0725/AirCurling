﻿/**
 * @file Camera.h
 * @brief カメラオブジェクト
 * @details　中身：カメラクラス
**/
#ifndef CAMERA_H_
#define CAMERA_H_
#include "../Object/ObjectBase.h"
#include <d3dx9.h>

constexpr __int8 AngleofView = 60;       //!画角
constexpr float Near = 1.1f;             
constexpr float Far = 20000000.0f;
constexpr unsigned __int8 CameraSensitivity = 50;  //!カメラ感度

/**
* カメラクラス
* ゴール床の情報を持つ
*/

class Camera : public ObjectBase
{
public:
	//!オブジェクト情報
	struct CameraInfo :public ObjectInfo
	{
		CameraInfo() :
			m_eye_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_camera_up(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_forward(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_packup(0.0f),
			m_yaw(0.0f),
			m_speed(0.0f),
			m_is_shotmode(false),
			m_is_operation(false)
		{
			D3DXMatrixIdentity(&mat_view);
		}

		D3DXVECTOR3 m_eye_pos;   //!注視点

		D3DXVECTOR3 m_camera_up; //!カメラの上向きのベクトル

		D3DXVECTOR3 m_forward;   //!カメラの前向きのベクトル

		D3DXMATRIX mat_view;   //!カメラのビュー情報を保存する変数

		float m_packup;          //!パックの上にカメラを配置するよう

		float m_yaw;     //!X軸回転

		float m_speed;   //!移動スピード

		bool m_is_shotmode; //!打つモードかどうか

		bool m_is_operation; //!操作可能フラグ

	};

private:
	CameraInfo m_camerainfo;

public:
	Camera() {}
	~Camera() {}

	/**
	 * @brief  初期化関数
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details オブジェクト情報初期化
	 */
	virtual void Init(std::string stage_str_)override;

	/**
	 * @brief  外部データ読み込み関数
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	virtual void LoadExternalInfo(std::string stage_str_)override;

	/**
     * @brief  視錐台作成関数
     * @details 視錐台作成
     */
	void CreateFrustum();

	/**
	 * @brief  更新関数
	 * @param[in] player_pos_ プレイヤー座標
	 * @details 更新処理まとめ関数
	 */
	void Update(D3DXVECTOR3 player_pos_);

	/**
	 * @brief  カメラ移動関数
	 * @param[in] player_pos_ プレイヤー座標(打つときのカメラ位置用)
	 * @details カメラの移動処理を行う
	 */
	void Move(D3DXVECTOR3 player_pos_);

	/**
	 * @brief  カメラ回転関数
	 * @details カメラの回転処理関数
	 */
	void RotEyePos();

	/**
	 * @brief  モード切替関数
	 * @param[in] player_pos_ プレイヤー座標(上から見るときのカメラ位置用)
	 * @details shotとviewモードの切り替えを行う
	 */
	void ModeChange(D3DXVECTOR3 player_pos_);

	/**
     * @brief  カメラ操作判定Setter関数
	 * @param[in] is_operation_ trueなら操作可能
     * @detail カメラの操作フラグを切り替える
	 * @details UIの開始演出時に使用
     */
	void SetCameraOperation(bool is_operation_) { m_camerainfo.m_is_operation = is_operation_; }

	/**
　　* @brief  オブジェクト情報Getter
	* @param[out] copy_info_ 保存用オブジェクト構造体
	* @details 引数にオブジェクトの情報を渡す
　　*/
	const void GetCameraInfo(CameraInfo& copy_info_) { copy_info_ = m_camerainfo; }

private:
	//!外部データ保存用構造体
	struct CameraExternalInfo
	{
		CameraExternalInfo() :
			m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_eye_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_packup(0.0f)
		{}

		//!座標
		D3DXVECTOR3 m_pos;
		//!サイズ
		D3DXVECTOR3 m_eye_pos;
		//!パックの上にカメラを配置するよう
		float m_packup;

	};

	CameraExternalInfo m_camera_externalinfo;
};

#endif