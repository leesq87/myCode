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
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	TableView* tableView1 = TableView::create(this, Size(250, 60));
	tableView1->setDirection(ScrollView::Direction::HORIZONTAL);
	tableView1->setPosition(Vec2(20, 130));
	tableView1->setDelegate(this);
	tableView1->setTag(100);
	this->addChild(tableView1);
	tableView1->reloadData();

	TableView* tableView2 = TableView::create(this, Size(60, 250));
	tableView2->setDirection(ScrollView::Direction::VERTICAL);
	tableView2->setPosition(Vec2(330, 40));
	tableView2->setTag(200);
	tableView2->setDelegate(this);
	tableView2->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	this->addChild(tableView2);
	tableView2->reloadData();

	return true;
}

void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell) {
	log("tag : %d \n Cell touched at idx : %ld", table->getTag(), cell->getIdx());
}

Size HelloWorld::tableCellSizeForIndex(TableView* table, ssize_t idx) {
	if (idx == 2) {
		return Size(100, 100);
	}
	return Size(60, 60);
}

TableViewCell* HelloWorld::tableCellAtIndex(TableView* table, ssize_t idx) {
	auto string = String::createWithFormat("%ld", idx);
	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CustomTableViewCell();
		cell->autorelease();
		auto sprite = Sprite::create("Images/Icon.png");
		sprite->setAnchorPoint(Vec2::ZERO);
		sprite->setPosition(Vec2(0, 0));
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
	}

	return cell;
}

ssize_t HelloWorld::numberOfCellsInTableView(TableView* table) {
	return 20;
}

