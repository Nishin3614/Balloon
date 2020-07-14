//=============================================================================
//
// ネットワーク処理 [network.cpp]
// Author : masayasu wakita
//
//=============================================================================
#include "network.h"
#include "debugproc.h"
#include "renderer.h"
#include "camera.h"
#include "player.h"
#include "game.h"

bool m_aKeyState[MAX_PLAYER][NUM_KEY_M] = {};				//キーボードの入力情報ワーク
bool m_aKeyStateOld[MAX_PLAYER][NUM_KEY_M] = {};			// 前のキーボード入力情報ワーク
bool m_aKeyStateTrigger[MAX_PLAYER][NUM_KEY_M] = {};		// Trigger

//=============================================================================
// 静的メンバ変数
//=============================================================================
char CNetwork::aIp[32] = {};
int CNetwork::nPort = 0;

//=============================================================================
// コンストラクタ
//=============================================================================
CNetwork::CNetwork()
{
	m_nId = -1;
}

//=============================================================================
// デストラクタ
//=============================================================================
CNetwork::~CNetwork()
{

}

//=============================================================================
// 初期化
//=============================================================================
HRESULT CNetwork::Init(void)
{
	HRESULT hr;
	hr = Build();					// ソケットの生成
	char debug[256];

	OutputDebugString("クライアント構築完了\n");

	int ans = ConvertDecimalToBinary(100);
	sprintf(debug, "ans = %d\n", ans);
	OutputDebugString(debug);

	ans = 100 & 15;
	sprintf(debug, "ans = %d\n", ans);
	OutputDebugString(debug);

	for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
	{
		m_fRot[nCount] = 0.0f;
	}

	m_bUpdate = false;

	return hr;
}

//=============================================================================
// 終了
//=============================================================================
void CNetwork::Uninit(void)
{
	//ソケット(クライアント)の開放
	closesocket(m_sockClient);
}

//=============================================================================
// 更新  if ( setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (const char *),  sizeof(param) )
//=============================================================================
void CNetwork::Update(void)
{
	DWORD dwCurrentTime;		// 現在時刻
	DWORD dwExecLastTime;		// 最後に処理した時刻
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;

	dwCurrentTime = 0;
	dwExecLastTime = timeGetTime();		// システム時刻をミリ秒単位で取得

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();		// システム時刻をミリ秒単位で取得

	while (m_bUpdate)
	{
		// DirectXの処理
		dwCurrentTime = timeGetTime();		// システム時刻を取得

		if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))		// 1/60秒ごとに実行
		{
			dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

			OutputDebugString("更新開始");

			char debug[1024];
			int nError = -1;
			float fData[NUM_KEY_M + 1 + 3];
			char cDie[32];

			char cDataText[128];		//文字
			char cPlayerData[MAX_PLAYER][128];		//比較

			OutputDebugString("送信開始\n");
			KeyData();
			OutputDebugString("送信完了\n");

			fd_set readfds;
			FD_ZERO(&readfds);
			FD_SET(m_sockServerToClient, &readfds);

			struct timeval tv;

			// 指定した秒数でタイムアウトさせます
			tv.tv_sec = 0;
			tv.tv_usec = 0;

			nError = select(0, &readfds, NULL, NULL, &tv);
			if (nError == 0)
			{
				OutputDebugString("タイムアウト\n");
				continue;
			}

			if (FD_ISSET(m_sockServerToClient, &readfds))
			{
				OutputDebugString("受信開始\n");
				nError = recv(m_sockServerToClient, debug, sizeof(debug), 0);
				OutputDebugString("受信完了\n");
			}

			if (nError == SOCKET_ERROR)
			{
				// ソケットの作成に失敗したとき
				char aError[64];
				sprintf(aError, "サーバーに接続失敗!!\n エラーコード : %d", WSAGetLastError());
				MessageBox(NULL, aError, "警告！", MB_ICONWARNING);
			}
			else
			{
				sscanf(debug, "%s %s %s %s %s", &cDie, &cPlayerData[0], &cPlayerData[1], &cPlayerData[2], &cPlayerData[3]);

				for (int nCount = 0; nCount < MAX_PLAYER; nCount++)
				{
					ConvertStringToFloat(cPlayerData[nCount], ",", fData);

					for (int nCntkey = 0; nCntkey < NUM_KEY_M; nCntkey++)
					{
						m_aKeyStateOld[nCount][nCntkey] = m_aKeyState[nCount][nCntkey];
					}

					for (int nCntKey = 0; nCntKey < NUM_KEY_M; nCntKey++)
					{
						m_aKeyState[nCount][nCntKey] = fData[nCntKey];
					}

					for (int nCntKey = 0; nCntKey < NUM_KEY_M; nCntKey++)
					{
						m_aKeyStateTrigger[nCount][nCntKey] = (m_aKeyStateOld[nCount][nCntKey] ^ m_aKeyState[nCount][nCntKey]) & m_aKeyState[nCount][nCntKey];
					}
					m_fRot[nCount] = fData[NUM_KEY_M];

					m_playerPos[nCount] = D3DXVECTOR3(fData[NUM_KEY_M + 1], fData[NUM_KEY_M + 2], fData[NUM_KEY_M + 3]);
				}
			}
		}
	}
}

