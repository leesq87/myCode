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
    
	auto map = TMXTiledMap::create("tilemap/orthogonal-test-zorder.tmx");
	addChild(map, 0, 1);

	Size s = map->getContentSize();
	log("ContentSize: %f, %f", s.width, s.height);

	m_tamara = Sprite::create("tilemap/grossinis_sister1.png");
	map->addChild(m_tamara, map->getChildren().size());
	m_tamara->setAnchorPoint(Vec2(0.5f, 0));

	auto move = MoveBy::create(10, Vec2(400, 320));
	auto back = move->reverse();
	auto seq = Sequence::create(move, back, nullptr);
	m_tamara->runAction(RepeatForever::create(seq));

	schedule(schedule_selector(HelloWorld::repositionSprite));


    return true;
}

void HelloWorld::repositionSprite(float dt) {
	Vec2 p = m_tamara->getPosition();
	p = CC_POINT_POINTS_TO_PIXELS(p);
	Node* map = getChildByTag(1);

	//there are only 4 layer (grass and 3trees)
	//if tamara<81, z= 4
	//if tamara<162, z= 3
	//if tamara <243, z=2

	int newZ = 4 - ((p.y - 10) / 81);
	newZ = MAX(newZ, 0);

	map->reorderChild(m_tamara, newZ);

}