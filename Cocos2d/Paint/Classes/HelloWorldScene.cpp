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
	winSize = Director::getInstance()->getWinSize();
	idxNum = -1;




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
	this->addChild(image2, 2);

	auto image1 = Sprite::create("ima/image01.png");
	image1->setPosition(Vec2(240, 160));
	this->addChild(image1, 3);


	m_pTarget = RenderTexture::create(winSize.width/2,winSize.height/2 , Texture2D::PixelFormat::RGBA8888);
	m_pTarget->retain();
	m_pTarget->setPosition(Vec2(winSize.width / 2, winSize.height / 2));

	this->addChild(m_pTarget, 1);


	MenuItemFont::setFontSize(16);
	auto item2 = MenuItemFont::create("Clear", CC_CALLBACK_1(HelloWorld::clearImage, this));
	item2->setColor(Color3B::BLACK);
	auto menu = Menu::create(item2, nullptr);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(winSize.width - 80, winSize.height - 30));
	this->addChild(menu, 3);



    return true;
}

HelloWorld::~HelloWorld() {
	m_pTarget->release();
	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

void HelloWorld::onEnter() {
	Layer::onEnter();

	listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void HelloWorld::onTouchesMoved(const std::vector<Touch*>& touches, Event* event) {

	auto touch = touches[0];
	Vec2 start = touch->getLocation();
	Vec2 end = touch->getPreviousLocation();

	start.x = start.x -120 ;
	end.x = end.x - 120;

	start.y = start.y - 80;
	end.y = end.y -80;

	m_pTarget->begin();

	float distance = start.getDistance(end);

	if (distance > 1) {
		int d = (int)distance;
		m_pBrush.clear();

		for (int i = 0; i < d; ++i) {
			auto sprite = Sprite::create("ima/brush.png");
			sprite->setScale(0.5);

			switch (idxNum) {
			case 0:
				sprite->setColor(Color3B::RED);
				break;
			case 1:
				sprite->setColor(Color3B::ORANGE);
				break;
			case 2:
				sprite->setColor(Color3B::YELLOW);
				break;
			case 3:
				sprite->setColor(Color3B::GREEN);
				break;
			case 4:
				sprite->setColor(Color3B::BLUE);
				break;
			case 5:
				sprite->setColor(Color3B::MAGENTA);
				break;
			case 6:
				sprite->setColor(Color3B(181, 000, 255));
				break;
			case 7:
				sprite->setColor(Color3B::WHITE);
				break;
			case 8:
				sprite->setColor(Color3B::BLACK);
				break;
			case 9:
				sprite->setColor(Color3B::GRAY);
				break;
			case 10:
				sprite->setColor(Color3B(100, 60, 0));
				break;
			case 11:
				sprite->setColor(Color3B(255, 200, 150));
				break;
			case 12:
				sprite->setColor(Color3B(255, 200, 200));
				break;
			default:
				break;
			}
			m_pBrush.pushBack(sprite);
		}

		for (int i = 0; i < d; i++)
		{
			float difx = end.x - start.x;
			float dify = end.y - start.y;
			float delta = (float)i / distance;
			m_pBrush.at(i)->setPosition(Vec2(start.x + (difx * delta), start.y + (difx * delta)));
			m_pBrush.at(i)->setRotation(rand() & 360);
			float r = (float)(rand() % 50 / 50.f) + 0.25f;
			m_pBrush.at(i)->setScale(r);
			m_pBrush.at(i)->visit();
		}
	}
	m_pTarget->end();
}


void HelloWorld::tableCellTouched(TableView* table, TableViewCell* cell) {
	log("tag : %d \n Cell touched at idx : %ld", table->getTag(), cell->getIdx());
	if (idxNum != -1) {
		auto temp = table->cellAtIndex(idxNum);
		temp->getChildByTag(321) -> setPosition(Vec2(0, 0));
	}

	idxNum = cell->getIdx();
	auto sprite = (Sprite*)cell->getChildByTag(321);
	sprite->setPosition(Vec2(0, 10));

	table->reloadData();

}

Size HelloWorld::tableCellSizeForIndex(TableView* table, ssize_t idx) {
	return Size(30, 60);
}


TableViewCell* HelloWorld::tableCellAtIndex(TableView* table, ssize_t idx) {
	char png[25];
	sprintf(png, "ima/crayon_%02d.png",idx+1 );
	auto string = String::createWithFormat("%ld", idx);
	auto sprite = Sprite::create(png);

	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CustomTableViewCell();
		cell->autorelease();
		sprite->setAnchorPoint(Vec2::ZERO);
		sprite->setPosition(Vec2(0, 0));
		sprite->setScale(0.3f);
		sprite->setTag(321);
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

		sprite = (Sprite*)cell->getChildByTag(321);
		sprite->setTexture(png);

	}

	return cell;
}

ssize_t HelloWorld::numberOfCellsInTableView(TableView* table) {
	return 13;
}



void HelloWorld::clearImage(Ref* sender) {
	m_pTarget->clear(255, 255, 255, 255);
}