#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "CustomTableViewChell.h"

using namespace cocos2d;
using namespace cocos2d::extension;


class HelloWorld : public cocos2d::LayerColor, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	virtual void scrollViewDidScroll(ScrollView* view) {};
	virtual void scrollViewDidZoom(ScrollView* view) {};
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual Size tableCellSizeForIndex(TableView* table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idx);
	virtual ssize_t	numberOfCellsInTableView(TableView* table);

	cocos2d::EventListenerTouchAllAtOnce* listener;
	cocos2d::Size winSize;
	cocos2d::RenderTexture* m_pTarget;
	cocos2d::Vector<Sprite*> m_pBrush;

	~HelloWorld();
	virtual void onEnter();
	//virtual void onExit();
	void onTouchesMoved(const std::vector<Touch*>&touches, Event* event);
	//void saveImage(Ref* sender);
	void clearImage(Ref* sender);

	int idxNum;

};

#endif // __HELLOWORLD_SCENE_H__
