#include "GameScene.h"
#include "Definition.h"
#include "LAVEL2.h"
#include "Keyboard.h"
#include "cocostudio/SimpleAudioEngine.h"

/////////////////////////
#include "cocos2d.h"



using namespace CocosDenshion;

USING_NS_CC;

Scene* GameScene::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
   


    // 'layer' is an autorelease object
    auto layer = GameScene::create();


    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
/////////////////////////////////////////

void GameScene::physique1(cocos2d::Sprite* sprite)
{
    auto BODY= PhysicsBody::createCircle(sprite->getContentSize().width / 2);
    BODY->setContactTestBitmask(true);
    BODY->setDynamic (true);
    sprite->setPhysicsBody(BODY);
}

/////////////////////////////////////////

// on "init" you need to initialize your instance
bool GameScene::init()
{
    
        // 1. super init first
    if (!Layer::init())
    {

        return false;
    }
   /////////////////////

    
   // ///////////////////
    // Récupère la taille de la fenêtre ou de l'écran actuellement affichée
    Size visibleSize = Director::getInstance()->getVisibleSize();

    // Récupère le point d'origine de la zone visible dans le système de coordonnées du noeud parent
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////////////////////////////////////
     auto audio = SimpleAudioEngine::getInstance();

// set the background music and continuously play it.
    audio->playBackgroundMusic("05Flying.mp3", true);
    audio->playBackgroundMusic("05Flying.mp3", false);

   
    auto background = Sprite::create("white.png");
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2;
    background->setPosition(Vec2(x, y));
    this->addChild(background);

    //////////////////////////////////////////////////////////
    auto floor = Sprite::create("Floorcopie.png");

    // set the initial position of the floor
    floor->setPosition(Vec2(450, 0));

    // add the floor to the scene
    this->addChild(floor);

    ////////////////////////////////

    auto titre = Sprite::create("title.png");
    titre->setPosition(Vec2(470, 480));
    this->addChild(titre);
    /////////////////////////////////////////
   auto mer = Sprite::create("mer.png");
    mer->setPosition(Vec2(460, 97));
    this->addChild(mer);



    ///////////////////////////////////////////////////////
    auto porte = Sprite::create("door.png");
    porte->setPosition(Vec2(900, 96));
    this->addChild(porte);
   
    /////////////////////////////////////////////////////////
    KEY = Sprite::create("key.PNG");
    KEY->setPosition(Vec2(730, 250));
    this->addChild(KEY);
    physique1(KEY);
    //////////////////////////////////////////////////////
   cat = Sprite::create("0_stand1.png");
    cat->setPosition(Vec2(90, 100));
    this->addChild(cat);
      physique1(cat);
    ///////////////////////////////////////
      auto contactListener = EventListenerPhysicsContact::create();
      contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
      this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
  
    /// ///////////////////////////////////////////////////////////////////////
    auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event)
    {


        Vec2 loc = event->getCurrentTarget()->getPosition();
        switch (keyCode)
        {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            event->getCurrentTarget()->runAction(MoveBy::create(0.5, Point(-20, 0)));
            // event->getCurrentTarget()->setPosition(loc.x-20, loc.y);
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            event->getCurrentTarget()->runAction(JumpBy::create(0.5, Point(297, 0), 80, 1));
            // event->getCurrentTarget()->setPosition(loc.x,loc.y+20);
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            event->getCurrentTarget()->runAction(MoveBy::create(0.5, Point(20, 0)));

            //event->getCurrentTarget()->runAction(RotateBy::create(2,90));
            break;
        case EventKeyboard::KeyCode::KEY_K:
            //if (event->getCurrentTarget()->getPosition().y==90)
            event->getCurrentTarget()->runAction(JumpBy::create(0.5, Point(0, 0), 100, 1));

            break;
        };
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, cat);
    ////////////////////////////////////////////////////////////////COLLISION
    auto playItem = MenuItemImage::create("level2.png", "startvert.png", CC_CALLBACK_1(GameScene::GoToLEVEL2, this));

    playItem->setPosition(Point(900, 480));


    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);
  

    return true;
}

bool GameScene::onContactBegin(PhysicsContact& contact)
{


    auto nodeB = contact.getShapeB()->getBody()->getNode();
    nodeB->removeFromParent();
    //_director->replaceScene(TransitionFade::create(5.0, LEVEL2::createScene()));


    // mySprite->runAction(MoveBy::create(2.0, Point(-200, 200)));
    return true;
}
void GameScene::GoToLEVEL2(cocos2d::Ref* sender)
{
    auto scene = LEVEL2::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////



















