#include "LAVEL2.h"
#include "Definition.h"
#include "LEVEL3.h"
#include "Keyboard.h"


USING_NS_CC;

Scene* LEVEL2::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);



    // 'layer' is an autorelease object
    auto layer = LEVEL2::create();


    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
////////////////////////////////////////
void LEVEL2::physique1(cocos2d::Sprite* sprite)
{
    auto BODY = PhysicsBody::createCircle(sprite->getContentSize().width / 15);
    BODY->setContactTestBitmask(true);
    BODY->setDynamic(true);
    sprite->setPhysicsBody(BODY);
}
////////////////////////////////////////////

// on "init" you need to initialize your instance
bool LEVEL2::init()
{
    //////////////////////////////
    
        // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    // Récupère la taille de la fenêtre ou de l'écran actuellement affichée
    Size visibleSize = Director::getInstance()->getVisibleSize();

    // Récupère le point d'origine de la zone visible dans le système de coordonnées du noeud parent
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    ///////////////////////////////////////////////////////////////
   

// set the background music and continuously play it.
   
   
    /////////////////////////////////////////////////////////////
    auto background1 = Sprite::create("white.png");
    float x = origin.x + visibleSize.width / 2;
    float y = origin.y + visibleSize.height / 2;
    background1->setPosition(Vec2(x, y));
    this->addChild(background1);
    //////////////////////////////////////////////////////////
    auto floor2 = Sprite::create("floor2.png");
    floor2->setPosition(Vec2(500, 290));
    this->addChild(floor2);
    // update the position of the floor as the player moves
    ////////////////////////////////
    auto obstacle1 = Sprite::create("dang.png");
    obstacle1->setPosition(Vec2(430,210));
    this->addChild(obstacle1);
    physique1(obstacle1);

    auto obstacle2 = Sprite::create("dang.png");
    obstacle2->setPosition(Vec2(570, 210));
    this->addChild(obstacle2);
    physique1(obstacle2);

    auto obstacle3 = Sprite::create("dang.png");
    obstacle3->setPosition(Vec2(710, 210));
    this->addChild(obstacle3);
    physique1(obstacle3);
    
    ////////////////////////////////////////////
    
   
    /////////////////////////////////////
    auto titre = Sprite::create("title.png");
    titre->setPosition(Vec2(470, 480));
    this->addChild(titre);
    ///////////////////////////////////////////////////////
    auto door = Sprite::create("door.png");
    door->setPosition(Vec2(940, 220));
    this->addChild(door);
    ////////////////////////////////////////////////////
    auto cat = Sprite::create("0_stand1.png");
    cat->setPosition(Vec2(45, 90));
    this->addChild(cat);
    physique1(cat);
    ///////////////////////////////////////////////////
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(LEVEL2::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

    ///////////////////////////////////////////////////
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
            event->getCurrentTarget()->runAction(JumpBy::create(0.5, Point(90, 47), 80, 1));
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
        case EventKeyboard::KeyCode::KEY_O:
            event->getCurrentTarget()->runAction(JumpBy::create(0.5, Point(140, 0), 80, 1));
            // event->getCurrentTarget()->setPosition(loc.x,loc.y+20);
            break;
        };
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, cat);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    auto playItem = MenuItemImage::create("level3 (3).png", "startvert.png", CC_CALLBACK_1(LEVEL2::GoToLEVEL3, this));

    playItem->setPosition(Point(1000, 480));
    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);

    this->addChild(menu);

 return true;
}
bool LEVEL2::onContactBegin(PhysicsContact& contact)
{
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    //nodeB->removeFromParent();
    _director->replaceScene(TransitionFade::create(5.0, LEVEL2::createScene()));


    //cat->runAction(MoveBy::create(2.0, Point(-200, 200)));
    return true;
}

void LEVEL2::GoToLEVEL3(cocos2d::Ref* sender)
{
    auto scene = LEVEL3::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}
