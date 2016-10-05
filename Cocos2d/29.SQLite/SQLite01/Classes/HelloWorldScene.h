#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "sqlite3.h"

class HelloWorld : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(HelloWorld);

    void createDatabase();
    void insertData(Ref* pSender);
    void selectData(Ref* pSender);
    void updateData(Ref* pSender);
    void deleteData(Ref* pSender);

    std::string dbfileName;
    cocos2d::LabelTTF* lblStatus;
};

#endif // __HELLOWORLD_SCENE_H__
