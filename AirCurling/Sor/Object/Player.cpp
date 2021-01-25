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
void Player::Init(std::string stage_id_)
{
	FILE* fp = NULL;

	std::string stage_id = "Res/ObjectData/" + stage_id_ + "PlayerData.dat";

	//!ファイル読み込み
	fopen_s(&fp, stage_id.c_str(), "rb");

	if (fp != nullptr)
	{
		//!書き込む
		fread(&player_info_copy, sizeof(ObjectInfoCopy), 1, fp);

		/* ファイルクローズ */
		fclose(fp);
	}

	player_info.key = "pac";  //!描画用キー
	//player_info.pos = D3DXVECTOR3(-29.0f, 0.0f, -29.0f); //!座標

	player_info.pos = D3DXVECTOR3(player_info_copy.pos_x, player_info_copy.pos_y, player_info_copy.pos_z); //!座標
	player_info.scale = D3DXVECTOR3(player_info_copy.scale_x, player_info_copy.scale_y, player_info_copy.scale_z);	 //!描画サイズ

	player_info.mat_world = Calculation::Matrix(player_info.pos, player_info.scale, player_info.angle);  //!ワールド座標

	player_info.m = player_info_copy.m;     //!質量
	player_info.fa = player_info_copy.fa;   //!摩擦係数
	player_info.a = -player_info.fa * 9.8f; //!摩擦係数


	player_info.radius = player_info_copy.radius; //!半径
	player_info.speed = player_info_copy.speed;   //!移動スピード

	player_info.timer = 0;  
	player_info.truncounter = 0;    //!進行ターン数
	player_info.reflectcounter = 0; //!反射回数
	player_info.turnend = false;    //!1ターン終了フラグ
	player_info.goal = false;       //!ゴールフラグ
	player_info.end = false;        //!ゲームエンドフラグ
	player_info.score_counter = player_info_copy.score_counter;

	player_info.m_move = false;

	player_info.nor_speed.y = 0.0f;
}

//!描画情報送信関数
void Player::SetUpBuffer()
{
	FbxController::Instance()->DrawFbx(player_info.key, player_info.mat_world);
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

		Hit();   //!当たり判定

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
	player_info.turnend = false;
	
	//!プレイヤーが移動していない間
	if (player_info.m_move == false)
	{
		//!カメラが向いている方向に方向ベクトルを合わせる
		player_info.nor_speed.x = m_camera->GetObjInfo()->m_forward.x / Calculation::Length(m_camera->GetObjInfo()->m_forward.x, m_camera->GetObjInfo()->m_forward.z);
		player_info.nor_speed.z = m_camera->GetObjInfo()->m_forward.z / Calculation::Length(m_camera->GetObjInfo()->m_forward.x, m_camera->GetObjInfo()->m_forward.z);
	}

	//!プレイヤーが移動している間
	if (player_info.m_move == true)
	{
		player_info.timer += 0.001f;

		player_info.speed = player_info.speed2 + player_info.a * player_info.timer;

		//player_info.timer++;
		////!
		//if (player_info.timer == 10)
		//{
		//	player_info.speed *= exp((-player_info.fa) * player_info.timer / player_info.m);//時間tにおける速度
		//	player_info.timer = 0;
		//}

		//!移動スピードが0に等しくなった場合
		if (player_info.speed <= 0.01f)
		{
			player_info.speed = 0.0f;  //!移動スピードを0に
			player_info.turnend = true;  //!ターン終了
			player_info.m_move = false;  //!移動終了
			player_info.timer = 0;
			player_info.truncounter++; //!ターン数加算
		}
	}

	//!1フレーム前の座標保存
	player_info.old_pos = player_info.pos;

	//!方向ベクトル正規化
	D3DXVec3Normalize(&player_info.nor_speed, &player_info.nor_speed);

	//!プレイヤー座標に移動スピード加算
	player_info.pos.x += player_info.nor_speed.x * player_info.speed;
	player_info.pos.z += player_info.nor_speed.z * player_info.speed;

	//!ワールド座標更新
	player_info.mat_world = Calculation::Matrix(player_info.pos, player_info.scale, player_info.angle);
}

