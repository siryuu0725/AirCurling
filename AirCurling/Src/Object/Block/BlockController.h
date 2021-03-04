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
constexpr unsigned __int8 RectBlockMaxNum = 20;
constexpr unsigned __int8 CircleBlockMaxNum = 20;

/**
 * ブロック管理クラス
 */
class BlockController
{
public:
	BlockController() {}
	~BlockController();

	/**
	 * @brief  初期化関数
	 * @param[in] stage_str_ 選択ステージ名(例"Stage1")
	 * @details 各ブロックのメンバ変数初期化
	 */
	void Init(std::string stage_str_);

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
	void Draw();

	/**
	 * @brief   FBXモデル解放関数
	 */
	void ReleaseModel();

	/**
 　　* @brief 当たり判定用情報Set関数
	 * @details ObjectCollisionで使用するオブジェクトコピー情報にオリジナルの情報を渡す
 　　*/
	void SetCollisionInfo();

	///**
	// * @brief 各ブロック情報Getter関数
	// * @return 各ブロック座標、サイズの情報を返す
	// */
	//const std::vector<Shape*>* GetRectShape()const { return &m_rect_shapes; }
	//const std::vector<Shape*>* GetCircleShape()const { return &m_circleshapes; }

	const std::vector<CircleBlock*>* GetCircleBlock()const { return &m_circleblocks; }

	/**
 　　* @brief 円形ブロック情報Getter
	 * @param[out] copy_info_ 保存用オブジェクト構造体
	 * @param[in] id_ 受け取りたいブロックのid
	 * @details 引数に円形ブロックの情報を渡す
 　　*/
	void GetCircleBlockInfo(CircleBlock::ObjectInfo& copy_info_, int id_);

	/**
　　* @brief 矩形ブロック情報Getter
	* @param[out] copy_info_ 保存用オブジェクト構造体
	* @param[in] id_ 受け取りたいブロックのid
	* @details 引数に矩形ブロックの情報を渡す
　　*/
	void GetRectBlockInfo(RectBlock::ObjectInfo& copy_info_, int id_);

private:
	std::vector<CircleBlock*> m_circleblocks;  //!円形ブロック
	std::vector<RectBlock*> m_rectblocks;	   //!矩形ブロック

	std::vector<Shape*> m_rect_shapes;   //!矩形情報保存用(当たり判定用)
	std::vector<Shape*> m_circleshapes;	 //!円形情報保存用(当たり判定用)

	int m_rectblock_num;    //!矩形ブロックデータ数
	int m_circleblock_num;  //!円形ブロックデータ数

	//!外部データ保存用構造体(矩形ブロック)
	struct RectBlockExternalInfo
	{
		RectBlockExternalInfo():
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
	CircleBlockExternalInfo m_circleblock_externalinfo[RectBlockMaxNum]; //!円形ブロック
	RectBlockExternalInfo m_rectblock_externalinfo[CircleBlockMaxNum];	  //!矩形ブロック
};


#endif