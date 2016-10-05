#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "CustomTableViewCell.h"


using namespace cocos2d;
using namespace cocos2d::extension;

class HelloWorld : public cocos2d::LayerColor,public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
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


};

#endif // __HELLOWORLD_SCENE_H__
