#ifndef CAMERA_H_
#define CAMERA_H_
#include "../Object/ObjectBase.h"
#include <d3dx9.h>


constexpr float ShotModeEyePos = -27.8f; //!Viewモード時のカメラの注視点(Y軸)
constexpr float ViewModeEyePos = -50.0f; //!Shotモード時のカメラの注視点(Y軸)
constexpr __int8 AngleofView = 60;       //!画角
constexpr float Near = 1.1f;             
constexpr float Far = 20000000.0f;
constexpr unsigned __int8 CameraSensitivity = 50;  //!カメラ感度

/**
*@class   カメラクラス
*/

class Camera : public ObjectBase
{
private:
	//!オブジェクト情報
	struct CAMERA_INFO :public ObjectInfo
	{
		D3DXVECTOR3 m_eye_pos;   //!注視点

		D3DXVECTOR3 m_camera_up; //!カメラの上向きのベクトル

		D3DXVECTOR3 m_forward;   //!カメラの前向きのベクトル

		D3DXMATRIX mat_view;   //!カメラのビュー情報を保存する変数

		float m_packup;          //!パックの上にカメラを配置するよう

		float m_yaw;     //!X軸回転

		float m_speed;   //!移動スピード

		bool m_is_shotmode; //!打つモードかどうか

		bool m_is_operation; //!操作可能フラグ

	}m_camerainfo;

	//!外部データ保存用構造体
	struct CameraExternalInfo
	{
		//!座標
		D3DXVECTOR3 m_pos;
		//!サイズ
		D3DXVECTOR3 m_eye_pos;
		//!パックの上にカメラを配置するよう
		float m_packup;          

	}m_camera_externalinfo;

public:
	Camera() {}
	~Camera() {}

	/**
	 * @brief  初期化関数
	 * @param (stage_id_) 選択ステージ名(例"Stage1")
	 * @detail オブジェクト情報初期化
	 */
	void Init(std::string stage_str_);

	/**
	 * @brief  外部データ読み込み関数
	 * @detail 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadCameraExternalInfo(std::string stage_str_);

	/**
	 * @brief  更新関数
	 * @detail 更新処理まとめ関数
	 */
	void Update(D3DXVECTOR3 player_pos_);

	/**
	 * @brief  カメラ移動関数
	 * @param (player_pos_) 打つときのカメラ位置
	 * @detail カメラの移動処理を行う
	 */
	void Move(D3DXVECTOR3 player_pos_);

	/**
	 * @brief  カメラ回転関数
	 * @detail カメラの回転処理関数
	 */
	void EyePosRotate();

	/**
	 * @brief  モード切替関数
	 * @detail shotとviewモードの切り替えを行う
	 */
	void ModeChange(D3DXVECTOR3 player_pos_);

	/**
     * @brief  カメラ操作判定Setter関数
     * @detail カメラの操作フラグを切り替える
	 * @detail UIの開始演出時に使用
     */
	void SetCameraOperation(bool operation_) { m_camerainfo.m_is_operation = operation_; }

	/**
 　　* @brief  オブジェクト情報Getter
 　　*/
	const CAMERA_INFO* GetObjInfo()const { return &m_camerainfo; }

};

#endif