#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameMainScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene(){
    auto scene = Scene::create();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init(){

    // 初期化
    if ( !Layer::init() ){
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    text = Label::createWithSystemFont("エンターでゲームスタート", "Arial", 20);
    text->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height / 2 + origin.y ));
    addChild(text, 1);

    // キーバインディング
    keyBinding();

    return true;
}

/* キーバインディング */
void HelloWorld::keyBinding(){
    auto listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event){
        if( keyCode == EventKeyboard::KeyCode::KEY_ENTER ){
            changeScene();
        }

        if( keyCode == EventKeyboard::KeyCode::KEY_ESCAPE ){
            endGame();
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

/* シーン切り替え */
void HelloWorld::changeScene(){
    auto scene = GameMain::createScene();
    // TransitionFade* fade = TransitionFade::create(0.5f, scene, Color3B::WHITE);
    Director::getInstance()->replaceScene(scene);
}

/* ゲーム終了 */
void HelloWorld::endGame(){
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
