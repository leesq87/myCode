#ifndef __CHESS_MAN_H__
#define __CHESS_MAN_H__

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class ChessMan : public cocos2d::Sprite{
public:

	//체스맨 기본속성
	int index;
	char* Name;  // 이름
	int move_dice; // 이동주사위수
	int att_dice; // 공격주사위수
	int def_dice; // 방어주사위수
	int cup_dice; // 지능카운트
	char* abillity; // 캐릭터 어빌리티 종류
	char* attri; // 캐릭터속성
	char* value; //속성
	int player;
	char* state; // 상태

	//체스맨 어빌 프로그레스, 현재 포지션
	cocos2d::ProgressTimer* pt;
	int ability_progress;
	int now_Position;

	void progressUpdate();
	void spriteProgresstoRadial(float f);

	//이동
	bool back;

	//파티여부 및 해당포지션
	bool inParty;
	int party_position;

	SpriteFrameCache* cache;

	cocos2d::Sprite* gameSprite;
	char gameSprite_string[99];
	cocos2d::Sprite* infoSprite;
	char infoSprite_string[99];

	void setInit();
	void setName(int num);


	cocos2d::Vector<SpriteFrame*> _frontWait;
	cocos2d::Vector<SpriteFrame*> _leftWait;
	cocos2d::Vector<SpriteFrame*> _rightWait;
	cocos2d::Vector<SpriteFrame*> _moveUp;
	cocos2d::Vector<SpriteFrame*> _moveDown;
	cocos2d::Vector<SpriteFrame*> _moveLeft;
	cocos2d::Vector<SpriteFrame*> _moveRight;
	cocos2d::Vector<SpriteFrame*> _leftAttack;
	cocos2d::Vector <SpriteFrame* > _rightAttack;

	void makeFrontWiatMotion();
	void makeLeftWaitMotion();
	void makeRightWaitMotion();
	void makeMoveUpMotion();
	void makeMoveDownMotion();
	void makeMoveLeftMotion();
	void makeMoveRightMotion();
	void makeLeftAttackMotion();
	void makeRightAttackMotion();


	void makeAction(cocos2d::Vector<SpriteFrame*> act);

};

#endif 
