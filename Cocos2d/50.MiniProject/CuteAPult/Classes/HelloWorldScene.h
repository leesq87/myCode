#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"Box2D\Box2D.h"

using namespace cocos2d;


class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

	bool createBox2dWorld(bool debug);
	virtual void onEnter();
	virtual void onExit();
	Size winSize;
	~HelloWorld();
	
	// adds a new sprite at a given coordinate
	//virtual void draw();
	virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
	void tick(float dt);
	//virtual void onTouchesBegan(cocos2d::Set* touches, cocos2d::Event* event);
	//virtual void onTouchesMoved(cocos2d::Set* touches, cocos2d::Event* event);
	//virtual void onTouchesEnded(cocos2d::Set* touches, cocos2d::Event* event);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void createBullets(int count);
	bool attachBullet();
	void resetBullet();
	void resetGame();
	
	void createTargets();
	void createTarget(String* imageName,
		cocos2d::Vec2 position,
		float rotation,
		bool isCircle,
		bool isStatic,
		bool isEnemy);
	

	bool bDrag;
	b2Body* dragBody;
	b2MouseJoint* mouseJoint;
	b2Body* gbody;



private:
	std::vector<b2Body *> m_bullets;
	std::vector<b2Body *> m_targets;
	std::vector<b2Body *> m_enemies;

	int m_currentBullet;
	b2World* m_world;
	b2Body* m_groundBody;
	b2Fixture *m_armFixture;
	b2Body *m_armBody;
	b2RevoluteJoint *m_armJoint;
	b2MouseJoint *m_mouseJoint;
	
	b2Body *m_bulletBody;
	b2WeldJoint *m_bulletJoint;
	
	bool m_releasingArm;



	void onDraw(const cocos2d::Mat4& transform, uint32_t flags);
	cocos2d::CustomCommand _customCmd;

};

#endif // __HELLOWORLD_SCENE_H__

//};
//
//#endif // __HELLO_m_worldH__
