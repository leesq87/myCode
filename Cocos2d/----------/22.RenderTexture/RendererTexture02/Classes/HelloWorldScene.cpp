#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(255,255,255,255)) )
    {
        return false;
    }
    
	TableView* tableView1 = TableView::create(this, Size(250, 60));
	tableView1->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView1->setPosition(Vec2(115, 10));
	tableView1->setDelegate(this);
	tableView1->setTag(100);
	this->addChild(tableView1);
	tableView1->reloadData();

	auto image2 = Sprite::create("ima/image02.png");
	image2->setPosition(Vec2(240, 160));
	image2->setScale(1.1f);
	this->addChild(image2, 1);

	auto image1 = Sprite::create("ima/image01.png");
	image1->setPosition(Vec2(240, 160));
	this->addChild(image1, 2);

    return true;
}


void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell) {
	log("tag : %d \n Cell touched at idx : %ld", table->getTag(), cell->getIdx());
}

Size HelloWorld::tableCellSizeForIndex(TableView* table, ssize_t idx) {
	return Size(30, 60);
}


TableViewCell* HelloWorld::tableCellAtIndex(TableView* table, ssize_t idx) {
	static int counter = 1;
	char png[25];
	sprintf(png, "ima/crayon_%02d.png",counter++ );
	auto string = String::createWithFormat("%ld", idx);
	auto sprite = Sprite::create(png);

	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CustomTableViewCell();
		cell->autorelease();
		sprite->setAnchorPoint(Vec2::ZERO);
		sprite->setPosition(Vec2(0, 0));
		sprite->setScale(0.3f);
		cell->addChild(sprite);

		auto label = LabelTTF::create(string->getCString(), "Helvetica", 20);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(123);
		cell->addChild(label);
	}
	else {
		auto label = (LabelTTF*)cell->getChildByTag(123);
		label->setString(string->getCString());
		auto temp = (Sprite*)cell->getChildByTag(123);
		//temp->setSpriteFrame(sprite->getSpriteFrame());
	}

	return cell;
}

ssize_t HelloWorld::numberOfCellsInTableView(TableView* table) {
	return 13;
}


