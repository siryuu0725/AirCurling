#include "TitleUI.h"
#include "../../System/Inputter.h"
#include "../../Utility/Collision/Collision.h"

//初期化関数
void TitleUI::Init()
{
	if (mp_title_item == nullptr) { mp_title_item = new TitleItem; }
	if (mp_bg == nullptr) { mp_bg = new TitleBG(mp_title_item); }
	if (mp_stage_item == nullptr) { mp_stage_item = new TitleStageItem(mp_title_item); }
	if (mp_game_name == nullptr) { mp_game_name = new GameName(mp_title_item); }

	//外部データ読み込み
	LoadTitleUIExternalInfo();

	//外部データセット
	SetUIPos();

	//各UIを配列でまとめる
	UIBase* ui[TitleUICategoryNum] =
	{ mp_bg ,mp_stage_item ,mp_title_item,mp_game_name };

	for (int i = 0; i < TitleUICategoryNum; i++)
	{
		ui[i]->Init(); //初期化
	}

	m_titleui_info.startui_flg = false; //ゲームシーン移行フラグ
	m_titleui_info.endui_flg = false;	//終了フラグ
	m_titleui_info.helpui_flg = false;	//ヘルプシーン移行フラグ
	m_titleui_info.m_stage_1 = false;	//ステージ1を選んだ場合
	m_titleui_info.m_stage_2 = false;	//ステージ2を選んだ場合
}

//外部データセット関数
void TitleUI::SetUIPos()
{
	mp_bg->SetUIPos(m_titleui_externalinfo[(__int8)TitleUICategory::BG].m_pos,
		           m_titleui_externalinfo[(__int8)TitleUICategory::HelpBG].m_pos);

	mp_stage_item->SetUIPos(m_titleui_externalinfo[(__int8)TitleUICategory::SelectStage1].m_pos,
		m_titleui_externalinfo[(__int8)TitleUICategory::SelectStage2].m_pos,
		m_titleui_externalinfo[(__int8)TitleUICategory::NowSelectStage].m_pos,
		m_titleui_externalinfo[(__int8)TitleUICategory::SelectStageFont].m_pos);


	mp_title_item->SetUIPos(m_titleui_externalinfo[(__int8)TitleUICategory::Start].m_pos,
	m_titleui_externalinfo[(__int8)TitleUICategory::End].m_pos,
		m_titleui_externalinfo[(__int8)TitleUICategory::Help].m_pos,
	m_titleui_externalinfo[(__int8)TitleUICategory::NowSelect].m_pos);


	mp_game_name->SetUIPos(m_titleui_externalinfo[(__int8)TitleUICategory::Name].m_pos);

}

//外部データ読み込み関数
void TitleUI::LoadTitleUIExternalInfo()
{
	FILE* fp = nullptr;

	fopen_s(&fp, "Res/UIData/TitleUIData.dat", "rb");

	if (fp != nullptr)
	{
		fread(&m_ui_num, sizeof(m_ui_num), 1, fp);

		//書き込む
		fread(&m_titleui_externalinfo, sizeof(UIExternalInfo), m_ui_num, fp);

		//ファイルクローズ
		fclose(fp);
	}
}

//描画情報送信関数
void TitleUI::Draw()
{
	//各UIを配列でまとめる
	UIBase* ui[TitleUICategoryNum] =
	{ mp_bg ,mp_stage_item ,mp_title_item,mp_game_name };

	for (int i = 0; i < TitleUICategoryNum; i++)
	{
		ui[i]->Draw();
	}
}

//更新関数
void TitleUI::Update()
{
	if (m_titleui_info.startui_flg == false)
	{
		//タイトルの各項目更新処理
		mp_title_item->Update();

		//情報更新
		TitleItem::ItemInfo title_item_info;
		mp_title_item->GetTitleItemInfo(title_item_info);

		//各フラグ保存
		m_titleui_info.startui_flg = title_item_info.m_is_start;
		m_titleui_info.helpui_flg = title_item_info.m_is_help;
		m_titleui_info.endui_flg = title_item_info.m_is_end;
	}
	//「はじめる」が押された後(ステージ選択画面中)
	else if(m_titleui_info.startui_flg == true)
	{
		//ステージ選択画面の各項目更新処理
		mp_stage_item->Update();

		//情報更新
		TitleStageItem::TitleStageItemInfo stage_item_info;
		mp_stage_item->GetStageItemInfo(stage_item_info);

		//各フラグ保存
		m_titleui_info.m_stage_1 = stage_item_info.m_stage_1;	//ステージ1を選んだ場合
		m_titleui_info.m_stage_2 = stage_item_info.m_stage_2;	//ステージ2を選んだ場合

		if (Inputter::Instance()->GetKeyDown(Inputter::ESCKey))
		{
			m_titleui_info.startui_flg = false;
			mp_title_item->FlgReset();
		}
	}
}

//テクスチャ解放関数
void TitleUI::ReleaseTex()
{
	//各UIを配列でまとめる
	UIBase* ui[TitleUICategoryNum] =
	{ mp_bg ,mp_stage_item ,mp_title_item,mp_game_name };

	for (int i = 0; i < TitleUICategoryNum; i++)
	{
		ui[i]->ReleaseTex();
	}
}


