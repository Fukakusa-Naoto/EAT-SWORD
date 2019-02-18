//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  ゲーム関連のヘッダファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once




// 列挙体の定義 ============================================================

// <ゲームに必要なシーンのIDを登録> -----------------------------------
enum tag_SceneId
{
	SCENE_NONE,		//なし
	SCENE_LOGO,		//ロゴ
	SCENE_TITLE,	//タイトル
	SCENE_SELECT,	//ステージ選択
	SCENE_PLAYING,	//プレイ

};
typedef enum tag_SceneId SceneId;

// <動作リスト>--------------------------------------------------------
enum Tag_Action
{
	RUN,		//走る
	EAT,		//食べる
	SWING,		//剣を振る
	FLYING,		//飛行
	GLUTTONY	//暴食
};
typedef enum Tag_Action Action;

// <タイプ>------------------------------------------------------------
enum Tag_Type
{
	NONE,	//なし
	NORMAL,	//ノーマル
	SWORD,	//ソード
	FIRE,	//ファイア
	FLY,	//フライ
	BIG		//ビッグ
};
typedef enum Tag_Type Type;


// データ型の定義 ==========================================================

// <Vec2D型> ----------------------------------------------------------
struct Tag_Vec2D
{
	float x;	//x成分
	float y;	//y成分
};
typedef struct Tag_Vec2D Vec2D;

// <Size型> -----------------------------------------------------------
struct Tag_Size
{
	int width;	//幅
	int height;	//高さ
};
typedef struct Tag_Size Size;

// <Image型> ----------------------------------------------------------
struct Tag_Image
{
	HGRP handle[100];		//グラフィックハンドル
	float extRate;			//拡大率
	float angle;			//角度
};
typedef struct Tag_Image Image;

// <Animation型> -----------------------------------------------------
struct Tag_Animation
{
	int numFrames;		// アニメーションの総フレーム数
	int frameDuration;	// 1フレームを表示する時間
	int frameNum;		// 現在のフレーム番号
	int elapsedTime;	// 現在のフレームの表示時間
	int state;			//アニメーションの状態
};
typedef struct Tag_Animation Animation;

// <BackGround型> ----------------------------------------------------
struct Tag_BackGround
{
	Vec2D pos;		//座標
	HGRP handle;	//グラフィックハンドル
};
typedef struct Tag_BackGround BackGround;

// <ObjectPlayer型> ---------------------------------------------------
struct Tag_ObjectPlayer
{
	Vec2D pos;					//座標
	Vec2D dataPos;				//データ上の座標
	Vec2D vel;					//速度
	Image image[10];			//画像
	Animation animation[10];	//アニメーション
	Action action;				//動作
	BOOL turn;					//反転
	int state;					//状態
	Type type;					//タイプ
	int count;					//特殊能力の使用時間
	int hp;						//体力
};
typedef struct Tag_ObjectPlayer ObjectPlayer;

// <ObjectEnemy型> ----------------------------------------------------
struct Tag_ObjectEnemy
{
	Vec2D pos;					//座標
	Vec2D vel;					//速度
	HGRP image;					//画像
	float extRate;				//拡大率
	float angle;				//角度
	int state;					//状態
	Type type;					//タイプ
	int actionInterval;			//動作の間隔
};
typedef struct Tag_ObjectEnemy ObjectEnemy;

// <ObjectStage型> ----------------------------------------------------
struct Tag_ObjectStage
{
	Vec2D pos;		//座標
	int state;		//状態
	int type;		//タイプ
};
typedef struct Tag_ObjectStage ObjectStage;

// <ObjectJaw型> ------------------------------------------------------
struct Tag_ObjectJaw
{
	Vec2D pos;	//座標
	Size size;	//サイズ
	float space;	//スペース
};
typedef struct Tag_ObjectJaw ObjectJaw;


// 定数の定義 ==============================================================

// <システム> ----------------------------------------------------------
#define GAME_TITLE "EAT SWORD"        // ゲームタイトル


// <画面> --------------------------------------------------------------
#define SCREEN_WIDTH    (640)                  // 画面の幅[pixel]
#define SCREEN_HEIGHT   (480)                  // 画面の高さ[pixel]

#define SCREEN_TOP      (0)                    // 画面の上端
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // 画面の下端
#define SCREEN_LEFT     (0)                    // 画面の左端
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // 画面の右端

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // 画面の中央(X座標)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // 画面の中央(Y座標)


// <デバッグ> ---------------------------------------------------------
#define DEBUG (0)		// 0 : デバッグ情報なし
						// 1 : デバッグ情報あり


// グローバル変数の定義 ====================================================

// <シーン管理> -------------------------------------------------------
extern SceneId g_currentSceneId;	//現在のシーンのID

// <キーの入力状態> ---------------------------------------------------
extern int g_currentInputState;	//現在
extern int g_lastInputState;	//前回


// 関数の宣言 ==============================================================

// ゲームの初期化処理
void InitializeGame(void);

// ゲームの更新処理
void UpdateGame(void);

// ゲームの描画処理
void RenderGame(void);

// ゲームの終了処理
void FinalizeGame(void);

//シーンの切り替え
void ChangeScene(SceneId nextSceneId);
