#ifndef __CHESS_MAN_H__
#define __CHESS_MAN_H__

#include "cocos2d.h"
#include <iostream>

USING_NS_CC;

class ChessMan : public cocos2d::Sprite{
public:

	//ü���� �⺻�Ӽ�
	int index;
	char* Name;  // �̸�
	int move_dice; // �̵��ֻ�����
	int att_dice; // �����ֻ�����
	int def_dice; // ����ֻ�����
	int cup_dice; // ����ī��Ʈ
	char* abillity; // ĳ���� �����Ƽ ����
	char* attri; // ĳ���ͼӼ�
	char* value; //�Ӽ�
	int player;
	char* state; // ����

	//ü���� ��� ���α׷���, ���� ������
	cocos2d::ProgressTimer* pt;
	int ability_progress;
	int now_Position;

	void progressUpdate();
	void spriteProgresstoRadial(float f);

	//�̵�
	bool back;

	//��Ƽ���� �� �ش�������
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
