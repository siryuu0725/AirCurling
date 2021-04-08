#include "StageItem.h"

//初期化関数
void TitleStageItem::Init()
{
	//座標初期化
	for (__int8 i = 0; i < (__int8)TitleStageItemTexCategory::CategoryMax; i++)
	{
		m_stageitem_info.m_ui_pos[i] = m_external_pos[i];
	}

	//テクスチャ読み込み
	Graphics::Instance()->LoadTexture("Res/Tex/Stage_1.png", &m_stageitem_info.m_ui_tex[(__int8)TitleStageItemTexCategory::SelectStage1]);
	Graphics::Instance()->LoadTexture("Res/Tex/Stage_2.png", &m_stageitem_info.m_ui_tex[(__int8)TitleStageItemTexCategory::SelectStage2]);
	Graphics::Instance()->LoadTexture("Res/Tex/StageSelectFrame.png", &m_stageitem_info.m_ui_tex[(__int8)TitleStageItemTexCategory::NowSelectStage]);
	Graphics::Instance()->LoadTexture("Res/Tex/StageSelect.png", &m_stageitem_info.m_ui_tex[(__int8)TitleStageItemTexCategory::SelectStageFont]);
}

//描画情報送信関数
void TitleStageItem::Draw()
{
	TitleItem::ItemInfo item_info;
	mp_title_item->GetTitleItemInfo(item_info);

	//「はじめる」が押された時
	if (item_info.m_is_start == true)
	{
		Graphics::Instance()->DrawTexture(&m_stageitem_info.m_ui_tex[(__int8)TitleStageItemTexCategory::SelectStageFont], m_stageitem_info.m_ui_pos[(__int8)TitleStageItemTexCategory::SelectStageFont]);
		Graphics::Instance()->DrawTexture(&m_stageitem_info.m_ui_tex[(__int8)TitleStageItemTexCategory::SelectStage1], m_stageitem_info.m_ui_pos[(__int8)TitleStageItemTexCategory::SelectStage1]);
		Graphics::Instance()->DrawTexture(&m_stageitem_info.m_ui_tex[(__int8)TitleStageItemTexCategory::SelectStage2], m_stageitem_info.m_ui_pos[(__int8)TitleStageItemTexCategory::SelectStage2]);
		Graphics::Instance()->DrawTexture(&m_stageitem_info.m_ui_tex[(__int8)TitleStageItemTexCategory::NowSelectStage], m_stageitem_info.m_ui_pos[(__int8)TitleStageItemTexCategory::NowSelectStage]);
	}
}

//更新関数
void TitleStageItem::Update()
{
	//文字「1」との当たり判定
	if (HitStageItem(TitleStageItemTexCategory::SelectStage1) == true)
	{
		//マウスの左ボタンが押されたら
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			//ステージ1を選んだフラグtrue
			m_stageitem_info.m_stage_1 = true;
		}
	}
	//文字「1」との当たり判定
	else if (HitStageItem(TitleStageItemTexCategory::SelectStage2) == true)
	{
		//マウスの左ボタンが押されたら
		if (Inputter::Instance()->OnMouseDown(Inputter::Left))
		{
			//ステージ2を選んだフラグtrue
			m_stageitem_info.m_stage_2 = true;
		}
	}
	//音が連続してならないようにする
	else
	{
		//選択枠テクスチャの座標を代入
		m_stageitem_info.m_ui_pos[(__int8)TitleStageItemTexCategory::NowSelectStage].y = 1200.0f;
		SoundController::Instance()->ResetSelectFlag();
	}
}

//テクスチャ解放関数
void TitleStageItem::ReleaseTex()
{
	for (__int8 i = 0; i < (__int8)TitleStageItemTexCategory::CategoryMax; i++)
	{
		if (&m_stageitem_info.m_ui_tex[i] != nullptr)
		{
			m_stageitem_info.m_ui_tex[i].Texture->Release();
			m_stageitem_info.m_ui_tex[i].Texture = nullptr;
		}
	}
}

//ステージ項目当たり判定関数
bool TitleStageItem::HitStageItem(TitleStageItemTexCategory category_)
{
	//マウスと引数の項目との当たり判定を行う
	if (Collision::RectAndPoint(m_stageitem_info.m_ui_pos[(__int8)category_],
		D3DXVECTOR2(Inputter::Instance()->GetMousePos().X, Inputter::Instance()->GetMousePos().Y),
		m_stageitem_info.m_ui_tex[(__int8)category_].Width, m_stageitem_info.m_ui_tex[(__int8)category_].Height) == true)
	{
		//選択枠テクスチャの座標を代入
		m_stageitem_info.m_ui_pos[(__int8)TitleStageItemTexCategory::NowSelectStage] = m_stageitem_info.m_ui_pos[(__int8)category_];
		SoundController::Instance()->PlaySoundSE(PlaySEType::Selsect);

		//ステージ1を選んだフラグtrue
		return true;
		
	}
	

	return false;
}
