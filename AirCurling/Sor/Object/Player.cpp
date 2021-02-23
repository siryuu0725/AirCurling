#include "Player.h"
#include "../System/Effect.h"
#include "../Score/GameScore.h"
#include <time.h> 

//!コンストラクタ
Player::Player(Camera* camera_, BlockController* block_, 
	Floor* floor_, DebufController* debuf_, Goal* goal_) :
	m_camera(camera_), m_block(block_), m_floor(floor_), m_debuf(debuf_), m_goal(goal_)
{
	m_update_step = PlayerUpdateStep::StartProduction;  //!更新ステップを開始演出で初期化
}

//!初期化関数
void Player::Init(std::string stage_str_)
{
	//!外部データ読み込み
	LoadPlayerExternalInfo(stage_str_);

	player_info.m_key = "pac";  //!描画用キー

	player_info.m_pos = D3DXVECTOR3(m_player_info_copy.pos[ARRAY_DATA::X], m_player_info_copy.pos[ARRAY_DATA::Y], m_player_info_copy.pos[ARRAY_DATA::Z]); //!座標
	player_info.m_scale = D3DXVECTOR3(m_player_info_copy.scale[ARRAY_DATA::X], m_player_info_copy.scale[ARRAY_DATA::Y], m_player_info_copy.scale[ARRAY_DATA::Z]);	 //!描画サイズ

	player_info.m_mat_world = Calculation::Matrix(player_info.m_pos, player_info.m_scale, player_info.m_angle);  //!ワールド座標
	
	player_info.m_friction = m_player_info_copy.fa;   //!動摩擦係数
	player_info.m_acceleration = -player_info.m_friction * 9.8f; //!加速度


	player_info.m_radius = m_player_info_copy.radius;    //!半径
	player_info.m_speed = m_player_info_copy.speed;  //!移動スピード

	player_info.m_timer = 0;  //!経過時間
	player_info.m_truncounter = 0;    //!進行ターン数
	player_info.m_reflectcounter = 0; //!反射回数
	player_info.m_is_turnend = false;    //!1ターン終了フラグ
	player_info.m_is_goal = false;       //!ゴールフラグ
	player_info.m_end = false;        //!ゲームエンドフラグ
	player_info.m_score_counter = m_player_info_copy.score_counter;

	player_info.m_is_movement = false;

	player_info.m_nor_speed.y = 0.0f;
}

//!外部データ読み込み関数
void Player::LoadPlayerExternalInfo(std::string stage_str_)
{
	FILE* fp = nullptr;

	std::string stage_id = "Res/ObjectData/" + stage_str_ + "PlayerData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");

	if (fp != nullptr)
	{
		//!書き込む
		fread(&m_player_info_copy, sizeof(PlayerExternalInfo), 1, fp);

		/* ファイルクローズ */
		fclose(fp);
	}
}

//!描画情報送信関数
void Player::Draw()
{
	FbxController::Instance()->DrawFbx(player_info.m_key, player_info.m_mat_world);
}

//!FBXモデル解放関数
void Player::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(player_info.m_key);
}

//!更新関数
void Player::Update()
{
	switch (m_update_step)
	{
	case PlayerUpdateStep::StartProduction: //!開始演出
		StartMove();
		break;
	case PlayerUpdateStep::GameMain:  //!ゲーム本編
		Move();  //!移動

		HitController();   //!当たり判定

		ResetPos();
		break;
	case PlayerUpdateStep::EndProduction:  //!終了演出
		EndMove();
		break;
	default:
		break;
	}
}


