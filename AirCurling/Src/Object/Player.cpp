#include "Player.h"
#include "../System/Effect.h"
#include "../Score/GameScore.h"
#include <time.h> 
#include "../Utility/Collision/ObjectCollision.h"

//コンストラクタ
Player::Player(Camera* camera_, BlockController* block_, 
	Floor* floor_, DebufController* debuf_, Goal* goal_) :
	mp_camera(camera_), mp_block(block_), mp_floor(floor_), mp_debuf(debuf_), mp_goal(goal_)
{
	m_update_step = PlayerUpdateStep::StartProduction;  //更新ステップを開始演出で初期化
}

//初期化関数
void Player::Init(std::string stage_str_)
{
	//外部データ読み込み
	LoadExternalInfo(stage_str_);

	player_info.m_key = "pac";  //描画用キー

	player_info.m_pos = m_player_externalinfo.m_pos; //座標
	player_info.m_scale =  m_player_externalinfo.m_scale; //描画サイズ

	player_info.m_mat_world = Calculation::Matrix(player_info.m_pos, player_info.m_scale, player_info.m_angle);  //ワールド座標
	
	player_info.m_friction = m_player_externalinfo.m_friction;   //動摩擦係数
	player_info.m_acceleration = -player_info.m_friction * Gravity; //加速度


	player_info.m_radius = m_player_externalinfo.m_radius;    //半径
	player_info.m_speed = m_player_externalinfo.m_speed;  //移動スピード

	player_info.m_timer = 0;  //経過時間
	player_info.m_trun_counter = 0;    //進行ターン数
	player_info.m_reflect_counter = 0; //反射回数

	player_info.m_is_turnend = false;   //1ターン終了フラグ
	player_info.m_is_start = false;     //ゲームスタートフラグ
	player_info.m_is_goal = false;      //ゴールフラグ
	player_info.m_is_end = false;       //ゲームエンドフラグ
	player_info.m_is_movement = false;  //プレイヤーが動いているかどうか

	player_info.m_score_counter = m_player_externalinfo.m_score_counter; //加算するスコア数

	player_info.m_nor_vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //方向ベクトル
}

//他オブジェクト情報取得関数
void Player::SetOtherObjeInfo()
{
}

//外部データ読み込み関数
void Player::LoadExternalInfo(std::string stage_str_)
{
	FILE* fp = nullptr;

	std::string file_name = "Res/ObjectData/" + stage_str_ + "PlayerData.dat";

	//ファイル読み込み
	fopen_s(&fp, file_name.c_str(), "rb");

	if (fp != nullptr)
	{
		//書き込む
		fread(&m_player_externalinfo, sizeof(PlayerExternalInfo), 1, fp);

		//ファイルクローズ
		fclose(fp);
	}
}

//描画情報送信関数
void Player::Draw()
{
	FbxController::Instance()->DrawFbx(player_info.m_key, player_info.m_mat_world);
}

//FBXモデル解放関数
void Player::ReleaseModel()
{
	FbxController::Instance()->ReleaseFbxMesh(player_info.m_key);
}

//更新関数
void Player::Update()
{
	switch (m_update_step)
	{
	case PlayerUpdateStep::StartProduction: //開始演出
		StartProduction();
		break;
	case PlayerUpdateStep::GameMain:  //ゲーム本編
		Move();  //移動

		ObjectCollision::Instance()->SetPlayerInfo(player_info);

		//プレイヤーが移動している間
		if (player_info.m_is_movement == true)
		{
			HitController();   //当たり判定

			ResetPos();   //ステージ外に出たかどうか
		}
	
		break;
	case PlayerUpdateStep::EndProduction:  //終了演出
		EndProduction();
		break;
	default:
		break;
	}
}


