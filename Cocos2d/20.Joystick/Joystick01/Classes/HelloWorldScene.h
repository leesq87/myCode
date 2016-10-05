#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Joystick.h"
class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	Joystick* joystick;
	cocos2d::Sprite* pMan;
	void tick(float dt);


};

#endif // __HELLOWORLD_SCENE_H__
