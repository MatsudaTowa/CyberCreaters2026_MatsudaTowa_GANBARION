//=============================================
//
//アクティブシーンのステートパターン[active_scene_state.cpp]
//Author Matsuda Towa
//
//=============================================
#include "active_scene_state.h"
#include "active_scene.h"
#include "manager.h"

//=============================================
// コンストラクタ
//=============================================
CNormal::CNormal()
{
	while (1)
	{
		int nCnt = ShowCursor(FALSE);
		if (nCnt > 0)
		{
			continue;
		}
		break;
	}
	ShowCursor(FALSE);
}

//=============================================
// 通常処理
//=============================================
void CNormal::Normal(CActiveScene* active_scene)
{
	//オブジェクトのアップデートを許可する
	active_scene->UpdateObjectDecision(true);
	//カメラも
	CManager::GetInstance()->GetCamera()->SetActive(true);
}

//ポーズUI表示位置
const D3DXVECTOR3 CPause::POS[CPause::MAX]
{
	{SCREEN_WIDTH * HALF,200.0f,0.0f},
	{SCREEN_WIDTH * HALF,400.0f,0.0f},
	{SCREEN_WIDTH * HALF,600.0f,0.0f}
};

//=============================================
// コンストラクタ
//=============================================
CPause::CPause() :
	m_pSelect(),	//セレクトUIの数
	m_pMask(nullptr)	//黒いマスク
{
	while (1)
	{
		int nCnt = ShowCursor(TRUE);
		if (nCnt < 0)
		{
			continue;
		}
		break;
	}

	for (int i = 0; i < CPause::MAX; ++i)
	{
		if (m_pSelect[i] != nullptr)
		{
			continue;
		}
		switch (i)
		{
		case CONTINUE:
			m_pSelect[i] = CPauseSelect::Create(POS[i], new CPauseSelectContinue);
			break;
		case RETRY:
			m_pSelect[i] = CPauseSelect::Create(POS[i], new CPauseSelectRetry);
			break;
		case QUIT:
			m_pSelect[i] = CPauseSelect::Create(POS[i], new CPauseSelectQuit);
			break;
		default:
			break;
		}

	}

	m_pMask = CMask::Create(new CPauseMask);
}

//=============================================
// デストラクタ
//=============================================
CPause::~CPause()
{
	for (int i = 0; i < CPause::MAX; ++i)
	{
		if (m_pSelect[i] != nullptr)
		{
			m_pSelect[i]->Uninit();
			m_pSelect[i] = nullptr;
		}
	}
	if (m_pMask != nullptr)
	{
		m_pMask->Uninit();
		m_pMask = nullptr;
	}
}

//=============================================
// ポーズ処理
//=============================================
void CPause::Pause(CActiveScene* active_scene)
{
	//オブジェクトのアップデートを止める
	active_scene->UpdateObjectDecision(false);

	//ポーズ関連のオブジェクトの更新は許可
	m_pMask->SetisActive(true);

	for (int i = 0; i < CPause::MAX; ++i)
	{
		if (m_pSelect[i] != nullptr)
		{
			m_pSelect[i]->SetisActive(true);
			m_pSelect[m_nSelect]->SetSelect(false);
		}
	}

	CInputKeyboard* pKeyBoard = CManager::GetInstance()->GetKeyboard();

	if (pKeyBoard->GetTrigger(DIK_S))
	{
		if (m_nSelect >= CPause::QUIT)
		{
			m_nSelect = CPause::CONTINUE;
			return;
		}
		++m_nSelect;
	}
	if (pKeyBoard->GetTrigger(DIK_W))
	{
		if (m_nSelect <= CPause::CONTINUE)
		{
			m_nSelect = CPause::QUIT;
			return;
		}
		--m_nSelect;
	}

	m_pSelect[m_nSelect]->SetSelect(true);

	if (pKeyBoard->GetTrigger(DIK_RETURN))
	{
		active_scene->ResetPauseCnt();
		HandlePoseSelection(active_scene);
		return;
	}

	//カメラも
	CManager::GetInstance()->GetCamera()->SetActive(false);

	//入力デバイス取得
	CInputKeyboard* pKeyboard = CManager::GetInstance()->GetKeyboard();

	if (pKeyboard->GetTrigger(DIK_P) && active_scene->GetPauseKey())
	{
		active_scene->ResetPauseCnt();
		CancelPause(active_scene);
	}
}
