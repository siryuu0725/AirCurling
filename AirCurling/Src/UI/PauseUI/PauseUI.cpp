#include "PauseUI.h"
#include "../../Utility/Collision/Collision.h"
#include "../../System/Inputter.h"

//初期化関数
void PauseUI::Init()
{
	if (mp_item == nullptr) { mp_item = new PauseItemUI; }
	if (mp_bg == nullptr) { mp_bg = new PauseBG(mp_item); }

	//外部データ読み込み
	LoadPoseUIExternalInfo();

	//外部データセット
	SetUIPos();

	//各UIを配列でまとめる
	UIBase* ui[PauseUICategoryNum] =
	{ mp_bg ,mp_item };
	for (__int8 i = 0; i < PauseUICategoryNum; i++)
	{
		ui[i]->Init(); //初期化
	}

	m_poseui_info.m_select = false;
	m_poseui_info.m_is_continue = false;
	m_poseui_info.m_is_end = false;
	m_poseui_info.m_is_help = false;
}

//外部データセット関数
void PauseUI::SetUIPos()
{
	mp_bg->SetUIPos(m_pauseui_externalinfo[(__int8)PauseUICategory::BG].m_pos,
		m_pauseui_externalinfo[(__int8)PauseUICategory::HelpBG].m_pos);

	mp_item->SetUIPos(m_pauseui_externalinfo[(__int8)PauseUICategory::Continue].m_pos,
		m_pauseui_externalinfo[(__int8)PauseUICategory::End].m_pos,
		m_pauseui_externalinfo[(__int8)PauseUICategory::Help].m_pos,
		m_pauseui_externalinfo[(__int8)PauseUICategory::Select].m_pos);

}

//外部データ読み込み関数
void PauseUI::LoadPoseUIExternalInfo()
{
	FILE* fp = NULL;

	fopen_s(&fp, "Res/UIData/PoseUIData.dat", "rb");

	if (fp != nullptr)
	{
		fread(&m_ui_num, sizeof(m_ui_num), 1, fp);

		//書き込む
		fread(&m_pauseui_externalinfo, sizeof(UIExternalInfo), m_ui_num, fp);

		//ファイルクローズ
		fclose(fp);
	}
}

//更新関数
void PauseUI::Update()
{
	mp_item->Update();

	PauseItemUI::PauseItemInfo item_info;
	mp_item->GetPoseItemInfo(item_info);
	m_poseui_info.m_is_continue = item_info.m_is_continue;
	m_poseui_info.m_is_end = item_info.m_is_end;
	m_poseui_info.m_is_help = item_info.m_is_help;
}

//描画情報送信関数
void PauseUI::Draw()
{
	//各UIを配列でまとめる
	UIBase* ui[PauseUICategoryNum] =
	{ mp_bg ,mp_item };

	for (__int8 i = 0; i < PauseUICategoryNum; i++)
	{
		ui[i]->Draw();
	}
}

//テクスチャ解放関数
void PauseUI::ReleaseTex()
{
	//各UIを配列でまとめる
	UIBase* ui[PauseUICategoryNum] =
	{ mp_bg ,mp_item };

	for (__int8 i = 0; i < PauseUICategoryNum; i++)
	{
		ui[i]->ReleaseTex();
	}
}
