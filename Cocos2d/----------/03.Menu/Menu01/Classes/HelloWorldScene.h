#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	void doClick1(Ref *pSender);
	void doClick2(Ref *pSender);
	void doClick3(Ref *pSender);

};

#endif // __HELLOWORLD_SCENE_H__
