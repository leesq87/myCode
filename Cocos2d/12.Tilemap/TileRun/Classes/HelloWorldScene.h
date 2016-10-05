#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	cocos2d::Size winSize;


	cocos2d::Sprite* pWoman;
	cocos2d::TMXTiledMap* tMap;
	cocos2d::TMXLayer* background;
	cocos2d::TMXLayer* MetaInfo;

	cocos2d::TMXTiledMap* tMap2;
	cocos2d::TMXLayer* background2;
	cocos2d::TMXLayer* MetaInfo2;

	void moveGround();
	void check(float f);

};

#endif // __HELLOWORLD_SCENE_H__