//!当たり判定関数
void Player::Hit()
{
	HitRectBlock(); //!矩形型ブロック当たり判定関数
	
	HitCircleBlock(); //!円形型ブロック当たり判定関数

	HitReset(); //!リセットデバフ床との当たり判定
	HitStop();	//!ストップデバフ床との当たり判定
	HitGoal();	//!ゴール床との当たり判定

	//!反射が5回以上の行われるたびにスコアを減らす
	if (player_info.reflectcounter >= 5)
	{
		Score::Instance()->AddGameScore(-5);
		player_info.reflectcounter = 0;
	}
}

//!矩形型ブロック当たり判定関数
void Player::HitRectBlock()
{
	for (const auto& itr : *m_block->GetRectShape())
	{
		//!矩形型ブロックの上下との当たり判定
		if (Collision::RectTopToCircle(itr->GetBoxPos(), player_info.pos, itr->GetWidth(), itr->GetHeight(), player_info.radius, itr->GetRote()) == true)
		{
			player_info.pos = player_info.old_pos;
			//!エフェクト再生
			HitEffectStart(itr->GetBoxPos());
			//!反射
			player_info.nor_speed = RectReflection("Top", itr->GetRote());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.reflectcounter++;
		}
		//!矩形型ブロックの左右との当たり判定
		else if (Collision::RectLeftToCircle(itr->GetBoxPos(), player_info.pos, itr->GetWidth(), itr->GetHeight(), player_info.radius, itr->GetRote()) == true)
		{
			player_info.pos = player_info.old_pos;
			//!エフェクト再生
			HitEffectStart(itr->GetBoxPos());
			//!反射
			player_info.nor_speed = RectReflection("Left", itr->GetRote());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.reflectcounter++;
		}
		//!矩形型ブロックの左上との当たり判定
		else if (Collision::RectVertexToCircle("LeftTop", itr->GetBoxPos(), player_info.pos, itr->GetWidth(), itr->GetHeight(), player_info.radius, itr->GetRote()) == true)
		{
			player_info.pos = player_info.old_pos;
			//!エフェクト再生
			HitEffectStart(itr->GetBoxPos());
			//!反射
			player_info.nor_speed = VertexReflection("LeftTop", itr->GetBoxPos(), itr->GetWidth(), itr->GetHeight(), itr->GetRote());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.reflectcounter++;
		}
		//!矩形型ブロックの左下との当たり判定
		else if (Collision::RectVertexToCircle("LeftDown", itr->GetBoxPos(), player_info.pos, itr->GetWidth(), itr->GetHeight(), player_info.radius, itr->GetRote()) == true)
		{
			player_info.pos = player_info.old_pos;
			//!エフェクト再生
			HitEffectStart(itr->GetBoxPos());
			//!反射
			player_info.nor_speed = VertexReflection("LeftDown", itr->GetBoxPos(), itr->GetWidth(), itr->GetHeight(), itr->GetRote());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.reflectcounter++;
		}
		//!矩形型ブロックの右上との当たり判定
		else if (Collision::RectVertexToCircle("RightTop", itr->GetBoxPos(), player_info.pos, itr->GetWidth(), itr->GetHeight(), player_info.radius, itr->GetRote()) == true)
		{
			player_info.pos = player_info.old_pos;
			//!エフェクト再生
			HitEffectStart(itr->GetBoxPos());
			//!反射
			player_info.nor_speed = VertexReflection("RightTop", itr->GetBoxPos(), itr->GetWidth(), itr->GetHeight(), itr->GetRote());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.reflectcounter++;
		}
		//!矩形型ブロックの右下との当たり判定
		else if (Collision::RectVertexToCircle("RightDown", itr->GetBoxPos(), player_info.pos, itr->GetWidth(), itr->GetHeight(), player_info.radius, itr->GetRote()) == true)
		{
			//!エフェクト再生
			HitEffectStart(itr->GetBoxPos());
			//!反射
			player_info.nor_speed = VertexReflection("RightDown", itr->GetBoxPos(), itr->GetWidth(), itr->GetHeight(), itr->GetRote());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.reflectcounter++;
		}
	}
}

