//
//  MyBodyParser.h
//
//  Created by Jason Xu.
//
//

#pragma once

#include <string>
#include "cocos2d.h"
#include "json/document.h"
#include "Box2D/Box2D.h"

USING_NS_CC;
#define PTM_RATIO 32

class MyBodyParser {
    MyBodyParser(){}
    rapidjson::Document doc;
public:
    static MyBodyParser* getInstance();
    bool parseJsonFile(const std::string& pFile);
    bool parse(unsigned char* buffer, long length);
    void clearCache();
    PhysicsBody* physicsBodyJson(Node* pNode, const std::string& name, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT);
    void b2BodyJson(Node* pNode, const std::string& name, b2Body* body);
};