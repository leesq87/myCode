//
//  ControlManager.h
//  CCActionGame
//
//  Created by hrd321_00 on 13. 7. 16..
//
//

#pragma once

#include <stdio.h>
#include "Entity.h"

USING_NS_CC;

enum eTouchState
{
	BEGIN,
	MOVE,
	END
};

enum eButtonState
{
	UP,
	DOWN
};

enum eButtonID
{
	JOYPAD,
	A_BUTTON,
	MAX_BUTTON
};

//class CControlManager : public ISingleton<CControlManager>
class JControlManager : public cocos2d::Node
{
public:
    JControlManager();
    ~JControlManager();

    static JControlManager* getInstance();

public:
	
	void Initialize(Layer *layer);
	
	void Update(float deltaTime);

	MenuItemImage *AddButton(const char *texName, const Vec2 &position, SEL_MenuHandler selector);
	
	void SetTouchPoint(const Vec2 &position) {touchPoint_ = position;}
	void SetTouchState(eTouchState state) {touchState_ = state;}
	bool IsButtonDown() {return btnSpr_[DOWN]->isVisible();}
    bool IsButtonContainsPoint(eButtonID btnId, const Vec2 &point);
	
    Vec2 GetTouchPoint() { return touchPoint_; }
	eTouchState GetTouchState() {return touchState_;}
	
    Vec2 GetAxis() { return Vec2(horizontal_, vertical_); }
	float GetDistance() {return distance_ / joypadMaxRadius_;}

	Touch* btnTouchID_[MAX_BUTTON];
	eTouchState btnState_[MAX_BUTTON];
    Vec2 btnTouchPoint_[MAX_BUTTON];

private:
	void UpdateJoypad(float deltaTime);
	void UpdateButton(float deltaTime);

	CEntity* btnSpr_[2];
	
	CEntity* joypad_;
	CEntity* joypadCap_;
    Vec2 touchPoint_;
	eTouchState touchState_;
	float distance_;
	float touchAngle_;
	float horizontal_;
	float vertical_;
	float joypadMaxRadius_;
	bool touchJoypad_;
};
