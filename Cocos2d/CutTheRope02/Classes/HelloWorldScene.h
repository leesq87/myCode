#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"
#include "vrope-x\vrope-x\vrope.h"

//#define PTM_RATIO 32

USING_NS_CC;


class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	bool createBox2dWorld(bool debug);
	~HelloWorld();

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(Touch* touch, Event* event);
	virtual void onTouchMoved(Touch* touch, Event* event);

	b2Body* createCandyAt(Vec2 pt, bool userData);
	void createRope(b2Body* bodyA, b2Vec2 anchorA, b2Body* bodyB, b2Vec2 anchorB, float32 sag);

	void tick(float dt);

	bool checkLineIntersection(Vec2 p1, Vec2 p2, Vec2 p3, Vec2 p4);
	b2Body* addNewSprite(Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type);



	b2Body* createRopeTipBody();

	cocos2d::SpriteBatchNode* ropeSpriteSheet;

	std::vector<VRope *>* ropes;
	std::vector<b2Body *>* candies;

	Sprite* croc_;
	b2Body* crocMouth_;
	b2Fixture* corcMouthBottom_;
	bool crocMouthOpened;
	Sprite* fineapple;

	SpriteFrameCache* cache;

	Size winSize;
	Texture2D* texture;
	b2World* _world;
	//for debugging
	GLESDebugDraw* m_debugDraw;

	bool bDrag;
	b2Body* dragBody;
	b2MouseJoint* mouseJoint;
	b2Body* gbody;
	b2Body* groundBody;


	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
};

#endif // __HELLOWORLD_SCENE_H__
