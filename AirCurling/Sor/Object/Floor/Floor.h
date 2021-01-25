#ifndef FLOOR_H_
#define FLOOR_H_
#include "../ObjectBase.h"

/**
*@clss   ステージ床クラス
*/

class Floor :public ObjectBase
{
public:
	Floor() {}
	~Floor() {}

	/**
	 * @brief  初期化関数
	 * @detail オブジェクト情報初期化
	 */
	void Init(std::string stage_id_);

	/**
	 * @brief  描画情報送信関数
	 */
	void SetUpBuffer();

	/**
 　　* @brief  オブジェクト情報Getter
 　　*/
	const ObjectInfo* GetObjInfo()const { return &m_floor_info; }

private:
	ObjectInfo m_floor_info;  //!ステージ床情報

	struct ObjectInfoCopy
	{
		float pos_x;   //!座標
		float pos_y;   //!座標
		float pos_z;   //!座標

		float scale_x; //!サイズ
		float scale_y; //!サイズ
		float scale_z; //!サイズ

		float rote_x; //!サイズ
		float rote_y; //!サイズ
		float rote_z; //!サイズ

		float width;
		float height;


	}floor_info_copy;
};


#endif