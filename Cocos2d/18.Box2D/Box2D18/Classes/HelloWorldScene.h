#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D\Box2D.h"
#include "GLES-Render.h"

#define PTM_RATIO 32

USING_NS_CC;


class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	bool createBox2dWorld(bool debug);
	~HelloWorld();

	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;

	virtual void onEnter();
	virtual void onExit();
	b2Body* addNewSprite(Vec2 point, Size size, b2BodyType bodytype, const char* spriteName, int type);
	//b2Body* getBodyAtTab(Vec2 p);

	virtual bool onTouchBegan(Touch* touch, Event* event);
	//virtual void onTouchMoved(Touch* touch, Event* event);
	//virtual void onTouchEnded(Touch* touch, Event* event);
	void tick(float dt);
	void addNewSpriteAtPosition(Vec2 location);


	Size winSize;
	Texture2D* texture;
	b2World* _world;

	//for debugging
	GLESDebugDraw* m_debugDraw;

	//bool bDrag;
	//b2Body* dragBody;
	//b2MouseJoint* mouseJoint;
	//b2Body* gbody;

protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
};

#endif // __HELLOWORLD_SCENE_H__