//移動関数
void Player::Move()
{
	Camera::CameraInfo camera_info;
	mp_camera->GetCameraInfo(camera_info);

	player_info.m_is_turnend = false;
	
	//プレイヤーが移動していない間
	if (player_info.m_is_movement == false && camera_info.m_is_shotmode == true)
	{

		//カメラが向いている方向に方向ベクトルを合わせる
		player_info.m_nor_vec.x = camera_info .m_forward.x / Calculation::Length(camera_info.m_forward.x, camera_info.m_forward.z);
		player_info.m_nor_vec.z = camera_info.m_forward.z / Calculation::Length(camera_info.m_forward.x, camera_info.m_forward.z);
	}

	//プレイヤーが移動している間
	if (player_info.m_is_movement == true)
	{
		player_info.m_timer += FrameTime;

		player_info.m_speed = player_info.m_setspeed_power + player_info.m_acceleration * player_info.m_timer;

		player_info.m_acceleration = -player_info.m_friction * Gravity; //摩擦係数

		//別の移動方法
		//player_info.m_timer++;
		////
		//if (player_info.m_timer == 10)
		//{
		//	player_info.m_speed *= exp((-player_info.m_friction) * player_info.m_timer / player_info.m_m);//時間tにおける速度
		//	player_info.m_timer = 0;
		//}

		//移動スピードが0に等しくなった場合
		if (player_info.m_speed <= StopSpeed)
		{
			//!スコアを更新
			Score::Instance()->Add(player_info.m_score_counter);

			player_info.m_speed = 0.0f;  //移動スピードを0に
			player_info.m_is_turnend = true;  //ターン終了
			player_info.m_is_movement = false;  //移動終了
			player_info.m_timer = 0;
			player_info.m_trun_counter++; //ターン数加算

			//ターン数が制限以上経過した場合
			if (player_info.m_trun_counter >= GameTrun)
			{
				player_info.m_is_goal = true;
				//更新ステップを終了演出へ
				m_update_step = PlayerUpdateStep::EndProduction;
			}
		}
	}

	//1フレーム前の座標保存
	player_info.m_old_pos = player_info.m_pos;

	//方向ベクトル正規化
	D3DXVec3Normalize(&player_info.m_nor_vec, &player_info.m_nor_vec);

	//プレイヤー座標に移動スピード加算
	player_info.m_pos.x += player_info.m_nor_vec.x * player_info.m_speed;
	player_info.m_pos.z += player_info.m_nor_vec.z * player_info.m_speed;

	//ワールド座標更新
	player_info.m_mat_world = Calculation::Matrix(player_info.m_pos, player_info.m_scale, player_info.m_angle);
}

//!当たり判定関数
void Player::HitController()
{
	HitRectBlock(); //矩形型ブロック当たり判定関数
	
	HitCircleBlock(); //円形型ブロック当たり判定関数

	HitReset(); //リセットデバフ床との当たり判定
	HitStop();	//ストップデバフ床との当たり判定
	HitGoal();	//ゴール床との当たり判定

	//反射が5回以上の行われるたびにスコアを減らす
	if (player_info.m_reflect_counter >= ReflectMax)
	{
		Score::Instance()->Add(ReflectScore);
		player_info.m_reflect_counter = 0;
	}
}

//矩形型ブロック当たり判定関数
void Player::HitRectBlock()
{
	if (ObjectCollision::Instance()->HitRectBlock() == true)
	{
		player_info.m_pos = player_info.m_old_pos;

		RectBlock::ObjectInfo rect_block;

		//矩形ブロック情報取得
		mp_block->GetRectBlockInfo(rect_block, ObjectCollision::Instance()->GetRectBlockID());

		//エフェクト再生
		StartHitEffect(rect_block.m_pos);

		//矩形ブロックの上下、もしくは左右に当たった場合
		if (ObjectCollision::Instance()->GetHitRectPoint() == HitRectPoint::TopOrUnder ||
			ObjectCollision::Instance()->GetHitRectPoint() == HitRectPoint::LeftOrRight)
		{
			//反射
			player_info.m_nor_vec = ReflectionRect(ObjectCollision::Instance()->GetHitRectPoint(), rect_block.m_angle.y);
		}
		//矩形ブロックの各頂点に当たった場合
		else
		{
			//反射
			player_info.m_nor_vec = ReflectionVertex(ObjectCollision::Instance()->GetHitRectPoint(),
				rect_block.m_pos, rect_block.m_width, rect_block.m_height, rect_block.m_angle.y);
		}
		
		//サウンド再生
		SoundController::Instance()->PlaySoundSE(PlaySEType::Reflect);
		//反射回数加算
		player_info.m_reflect_counter++;
	}
}

