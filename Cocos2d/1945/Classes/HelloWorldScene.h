#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <stdlib.h>


#define RANDOM_INT(MIN, MAX) ((MIN) + rand() % ((MAX + 1) - (MIN)))

USING_NS_CC;

#define MAX_MISSILE	2

class HelloWorld : public cocos2d::LayerColor
{
public:
	HelloWorld();

    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	void menuCloseCallback(Ref* pSender);

	virtual void onEnter();
	virtual void onExit();

	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	void mytick(float time);
	void RegenEnemy(float time);
	void Shooting(float time);

	void PutCrashEffect(const Vec2 &pos);

	void AddEnemy(const Vec2& position);


private:
	cocos2d::Sprite * player_;//주인공 플레이어
	cocos2d::Vector<cocos2d::Sprite*> missile_;
	cocos2d::Vector<cocos2d::Sprite *> enemy_;//적비행기 CCArray(배열, 리스트 구조)

	cocos2d::Vec2 distance_;
	cocos2d::Size size_;

	float regenCheckTime_;
};

#endif // __HELLOWORLD_SCENE_H__
