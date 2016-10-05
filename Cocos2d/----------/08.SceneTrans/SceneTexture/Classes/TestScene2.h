#ifndef __TEST_SCENE2_H__
#define __TEST_SCENE2_H__

#include "cocos2d.h"

class TestScene2 : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TestScene2);

	void doClose(Ref *pSender);
	void doSoundAction(Ref *pSender);

};

#endif // __HELLOWORLD_SCENE_H__