//!円形型ブロック当たり判定関数
void Player::HitCircleBlock()
{
	for (const auto& itr : *m_block->GetCircleShape())
	{
		if (Collision::CircleToCircle(player_info.pos, itr->GetCirclePos(), player_info.radius, itr->GetRadius()) == true)
		{
			player_info.pos = player_info.old_pos;
			//!エフェクト再生
			HitEffectStart(itr->GetCirclePos());
			//!反射
			player_info.nor_speed = CircleReflection(itr->GetCirclePos());
			//!サウンド再生
			SoundManager::Instance()->SoundReflectSE();
			//!反射回数加算
			player_info.reflectcounter++;
		}
	}
	

}

//!リセットデバフ当たり判定関数
void Player::HitReset()
{
	for (const auto& itr : *m_debuf->GetResetShape())
	{
		if (Collision::CircleToCircle(player_info.pos, itr->GetCirclePos(), player_info.radius, itr->GetRadius()) == true)
		{
			//!エフェクト再生
			ResetEffectStart();

			//!座標を初期位置に戻す
			//player_info.pos = D3DXVECTOR3(-29.0f, -29.0f, -29.0f);
			player_info.pos = D3DXVECTOR3(0.0f, -29.0f, -70.0f);

			//!移動スピードを0に
			player_info.speed = 0.0f;

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
		if (Collision::RectLeftToCircle(itr->GetBoxPos(), player_info.pos, itr->GetWidth(), itr->GetHeight(), player_info.radius, itr->GetRote()) == true
			|| Collision::RectTopToCircle(itr->GetBoxPos(), player_info.pos, itr->GetWidth(), itr->GetHeight(), player_info.radius, itr->GetRote()) == true)
		{
			//!摩擦係数を増やす
			player_info.fa = 1.0f;
		}
		else
		{
			player_info.fa = 0.4f;
		}
	}
}

//!ゴール当たり判定関数
void Player::HitGoal()
{
	//!ターン終了時に当たっているかどうかを判定
	if (player_info.turnend == true)
	{
		//!スコアを更新
		Score::Instance()->AddGameScore(player_info.score_counter);

		//!赤の円に当たっていた場合
		if (Collision::CircleToCircle(player_info.pos, m_goal->GetObjInfo()->pos, 1, 1) == true)
		{
			//!エフェクト再生
			GoalEffectStart();

			//!スコアを減算するため-
			player_info.score_counter = -3;
			//!スコアを更新
			Score::Instance()->AddGameScore(player_info.score_counter);
			player_info.goal = true;

			//!更新ステップを終了演出へ
			m_update_step = PlayerUpdateStep::EndProduction;
		}
		//!黄の円に当たっていた場合
		else if (Collision::CircleToCircle(player_info.pos, m_goal->GetObjInfo()->pos, 1, 3) == true)
		{
			//!エフェクト再生
			GoalEffectStart();
			//!スコアを減算するため-
			player_info.score_counter = -2;
			//!スコアを更新
			Score::Instance()->AddGameScore(player_info.score_counter);
			player_info.goal = true;
			//!更新ステップを終了演出へ
			m_update_step = PlayerUpdateStep::EndProduction;
		}
		//!緑の円に当たっていた場合
		else if (Collision::CircleToCircle(player_info.pos, m_goal->GetObjInfo()->pos, 1, 7) == true)
		{
			//!エフェクト再生
			GoalEffectStart();
			//!スコアを減算するため-
			player_info.score_counter = -1;
			//!スコアを更新
			Score::Instance()->AddGameScore(player_info.score_counter);
			player_info.goal = true;
			//!更新ステップを終了演出へ
			m_update_step = PlayerUpdateStep::EndProduction;
		}

		if (player_info.truncounter >= 9)
		{
			player_info.goal = true;
			//!更新ステップを終了演出へ
			m_update_step = PlayerUpdateStep::EndProduction;
		}

		
	}
}

//!矩形型ブロック反射方向計算関数
D3DXVECTOR3 Player::RectReflection(std::string type_,float rad_)
{
	D3DXVECTOR3 old_direction = player_info.nor_speed;
	float change_radian;

	/*
		矩形の上下にあたったら方向ベクトルのy軸(z)を反転
		矩形の左右にあたったら方向ベクトルのx軸を反転
	*/
	if (type_ == "Top")
	{
		old_direction.z *= -1.0f;
	}
	else if (type_ == "Left")
	{
		old_direction.x *= -1.0f;
	}

	//3Dと2Dで回転する方向が逆のため逆に回転させる
	change_radian = -rad_;
	change_radian *= 2;

	//方向ベクトルを回転
	return Calculation::Rote(old_direction, D3DXVECTOR3(0.0f, 0.0f, 0.0f), change_radian);
}

//!円形型ブロック反射方向計算関数
D3DXVECTOR3 Player::CircleReflection(D3DXVECTOR3 circle_pos_)
{
	//値初期化
	D3DXVECTOR3 old_direction = player_info.nor_speed;

	//方向ベクトルを反転
	old_direction.x *= -1.0f;
	old_direction.z *= -1.0f;

	//プエイヤーと円の接線に垂直なベクトル
	D3DXVECTOR3 vec = player_info.pos - circle_pos_;

	//Playerの進む方向ベクトルと
	//Playerと円のベクトルのatanを求める
	float direction_rad = atan2f(old_direction.z, old_direction.x);
	float vec_rad = atan2f(vec.z, vec.x);

	//方向ベクトルと接線に垂直なベクトルのなす角を求める
	float degree2 = 0;
	degree2 = D3DXToDegree(Calculation::EggplantAngle(old_direction, vec));

	if (direction_rad > 0 && vec_rad < 0 &&
		D3DXToDegree(direction_rad) > 90 && D3DXToDegree(vec_rad) < -90)
	{
		vec_rad = 6.28319f + vec_rad;
	}
	else if (vec_rad > 0 && direction_rad < 0 &&
		D3DXToDegree(vec_rad) > 90 && D3DXToDegree(direction_rad) < -90)
	{
		direction_rad = 6.28319f + direction_rad;
	}

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
	//値初期化
	D3DXVECTOR3 old_direction = player_info.nor_speed;
	D3DXVECTOR3 vec;

	D3DXVECTOR3 player_lotepos = Calculation::Rote(player_info.pos, r_pos_, rad_);
	D3DXVECTOR3 ver_pos;

	//方向ベクトルを反転
	old_direction.x *= -1.0f;
	old_direction.z *= -1.0f;

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
	// Playerと頂点のベクトル
	D3DXVECTOR3 old_vec = player_lotepos - ver_pos;

	// 矩形が回転していたらベクトルも回転させる
	vec = Calculation::Rote(old_vec, D3DXVECTOR3(0.0f, 0.0f, 0.0f), -rad_);

	float direction_rad = atan2f(old_direction.z, old_direction.x);
	float vec_rad = atan2f(vec.z, vec.x);

	//方向ベクトルと接線に垂直なベクトルのなす角を求める
	float degree2 = 0;
	degree2 = D3DXToDegree(Calculation::EggplantAngle(old_direction, vec));

	//!
	if (direction_rad > 0 && vec_rad < 0 &&
		D3DXToDegree(direction_rad) > 90 && D3DXToDegree(vec_rad) < -90)
	{
		vec_rad = 6.28319f + vec_rad;
	}
	//!
	else if (vec_rad > 0 && direction_rad < 0 &&
		D3DXToDegree(vec_rad) > 90 && D3DXToDegree(direction_rad) < -90)
	{
		direction_rad = 6.28319f + direction_rad;
	}

	if (direction_rad > vec_rad)
	{
		degree2 = -degree2;
	}

	//方向ベクトルを回転
	return Calculation::Rote(old_direction, D3DXVECTOR3(0.0f, 0.0f, 0.0f), degree2 * 2);
}

//!初期位置移動関数
void Player::ResetPos()
{
	if (Inputter::Instance()->GetKeyDown(Inputter::A_KEY))
	{
		ResetEffectStart();
		//player_info.pos = D3DXVECTOR3(-29.0f, -29.0f, -29.0f);
		player_info.pos = D3DXVECTOR3(0.0f, -29.0f, -70.0f);
		player_info.speed = 0.0f;
	}
	if (player_info.pos.x <= m_floor->GetObjInfo()->pos.x - m_floor->GetObjInfo()->width
		|| player_info.pos.x >= m_floor->GetObjInfo()->pos.x + m_floor->GetObjInfo()->width
		|| player_info.pos.z <= m_floor->GetObjInfo()->pos.z - m_floor->GetObjInfo()->height
		|| player_info.pos.z >= m_floor->GetObjInfo()->pos.z + m_floor->GetObjInfo()->height)
	{

		ResetEffectStart();
		player_info.pos = D3DXVECTOR3(player_info_copy.pos_x, -29.0f, player_info_copy.pos_z); //!座標
		player_info.speed = 0.0f;

		FallEffectStart();
		SoundManager::Instance()->SoundFallSE();
	}
}


//!開始演出関数
void Player::StartMove()
{
	//!プレイヤーが上からステージ床に当たるまで
	if (player_info.pos.y > -29.0f
		&& player_info.goal == false)
	{
		//!摩擦によるスピード減算を利用
		player_info.timer++;

		if (player_info.timer == 10)
		{
			player_info.speed *= exp((-player_info.fa) * player_info.timer / player_info.m);//時間tにおける速度
			player_info.timer = 0;
		}
		player_info.pos.y -= player_info.speed;

		player_info.mat_world = Calculation::Matrix(player_info.pos, player_info.scale, player_info.angle);
	}
	//!床に着いた場合
	else
	{
		//!座標を正確な位置に戻す
		player_info.pos.y = -29.0f;
		player_info.speed = 0.0f;
		player_info.timer = 0;
		//!更新ステップをゲーム本編へ
		m_update_step = PlayerUpdateStep::GameMain;
	}
}

//!終了演出関数
void Player::EndMove()
{
	//!プレイヤーが上に上がっていく形にするためY座標を+
	player_info.pos.y += 0.1f;

	//!ワールド座標更新
	player_info.mat_world = Calculation::Matrix(player_info.pos, player_info.scale, player_info.angle);
}

//!衝突時エフェクト開始関数
void Player::HitEffectStart(D3DXVECTOR3 block_pos_)
{
	D3DXVECTOR3 block_vec = block_pos_ - player_info.pos;

	D3DXVec3Normalize(&block_vec, &block_vec);

	player_info.efk_pos = block_vec * 1.3f + player_info.pos;

	Effect::Instance()->PlayEffect(EffectType::HitEfc, player_info.efk_pos.x, -29.0f, player_info.efk_pos.z);
}

//!落下時エフェクト開始関数
void Player::FallEffectStart()
{
	player_info.efk_pos = player_info.pos;

	Effect::Instance()->PlayEffect(EffectType::FallEfc, player_info.efk_pos.x, -29.0f, player_info.efk_pos.z);
}

//!リセット時エフェクト開始関数
void Player::ResetEffectStart()
{
	player_info.efk_pos = player_info.pos;

	Effect::Instance()->PlayEffect(EffectType::ResetEfc, player_info.efk_pos.x, -29.0f, player_info.efk_pos.z);
}

//!ゲーム終了時エフェクト開始関数
void Player::GoalEffectStart()
{
	player_info.efk_pos = player_info.pos;

	Effect::Instance()->PlayEffect(EffectType::GoalEfc, player_info.efk_pos.x, player_info.efk_pos.y + 4.0f, player_info.efk_pos.z);
	Effect::Instance()->PlayEffect(EffectType::GoalEfc, player_info.efk_pos.x, player_info.efk_pos.y + 10.0f, player_info.efk_pos.z);
}



