#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);

	int cnt;
	int nNum;
	int nNum2;
	float yPos;
	bool down;
	int temp;
	int tempY;

	cocos2d::Sprite *pRun;
	cocos2d::Sprite *pYpos;
	cocos2d::Sprite *pYpos2;
	cocos2d::Sprite *pYpos3;


	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	void Jump();
	void GetY();
	void GetY2();
	void GetY3();
	void CallJump(float f);
	void CallJump2(float f);

};

#endif // __HELLOWORLD_SCENE_H__