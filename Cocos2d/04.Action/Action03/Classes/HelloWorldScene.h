#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	cocos2d::Sprite* pBall;
	cocos2d::Sprite* pMan;
	cocos2d::Sprite* pWomen1;
	cocos2d::Sprite* pWomen2;

	void doAction(Ref* pSender);
	void doActionReset();

};

#endif // __HELLOWORLD_SCENE_H__
