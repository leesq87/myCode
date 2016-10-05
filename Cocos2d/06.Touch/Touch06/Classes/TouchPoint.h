#ifndef __TouchEx6__TouchPoint__
#define __TouchEx6__touchPoint__

#include "cocos2d.h"

using namespace cocos2d;


static const Color3B* s_TouchColors[5] = {
	&Color3B::YELLOW,
	&Color3B::BLUE,
	&Color3B::GREEN,
	&Color3B::RED,
	&Color3B::MAGENTA
};

class TouchPoint : public Node
{
public:
	TouchPoint(const Vec2 &touchPoint, const Color3B &touchColor)
	{
		DrawNode* drawNode = DrawNode::create();
		auto s = Director::getInstance()->getWinSize();
		Color4F color(touchColor.r / 255.0f, touchColor.g / 255.0f, touchColor.b / 255.0f, 1.0f);
		drawNode->drawLine(Vec2(0, touchPoint.y), Vec2(s.width, touchPoint.y), color);
		drawNode->drawLine(Vec2(touchPoint.x, 0), Vec2(touchPoint.x, s.height), color);
		drawNode->drawDot(touchPoint, 3, color);
		addChild(drawNode);
	}

	static TouchPoint* touchPointWithParent(Node* pParent, const Vec2 &touchPoint, const Color3B &touchColor)
	{
		auto pRet = new (std::nothrow) TouchPoint(touchPoint, touchColor);
		pRet->setContentSize(pParent->getContentSize());
		pRet->setAnchorPoint(Vec2(0.0f, 0.0f));
		pRet->autorelease();
		return pRet;
	}
};

#endif