//=============================================
//
//アクティブシーンのステートパターン[active_scene_state.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _ACTIVE_SCENE_STATE_H_
#define _ACTIVE_SCENE_STATE_H_
#include "pause_mask.h"
#include "pause_select.h"
#include "pause_select_continue.h"
#include "pause_select_retry.h"
#include "pause_select_quit.h"

//=============================================
//前方宣言
//=============================================
class CActiveScene;

/** @brief アクティブシーンのステートクラス */
class CActiveSceneState
{
public:
	CActiveSceneState() {};
	virtual ~CActiveSceneState() {};
	/**
	* @brief 通常処理(親では何もしない)
	* @param [in]アクティブシーンポインタ
	*/
	virtual void Normal(CActiveScene* active_scene) {};

	/**
	* @brief ポーズ状態処理(親では何もしない)
	* @param [in]アクティブシーンポインタ
	*/
	virtual void Pause(CActiveScene* active_scene) {};
};

/** @brief 通常クラス */
class CNormal :public CActiveSceneState
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CNormal();
	/**
	* @brief ニュートラル処理
	* @param [in]アクティブシーンポインタ
	*/
	void Normal(CActiveScene* active_scene) override;
};

/** @brief 状態処理クラス */
class CPause :public CActiveSceneState
{
public:
	enum PAUSE_SELECT
	{
		CONTINUE = 0,
		RETRY,
		QUIT,
		MAX
	};
	/**
	 * @brief コンストラクタ
	 */
	CPause();
	/**
	 * @brief デストラクタ
	 */
	~CPause()override;
	/**
	* @brief ポーズ状態処理
	* @param [in]アクティブシーンポインタ
	*/
	void Pause(CActiveScene* active_scene) override;
	/**
	 * @brief ポーズの選択されたUIの更新実行処理
	 * @param [in]アクティブシーンのポインタ
	 */
	virtual void HandlePoseSelection(CActiveScene* active_scene) {};

	/**
	 * @brief ポーズキャンセル
	 * @param [in]アクティブシーンのポインタ
	 */
	virtual void CancelPause(CActiveScene* active_scene) {};

	/**
	 * @brief どれを選択してるか取得
	 * @return 選択されてるもの
	 */
	inline int GetSelect()
	{
		return m_nSelect;
	}

	/**
	 * @brief セレクトされてるUI
	 * @param [in]idx
	 * @return 選択UI
	 */
	inline CPauseSelect* GetSelectUI(int idx)
	{
		return m_pSelect[idx];
	}
private:
	static const D3DXVECTOR3 POS[MAX];

	int m_nSelect;
	CMask* m_pMask;
	CPauseSelect* m_pSelect[MAX];
};

#endif // !_GAME_STATE_H_
