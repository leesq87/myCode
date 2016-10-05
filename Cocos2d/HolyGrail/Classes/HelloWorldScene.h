#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);


	int Stage;
	int weapon;

	int a;
	cocos2d::Sprite* Panal;
	cocos2d::Sprite* State;
	cocos2d::Sprite* player;
	cocos2d::Vec2 playerPosition;
	
	//cocos2d::Sprite* Wolf;
	//cocos2d::Sprite* Jelly;
	//cocos2d::Sprite* Demon;
	//cocos2d::Sprite* Box;

	//cocos2d::Sprite* Sword;
	//cocos2d::Sprite* Mace;
	//cocos2d::Sprite* Holy;
	//cocos2d::Sprite* Key;

	cocos2d::Size winSize;
	cocos2d::TMXTiledMap* tmap;
	cocos2d::TMXLayer* stage;
	cocos2d::TMXLayer* metainfo;

	virtual void onEnter();
	virtual void onExit();
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);

	void createPlayer();
	void createStage(int a);
	void createMeta();

	cocos2d::Vec2 tileCoordForPosition(cocos2d::Vec2 position);
	void setPlayerPosition(cocos2d::Vec2 position);

	cocos2d::Vector<cocos2d::Sprite*> Wolf;
	cocos2d::Vector<cocos2d::Sprite*> Jelly;
	cocos2d::Vector<cocos2d::Sprite*> Demon;
	cocos2d::Sprite* Box;

	cocos2d::Vector<cocos2d::Sprite*> Sword;
	cocos2d::Vector<cocos2d::Sprite*> Mace;
	cocos2d::Vector<cocos2d::Sprite*> Holy;
	cocos2d::Sprite* Key;

	cocos2d::Sprite* iWeapon;
};

#endif // __HELLOWORLD_SCENE_H__
