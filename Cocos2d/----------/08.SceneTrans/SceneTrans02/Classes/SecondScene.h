#ifndef __SceneTrans1__SecondScene__
#define __SceneTrans1__SecondScene__

#include "cocos2d.h"

class SecondScene : public cocos2d::LayerColor {
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(SecondScene);
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExitTransitionDidStart();
	virtual void onExit();
	~SecondScene(void);
	void doClose(Ref *pSender);
};

#endif // __SceneTrans1__SecondScene__
