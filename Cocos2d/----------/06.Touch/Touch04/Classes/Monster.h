#ifndef __SpriteExtendEx__Monster__
#define __SpriteExtendEx__Monster__

#include "cocos2d.h"

class Monster:public cocos2d::Sprite {
public:
	Monster();

	void setPriority(int fixedPriority);
	void setPriorityWithThis(bool useNodePriority);

	virtual void onEnter();
	virtual void onExit();

private:
	cocos2d::EventListener *_listener;
	int _fixedPriority;
	bool _useNodePriority;

};

#endif 