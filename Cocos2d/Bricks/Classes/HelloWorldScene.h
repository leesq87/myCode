#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	//스프라이트용 객체 변수들
	Texture2D* texture;
	Sprite*	 ball;
	Sprite* paddle;
	Vector<Sprite*> targets;

	//벽돌 숫자 조정용
	int BRICKS_HEIGHT;
	int BRICKS_WIDTH;

	//게임이 진행 중인지 체크하기 위한 변수
	bool isPlaying;

	//패들이 터치됐는지 체크하기위한 변수
	bool isPaddleTouched;
	//공의 움직임을 저장하기 위한 변수
	Vec2 ballMovement;

	~HelloWorld();
	virtual void onEnter();
	//virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);

	void initializeBricks();
	void initializeBall();
	void initializepaddle();
	void startGame(float dt);
	void gameLogic(float dt);
	void processCollision(cocos2d::Sprite* brick);

	void onAcceleration(Acceleration* acc, Event* event);
	Size winSize;

};

#endif // __HELLOWORLD_SCENE_H__
