#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

using namespace cocos2d;

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	virtual void onEnter();
	void updateMinimap(float f);
	
	LayerColor* gameLayer;
	LayerColor* menuLayer;

	RenderTexture* miniMap;
	
};

#endif // __HELLOWORLD_SCENE_H__
