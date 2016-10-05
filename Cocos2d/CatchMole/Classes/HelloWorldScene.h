#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);
	bool underMole1;
	bool underMole2;
	bool underMole3;

	cocos2d::Sprite *grassLower;
	cocos2d::Sprite *grassUpper;
	cocos2d::Sprite *mole1;
	cocos2d::Sprite *mole2;
	cocos2d::Sprite *mole3;

	void callMole1();
	void callMole2();
	void callMole3();

	int RandomNumCreate();
	void callRandomNum(float f);



	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
//	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
//	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
//	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);


};

#endif // __HELLOWORLD_SCENE_H__
