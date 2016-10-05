﻿#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	cocos2d::Sprite *pMan;

	void doAction(Ref *pSender);

	void callback1();
	void callback2(Node* sender);
	void callback3(Node* sender, long data);
};

#endif // __HELLOWORLD_SCENE_H__