//=============================================
//
//3DTemplate[input.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _INPUT_H_ //定義されてなかったら
#define _INPUT_H_ //２種インクルード防止
#include "main.h"

//インプットクラス
class CInput
{
public:
	/**
	 * @brief コンストラクタ
	 */
	CInput();
	/**
	 * @brief デストラクタ
	 */
	~CInput();
	/**
	 * @brief 初期化
	 * @param [in]インスタンス
	 * @param [in]ハンドルワンド
	 * @return 成功したか
	 */
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	/**
	 * @brief 終了
	 */
	virtual void Uninit();
	/**
	 * @brief 更新
	 */
	virtual void Update() = 0;
protected:
	static LPDIRECTINPUT8 m_pInput;
	LPDIRECTINPUTDEVICE8 m_pDevice;
};

//キーボードクラス
class CInputKeyboard:public CInput
{
public:
	static const int NUM_KEY_MAX = 256; //キーボードのキー数
	/**
	 * @brief コンストラクタ
	 */
	CInputKeyboard();
	/**
	 * @brief デストラクタ
	 */
	~CInputKeyboard();
	/**
	 * @brief 初期化
	 * @param [in]インスタンス
	 * @param [in]ハンドルワンド
	 * @return 成功したか
	 */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	/**
	 * @brief 終了
	 */
	void Uninit() override;
	/**
	 * @brief 更新
	 */
	void Update() override;

	/**
	 * @brief プレス情報取得
	 * @param [in]キー番号
	 * @return 押されているか
	 */
	inline bool GetPress(int nKey)
	{
		return(m_aKeyState[nKey] & 0x80) != 0;
	}

	/**
	 * @brief トリガー情報取得
	 * @param [in]キー番号
	 * @return 押されているか
	 */
	inline bool GetTrigger(int nKey)
	{
		return(m_aKeyStateTrigger[nKey] & 0x80) != 0;
	}

	/**
	 * @brief リリース情報取得
	 * @param [in]キー番号
	 * @return 離されているか
	 */	
	inline bool GetRelease(int nKey)
	{
		return(m_aKeyStateRelease[nKey] & 0x80) != 0;
	}
private:
	BYTE m_aKeyStateTrigger[NUM_KEY_MAX]; //キーボードのトリガー情報
	BYTE m_aKeyStateRelease[NUM_KEY_MAX]; //キーボードのリリース情報
	BYTE m_aKeyState[NUM_KEY_MAX]; //キーボードのプレス情報
};

//マウスクラス
class CInputMouse :public CInput
{
public:
	static const int NUM_MOUSE_MAX = 3; //マウスのキー数
	/**
	 * @brief コンストラクタ
	 */
	CInputMouse();
	/**
	 * @brief デストラクタ
	 */
	~CInputMouse();
	/**
	 * @brief 初期化
	 * @param [in]インスタンス
	 * @param [in]ハンドルワンド
	 * @return 成功したか
	 */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	/**
	 * @brief 終了
	 */
	void Uninit() override;
	/**
	 * @brief 更新
	 */
	void Update() override;

	/**
	 * @brief プレス情報取得
	 * @param [in]キー番号
	 * @return 押されているか
	 */	
	inline bool GetPress(int nKey)
	{
		return(m_KeyState.rgbButtons[nKey] & 0x80) != 0;
	}

	/**
	* @brief トリガー情報取得
	* @param [in]キー番号
	* @return 押されているか
	*/	
	inline bool GetTrigger(int nKey)
	{
		return(m_KeyStateTrigger.rgbButtons[nKey] & 0x80) != 0;
	}

	/**
	* @brief リリース情報取得
	* @param [in]キー番号
	* @return 離されているか
	*/	
	inline bool GetRelease(int nKey)
	{
		return(m_KeyStateRelease.rgbButtons[nKey] & 0x80) != 0;
	}

	/**
	 * @brief 移動量取得
	 * @return 移動量
	 */
	inline D3DXVECTOR3 GetMouseMove(void)
	{
		return m_MouseMove;
	}

	/**
	 * @brief デバッグ情報
	 */
	void Debug();
private:
	DIMOUSESTATE m_KeyStateTrigger; //マウスのトリガー情報
	DIMOUSESTATE m_KeyStateRelease; //マウスのリリース情報
	DIMOUSESTATE m_KeyState; //マウスのプレス情報
	DIMOUSESTATE m_zdiMouseMove; //マウスムーブ
	D3DXVECTOR3 m_MousePos;
	D3DXVECTOR3 m_MouseMove;
};

//padクラス
class CInputPad :public CInput
{
public:
	//キーの種類
	enum JOYKEY
	{
		JOYKEY_UP = 0,
		JOYKEY_DOWN,
		JOYKEY_LEFT,
		JOYKEY_RIGHT,
		JOYKEY_START,
		JOYKEY_BACK,
		JOYKEY_L3,
		JOYKEY_R3,
		JOYKEY_LB,
		JOYKEY_RB,
		JOYKEY_LT,
		JOYKEY_RT,
		JOYKEY_A,
		JOYKEY_B,
		JOYKEY_X,
		JOYKEY_Y,
		JOYKEY_MAX
	};