//!移動関数
void Player::Move()
{
	player_info.m_is_turnend = false;
	
	//!プレイヤーが移動していない間
	if (player_info.m_is_movement == false)
	{
		//!カメラが向いている方向に方向ベクトルを合わせる
		player_info.m_nor_speed.x = m_camera->GetObjInfo()->m_forward.x / Calculation::Length(m_camera->GetObjInfo()->m_forward.x, m_camera->GetObjInfo()->m_forward.z);
		player_info.m_nor_speed.z = m_camera->GetObjInfo()->m_forward.z / Calculation::Length(m_camera->GetObjInfo()->m_forward.x, m_camera->GetObjInfo()->m_forward.z);
	}

	//!プレイヤーが移動している間
	if (player_info.m_is_movement == true)
	{
		player_info.m_timer += 0.001f;

		player_info.m_speed = player_info.m_setspeed + player_info.m_acceleration * player_info.m_timer;

		//player_info.m_timer++;
		////!
		//if (player_info.m_timer == 10)
		//{
		//	player_info.speed *= exp((-player_info.fa) * player_info.m_timer / player_info.m_m);//時間tにおける速度
		//	player_info.m_timer = 0;
		//}

		//!移動スピードが0に等しくなった場合
		if (player_info.m_speed <= 0.01f)
		{
			player_info.m_speed = 0.0f;  //!移動スピードを0に
			player_info.m_is_turnend = true;  //!ターン終了
			player_info.m_is_movement = false;  //!移動終了
			player_info.m_timer = 0;
			player_info.m_truncounter++; //!ターン数加算
		}
	}

	//!1フレーム前の座標保存
	player_info.m_old_pos = player_info.m_pos;

	//!方向ベクトル正規化
	D3DXVec3Normalize(&player_info.m_nor_speed, &player_info.m_nor_speed);

	//!プレイヤー座標に移動スピード加算
	player_info.m_pos.x += player_info.m_nor_speed.x * player_info.m_speed;
	player_info.m_pos.z += player_info.m_nor_speed.z * player_info.m_speed;

	//!ワールド座標更新
	player_info.m_mat_world = Calculation::Matrix(player_info.m_pos, player_info.m_scale, player_info.m_angle);
}

//!当たり判定関数
void Player::HitController()
{
	HitRectBlock(); //!矩形型ブロック当たり判定関数
	
	HitCircleBlock(); //!円形型ブロック当たり判定関数

	HitReset(); //!リセットデバフ床との当たり判定
	HitStop();	//!ストップデバフ床との当たり判定
	HitGoal();	//!ゴール床との当たり判定

	//!反射が5回以上の行われるたびにスコアを減らす
	if (player_info.m_reflectcounter >= 5)
	{
		Score::Instance()->AddGameScore(-5);
		player_info.m_reflectcounter = 0;
	}
}

