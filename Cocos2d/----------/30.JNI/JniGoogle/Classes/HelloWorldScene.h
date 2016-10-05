#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class HelloWorld
	: public cocos2d::LayerColor
	, public cocos2d::ui::EditBoxDelegate
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);

	cocos2d::ui::EditBox* _editNum;
	std::string txtNum;

	void doLogin(Ref* pSender);

	void doSendScore(Ref* pSender);
	void doSendTime(Ref* pSender);

	void doSendOne(Ref* pSender);
	void doSendMulti(Ref* pSender);

	void doShowLeaderBoard(Ref* pSender);
	void doShowAchivement(Ref* pSender);

	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
};

#endif // __HELLOWORLD_SCENE_H__