//=============================================================================
// ネットワークの設定データ読み込み
//=============================================================================
HRESULT CNetwork::LoadConfiguration(void)
{
	FILE *pFile;
	char cReadText[128];		//文字
	char cHeadText[128];		//比較
	char cDie[128];

	//テキストデータロード
	pFile = fopen(SCRIPT_NETWORK, "r");

	if (pFile != NULL)
	{
		//スクリプトが来るまでループ
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
		}

		//スクリプトだったら
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//エンドスクリプトが来るまで
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);

				//改行
				if (strcmp(cReadText, "\n") != 0)
				{
					if (strcmp(cHeadText, "IP") == 0)
					{//パーツ総数のとき
						sscanf(cReadText, "%s %s %s", &cDie, &cDie, aIp);					//パーツの数を取得
					}
					else if (strcmp(cHeadText, "PORT") == 0)
					{//パーツモデルのアドレス情報のとき
						sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nPort);					//パーツの数を取得
					}
				}
			}
		}

		//ファイル閉
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "ネットワークの設定データ読込失敗！", "警告！", MB_ICONWARNING);
	}

	return S_OK;
}

//=============================================================================
// キーボードの入力状態の取得
//=============================================================================
PLAYERSTATE CNetwork::GetKeystate(void)
{
	return keystate;
}

//=============================================================================
// 送信(TCP)
//=============================================================================
bool CNetwork::SendTCP(const char *data, int nSize)
{
	int nError;

	//クライアントへデータ(ID)送信
	nError = send(m_sockClient, data, nSize, 0);
	if (nError < 0)
	{
		printf("送信エラー : %d\n", WSAGetLastError());
	}

	return false;
}

//=============================================================================
// 送信(UDP)
//=============================================================================
bool CNetwork::SendUDP(const char *data, int nSize)
{
	int nError;

	//クライアントへデータ(ID)送信
	nError = sendto(m_sockClientToServer, data, nSize, 0, (struct sockaddr *)&m_addrClientToServer, sizeof(m_addrClientToServer));
	if (nError == SOCKET_ERROR)
	{
		char aError[256];
		memset(&aError, 0, sizeof(aError));
		sprintf(aError, "送信エラー : %d\n", WSAGetLastError());
		MessageBox(NULL, aError, "警告！", MB_ICONWARNING);
	}

	return false;
}

//=============================================================================
// 受信
//=============================================================================
bool CNetwork::DataRecv(SOCKETTYPE type, char *data, int nSize)
{
	int nError;
	char aError[256];

	switch (type)
	{
	case SOCKETTYPE_CLIENT:
		//クライアントへデータ(ID)送信
		nError = recv(m_sockClient, data, nSize, 0);
		break;
	case SOCKETTYPE_GAME:
		//クライアントへデータ(ID)送信
		nError = recv(m_sockClientToServer, data, nSize, 0);
		break;
	}

	if (nError < 0)
	{
		sprintf(aError, "受信エラー : %d\n", WSAGetLastError());
		MessageBox(NULL, aError, "警告！", MB_ICONWARNING);
		return false;
	}
	return false;
}

