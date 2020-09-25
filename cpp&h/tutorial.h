//=============================================================================
//
// チュートリアルの処理 [tutorial.h]
// Author : Ryouma Inoue
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"
#include "lake.h"
#include "floor.h"
#include "meshobit.h"
#include "meshdome.h"
#include "meshsphere.h"
#include "meshwall.h"
#include "3Deffect.h"
#include "bgdome.h"
#include "camera.h"
#include "3Dparticle.h"
#include "keyboard.h"
#include "3Dmap.h"
#include "item.h"
#include "thunder.h"

//=============================================================================
// 前方宣言	( ポインタだけなら使える )
//=============================================================================

//=============================================================================
// 管理クラス
//=============================================================================
class CTutorial
{
public:

	CTutorial();													// コンストラクタ
	~CTutorial();													// デストラクタ

	HRESULT Init();												// 初期化
	void	Uninit(void);										// 終了
	void	Update(void);										// 更新
	void	Draw(void);											// 描画

	static  CTutorial		*Create(void);						// チュートリアルの生成

private:
	void PopEvent(void);
	// チュートリアル説明文の生成処理
	void Create_Tutorial_Explan(void);
	int nCntPop;
};
#endif