//!矩形型ブロック当たり判定関数
void Player::HitRectBlock()
{
	for (const auto& itr : *m_block->GetRectShape())
	{
		//!矩形型ブロックの上下との当たり判定
		if (Collision::RectTopToCircle(itr->GetBoxPos(), player_info.m_pos, itr->GetWidth(), itr->GetHeight(), player_info.m_radius, itr->GetRote()) == true)
		{
			player_info.m_pos = player_info.m_old_pos;
			//!エフェクト再生
			HitEffectStart(itr->GetBoxPos());
			//!反射
			player_info.m_nor_speed = RectReflection("Top", itr->GetRote());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.m_reflectcounter++;
		}
		//!矩形型ブロックの左右との当たり判定
		else if (Collision::RectLeftToCircle(itr->GetBoxPos(), player_info.m_pos, itr->GetWidth(), itr->GetHeight(), player_info.m_radius, itr->GetRote()) == true)
		{
			player_info.m_pos = player_info.m_old_pos;
			//!エフェクト再生
			HitEffectStart(itr->GetBoxPos());
			//!反射
			player_info.m_nor_speed = RectReflection("Left", itr->GetRote());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.m_reflectcounter++;
		}
		//!矩形型ブロックの左上との当たり判定
		else if (Collision::RectVertexToCircle("LeftTop", itr->GetBoxPos(), player_info.m_pos, itr->GetWidth(), itr->GetHeight(), player_info.m_radius, itr->GetRote()) == true)
		{
			player_info.m_pos = player_info.m_old_pos;
			//!エフェクト再生
			HitEffectStart(itr->GetBoxPos());
			//!反射
			player_info.m_nor_speed = VertexReflection("LeftTop", itr->GetBoxPos(), itr->GetWidth(), itr->GetHeight(), itr->GetRote());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.m_reflectcounter++;
		}
		//!矩形型ブロックの左下との当たり判定
		else if (Collision::RectVertexToCircle("LeftDown", itr->GetBoxPos(), player_info.m_pos, itr->GetWidth(), itr->GetHeight(), player_info.m_radius, itr->GetRote()) == true)
		{
			player_info.m_pos = player_info.m_old_pos;
			//!エフェクト再生
			HitEffectStart(itr->GetBoxPos());
			//!反射
			player_info.m_nor_speed = VertexReflection("LeftDown", itr->GetBoxPos(), itr->GetWidth(), itr->GetHeight(), itr->GetRote());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.m_reflectcounter++;
		}
		//!矩形型ブロックの右上との当たり判定
		else if (Collision::RectVertexToCircle("RightTop", itr->GetBoxPos(), player_info.m_pos, itr->GetWidth(), itr->GetHeight(), player_info.m_radius, itr->GetRote()) == true)
		{
			player_info.m_pos = player_info.m_old_pos;
			//!エフェクト再生
			HitEffectStart(itr->GetBoxPos());
			//!反射
			player_info.m_nor_speed = VertexReflection("RightTop", itr->GetBoxPos(), itr->GetWidth(), itr->GetHeight(), itr->GetRote());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.m_reflectcounter++;
		}
		//!矩形型ブロックの右下との当たり判定
		else if (Collision::RectVertexToCircle("RightDown", itr->GetBoxPos(), player_info.m_pos, itr->GetWidth(), itr->GetHeight(), player_info.m_radius, itr->GetRote()) == true)
		{
			//!エフェクト再生
			HitEffectStart(itr->GetBoxPos());
			//!反射
			player_info.m_nor_speed = VertexReflection("RightDown", itr->GetBoxPos(), itr->GetWidth(), itr->GetHeight(), itr->GetRote());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.m_reflectcounter++;
		}
	}
}

//!円形型ブロック当たり判定関数
void Player::HitCircleBlock()
{
	for (const auto& itr : *m_block->GetCircleShape())
	{
		if (Collision::CircleToCircle(player_info.m_pos, itr->GetCirclePos(), player_info.m_radius, itr->GetRadius()) == true)
		{
			player_info.m_pos = player_info.m_old_pos;
			//!エフェクト再生
			HitEffectStart(itr->GetCirclePos());
			//!反射
			player_info.m_nor_speed = CircleReflection(itr->GetCirclePos());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.m_reflectcounter++;
		}
	}
	

}

//!リセットデバフ当たり判定関数
void Player::HitReset()
{
	for (const auto& itr : *m_debuf->GetResetShape())
	{
		if (Collision::CircleToCircle(player_info.m_pos, itr->GetCirclePos(), player_info.m_radius, itr->GetRadius()) == true)
		{
			//!エフェクト再生
			ResetEffectStart();

			//!座標を初期位置に戻す
			//player_info.pos = D3DXVECTOR3(-29.0f, -29.0f, -29.0f);
			player_info.m_pos = D3DXVECTOR3(0.0f, -29.0f, -70.0f);

			//!移動スピードを0に
			player_info.m_setspeed = 0.0f;

			//!サウンド再生
			SoundManager::Instance()->SoundFallSE();
		}
	}
}

//!停止デバフ当たり判定関数
void Player::HitStop()
{
	for (const auto& itr : *m_debuf->GetStopShape())
	{
		//!矩形のため上下左右の当たり判定を取る
		if (Collision::RectLeftToCircle(itr->GetBoxPos(), player_info.m_pos, itr->GetWidth(), itr->GetHeight(), player_info.m_radius, itr->GetRote()) == true
			|| Collision::RectTopToCircle(itr->GetBoxPos(), player_info.m_pos, itr->GetWidth(), itr->GetHeight(), player_info.m_radius, itr->GetRote()) == true)
		{
			//!摩擦係数を増やす
			player_info.m_friction = 1.0f;
		}
		else
		{
			player_info.m_friction = 0.4f;
		}
	}

	player_info.m_acceleration = -player_info.m_friction * 9.8f; //!摩擦係数
}