//円形型ブロック当たり判定関数
void Player::HitCircleBlock()
{
	if (ObjectCollision::Instance()->HitCircleBlock() == true)
	{
		CircleBlock::ObjectInfo circle_block;
		
		//円形ブロック情報取得
		mp_block->GetCircleBlockInfo(circle_block, ObjectCollision::Instance()->GetCircleBlockID());

		player_info.m_pos = player_info.m_old_pos;

		//エフェクト再生
		StartHitEffect(circle_block.m_pos);
		//反射
		player_info.m_nor_vec = ReflectionCircle(circle_block.m_pos);
		//サウンド再生
		SoundController::Instance()->PlaySoundSE(PlaySEType::Reflect);
		//反射回数加算
		player_info.m_reflect_counter++;
	}
}

//リセットデバフ当たり判定関数
void Player::HitReset()
{
	if (ObjectCollision::Instance()->HitResetFloor() == true)
	{
		//エフェクト再生
		StartResetEffect();

		//座標を初期位置に戻す
		player_info.m_pos = D3DXVECTOR3(m_player_externalinfo.m_pos.x, PlayerPosMin_Y, m_player_externalinfo.m_pos.z);

		//移動スピードを0に
		player_info.m_setspeed_power = 0.0f;

		//サウンド再生
		SoundController::Instance()->PlaySoundSE(PlaySEType::Reset);
	}
}

//停止デバフ当たり判定関数
void Player::HitStop()
{
	if (ObjectCollision::Instance()->HitStopFloor() == true)
	{
		//摩擦係数を増やす
		player_info.m_friction = StopFloorFriction;
		SoundController::Instance()->PlaySoundSE(PlaySEType::Stop);
	}
	else
	{
		//摩擦係数を元に戻す
		player_info.m_friction = m_player_externalinfo.m_friction;
		SoundController::Instance()->ResetStopFlag();
	}
}

//ゴール当たり判定関数
void Player::HitGoal()
{
	//ターン終了時に当たっているかどうかを判定
	if (player_info.m_is_turnend == true)
	{
		Goal::ObjectInfo m_goal_infocopy;

		mp_goal->GetGoalInfo(m_goal_infocopy);

		if (ObjectCollision::Instance()->HitGoal() == true)
		{
			//エフェクト再生
			StartGoalEffect();
			SoundController::Instance()->PlaySoundSE(PlaySEType::Goal);

			//ゴール時のスコア加算に変更
			switch ((GoalType)ObjectCollision::Instance()->GetGoalType())
			{
			case GoalType::Red:  //赤色ゴール
				player_info.m_score_counter = RedGoalScore;
				break;
			case GoalType::Yellow: //黄色ゴール
				player_info.m_score_counter = YellowGoalScore;
				break;
			case GoalType::Green:  //緑色ゴール
				player_info.m_score_counter = GreenGoalScore;
				break;
			default:
				break;
			}
			
			//スコアを更新
			Score::Instance()->Add(player_info.m_score_counter);
			player_info.m_is_goal = true;

			//更新ステップを終了演出へ
			m_update_step = PlayerUpdateStep::EndProduction;
		}

		
	}
}

//矩形型ブロック反射方向計算関数
D3DXVECTOR3 Player::ReflectionRect(HitRectPoint type_,float rad_)
{
	D3DXVECTOR3 old_direction = player_info.m_nor_vec;
	float m_change_radian;


	//矩形の上下にあたったら方向ベクトルのy軸(z)を反転
	//矩形の左右にあたったら方向ベクトルのx軸を反転
	switch (type_)
	{
	case HitRectPoint::TopOrUnder:  //上下
		old_direction.z = -old_direction.z;
		break;
	case HitRectPoint::LeftOrRight: //左右
		old_direction.x = -old_direction.x;
		break;
	default:
		break;
	}

	//3Dと2Dで回転する方向が逆のため逆に回転させる
	m_change_radian = -rad_;
	m_change_radian *= 2;

	//方向ベクトルを回転
	return Calculation::Rotate(old_direction, D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_change_radian);
}

