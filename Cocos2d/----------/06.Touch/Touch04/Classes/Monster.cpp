#include "Monster.h"

USING_NS_CC;

Monster::Monster()
	: _listener(nullptr), _fixedPriority(0), _useNodePriority(false) {
	bool bOk = initWithTexture(nullptr, Rect::ZERO);
	if (bOk) {
		this->autorelease();
	}
}

void Monster::setPriority(int fixedPriority) {
	_fixedPriority = fixedPriority;
	_useNodePriority = false;
}

void Monster::setPriorityWithThis(bool useNodePriority) {
	_useNodePriority = useNodePriority;
//	_fixedPriority = true;
}

void Monster::onEnter() {
	Sprite::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [=](Touch *touch, Event *event) {
		log("touch began...");
		Point locationInNode = this->convertToNodeSpace(touch->getLocation());
		Size s = this->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode)) {
			this->setColor(Color3B::RED);
			return true;
		}
		return false;
	};

	listener->onTouchMoved = [=](Touch *touch, Event *event) {
		//this->setPosition(this->getPosition() + touch->getDelta());
	};

	listener->onTouchEnded = [=](Touch *touch, Event *event) {
		this->setColor(Color3B::WHITE);
	};

	if (_useNodePriority) {
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	}
	else {
		_eventDispatcher->addEventListenerWithFixedPriority(listener, _fixedPriority);
	}
	_listener = listener;
}
void Monster::onExit() {
	_eventDispatcher->removeEventListener(_listener);
	Sprite::onExit();
}





