#ifndef __PopupTouchEx__SecondScene__
#define __PopupTouchEx__SecondScene__

#include "cocos2d.h"

using namespace cocos2d;

class SecondScene : public cocos2d::LayerColor {
public :
	static cocos2d::Scene* createScene();

	virtual bool init();
	CREATE_FUNC(SecondScene);

	void doSendMsg(Ref* pSender);
	void coClose(Ref* pSender);

};

#endif
