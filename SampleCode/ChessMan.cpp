#include "ChessMan.h"

USING_NS_CC;

void ChessMan::progressUpdate(){
	this->spriteProgresstoRadial(ability_progress);
	if (ability_progress >= 100)
		ability_progress = 100;
}

void ChessMan::spriteProgresstoRadial(float f){
	pt->setPercentage(f);
}

void ChessMan::setInit() {
	ability_progress = 0;
	now_Position = 0;
	inParty = false;
	back = false;
	state = "";
	party_position = 0;
	

	setName(index);

	sprintf(infoSprite_string, "gamescene/char/%02d/info.png", index);



	char temp[99];
	sprintf(temp, "gamescene/char/%02d/%02d.plist", index, index);
	cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(temp);

	char asdf[99];
	sprintf(asdf, "%02d_001.png", index);

	gameSprite = Sprite::createWithSpriteFrameName(asdf);
	infoSprite = Sprite::create(infoSprite_string);


	makeFrontWiatMotion();
	makeLeftWaitMotion();
	makeRightWaitMotion();
	makeMoveUpMotion();
	makeMoveDownMotion();
	makeMoveLeftMotion();
	makeMoveRightMotion();
	makeLeftAttackMotion();
	makeRightAttackMotion();


	makeAction(_frontWait);
	

}

void ChessMan::makeAction(cocos2d::Vector<SpriteFrame*> act){
	
	gameSprite->stopAllActions();
	auto animation = Animation::createWithSpriteFrames(act, 0.1f);
	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	gameSprite->runAction(rep);

}

void ChessMan::makeFrontWiatMotion(){
	char str[99];
	for (int i = 1; i <= 3; i++) {
		sprintf(str, "%02d_%03d.png",index, i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		_frontWait.pushBack(frame);
	}
}

void ChessMan::makeLeftWaitMotion(){
	char str[99];
	for (int i = 4; i <= 6; i++) {
		sprintf(str, "%02d_%03d.png", index, i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		_leftWait.pushBack(frame);
	}
}

void ChessMan::makeRightWaitMotion() {
	char str[99];
	for (int i = 48; i <= 50; i++) {
		sprintf(str, "%02d_%03d.png", index, i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		_rightWait.pushBack(frame);
	}
}

void ChessMan::makeMoveUpMotion(){
	char str[99];
	for (int i = 7; i <= 12; i++) {
		sprintf(str, "%02d_%03d.png", index, i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		_moveUp.pushBack(frame);
	}
}

void ChessMan::makeMoveDownMotion(){
	char str[99];
	for (int i = 19; i <= 24; i++) {
		sprintf(str, "%02d_%03d.png", index, i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		_moveDown.pushBack(frame);
	}
}

void ChessMan::makeMoveLeftMotion(){
	char str[99];
	for (int i = 13; i <= 18; i++) {
		sprintf(str, "%02d_%03d.png", index, i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		_moveLeft.pushBack(frame);
	}
}

void ChessMan::makeMoveRightMotion() {
	char str[99];
	for (int i = 34; i <= 39; i++) {
		sprintf(str, "%02d_%03d.png", index, i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		_moveRight.pushBack(frame);
	}
}

void ChessMan::makeLeftAttackMotion(){
	char str[99];
	for (int i = 25; i <= 32; i++) {
		sprintf(str, "%02d_%03d.png", index, i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		_leftAttack.pushBack(frame);
	}
}

void ChessMan::makeRightAttackMotion() {
	char str[99];
	for (int i = 40; i <= 47; i++) {
		sprintf(str, "%02d_%03d.png", index, i);
		SpriteFrame* frame = cache->getSpriteFrameByName(str);
		_rightAttack.pushBack(frame);
	}
}

void ChessMan::setName(int num) {
	switch (num)
	{
	case 1:
		Name = "ũ����Ƽ��";
		break;
	case 2:
		Name = "ö����";
		break;
	case 3:
		Name = "�Ҿ�";
		break;
	case 4:
		Name = "�ζ��ڵ�";
		break;
	case 5:
		Name = "����";
		break;
	case 6:
		Name = "����Ʈ";
		break;
	case 7:
		Name = "����";
		break;
	case 8:
		Name = "�����ڳ�";
		break;
	case 9:
		Name = "�����";
		break;
	case 10:
		Name = "������";
		break;
	case 11:
		Name = "�̹�";
		break;
	case 12:
		Name = "�ذ�";
		break;
	case 13:
		Name = "��ġ";
		break;
	default:
		break;
	}
}
