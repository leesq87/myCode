#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	int nIndex1 = 0;

    CREATE_FUNC(HelloWorld);

	void doPushScene(Ref *pSender);
	void doPushSceneTran(Ref *pSender);
	void doReplaceScene(Ref *pSender);
	void doReplaceSceneTran(Ref *pSender);

	cocos2d::TransitionScene* createTransition(int nIndex, float t, cocos2d::Scene* s);



};

#endif // __HELLOWORLD_SCENE_H__
