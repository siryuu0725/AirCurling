/**
 * @file BlockController.h
 * @brief ステージに配置されているブロックオブジェクトを管理している
 * @details　中身：ブロック管理クラス
**/
#ifndef BLOCKCONTROLLER_H_
#define BLOCKCONTROLLER_H_
#include "CircleBlock.h"
#include "RectBlock.h"
#include <vector>

//!ステージに置ける最大ブロック数 
constexpr unsigned __int8 RectBlockMaxNum = 15;
constexpr unsigned __int8 CircleBlockMaxNum = 15;

/**
 * ブロック管理クラス
 */
class BlockController :public ObjectBase
{
public:
	BlockController() {}
	~BlockController();

	/**
	 * @brief  初期化関数
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details 各ブロックのメンバ変数初期化
	 */
	virtual void Init(std::string stage_str_)override;

	/**
	 * @brief  外部データ読み込み関数(矩形ブロック)
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadRectBlockExternalInfo(std::string stage_str_);

	/**
	 * @brief  外部データ読み込み関数(円形ブロック)
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details 読み込んだ外部データを外部データ用の構造体に保存する
	 */
	void LoadCircleBlockExternalInfo(std::string stage_str_);


	/**
     * @brief  描画情報送信関数
     */
	virtual void Draw()override;

	/**
	 * @brief   FBXモデル解放関数
	 */
	virtual void ReleaseModel()override;

	/**
 　　* @brief 当たり判定用情報Set関数
	 * @details ObjectCollisionで使用するオブジェクトコピー情報にオリジナルの情報を渡す
 　　*/
	void SetCollisionInfo();

	/**
 　　* @brief 円形ブロック情報Getter
	 * @param[out] copy_info_ 保存用オブジェクト構造体
	 * @param[in] id_ 受け取りたいブロックのid
	 * @details 引数に円形ブロックの情報を渡す
 　　*/
	const void GetCircleBlockInfo(CircleBlock::ObjectInfo& copy_info_, __int8 id_);

	/**
　　* @brief 矩形ブロック情報Getter
	* @param[out] copy_info_ 保存用オブジェクト構造体
	* @param[in] id_ 受け取りたいブロックのid
	* @details 引数に矩形ブロックの情報を渡す
　　*/
	const void GetRectBlockInfo(RectBlock::ObjectInfo& copy_info_, __int8 id_);

private:
	std::vector<CircleBlock*> m_circleblocks;  //!円形ブロック
	std::vector<RectBlock*> m_rectblocks;	   //!矩形ブロック

	int m_rectblock_num;    //!矩形ブロックデータ数
	int m_circleblock_num;  //!円形ブロックデータ数

	//!外部データ保存用構造体(矩形ブロック)
	struct RectBlockExternalInfo
	{
		RectBlockExternalInfo():
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

	//!外部データ保存用構造体(円形ブロック)
	struct CircleBlockExternalInfo
	{
		CircleBlockExternalInfo() :
			m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_scale(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
			m_radius(0.0f)
		{}

		//!座標
		D3DXVECTOR3 m_pos;
		//!サイズ
		D3DXVECTOR3 m_scale;
		//!半径
		float m_radius;
	};

	//!外部データ保存用
	CircleBlockExternalInfo m_circleblock_externalinfo[CircleBlockMaxNum]; //!円形ブロック
	RectBlockExternalInfo m_rectblock_externalinfo[RectBlockMaxNum];	  //!矩形ブロック
};


#endif