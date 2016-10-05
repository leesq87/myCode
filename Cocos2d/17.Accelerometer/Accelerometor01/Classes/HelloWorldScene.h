#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	~HelloWorld(void);
	virtual void onEnter();
	void onAcceleration(Acceleration* acc, Event* event);

	cocos2d::Sprite* m_pBall;
	cocos2d::Size winSize;

};

#endif // __HELLOWORLD_SCENE_H__
