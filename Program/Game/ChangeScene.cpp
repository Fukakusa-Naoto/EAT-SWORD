//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ChangeScene.cpp
//!
//! @brief  シーン切り替え関連のソースファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "ChangeScene.h"
#include "SceneLogo.h"
#include "SceneTitle.h"
#include "SceneSelect.h"
#include "ScenePlaying.h"


// データ型の定義 ==========================================================




// 定数の定義 ==============================================================




// グローバル変数の定義 ====================================================




// 関数のプロトタイプ宣言 ==================================================




// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief シーン別の初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeScene(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//シーンの切り替え
	switch (g_currentSceneId)
	{
	case SCENE_LOGO:	//ロゴ
		InitializeLogo();
		break;
	case SCENE_TITLE:	//タイトル
		InitializeTitle();
		break;
	case SCENE_SELECT:	//ステージ選択
		InitializeSelect();
		break;
	case SCENE_PLAYING:	//プレイ
		InitializePlaying();
		break;
	default:

		break;
	}

}



//----------------------------------------------------------------------
//! @brief シーン別の更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateScene(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//シーンの切り替え
	switch (g_currentSceneId)
	{
	case SCENE_LOGO:	//ロゴ
		UpdateLogo();
		break;
	case SCENE_TITLE:	//タイトル
		UpdateTitle();
		break;
	case SCENE_SELECT:	//ステージ選択
		UpdateSelect();
		break;
	case SCENE_PLAYING:	//プレイ
		UpdatePlaying();
		break;
	default:

		break;
	}

}



//----------------------------------------------------------------------
//! @brief シーン別の描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderScene(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//シーンの切り替え
	switch (g_currentSceneId)
	{
	case SCENE_LOGO:	//ロゴ
		RenderLogo();
		break;
	case SCENE_TITLE:	//タイトル
		RenderTitle();
		break;
	case SCENE_SELECT:	//ステージ選択
		RenderSelect();
		break;
	case SCENE_PLAYING:	//プレイ
		RenderPlaying();
		break;
	default:

		break;
	}

}



//----------------------------------------------------------------------
//! @brief シーン別の終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeScene(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//シーンの切り替え
	switch (g_currentSceneId)
	{
	case SCENE_LOGO:	//ロゴ
		FinalizeLogo();
		break;
	case SCENE_TITLE:	//タイトル
		FinalizeTitle();
		break;
	case SCENE_SELECT:	//ステージ選択
		FinalizeSelect();
		break;
	case SCENE_PLAYING:	//プレイ
		FinalizePlaying();
		break;
	default:

		break;
	}

}