//!ゴール当たり判定関数
void Player::HitGoal()
{
	//!ターン終了時に当たっているかどうかを判定
	if (player_info.m_is_turnend == true)
	{
		//!スコアを更新
		Score::Instance()->AddGameScore(player_info.m_score_counter);

		//!赤の円に当たっていた場合
		if (Collision::CircleToCircle(player_info.m_pos, m_goal->GetObjInfo()->m_pos, 1, 1) == true)
		{
			//!エフェクト再生
			GoalEffectStart();

			//!スコアを減算するため-
			player_info.m_score_counter = -3;
			//!スコアを更新
			Score::Instance()->AddGameScore(player_info.m_score_counter);
			player_info.m_is_goal = true;

			//!更新ステップを終了演出へ
			m_update_step = PlayerUpdateStep::EndProduction;
		}
		//!黄の円に当たっていた場合
		else if (Collision::CircleToCircle(player_info.m_pos, m_goal->GetObjInfo()->m_pos, 1, 3) == true)
		{
			//!エフェクト再生
			GoalEffectStart();
			//!スコアを減算するため-
			player_info.m_score_counter = -2;
			//!スコアを更新
			Score::Instance()->AddGameScore(player_info.m_score_counter);
			player_info.m_is_goal = true;
			//!更新ステップを終了演出へ
			m_update_step = PlayerUpdateStep::EndProduction;
		}
		//!緑の円に当たっていた場合
		else if (Collision::CircleToCircle(player_info.m_pos, m_goal->GetObjInfo()->m_pos, 1, 7) == true)
		{
			//!エフェクト再生
			GoalEffectStart();
			//!スコアを減算するため-
			player_info.m_score_counter = -1;
			//!スコアを更新
			Score::Instance()->AddGameScore(player_info.m_score_counter);
			player_info.m_is_goal = true;
			//!更新ステップを終了演出へ
			m_update_step = PlayerUpdateStep::EndProduction;
		}

		if (player_info.m_truncounter >= GAME_TRUN)
		{
			player_info.m_is_goal = true;
			//!更新ステップを終了演出へ
			m_update_step = PlayerUpdateStep::EndProduction;
		}

		
	}
}

//!矩形型ブロック反射方向計算関数
D3DXVECTOR3 Player::RectReflection(std::string type_,float rad_)
{
	D3DXVECTOR3 old_direction = player_info.m_nor_speed;
	float m_change_radian;

	/*
		矩形の上下にあたったら方向ベクトルのy軸(z)を反転
		矩形の左右にあたったら方向ベクトルのx軸を反転
	*/
	if (type_ == "Top")
	{
		old_direction.z = -old_direction.z;
	}
	else if (type_ == "Left")
	{
		old_direction.x = -old_direction.x;
	}

	//!3Dと2Dで回転する方向が逆のため逆に回転させる
	m_change_radian = -rad_;
	m_change_radian *= 2;

	//!方向ベクトルを回転
	return Calculation::Rote(old_direction, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_change_radian);
}

