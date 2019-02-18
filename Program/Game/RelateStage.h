//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateStage.h
//!
//! @brief  ステージ関連のヘッダファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once




// データ型の定義 ==========================================================

// StageAnimation型 --------------------------------------------------------
struct Tag_StageAnimation
{
	Vec2D pos;
	Image image;
	Animation animation;
};
typedef struct Tag_StageAnimation StageAnimation;


// 定数の定義 ==============================================================

// <ステージのサイズ>
// 幅
#define STAGE_WIDTH (210)
// 高さ
#define STAGE_HEIGHT (15)
// チップサイズ
#define STAGE_SIZE (32)

//ステージの最大数
#define MAX_STAGE (7)

//マップチップの最大数
#define MAX_STAGECHIP (3150)


// <地形条件> ---------------------------------------------------------
// 地面
#define GRAND_LINE (400)

// 重力加速度
#define GRAVITY (4.9f)

// 最大落下速度
#define MAX_FALL_SPEED (10.0f)


// グローバル変数の定義 ====================================================

// ステージデータ
extern int g_stageData[STAGE_HEIGHT][STAGE_WIDTH];

extern ObjectStage g_objectStage[MAX_STAGECHIP];

// ステージID
extern int g_stageId;

// 使用中のステージオブジェクトの数
extern int g_stageObjectNumber;

//アニメーション
extern StageAnimation g_stageAnimation[100];

// 関数の宣言 ==============================================================

// ステージの初期化処理
void InitializeStage(void);

// ステージの更新処理
void UpdateStage(void);

// ステージの描画処理
void RendarStage(void);

// ステージオブジェクトの生成
void CreateStageObject(ObjectStage *stageObject, float posX, float posY, int type);
