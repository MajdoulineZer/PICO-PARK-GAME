#include "LEVEL3.h"

#include "Definition.h"

#include "Keyboard.h"


USING_NS_CC;

Scene* LEVEL3::createScene()
{
	// autorisation d'object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));

	// 'layer' is an autorelease object


	auto layer = LEVEL3::create();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);


	// add layer as a child to scene

	scene->addChild(layer);


	// return the scene
	return scene;
}

void LEVEL3::physique2(cocos2d::Sprite* sprite)
{
	auto cuerpo = PhysicsBody::createCircle(sprite->getContentSize().width / 7);
	cuerpo->setContactTestBitmask(true);
	cuerpo->setDynamic(true);
	sprite->setPhysicsBody(cuerpo);
}

void LEVEL3::BOMBE(float dt)
{
	auto director = Director::getInstance();
	auto taille= director->getWinSize();
	Sprite* bombe= nullptr;
	for (int i = 0; i < 3; i++)
	{
		bombe= Sprite::create("dang.png");
		bombe->setAnchorPoint(Vec2::ZERO);
		bombe->setPosition(CCRANDOM_0_1() * taille.width, taille.height);
		physique2(bombe);
		bombe->getPhysicsBody()->setVelocity(Vect(0, ((CCRANDOM_0_1() + 0.2f) * -250)));
		bombes.pushBack(bombe);
		this->addChild(bombe, 1);
	}
}

// on "init" you need to initialize your instance

bool LEVEL3::init()
{
	
	// 1.init 

	if (!Layer::init())
	{
		return false;
	}
 ///////////////////////////////////////////////////////////////
    

   
    /////////////////////////////////////////////////////////////
	auto director = Director::getInstance();
	auto taille = director->getWinSize();
	auto background= Sprite::create("arriere.png");
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(0, 0);
	addChild(background, 0);
	cat = Sprite::create("0_stand1.png");
	cat->setPosition(taille.width / 2,taille.height * 0.23);

	physique2(cat);
	addChild(cat, 1);
	
	schedule(CC_SCHEDULE_SELECTOR(LEVEL3::BOMBE), 5.0f);
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
    
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            event->getCurrentTarget()->runAction(MoveBy::create(0.5, Point(20, 0)));

            //event->getCurrentTarget()->runAction(RotateBy::create(2,90));
            break;
       
        };
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, cat);


	return true;
}