//!円形型ブロック反射方向計算関数
D3DXVECTOR3 Player::CircleReflection(D3DXVECTOR3 circle_pos_)
{
	//!値初期化
	D3DXVECTOR3 old_direction = player_info.m_nor_speed;

	//!方向ベクトルを反転
	old_direction.x = -old_direction.x;
	old_direction.z = -old_direction.z;

	//!プレイヤーと円の接線に垂直なベクトル
	D3DXVECTOR3 vec = player_info.m_pos - circle_pos_;

	//!Playerの進む方向ベクトルと
	//!Playerと円のベクトルのatanを求める
	float direction_rad = atan2f(old_direction.z, old_direction.x);
	float vec_rad = atan2f(vec.z, vec.x);

	//!方向ベクトルと接線に垂直なベクトルのなす角を求める
	float degree2 = 0;
	degree2 = D3DXToDegree(Calculation::EggplantAngle(old_direction, vec));

	//!atan()が0～180、0～-180の範囲でしか値が出せないため、どちらかのベクトルが負の場合360度足して比較する値を直す
	if (direction_rad > 0 && vec_rad < 0 &&
		D3DXToDegree(direction_rad) > 90 && D3DXToDegree(vec_rad) < -90)
	{
		vec_rad = D3DXToRadian(360) + vec_rad;
	}
	else if (vec_rad > 0 && direction_rad < 0 &&
		D3DXToDegree(vec_rad) > 90 && D3DXToDegree(direction_rad) < -90)
	{
		direction_rad = D3DXToRadian(360) + direction_rad;
	}

	/*
		方向ベクトルとプレイヤーと円の接線に垂直なベクトルの角度を比較し
		方向ベクトルを回転させる方向を決める(右回転か左回転か)
	*/
	if (direction_rad > vec_rad)
	{
		degree2 = -degree2;
	}

	//方向ベクトルを回転回転
	return Calculation::Rote(old_direction, D3DXVECTOR3(0.0f, 0.0f, 0.0f), degree2 * 2);
}

//!矩形型ブロック頂点反射方向計算関数
D3DXVECTOR3 Player::VertexReflection(std::string type_, D3DXVECTOR3 r_pos_, float width_, float height_, float rad_)
{
	//!値初期化
	D3DXVECTOR3 old_direction = player_info.m_nor_speed;
	D3DXVECTOR3 vec;

	D3DXVECTOR3 player_lotepos = Calculation::Rote(player_info.m_pos, r_pos_, rad_);
	D3DXVECTOR3 ver_pos;

	//!方向ベクトルを反転
	old_direction.x = -old_direction.x;
	old_direction.z = -old_direction.z;

	//!左上
	if (type_ == "LeftTop")
	{
		ver_pos.x = r_pos_.x - (width_ / 2);
		ver_pos.z = r_pos_.z + (height_ / 2);
	}
	//!左下
	else if (type_ == "LeftDown")
	{
		ver_pos.x = r_pos_.x - (width_ / 2);
		ver_pos.z = r_pos_.z - (height_ / 2);
	}
	//!右上
	else if (type_ == "RightTop")
	{
		ver_pos.x = r_pos_.x + (width_ / 2);
		ver_pos.z = r_pos_.z + (height_ / 2);
	}
	//!右下
	else if (type_ == "RightDown")
	{
		ver_pos.x = r_pos_.x + (width_ / 2);
		ver_pos.z = r_pos_.z - (height_ / 2);
	}
	//!Playerと頂点のベクトル
	D3DXVECTOR3 old_vec = player_lotepos - ver_pos;

	//!矩形が回転していたらベクトルも回転させる
	vec = Calculation::Rote(old_vec, D3DXVECTOR3(0.0f, 0.0f, 0.0f), -rad_);

	float direction_rad = atan2f(old_direction.z, old_direction.x);
	float vec_rad = atan2f(vec.z, vec.x);

	//!方向ベクトルと接線に垂直なベクトルのなす角を求める
	float degree2 = 0;
	degree2 = D3DXToDegree(Calculation::EggplantAngle(old_direction, vec));

	//!atan()が0～180、0～-180の範囲でしか値が出せないため、どちらかのベクトルが負の場合360度足して比較する値を直す
	if (direction_rad > 0 && vec_rad < 0 &&
		D3DXToDegree(direction_rad) > 90 && D3DXToDegree(vec_rad) < -90)
	{
		vec_rad = D3DXToRadian(360) + vec_rad;
	}
	else if (vec_rad > 0 && direction_rad < 0 &&
		D3DXToDegree(vec_rad) > 90 && D3DXToDegree(direction_rad) < -90)
	{
		direction_rad = D3DXToRadian(360) + direction_rad;
	}

	/*
		方向ベクトルとプレイヤーと円の接線に垂直なベクトルの角度を比較し
		方向ベクトルを回転させる方向を決める(右回転か左回転か)
	*/
	if (direction_rad > vec_rad)
	{
		degree2 = -degree2;
	}

	//!方向ベクトルを回転
	return Calculation::Rote(old_direction, D3DXVECTOR3(0.0f, 0.0f, 0.0f), degree2 * 2);
}

