#pragma once
#include "../SceneBase.h"
class HelpScene :
    public SceneBase
{
private:
	//シーンに必要な変数を定義
	int page; //現在のページ (1 or 2)
	int cursor;

	//アイテム画像
	int apple_image;
	int	rock_image;
	int bomb_image;
	int	heal_image;
	int	power_image;

	int help_image;

public:
	HelpScene();
	~HelpScene();

	void Initialize() override;		//初期化処理
	eSceneType Update() override;	//更新処理
	void Draw() const override;		//描画処理
	void Finalize() override;		//終了時処理

	eSceneType GetNowSceneType()const override;

public:
	//必要に応じて追加する関数をここに定義
	void DrawDPad()const;
};

