#ifndef __LEVEL_3__
#define __LEVEL_3__

#include "cocos2d.h"

class LEVEL3: public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
   

    // implement the "static create()" method manually
    CREATE_FUNC(LEVEL3);
private:
    cocos2d::Sprite* cat;
    cocos2d::Vector<cocos2d::Sprite*> bombes;
    
    void BOMBE(float dt);
    void physique2(cocos2d::Sprite* sprite);
    
};

#endif // __LEVEL_3__