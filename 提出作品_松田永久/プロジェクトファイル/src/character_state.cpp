//=============================================
//
//キャラクターのステートパターン[character_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "character_state.h"

//=============================================
//最初に呼ばれる関数
//=============================================
void CCharacterState::Start(CCharacter* character)
{
}

//=============================================
//キャラクターのショット
//=============================================
void CCharacterState::Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character)
{
}

//=============================================
//キャラクターのスタン
//=============================================
void CCharacterState::Stan(CCharacter* character)
{
}


//=============================================
//キャラクターの混乱
//=============================================
void CCharacterState::Confusion(CCharacter* character)
{
}

//=============================================
//キャラクターの動き
//=============================================
void CCharacterState::Move(CCharacter* character)
{
}

//=============================================
//キャラクターのショット
//=============================================
void CShotState::Shot(CBullet::BULLET_ALLEGIANCE Allegiance, CCharacter* character)
{
	character->GetGunAttack()->GunAttack(Allegiance,character);
}

//=============================================
//キャラクターの動き
//=============================================
void CMoveState::Move(CCharacter* character)
{
	CMove* move = character->GetMoveStrategy();
	if (move != nullptr)
	{
		move->Move(character);
	}
}

//=============================================
//最初に呼ばれる関数
//=============================================
void CStanState::Start(CCharacter* character)
{
	//カウントリセット
	m_StanCnt = 0;
}

//=============================================
//キャラクターのスタン状態
//=============================================
void CStanState::Stan(CCharacter* character)
{
	const int StanFrame = character->GetStanFrame();

	if (m_StanCnt < StanFrame)
	{
		++m_StanCnt;

		CStan* stan = character->GetStan();

		if (stan != nullptr)
		{
			stan->Stan(character);
		}
	}
	if (m_StanCnt >= StanFrame)
	{
		m_StanCnt = 0;

		//射撃状態に遷移
		character->ChangeState(new CShotState);
		return;
	}
}

//=============================================
//最初に呼ばれる関数
//=============================================
void CConfusionState::Start(CCharacter* character)
{
	m_StartRot = character->GetRot().y;
	if (m_StartRot < HALF_PI && m_StartRot > -HALF_PI)
	{
		m_isRight = false;
	}
	else if (m_StartRot > HALF_PI && m_StartRot < -HALF_PI)
	{
		m_isRight = true;
	}
}

//=============================================
//キャラクターの混乱状態
//=============================================
void CConfusionState::Confusion(CCharacter* character)
{
	CConfusion* confusion = character->GetConfusion();
	if (confusion != nullptr)
	{
		confusion->Confusion(character, m_StartRot);
	}
}
