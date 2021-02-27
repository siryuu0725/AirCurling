#ifndef FLOOR_H_
#define FLOOR_H_
#include "../ObjectBase.h"

/**
*@class   ステージ床クラス
*/

class Floor :public ObjectBase
{
public:
	Floor() {}
	~Floor() {}

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
	void LoadFloorExternalInfo(std::string stage_str_);

	/**
	 * @brief  描画情報送信関数
	 */
	void Draw();

	/**
	 * @brief   FBXモデル解放関数
	 */
	void ReleaseModel();

	/**
 　　* @brief  オブジェクト情報Getter
 　　*/
	const ObjectInfo* GetObjInfo()const { return &m_floor_info; }

private:
	//!外部データ保存用構造体
	struct FloorExternalInfo
	{
		FloorExternalInfo() :
			m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_rote(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_width(0.0f),
			m_height(0.0f)
		{}

		//!座標
		D3DXVECTOR3 m_pos;
		//!サイズ
		D3DXVECTOR3 m_scale;

		//!回転角度
		D3DXVECTOR3 m_rote;

		float m_width;  //!横幅
		float m_height; //!縦幅


	};

	ObjectInfo m_floor_info;  //!ステージ床情報
	FloorExternalInfo m_floor_externalinfo;
};


#endif