//
//  ControlManager.cpp
//  CCActionGame
//
//  Created by hrd321_00 on 13. 7. 16..
//
//

#include "ControlManager.h"

JControlManager::JControlManager()
    : touchJoypad_(false)
    , touchPoint_(Vec2::ZERO)
    , touchState_(END)
    , distance_(0.f)
    , touchAngle_(0.f)
    , horizontal_(0.f)
    , vertical_(0.f)
    , joypadMaxRadius_(32.f)
{
    log("ccc");
    for (int a = 0; a < MAX_BUTTON; ++a)
		btnState_[a] = END;

	memset(btnTouchID_, NULL, sizeof(btnTouchID_));
	memset(btnSpr_, NULL, sizeof(btnSpr_));
}

JControlManager::~JControlManager()
{
}

static JControlManager* pSingleton;

JControlManager* JControlManager::getInstance()
{
    if (!pSingleton)
    {
        pSingleton = new JControlManager();
    }

    return pSingleton;
}

void JControlManager::Initialize(Layer *layer)
{
    btnSpr_[UP] = CEntity::create(layer, NULL, "Joystick/button_a.png", Vec2(400, 60));
    btnSpr_[DOWN] = CEntity::create(layer, NULL, "Joystick/button_pushed_a.png", Vec2(400, 60));
	btnSpr_[DOWN]->setVisible(false);
	
    joypad_ = CEntity::create(layer, NULL, "Joystick/joypad.png", Vec2(64, 64));
    joypadCap_ = CEntity::create(layer, NULL, "Joystick/joypadCap.png", Vec2(64, 64));
	joypad_->setVisible(false);
	joypadCap_->setVisible(false);
}

void JControlManager::Update(float deltaTime)
{
	UpdateJoypad(deltaTime);
	UpdateButton(deltaTime);
}

void JControlManager::UpdateJoypad(float deltaTime)
{
	Size size = Director::getInstance()->getWinSizeInPixels();
	Rect rect = Rect(size.width - 150, 0, 150, 100);
	
	if (rect.containsPoint(touchPoint_))
		return;

    Vec2 center = joypad_->getPosition();
	float dx = center.x - btnTouchPoint_[JOYPAD].x;
	float dy = center.y - btnTouchPoint_[JOYPAD].y;
	
	if (btnState_[JOYPAD] != END)
		touchJoypad_ = true;

	if (touchJoypad_)
	{
		distance_ = sqrt(dx * dx + dy * dy);
		touchAngle_ = atan2f(dy, dx);
		horizontal_ = -cosf(touchAngle_);
		vertical_ = -sinf(touchAngle_);
		
		if (distance_ > joypadMaxRadius_)
		{
			distance_ = joypadMaxRadius_;
			
            joypadCap_->setPosition(Vec2(center.x + horizontal_ * joypadMaxRadius_, center.y + vertical_ * joypadMaxRadius_));
		}
		else
		{
			joypadCap_->setPosition(btnTouchPoint_[JOYPAD]);
		}
	}
	
	if (btnState_[JOYPAD] == END)
	{
		joypad_->setVisible(false);
		joypadCap_->setVisible(false);
		joypadCap_->setPosition(joypad_->getPosition());
		touchJoypad_ = false;
		touchAngle_ = 0.f;
		distance_ = 0.f;
		horizontal_ = 0.f;
		vertical_ = 0.f;
	}
}

void JControlManager::UpdateButton(float deltaTime)
{
	if (btnState_[A_BUTTON] == END)
	{
		btnSpr_[UP]->setVisible(true);
		btnSpr_[DOWN]->setVisible(false);
	}
	else
	{
		btnSpr_[UP]->setVisible(false);
		btnSpr_[DOWN]->setVisible(true);
	}
}

bool JControlManager::IsButtonContainsPoint(eButtonID btnId, const Vec2 &point)
{
	if (btnId == JOYPAD)
	{
		Size size = Director::getInstance()->getWinSizeInPixels();
		Rect rect = Rect(size.width - 150, 0, 150, 100);
		
		if (rect.containsPoint(point))
			return false;

		joypad_->setVisible(true);
		joypadCap_->setVisible(true);
		
		if (btnState_[JOYPAD] != END)
		{
			if (joypad_->getBoundingBox().containsPoint(point))
				return true;
		}
		else
		{
			joypad_->setPosition(point);
			return true;
		}
	}
	else if (btnId == A_BUTTON)
	{
        return btnSpr_[0]->getBoundingBox().containsPoint(point);
	}
	
	return false;
}