//円形型ブロック反射方向計算関数
D3DXVECTOR3 Player::ReflectionCircle(D3DXVECTOR3 circle_pos_)
{
	//値初期化
	D3DXVECTOR3 old_direction = player_info.m_nor_vec;

	//方向ベクトルを反転
	old_direction.x = -old_direction.x;
	old_direction.z = -old_direction.z;

	//プレイヤーと円の接線に垂直なベクトル
	D3DXVECTOR3 vec = player_info.m_pos - circle_pos_;

	//Playerの進む方向ベクトルと
	//Playerと円のベクトルのatanを求める
	float direction_rad = atan2f(old_direction.z, old_direction.x);
	float vec_rad = atan2f(vec.z, vec.x);

	//方向ベクトルと接線に垂直なベクトルのなす角を求める
	float degree2 = 0;
	degree2 = D3DXToDegree(Calculation::EggplantAngle(old_direction, vec));

	//atan()が0～180、0～-180の範囲でしか値が出せないため、どちらかのベクトルが負の場合360度足して比較する値を直す
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


	//方向ベクトルとプレイヤーと円の接線に垂直なベクトルの角度を比較し
	//方向ベクトルを回転させる方向を決める(右回転か左回転か)
	if (direction_rad > vec_rad)
	{
		degree2 = -degree2;
	}

	//方向ベクトルを回転回転
	return Calculation::Rotate(old_direction, D3DXVECTOR3(0.0f, 0.0f, 0.0f), degree2 * 2);
}

//矩形型ブロック頂点反射方向計算関数
D3DXVECTOR3 Player::ReflectionVertex(HitRectPoint type_, D3DXVECTOR3 r_pos_, float width_, float height_, float rad_)
{
	//値初期化
	D3DXVECTOR3 old_direction = player_info.m_nor_vec;
	D3DXVECTOR3 vec(0.0f, 0.0f, 0.0f);

	D3DXVECTOR3 player_lotepos = Calculation::Rotate(player_info.m_pos, r_pos_, rad_);
	D3DXVECTOR3 ver_pos(0.0f, 0.0f, 0.0f);

	//方向ベクトルを反転
	old_direction.x = -old_direction.x;
	old_direction.z = -old_direction.z;

	//当たり判定を取る箇所
	switch (type_)
	{
	case HitRectPoint::LeftTop:  //左上
		ver_pos.x = r_pos_.x - (width_ / 2);
		ver_pos.z = r_pos_.z + (height_ / 2);
		break;
	case HitRectPoint::RightTop:  //右上
		ver_pos.x = r_pos_.x - (width_ / 2);
		ver_pos.z = r_pos_.z - (height_ / 2);
		break;
	case HitRectPoint::LeftUnder:  //左下
		ver_pos.x = r_pos_.x + (width_ / 2);
		ver_pos.z = r_pos_.z + (height_ / 2);
		break;
	case HitRectPoint::RightUnder:  //右下
		ver_pos.x = r_pos_.x + (width_ / 2);
		ver_pos.z = r_pos_.z - (height_ / 2);
		break;
	default:
		break;
	}

	//Playerと頂点のベクトル
	D3DXVECTOR3 old_vec = player_lotepos - ver_pos;

	//矩形が回転していたらベクトルも回転させる
	vec = Calculation::Rotate(old_vec, D3DXVECTOR3(0.0f, 0.0f, 0.0f), -rad_);

	float direction_rad = atan2f(old_direction.z, old_direction.x);
	float vec_rad = atan2f(vec.z, vec.x);

	//方向ベクトルと接線に垂直なベクトルのなす角を求める
	float degree2 = 0;
	degree2 = D3DXToDegree(Calculation::EggplantAngle(old_direction, vec));

	//atan()が0～180、0～-180の範囲でしか値が出せないため、どちらかのベクトルが負の場合360度足して比較する値を直す
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

	
	//方向ベクトルとプレイヤーと円の接線に垂直なベクトルの角度を比較し
	//方向ベクトルを回転させる方向を決める(右回転か左回転か)
	if (direction_rad > vec_rad)
	{
		degree2 = -degree2;
	}

	//!方向ベクトルを回転
	return Calculation::Rotate(old_direction, D3DXVECTOR3(0.0f, 0.0f, 0.0f), degree2 * 2);
}

