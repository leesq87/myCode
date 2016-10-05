#ifndef __TEST_SCENE3_H__
#define __TEST_SCENE3_H__

#include "cocos2d.h"


class TestScene3 : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TestScene3);
	void doClose(Ref *pSender);

};

#endif // __HELLOWORLD_SCENE_H__
