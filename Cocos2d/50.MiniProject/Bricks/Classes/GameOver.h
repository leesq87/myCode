#ifndef __BrickEx__GameOver__
#define __BrickEx__GameOver__

#include "cocos2d.h"

using namespace cocos2d;

class GameOver : public cocos2d::Layer {
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(GameOver);
	
	void doClose(Ref* pSender);

};

#endif