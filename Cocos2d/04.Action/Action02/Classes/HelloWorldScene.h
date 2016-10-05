#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
   
    CREATE_FUNC(HelloWorld);

	cocos2d::Sprite *pMan;
	void doAction(Ref * pSender);
	void ActionSequence(Ref *pSender);
	void ActionSpawn(Ref *pSender);
	void ActionReverse(Ref * pSender);
	void ActionRepeat(Ref *pSender);
	void ActionRepeatForever(Ref *pSender);
	void ActionDelayTime(Ref *pSender);

};

#endif // __HELLOWORLD_SCENE_H__
