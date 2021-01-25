#ifndef SKY_H_
#define SKY_H_
#include "ObjectBase.h"

/**
*@clss  空オブジェクトクラス
*/

//空(上空)
class SkyDome :public ObjectBase
{
public:
	SkyDome() {}
	~SkyDome() {}

	/**
	 * @brief  初期化関数
	 * @detail オブジェクト情報初期化
	 */
	void Init(std::string stage_id_);

	/**
	 * @brief   描画情報送信関数
	 * @detail  Fbx管理クラスにオブジェクト情報を送る
	 */
	void SetUpBuffer();

	/**
 　　* @brief  オブジェクト情報Getter
 　　*/
	const ObjectInfo* GetObjInfo()const { return &skydome_info; }
private:
	ObjectInfo skydome_info;

	struct ObjectInfoCopy
	{
		//!座標
		float pos_x;   
		float pos_y;  
		float pos_z;   

		//!サイズ
		float scale_x; 
		float scale_y; 
		float scale_z; 
	}skydome_info_copy;
};

/**
*@clss  背景床クラス
*/

//空(床)
class SkyFloor :public ObjectBase
{
public:
	SkyFloor();

	/**
	 * @brief  初期化関数
	 * @detail オブジェクト情報初期化
	 */
	void Init(std::string stage_id_);

	/**
	 * @brief   描画情報送信関数
	 * @detail  Fbx管理クラスにオブジェクト情報を送る
	 */
	void SetUpBuffer();

	/**
 　　* @brief  オブジェクト情報Getter
 　　*/
	const ObjectInfo* GetObjInfo()const { return &skyfloor_info; }

private:
	ObjectInfo skyfloor_info;

	struct ObjectInfoCopy
	{
		//!座標
		float pos_x; 
		float pos_y;  
		float pos_z;  

		//!サイズ
		float scale_x; 
		float scale_y; 
		float scale_z; 

	}skyfloor_info_copy;
};
#endif