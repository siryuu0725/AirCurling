/**
 * @file Graphics.h
 * @brief 2D描画(UIや文字)を扱う
 * @details 中身：2D描画クラス
**/
#ifndef DIRECTGRAHPICS_H_
#define DIRECTGRAHPICS_H_
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include <vector>
#include <fbxsdk.h>
#include <Windows.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")


// 解放
#define	SAFE_DESTROY(x)	{ if(x) { (x)->Destroy(); (x) = NULL; } }

// 解放処理用のマクロを定義
#define SAFE_RELEASE(x) { if(x) { (x)->Release(); (x) = NULL; } }

constexpr int SMALL_FONT_SIZE(16);	//!< フォントサイズ(小)
constexpr int REGULAR_FONT_SIZE(60);	//!< フォントサイズ(中)
constexpr int LARGE_FONT_SIZE(120);	//!< フォントサイズ(大)

constexpr int	TEXTURE_MAX(1000);


/**
* 2D描画クラス
*/

class Graphics
{
public:
	//!テクスチャ情報
	struct TextureData
	{
		TextureData():
			Texture(nullptr),
			Width(0.0f),
			Height(0.0f)
		{}

		LPDIRECT3DTEXTURE9 Texture; //!テクスチャデータ
		float Width;  //!横幅
		float Height; //!縦幅
	};

	//!テクスチャ頂点情報
	struct CustomVertex
	{
		float x;
		float y;
		float z;
		float rhw;
		float tu;
		float tv;
	};

	//!描画文字カラー情報
	enum FontColor
	{
		Black,   //!黒
		White,	 //!白
		Red,	 //!赤
		Yellow,	 //!黄色
	};

	//!描画文字サイズ情報
	enum FontSize
	{
		Small,       //!小 
		Regular,	 //!中
		Large,		 //!大
		FontSizeMax, //!サイズ数
	};

private:
	Graphics() {}
	~Graphics() {}

public:
	/**
　　* @brief  インスタンス化関数
　　*/
	static Graphics* Instance();

	/**
　　* @brief  α値設定関数
　　* @details α値の設定を行う
    * @param[in] enableAlpa_  α値の有効(true)か無効(false)
　　*/
	void SetRenderMode(bool enableAlpa_);

	/**
　　* @brief  描画情報初期化まとめ関数
　　* @details インターフェース、デバイス、ビューポートの設定をまとめている
　　*/
	bool InitGraphics();

	/**
　　* @brief  描画情報解放関数
　　* @details インターフェース、デバイスの解放を行う
　　*/
	void ReleaseGraphics();

	/**
　　* @brief  インターフェース作成関数
　　*/
	bool CreateGraphicsInterface();

	/**
　　* @brief  デバイス作成関数
　　*/
	bool CreateGraphicsDevice(D3DPRESENT_PARAMETERS* present_param_);

	/**
　　* @brief  ビューポート設定関数
　　*/
	bool SetUpViewPort(D3DPRESENT_PARAMETERS* present_param_);

	/**
　　* @brief  描画開始関数
　　*/
	void DrawStart();

	/**
　　* @brief  描画終了関数
　　*/
	void DrawEnd();

	/**
　　* @brief  テクスチャ描画関数
  　* @param[in] texture_  テクスチャ情報構造体
    * @param[in] pos_      ファイルパス
　　*/
	void DrawTexture(TextureData* texture_, D3DXVECTOR2 pos_);

	/**
　　* @brief  テクスチャ描画関数(UV指定用)
  　* @param[in] texture_  テクスチャ情報構造体
    * @param[in] pos_      テクスチャ座標
	* @param[in] sprite_width_  切り抜きサイズ(横幅)
	* @param[in] sprite_height_ 切り抜きサイズ(縦幅)
	* @param[in] tu_  指定TU値
	* @param[in] tv_  指定TV値
　　*/
	void DrawUVTexture(TextureData* texture_, D3DXVECTOR2 pos_, float sprite_width_, float sprite_height_, float tu_, float tv_);
	
	/**
　　* @brief  テクスチャ描画関数(テクスチャ回転用)
    * @param[in] texture_       テクスチャ情報構造体
	* @param[in] lefttop_pos_   テクスチャの左上頂点座標
	* @param[in] righttop_pos_  テクスチャの右上頂点座標
	* @param[in] leftdown_pos_  テクスチャの左下頂点座標
	* @param[in] rightdown_pos_ テクスチャの右下頂点座標
　　*/
	void DrawRotTexture(TextureData* texture_, D3DXVECTOR2 lefttop_pos_, D3DXVECTOR2 righttop_pos_, D3DXVECTOR2 leftdown_pos_, D3DXVECTOR2 rightdown_pos_);

	/**
　　* @brief  テクスチャ読み込み関数
　　* @param[in] file_name_  ファイルパス
　　* @param[in] texture_    テクスチャ情報構造体
　　*/
	bool LoadTexture(const char* file_name_, TextureData* texture_);

	/**
　　* @brief  テクスチャ解放関数
　　* @param[in] texture_  テクスチャ情報構造体
　　*/
	void ReleaseTexture(TextureData* texture_data_);

	/**
　　* @brief  文字描画関数
　　* @param[in] pos_x_  描画X座標
  　* @param[in] pos_y_  描画Y座標
    * @param[in] text_   描画文字
	* @param[in] font_type_  描画サイズ
	* @param[in] color_  描画カラー
　　*/
	void DrawFont(D3DXVECTOR2 pos_, const char* text_, FontSize font_type_, FontColor color_);

	/**
　　* @brief  文字描画用デバイス作成関数
　　*/
	bool CreateFontDevice();

	/**
　　* @brief  文字描画用デバイス作成関数
　　*/
	const LPDIRECT3DDEVICE9 GetD3DDevice() { return g_device; }

	/**
　　* @brief  ライト設定関数
　　*/
	void SetLight();

	/**
	*	@brief Instance解放関数(Debug用)
	*	@details 手動でインスタンスを解放する
	*/
	void ReleaseInstance();

private:
	static Graphics* mp_instance;

	LPDIRECT3D9 g_interface; //!インターフェース
	LPDIRECT3DDEVICE9 g_device; //!デバイス
	LPD3DXFONT g_font_list[Graphics::FontSize::FontSizeMax];
};

#endif
