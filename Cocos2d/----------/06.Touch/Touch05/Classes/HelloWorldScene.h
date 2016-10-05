#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	cocos2d::EventListenerCustom *_listener1;
	cocos2d::EventListenerCustom *_listener2;
	cocos2d::LabelTTF *statusLabel;

	virtual void onEnter();
	virtual void onExit();
	void doClick1(cocos2d::Ref *pSender);
	void doClick2(cocos2d::Ref *pSender);
	void doEvent1(cocos2d::EventCustom *event);
	void doEvent2(cocos2d::EventCustom *event);

};

#endif // __HELLOWORLD_SCENE_H__