	//スティックの番号
	enum STICKTYPE
	{
		STICKTYPE_LEFT = 0, // 左スティック
		STICKTYPE_RIGHT, // 右スティック
		STICKTYPE_MAX
	};

	//スティックの方向
	enum STICKANGLE
	{
		STICKANGLE_UP = 0, // 上
		STICKANGLE_DOWN,   // 下
		STICKANGLE_LEFT,   // 左
		STICKANGLE_RIGHT,  // 右
		STICKANGLE_MAX,
	};

	//スティックの入力情報
	struct STICKINPUT
	{
		float afTplDiameter[STICKTYPE_MAX];                      // スティックの倒し具合
		float afAngle[STICKTYPE_MAX];                            // スティックの角度
		bool abAnglePress[STICKTYPE_MAX][STICKANGLE_MAX];        // スティックの方向プレス情報
		bool abAngleTrigger[STICKTYPE_MAX][STICKANGLE_MAX];      // スティックの方向トリガー情報
		bool abAngleRepeat[STICKTYPE_MAX][STICKANGLE_MAX];       // スティックの方向リピート情報
		bool abAngleRelease[STICKTYPE_MAX][STICKANGLE_MAX];      // スティックの方向リリース情報
	};

	//マクロ定義
	static const int JOYPAD_ZONE = 1;
	static const int JOYPAD_SPEED = 15;

	/**
	 * @brief コンストラクタ
	 */
	CInputPad();
	/**
	 * @brief デストラクタ
	 */
	~CInputPad();
	/**
	 * @brief 初期化
	 * @param [in]インスタンス
	 * @param [in]ハンドルワンド
	 * @return 成功したか
	 */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd) override;
	/**
	 * @brief 終了
	 */
	void Uninit() override;
	
	/**
	 * @brief 更新
	 */
	void Update() override;

	/**
	 * @brief 接続されているか取得
	 * @return 接続されてるか
	 */
	inline bool GetConnet()
	{
		return m_Connect;
	}

	/**
	 * @brief プレス情報取得
	 * @param [in]キー
	 * @return 押されているか
	 */
	inline bool GetPress(JOYKEY Key)
	{
		return (m_joyKeyState & (0x01 << Key)) ? true : false;
	}

	/**
	 * @brief トリガー情報取得
	 * @param [in]キー
	 * @return 押されているか
	 */
	inline bool GetTrigger(JOYKEY Key)
	{
		return (m_joyKeyStateTrigger & (0x01 << Key)) ? true : false;
	}

	/**
	 * @brief リリース情報取得
	 * @param [in]キー
	 * @return 離されているか
	 */
	inline bool GetRelease(JOYKEY Key)
	{
		return(m_ajoyKeyStateRelease & (0x01 << Key)) ? true : false;
	}

	/**
	 * @brief ステート取得
	 * @return ステート
	 */
	inline XINPUT_STATE* GetXInputState(void)
	{
		return &m_XInput;
	}

	/**
	 * @brief スティック更新
	 * @param [in]状態
	 */
	void UpdateStick(XINPUT_STATE state);
	/**
	 * @brief スティック取得
	 * @return スティックのインプット情報
	 */
	STICKINPUT GetStick(void);
	/**
	 * @brief 角度計算
	 * @param [in]位置
	 * @param [in]目的の位置
	 * @return 角度
	 */
	float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 TargetPos);
	/**
	 * @brief スティック情報取得
	 * @param [in]Xの倒し度
	 * @param [in]Xの倒し度
	 * @param [in]デッドゾーン
	 * @return 方向
	 */
	WORD GetJoypadStick(SHORT sThumbX, SHORT sThumbY, SHORT sDeadZone);
private:
	//コントローラー
	bool m_Connect; //接続されてるかどうか
	WORD m_joyKeyState; //ジョイパッドのプレス情報
	WORD m_joyKeyStateTrigger; //ジョイパッドのトリガー情報
	WORD m_joyKeyStateRepeat; //ジョイパッドのリピート情報
	WORD m_ajoyKeyStateRelease; //コントローラーのリリース情報
	WORD m_aJoypadCurrentTime; //コントローラーの現在の時間
	WORD m_aJoypadExecLastTime; //コントローラーの最後に真を返した時間
	WORD m_JoypadInput; //コントローラーの入力情報
	D3DXVECTOR3 m_joyStickPos; //スティックの傾き
	bool m_bAngle[STICKTYPE_MAX][STICKANGLE_MAX]; //スティックの入力情報
	DWORD m_aStickCurrentTime[STICKTYPE_MAX][STICKANGLE_MAX]; //スティックの現在の時間
	DWORD m_aStickExecLastTime[STICKTYPE_MAX][STICKANGLE_MAX]; //スティックの現在の時間
	STICKINPUT m_stick; //スティックの入力情報
	XINPUT_STATE m_XInput; //入力情報
	XINPUT_VIBRATION m_JoypadMotor;
	int m_nCntkey;
};
#endif // _INPUT_H_ //定義されてなかったら