//初期位置移動関数
void Player::ResetPos()
{
	Floor::ObjectInfo m_floor_infocopy;

	mp_floor->GetFloorInfo(m_floor_infocopy);

	//ステージから落ちた場合
	if (player_info.m_pos.x <= m_floor_infocopy.m_pos.x - m_floor_infocopy.m_width
		|| player_info.m_pos.x >= m_floor_infocopy.m_pos.x + m_floor_infocopy.m_width
		|| player_info.m_pos.z <= m_floor_infocopy.m_pos.z - m_floor_infocopy.m_height
		|| player_info.m_pos.z >= m_floor_infocopy.m_pos.z + m_floor_infocopy.m_height)
	{

		StartResetEffect(); //エフェクト再生
		player_info.m_pos = D3DXVECTOR3(m_player_externalinfo.m_pos.x, PlayerPosMin_Y, m_player_externalinfo.m_pos.z); //座標
		player_info.m_setspeed_power = 0.0f;

		StartFallEffect();
		SoundController::Instance()->PlaySoundSE(PlaySEType::Reset);
	}
}


//開始演出関数
void Player::StartProduction()
{
	//プレイヤーが上からステージ床に当たるまで
	if (player_info.m_pos.y > PlayerPosMin_Y
		&& player_info.m_is_goal == false)
	{
		player_info.m_pos.y -= player_info.m_speed;

		player_info.m_mat_world = Calculation::Matrix(player_info.m_pos, player_info.m_scale, player_info.m_angle);
	}
	//床に着いた場合
	else
	{
		//座標を正確な位置に戻す
		player_info.m_pos.y = PlayerPosMin_Y;
		player_info.m_speed = 0.0f;
		player_info.m_timer = 0;
		//更新ステップをゲーム本編へ
		m_update_step = PlayerUpdateStep::GameMain;
	}
}

//終了演出関数
void Player::EndProduction()
{
	//プレイヤーが上に上がっていく形にするためY座標を+
	player_info.m_pos.y += PlayerUpSpeed;

	//ワールド座標更新
	player_info.m_mat_world = Calculation::Matrix(player_info.m_pos, player_info.m_scale, player_info.m_angle);
}

//衝突時エフェクト開始関数
void Player::StartHitEffect(D3DXVECTOR3 block_pos_)
{
	D3DXVECTOR3 block_vec = block_pos_ - player_info.m_pos;

	D3DXVec3Normalize(&block_vec, &block_vec);

	//エフェクト座標設定
	player_info.m_efk_pos = block_vec * HitEffectPosLength + player_info.m_pos;

	//エフェクト再生
	Effect::Instance()->PlayEffect(EffectType::HitEfc, player_info.m_efk_pos.x, PlayerPosMin_Y, player_info.m_efk_pos.z);
}

//落下時エフェクト開始関数
void Player::StartFallEffect()
{
	//エフェクト座標設定
	player_info.m_efk_pos = player_info.m_pos;

	//エフェクト再生
	Effect::Instance()->PlayEffect(EffectType::FallEfc, player_info.m_efk_pos.x, PlayerPosMin_Y, player_info.m_efk_pos.z);
}

//リセット時エフェクト開始関数
void Player::StartResetEffect()
{
	//エフェクト座標設定
	player_info.m_efk_pos = player_info.m_pos;

	Effect::Instance()->PlayEffect(EffectType::ResetEfc, player_info.m_efk_pos.x, PlayerPosMin_Y, player_info.m_efk_pos.z);
}

//ゲーム終了時エフェクト開始関数
void Player::StartGoalEffect()
{
	//エフェクト座標設定
	player_info.m_efk_pos = player_info.m_pos;

	Effect::Instance()->PlayEffect(EffectType::GoalEfc, player_info.m_efk_pos.x, player_info.m_efk_pos.y + GoalEffect2PosHeight, player_info.m_efk_pos.z);
	Effect::Instance()->PlayEffect(EffectType::GoalEfc, player_info.m_efk_pos.x, player_info.m_efk_pos.y + GoalEffect2PosHeight, player_info.m_efk_pos.z);
}



