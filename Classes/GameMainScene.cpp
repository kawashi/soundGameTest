#include "SimpleAudioEngine.h"
#include "GameMainScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* GameMain::createScene(){
    auto scene = Scene::create();
    auto layer = GameMain::create();
    scene->addChild(layer);

    return scene;
}

/* シーンが変わって最初に実行される関数 */
bool GameMain::init(){
    // 初期化
    if ( !Layer::init() ) return false;

    // ゲームカウント取得
    startCount = std::chrono::high_resolution_clock::now();

    return main();
}

/* メイン処理 */
bool GameMain::main(){
    graph();
    keyBinding();
    this->schedule(schedule_selector(GameMain::updateGameCount), 0.01);

    return true;
}

/* 描画処理 */
void GameMain::graph(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // ゲームカウントとか説明とかイベントドリブンではないものを表示
}

/* キーを対応づけする */
void GameMain::keyBinding(){
    auto listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = [&](cocos2d::EventKeyboard::KeyCode keyCode, Event* event){
        if( keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ){
            endGame();
        }
        if( keyCode == EventKeyboard::KeyCode::KEY_ENTER ){
            changeScene();
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

/* タイトル画面へ戻る */
void GameMain::changeScene(){
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(scene);
}

/* 終了処理 */
void GameMain::endGame(){
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

/* 1ms ごとに表示 */
void GameMain::updateGameCount(float delta){
    auto nowCount  = std::chrono::high_resolution_clock::now();
    int  gameCount = (nowCount - startCount).count() / 1000 / 1000 / 1000;

    if(gameCount == 2) drawNote();
}

/* ノーツ描画 */
void GameMain::drawNote(){
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    static bool doneFlag = false;

    // 一度だけ実行する
    if(!doneFlag){
        // ノーツ画像描画
        auto note = Sprite::create("res/img/note.png");
        note->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        this->addChild(note, 1);

        doneFlag = true;
    }

}
