#pragma once
#include "SceneBase.h"

class SceneManager
{
public:

private:
    static SceneManager* instance;
    SceneBase* current_scene;   //現在シーン情報のポインタ

    int score = 0; // スコアを保存する変数

public:
    SceneManager();
    ~SceneManager();

    // コピー禁止
    SceneManager(const SceneManager&) = delete;
    SceneManager& operator=(const SceneManager&) = delete;

    //インスタンス取得する処理
    static SceneManager* GetInstance();
    //インスタンスの削除
    static void DeleteInstance();

    void Initialize();  //初期化処理
    void Update();      //更新処理
    void Finalize();    //終了時処理

    SceneBase* GetCurrentScene() const;

    void SetScore(int _score) { score = _score; }
    int GetScore() const { return score; }

private:
    void Draw() const;  //描画処理

    //シーン切替処理
    void ChangeScene(eSceneType type);

    //シーン生成処理
    SceneBase* CreateScene(eSceneType type);
};

