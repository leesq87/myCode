//
//  MyBodyParser.cpp
//
//  Created by Jason Xu.
//
//  2014.05.30. Modified by Jaehwan Lee. (gikimirane@naver.com)
//  For PhysicsBody
//  Before..PhysicsBody* bodyFormJson(Node* pNode, const std::string& name);
//  After...PhysicsBody* physicsBodyJson(Node* pNode, const std::string& name, PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT);
//
//  2015.06.19. Modified by Jaehwan Lee.
//  For b2Body ( Box2D )
//  Before..PhysicsBody* bodyFormJson(Node* pNode, const std::string& name);
//  After...void b2BodyJson(cocos2d::Node *pNode, const std::string& name, b2Body* body)
//

#include "MyBodyParser.h"

MyBodyParser* MyBodyParser::getInstance()
{
    static MyBodyParser* sg_ptr = nullptr;
    if (nullptr == sg_ptr)
    {
        sg_ptr = new MyBodyParser;
    }
    return sg_ptr;
}

bool MyBodyParser::parse(unsigned char *buffer, long length)
{
    bool result = false;
    std::string js((const char*)buffer, length);
    doc.Parse<0>(js.c_str());
    if(!doc.HasParseError())
    {
        result = true;
    }
    return result;
}

void MyBodyParser::clearCache()
{
    doc.SetNull();
}

bool MyBodyParser::parseJsonFile(const std::string& pFile)
{
    auto content = FileUtils::getInstance()->getDataFromFile(pFile);
    bool result = parse(content.getBytes(), content.getSize());
    return result;
}

PhysicsBody* MyBodyParser::physicsBodyJson(cocos2d::Node *pNode, const std::string& name, PhysicsMaterial material)
{
    PhysicsBody* body = nullptr;
    rapidjson::Value &bodies = doc["rigidBodies"];
    if (bodies.IsArray())
    {
        for (int i = 0; i<bodies.Size(); ++i)
        {
            if (0 == strcmp(name.c_str(), bodies[i]["name"].GetString()))
            {
                rapidjson::Value &bd = bodies[i];
                if (bd.IsObject())
                {
                    body = PhysicsBody::create();
                    float width = pNode->getContentSize().width;
                    float offx = -pNode->getAnchorPoint().x*pNode->getContentSize().width;
                    float offy = -pNode->getAnchorPoint().y*pNode->getContentSize().height;

                    Point origin(bd["origin"]["x"].GetDouble(), bd["origin"]["y"].GetDouble());
                    rapidjson::Value &polygons = bd["polygons"];
                    for (int i = 0; i<polygons.Size(); ++i)
                    {
                        int pcount = polygons[i].Size();
                        Point* points = new Point[pcount];
                        for (int pi = 0; pi<pcount; ++pi)
                        {
                            points[pi].x = offx + width * polygons[i][pcount - 1 - pi]["x"].GetDouble();
                            points[pi].y = offy + width * polygons[i][pcount - 1 - pi]["y"].GetDouble();
                        }
                        body->addShape(PhysicsShapePolygon::create(points, pcount, material));
                        delete[] points;
                    }
                }
                else
                {
                    log("body: %s not found!", name.c_str());
                }
                break;
            }
        }
    }
    return body;
}

void MyBodyParser::b2BodyJson(cocos2d::Node *pNode, const std::string& name, b2Body* body)
{
    rapidjson::Value &bodies = doc["rigidBodies"];
    if (bodies.IsArray())
    {
        for (int i=0; i<bodies.Size(); ++i)
        {
            if (0 == strcmp(name.c_str(), bodies[i]["name"].GetString()))
            {
                rapidjson::Value &bd = bodies[i];
                if (bd.IsObject())
                {
                    float width = pNode->getContentSize().width;
                    float offx = - pNode->getAnchorPoint().x*pNode->getContentSize().width;
                    float offy = - pNode->getAnchorPoint().y*pNode->getContentSize().height;

                    Vec2 origin( bd["origin"]["x"].GetDouble(), bd["origin"]["y"].GetDouble());
                    rapidjson::Value &polygons = bd["polygons"];

                    for (int i = 0; i<polygons.Size(); ++i)
                    {
                        int pcount = polygons[i].Size();
                        b2Vec2* points = new b2Vec2[pcount];
                        for (int pi = 0; pi<pcount; ++pi)
                        {
                            points[pi].x = (offx + width * polygons[i][pcount - 1 - pi]["x"].GetDouble()) / PTM_RATIO;
                            points[pi].y = (offy + width * polygons[i][pcount - 1 - pi]["y"].GetDouble()) / PTM_RATIO;
                        }

                        b2PolygonShape dynamicPolygon;
                        dynamicPolygon.Set(points, pcount);

                        b2FixtureDef fixtureDef;
                        fixtureDef.shape = &dynamicPolygon;
                        fixtureDef.density = 1.0f;
                        fixtureDef.friction = 0.3f;
                        fixtureDef.restitution = 0.7f;

                        body->CreateFixture(&fixtureDef);

                        delete [] points;
                    }
                }
                else
                {
                    log("body: %s not found!", name.c_str());
                }
                break;
            }
        }
    }


}