//=============================================================================
// クライアントソケットの作成
//=============================================================================
HRESULT CNetwork::Build(void)
{
	WSADATA wsaData;								//winsockの情報
	int nError;										//エラー取得

	//winsockの初期化
	nError = WSAStartup(MAKEWORD(2, 0), &wsaData);
	if (nError != 0)
	{
		switch (nError)
		{
		case WSASYSNOTREADY:
			MessageBox(NULL, "ネットワークサブシステムがネットワークへの接続を準備できていません!", "警告！", MB_ICONWARNING);
			return E_FAIL;
			break;
		case WSAVERNOTSUPPORTED:
			MessageBox(NULL, "要求されたwinsockのバージョンがサポートされていません！", "警告！", MB_ICONWARNING);
			return E_FAIL;
			break;
		case WSAEINPROGRESS:
			MessageBox(NULL, "ブロッキング操作の実行中であるか、 またはサービスプロバイダがコールバック関数を処理しています！", "警告！", MB_ICONWARNING);
			return E_FAIL;
			break;
		case WSAEPROCLIM:
			MessageBox(NULL, "winsockが処理できる最大プロセス数に達しました！", "警告！", MB_ICONWARNING);
			return E_FAIL;
			break;
		case WSAEFAULT:
			MessageBox(NULL, "第二引数であるlpWSAData は有効なポインタではありません！", "警告！", MB_ICONWARNING);
			return E_FAIL;
			break;
		}
	}

	// ソケット作成
	m_sockClient = socket(AF_INET, SOCK_STREAM, 0);

	if (m_sockClient == INVALID_SOCKET)
	{// ソケットの作成に失敗したとき
		char aError[64];
		sprintf(aError, "ソケットの生成に失敗!!\n エラーコード : %d", WSAGetLastError());
		MessageBox(NULL, aError, "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// ソケット作成
	m_sockClientToServer = socket(AF_INET, SOCK_DGRAM, 0);

	if (m_sockClientToServer == INVALID_SOCKET)
	{// ソケットの作成に失敗したとき
		char aError[64];
		sprintf(aError, "ソケットの生成に失敗!!\n エラーコード : %d", WSAGetLastError());
		MessageBox(NULL, aError, "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	//ソケットの設定
	m_addrServer.sin_family = AF_INET;
	m_addrServer.sin_port = htons(12345);
	m_addrServer.sin_addr.S_un.S_addr = inet_addr(aIp);

	bind(m_sockClientToServer, (struct sockaddr *)&m_addrServer, sizeof(m_addrServer));

	m_addrClientToServer.sin_family = AF_INET;
	m_addrClientToServer.sin_port = htons(10032);
	m_addrClientToServer.sin_addr.S_un.S_addr = inet_addr(aIp);

	// ソケット作成
	m_sockServerToClient = createServerSocket(nPort);

	return S_OK;
}

//=============================================================================
// コネクト
//=============================================================================
HRESULT CNetwork::Connect(void)
{
	int val = -1;
	char debug[256];

	//サーバに接続
	val = connect(m_sockClient, (struct sockaddr *)&m_addrServer, sizeof(m_addrServer));
	if (val == SOCKET_ERROR)
	{
		char aError[64];
		sprintf(aError, "ネットワークエラー!\nerror : %d\n", WSAGetLastError());
		MessageBox(NULL, aError, "警告!", MB_ICONWARNING);
		return E_FAIL;
	}

	SendTCP("LOAD_ID", sizeof("LOAD_ID"));
	DataRecv(SOCKETTYPE_CLIENT, (char*)&m_nId, sizeof(int));

	sprintf(debug, "ID = %d\n", m_nId);
	OutputDebugString(debug);
	OutputDebugString("サーバとの接続完了\n");
	return S_OK;
}

//=============================================================================
// キーデータ
//=============================================================================
bool CNetwork::KeyData(void)
{
	CKeyboard *pKeyboard = CManager::GetKeyboard();
	CRenderer *pRenderer = CManager::GetRenderer();
	CCamera *pCamera = pRenderer->GetCamera();
	CPlayer *pPlayer = CGame::GetPlayer(m_nId);
	PLAYERSTATE state;

	D3DXVECTOR3 pos = pPlayer->GetPos();

	if (pPlayer != NULL)
	{
		if (pCamera != NULL)
		{
			D3DXVECTOR3 rot = pCamera->GetRot();

			memset(&state, 0, sizeof(PLAYERSTATE));
			CNetwork *pNetwork = CManager::GetNetwork();

			if (pKeyboard != NULL)
			{
				if (pNetwork != NULL)
				{
					char data[1024];

					sprintf(data, "SAVE_KEY %d %d %d %d %d %d %f %f %f %f", m_nId, pKeyboard->GetKeyboardPress(DIK_W), pKeyboard->GetKeyboardPress(DIK_A),
						pKeyboard->GetKeyboardPress(DIK_S), pKeyboard->GetKeyboardPress(DIK_D), pKeyboard->GetKeyboardPress(DIK_SPACE),		// キー入力情報
						rot.y,						// 回転
						pos.x, pos.y, pos.z);		// 位置
					pNetwork->SendUDP(data, sizeof("SAVE_KEY") + 1024);
				}
			}
		}
	}

	return false;
}

//=============================================================================
// キーボードのプレス状態取得
//=============================================================================
bool CNetwork::GetPressKeyboard(int nId, int nKey)
{
	return m_aKeyState[nId][nKey];
}

//=============================================================================
// キーボードのトリガー状態取得
//=============================================================================
bool CNetwork::GetTriggerKeyboard(int nId, int nKey)
{
	return m_aKeyStateTrigger[nId][nKey];
}

//=============================================================================
// サーバーソケットを作成する
//=============================================================================
SOCKET CNetwork::createServerSocket(unsigned short port)
{
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == SOCKET_ERROR)
	{// ソケットの作成に失敗したとき
		char aError[64];
		sprintf(aError, "ソケットの生成に失敗!!\n エラーコード : %d", WSAGetLastError());
		MessageBox(NULL, aError, "警告！", MB_ICONWARNING);
		return sock;
	}

	struct sockaddr_in adr;

	adr.sin_family = AF_INET;
	adr.sin_port = htons(port);
	adr.sin_addr.S_un.S_addr = INADDR_ANY;  // サーバ側で割り当てられている IP を自動で設定

	if (SOCKET_ERROR == bind(sock, (struct sockaddr *)&adr, sizeof(adr)))
	{
		char aError[64];
		sprintf(aError, "ソケットの生成に失敗!!\n エラーコード : %d", WSAGetLastError());
		MessageBox(NULL, aError, "警告！", MB_ICONWARNING);
		return sock;
	}

	return sock;
}

//=============================================================================
// 形式変換(float)関数
//=============================================================================
void CNetwork::ConvertStringToFloat(char* text, const char* delimiter, float* pResult)
{
	char* tp;
	char* ctx;
	int nTemp = 1;

	tp = strtok_s(text, delimiter, &ctx);
	pResult[0] = (float)atof(tp);

	while (tp = strtok_s(NULL, ",", &ctx))
	{
		pResult[nTemp++] = (float)atof(tp);
	}
}

//=============================================================================
// 更新開始
//=============================================================================
void CNetwork::StartUpdate(void)
{
	if (!m_bUpdate)
	{// 更新フラグが折れていたとき
		// マルチスレッドにて更新開始
		m_bUpdate = true;								// 更新フラグを立てる
		m_th = std::thread(&CNetwork::Update, this);	// スレッドの作成
		m_th.detach();									// スレッドの管理を切り離す
	}
}

//=============================================================================
// 更新停止
//=============================================================================
void CNetwork::StopUpdate(void)
{
	if (m_bUpdate)
	{// 更新フラグが立っていた時
		m_bUpdate = false;
	}
}

//=============================================================================
// 2進数変換
//=============================================================================
int CNetwork::ConvertDecimalToBinary(int nValue) {
	int ans = 0;
	for (int nCount = 0; nValue > 0; nCount++)
	{
		ans = ans + (nValue % 2)*pow(10, nCount);
		nValue = nValue / 2;
	}
	return ans;
}