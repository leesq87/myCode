#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include <GLES-Render.h>

#define PTM_RATIO 32

using namespace cocos2d;

class HelloWorld : public cocos2d::LayerColor
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(HelloWorld);

	bool createBox2dWorld(bool debug);
	~HelloWorld();
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags);


	virtual void onEnter();
	virtual void onExit();
	void tick(float dt);
	
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void createBullets(int count);
	bool attachBullet();
	void resetBullet();
	void resetGame();

	void createTargets();
	void createTarget(const char *imageName,
		cocos2d::Vec2 position,
		float rotation,
		bool isCircle,
		bool isStatic,
		bool isEnemy);

	cocos2d::Sprite* arm;

	Size winSize;
	Texture2D* texture;
	b2World* _world;
	GLESDebugDraw* m_debugDraw;

	std::vector<b2Body *> m_bullets;
	std::vector<b2Body *> m_targets;
	std::vector<b2Body *> m_enemies;

	int m_currentBullet;
	b2Body* _groundBody;
	b2Fixture *_armFixture;
	b2Body *_armBody;
	b2RevoluteJoint *_armJoint;
	b2MouseJoint *_mouseJoint;

	b2Body *m_bulletBody;
	b2WeldJoint *m_bulletJoint;


	bool m_releasingArm;


protected:
	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;
};

#endif // __HELLOWORLD_SCENE_H__
