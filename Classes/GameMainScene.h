#ifndef __GAMEMAIN_SCENE_H__
#define __GAMEMAIN_SCENE_H__

#include "cocos2d.h"

class GameMain : public cocos2d::Layer
{
private:
    // 変数
    bool initFlag;
    std::chrono::high_resolution_clock::time_point startCount;
    cocos2d::Sprite *note;

    bool main();
    void graph();
    void keyBinding();
    void updateGameCount(float delta);

    // イベント・ドリブン
    void changeScene();
    void endGame();
    void drawNote();
    void judgeTiming();

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    CREATE_FUNC(GameMain);
};





#endif // __GAMEMAIN_SCENE_H__
