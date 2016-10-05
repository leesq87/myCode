#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"

#define PTM_RATIO 32

USING_NS_CC;


class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	~HelloWorld();
	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(Touch* touch, Event* event);
	void tick(float dt);
	void addNewSpriteAtPosition(Vec2 location);

	Size winSize;
	Texture2D* texture;
	b2World* _world;

};

#endif // __HELLOWORLD_SCENE_H__
