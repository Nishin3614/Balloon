// ------------------------------------------
//
// ネットワーク処理 [network.cpp]
// Author : masayasu wakita
//
// ------------------------------------------
#include "network.h"
#include "keyboard.h"

// ------------------------------------------
// 静的メンバ変数
// ------------------------------------------
char CNetwork::aIp[32] = {};
int CNetwork::nPort = 0;

// ------------------------------------------
// コンストラクタ
// ------------------------------------------
CNetwork::CNetwork()
{

}

// ------------------------------------------
// デストラクタ
// ------------------------------------------
CNetwork::~CNetwork()
{

}

// ------------------------------------------
// 初期化
// ------------------------------------------
HRESULT CNetwork::Init(HINSTANCE hInstance, HWND hWnd)
{
	HRESULT hr;

	hr = Build();					// ソケットの生成
	OutputDebugString("クライアント構築完了\n");

	return hr;
}

// ------------------------------------------
// 終了
// ------------------------------------------
void CNetwork::Uninit(void)
{
	//ソケット(クライアント)の開放
	closesocket(m_sockClient);
}

// ------------------------------------------
// 更新
// ------------------------------------------
void CNetwork::Update(void)
{
	//send(m_sockClient, "LOAD", sizeof("LOAD"), 0);
	//recv(m_sockClient, (char*)&keystate, sizeof(KEYSTATE), 0);
}

// ------------------------------------------
// ネットワークの設定データ読み込み
// ------------------------------------------
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

// ------------------------------------------
// キーボードの入力状態の取得
// -----------------------------------------
KEYSTATE CNetwork::GetKeystate(void)
{
	return keystate;
}

// ------------------------------------------
// クライアントソケットの作成
// -----------------------------------------
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

	//ソケットの設定
	m_addrServer.sin_family = AF_INET;
	m_addrServer.sin_port = htons(nPort);
	m_addrServer.sin_addr.S_un.S_addr = inet_addr(aIp);
	return S_OK;
}

// ------------------------------------------
// コネクト
// ------------------------------------------
HRESULT CNetwork::Connect(void)
{
	int val = -1;

	//サーバに接続
	val = connect(m_sockClient, (struct sockaddr *)&m_addrServer, sizeof(m_addrServer));
	if (val == SOCKET_ERROR)
	{
		char aError[64];
		sprintf(aError, "ネットワークエラー!\nerror : %d\n", WSAGetLastError());
		MessageBox(NULL, aError, "警告!", MB_ICONWARNING);
		return E_FAIL;
	}

	OutputDebugString("サーバとの接続完了\n");
	return S_OK;
}