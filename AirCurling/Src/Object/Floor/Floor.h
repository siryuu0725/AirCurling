/**
 * @file Floor.h
 * @brief ステージの土台となる床オブジェクト
 * @details　中身：ステージ床クラス
**/
#ifndef FLOOR_H_
#define FLOOR_H_
#include "../ObjectBase.h"

/**
* ステージ床クラス
*/
class Floor :public ObjectBase
{
public:
	Floor() {}
	~Floor() {}

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
	 * @brief  描画情報送信関数
	 */
	virtual void Draw()override;

	/**
	 * @brief   FBXモデル解放関数
	 */
	virtual void ReleaseModel()override;

	/**
　　* @brief  オブジェクト情報Getter
	* @param[out] copy_info_ 保存用オブジェクト構造体
	* @details 引数にオブジェクトの情報を渡す
　　*/
	const void GetFloorInfo(ObjectInfo& copy_info_) { copy_info_ = m_floor_info; }

private:
	//!外部データ保存用構造体
	struct FloorExternalInfo
	{
		FloorExternalInfo() :
			m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_rot_angle(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_width(0.0f),
			m_height(0.0f)
		{}

		//!座標
		D3DXVECTOR3 m_pos;
		//!サイズ
		D3DXVECTOR3 m_scale;

		//!回転角度
		D3DXVECTOR3 m_rot_angle;

		float m_width;  //!横幅
		float m_height; //!縦幅


	};

	ObjectInfo m_floor_info;  //!ステージ床情報
	FloorExternalInfo m_floor_externalinfo;
};


#endif