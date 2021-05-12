#include "LoadUI.h"
#include "../../Utility/Calculation.h"

//初期化関数
void LoadUI::Init()
{
	if (mp_load_font == nullptr) { mp_load_font = new LoadFontUI; }
	if (mp_load_icon == nullptr) { mp_load_icon = new LoadIconUI; }

	//外部データ読み込み
	LoadPoseUIExternalInfo();

	//外部データセット
	SetUIPos();

	//各UIを配列でまとめる
	UIBase* ui[LoadUICategoryNum] =
	{ mp_load_font ,mp_load_icon };

	for (__int8 i = 0; i < LoadUICategoryNum; i++)
	{
		ui[i]->Init(); //初期化
	}
}

//外部データセット関数
void LoadUI::SetUIPos()
{
	mp_load_icon->SetUIPos(m_loadui_externalinfo[(__int8)LoadUICategory::RotTex].m_pos);

	mp_load_font->SetUIPos(m_loadui_externalinfo[(__int8)LoadUICategory::NowLoad ].m_pos);
}

//外部データ読み込み関数
void LoadUI::LoadPoseUIExternalInfo()
{
	FILE* fp = nullptr;

	fopen_s(&fp, "Res/UIData/LoadUIData.dat", "rb");

	if (fp != nullptr)
	{
		fread(&m_ui_num, sizeof(m_ui_num), 1, fp);

		//書き込む
		fread(&m_loadui_externalinfo, sizeof(UIExternalInfo), m_ui_num, fp);

		//ファイルクローズ
		fclose(fp);
	}
}

//描画情報送信関数
void LoadUI::Draw()
{
	//各UIを配列でまとめる
	UIBase* ui[LoadUICategoryNum] =
	{ mp_load_font ,mp_load_icon };

	for (__int8 i = 0; i < LoadUICategoryNum; i++)
	{
		ui[i]->Draw();
	}
}

//更新関数
void LoadUI::Update()
{
	mp_load_icon->Update();
	//LoadTexRote();
}

//テクスチャ解放関数
void LoadUI::ReleaseTex()
{
	//各UIを配列でまとめる
	UIBase* ui[LoadUICategoryNum] =
	{ mp_load_font ,mp_load_icon };

	for (__int8 i = 0; i < LoadUICategoryNum; i++)
	{
		ui[i]->ReleaseTex();
		delete ui[i];
	}

	mp_load_font = nullptr;
	mp_load_icon = nullptr;
}