//!初期位置移動関数
void Player::ResetPos()
{
	//!ステージから落ちた場合
	if (player_info.m_pos.x <= m_floor->GetObjInfo()->m_pos.x - m_floor->GetObjInfo()->m_width
		|| player_info.m_pos.x >= m_floor->GetObjInfo()->m_pos.x + m_floor->GetObjInfo()->m_width
		|| player_info.m_pos.z <= m_floor->GetObjInfo()->m_pos.z - m_floor->GetObjInfo()->m_height
		|| player_info.m_pos.z >= m_floor->GetObjInfo()->m_pos.z + m_floor->GetObjInfo()->m_height)
	{

		ResetEffectStart();
		player_info.m_pos = D3DXVECTOR3(m_player_info_copy.pos[ARRAY_DATA::X], -29.0f, m_player_info_copy.pos[ARRAY_DATA::Z]); //!座標
		player_info.m_setspeed = 0.0f;

		FallEffectStart();
		SoundManager::Instance()->SoundFallSE();
	}
}


//!開始演出関数
void Player::StartMove()
{
	//!プレイヤーが上からステージ床に当たるまで
	if (player_info.m_pos.y > -29.0f
		&& player_info.m_is_goal == false)
	{
		player_info.m_pos.y -= player_info.m_speed;

		player_info.m_mat_world = Calculation::Matrix(player_info.m_pos, player_info.m_scale, player_info.m_angle);
	}
	//!床に着いた場合
	else
	{
		//!座標を正確な位置に戻す
		player_info.m_pos.y = -29.0f;
		player_info.m_speed = 0.0f;
		player_info.m_timer = 0;
		//!更新ステップをゲーム本編へ
		m_update_step = PlayerUpdateStep::GameMain;
	}
}

//!終了演出関数
void Player::EndMove()
{
	//!プレイヤーが上に上がっていく形にするためY座標を+
	player_info.m_pos.y += 0.1f;

	//!ワールド座標更新
	player_info.m_mat_world = Calculation::Matrix(player_info.m_pos, player_info.m_scale, player_info.m_angle);
}

//!衝突時エフェクト開始関数
void Player::HitEffectStart(D3DXVECTOR3 block_pos_)
{
	D3DXVECTOR3 block_vec = block_pos_ - player_info.m_pos;

	D3DXVec3Normalize(&block_vec, &block_vec);

	player_info.m_efk_pos = block_vec * 1.3f + player_info.m_pos;

	Effect::Instance()->PlayEffect(EffectType::HitEfc, player_info.m_efk_pos.x, -29.0f, player_info.m_efk_pos.z);
}

//!落下時エフェクト開始関数
void Player::FallEffectStart()
{
	player_info.m_efk_pos = player_info.m_pos;

	Effect::Instance()->PlayEffect(EffectType::FallEfc, player_info.m_efk_pos.x, -29.0f, player_info.m_efk_pos.z);
}

//!リセット時エフェクト開始関数
void Player::ResetEffectStart()
{
	player_info.m_efk_pos = player_info.m_pos;

	Effect::Instance()->PlayEffect(EffectType::ResetEfc, player_info.m_efk_pos.x, -29.0f, player_info.m_efk_pos.z);
}

//!ゲーム終了時エフェクト開始関数
void Player::GoalEffectStart()
{
	player_info.m_efk_pos = player_info.m_pos;

	Effect::Instance()->PlayEffect(EffectType::GoalEfc, player_info.m_efk_pos.x, player_info.m_efk_pos.y + 4.0f, player_info.m_efk_pos.z);
	Effect::Instance()->PlayEffect(EffectType::GoalEfc, player_info.m_efk_pos.x, player_info.m_efk_pos.y + 10.0f, player_info.m_efk_pos.z);
}



