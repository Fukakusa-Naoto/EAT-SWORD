//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateUI.h
//!
//! @brief UI関連のヘッダファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once




// データ型の定義 ==========================================================





// 定数の定義 ==============================================================





// グローバル変数の定義 ====================================================





// 関数の宣言 ==============================================================

// UIの初期化処理
void InitializeUI(void);

// HPゲージの描画
void DrawHPGauge(float x, float y, float width, float height, int max, int now);

// 時間の描画
void DrawTimer(float x, float y, int time, HGRP handle[], Type type);

// 顎の描画
void DrawJaw(float x, float y, float width, float height, float spece, HGRP upperHandle, HGRP lowerHandle);

// テキストボックスの描画
void DrawTextBox(float x, float y, float width, float height, char *text);
