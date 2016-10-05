//
//  Joystick.h
//  JoyStickEx
//
//  Created by Jaewhan Lee on 13. 6. 5..
//  Copyright www.cocos2d-x.kr 2013년. All rights reserved.
//

#ifndef __JoyStickEx__Joystick__
#define __JoyStickEx__Joystick__

#include "cocos2d.h"

using namespace cocos2d;

class Joystick : public Layer
{
    
public:
    virtual bool init();
    CREATE_FUNC(Joystick);

    Vec2 getVelocity(){ return velocity; }

private:
    
    Vec2 kCenter;
    Sprite* thumb;
    bool isPressed;
    
    Vec2 velocity;
    
    void updateVelocity(Vec2 point);
    void resetJoystick();
    bool handleLastTouch();

    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event* event);
};

#endif
