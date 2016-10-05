#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) )
    {
        return false;
    }
    
    /////////////////////////////


    // 메뉴 아이템 생성 및 초기화
    MenuItemFont::setFontSize(20);

    auto item1 = MenuItemFont::create(
        "Insert Data",
        CC_CALLBACK_1(HelloWorld::insertData, this));
    item1->setColor(Color3B(0, 0, 0));

    auto item2 = MenuItemFont::create(
        "Select Data",
        CC_CALLBACK_1(HelloWorld::selectData, this));
    item2->setColor(Color3B(0, 0, 0));

    auto item3 = MenuItemFont::create(
        "Update Data",
        CC_CALLBACK_1(HelloWorld::updateData, this));
    item3->setColor(Color3B(0, 0, 0));

    auto item4 = MenuItemFont::create(
        "Delete Data",
        CC_CALLBACK_1(HelloWorld::deleteData, this));
    item4->setColor(Color3B(0, 0, 0));

    // 메뉴 생성
    auto pMenu = Menu::create(item1, item2, item3, item4, nullptr);
    pMenu->alignItemsVertically();
    pMenu->setPosition(Vec2(240, 80));
    this->addChild(pMenu);



    // 상태보기용 레이블 추가
    lblStatus = LabelTTF::create("a\nb\nc\nd",
        "Arial",
        16,
        Size(480, 200),
        TextHAlignment::CENTER,
        TextVAlignment::CENTER);
    lblStatus->setPosition(Vec2(240, 240));
    lblStatus->setColor(Color3B(0, 0, 0));  // 255, 0, 0
    this->addChild(lblStatus);



    // 데이타베이스 이름 지정
    dbfileName = cocos2d::FileUtils::getInstance()->getWritablePath();
    dbfileName = dbfileName + "testdb.sqlite";
    log("%s", dbfileName.c_str());

    // 데이타베이스 생성
    this->createDatabase();

    return true;
}


void HelloWorld::createDatabase()
{
    sqlite3* pDB = nullptr;
    char* errMsg;
    int result;

    result = sqlite3_open(dbfileName.c_str(), &pDB);

    if (result != SQLITE_OK)
    {
        log("Open Error : Code:%d  Msg:%s", result, errMsg);
    }

    // create database
    std::string sqlStr;
    sqlStr = "create table IF NOT EXISTS TestTabel( \
                             ID integer primary key autoincrement, \
                             name nvarchar(32), \
                             class nvarchar(32))";

    result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
    if (result != SQLITE_OK)
    {
        log("Create Error : Code:%d  Msg:%s", result, errMsg);
    }
    else
    {
        log("Database created successfully!");
    }

    sqlite3_close(pDB);
}

void HelloWorld::insertData(Ref* pSender)
{
    sqlite3* pDB = nullptr;
    char* errMsg = nullptr;
    int result;

    result = sqlite3_open(dbfileName.c_str(), &pDB);

    if (result != SQLITE_OK)
    {
        log("Open Error : Code:%d  Msg:%s", result, errMsg);
    }

    // insert data
    std::string sqlStr;
    sqlStr = "insert into TestTabel(name, class) values ('이름', '직업')";

    result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
    if (result != SQLITE_OK)
    {
        log("Insert Error : Code:%d  Msg:%s", result, errMsg);
    }

    sqlite3_close(pDB);
}

void HelloWorld::selectData(Ref* pSender)
{
    sqlite3* pDB = NULL;
    char* errMsg = nullptr;
    int result;

    result = sqlite3_open(dbfileName.c_str(), &pDB);

    if (result != SQLITE_OK)
    {
        log("Open Error : Code:%d   Msg:%s", result, errMsg);
    }

    // select data
    std::string sqlStr;
    sqlStr = "select ID, name, class from TestTabel";

    sqlite3_stmt* statement;
    if (sqlite3_prepare_v2(pDB, sqlStr.c_str(), -1, &statement, nullptr) == SQLITE_OK)
    {
        std::string str1 = "";
        while (sqlite3_step(statement) == SQLITE_ROW)
        {
            int   row1 = sqlite3_column_int(statement, 0);
            char* row2 = (char *)sqlite3_column_text(statement, 1);
            char* row3 = (char *)sqlite3_column_text(statement, 2);

            log("%d | %s | %s", row1, row2, row3);

            char str2[50] = { 0 };
            sprintf(str2, "\n%d | %s | %s", row1, row2, row3);
            str1 = str1 + str2;
        }

        lblStatus->setString(str1);
    }
    sqlite3_finalize(statement);

    sqlite3_close(pDB);
}

void HelloWorld::updateData(Ref* pSender)
{
    sqlite3* pDB = nullptr;
    char* errMsg = nullptr;
    int result;

    result = sqlite3_open(dbfileName.c_str(), &pDB);

    if (result != SQLITE_OK)
    {
        log("Open Error : Code:%d   Msg:%s", result, errMsg);
    }

    // select data
    std::string sqlStr;
    sqlStr = "update TestTabel set class = '변경' where ID = 1";

    result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
    if (result != SQLITE_OK)
    {
        log("Update Error : Code:%d  Msg:%s", result, errMsg);
    }

    sqlite3_close(pDB);
}

void HelloWorld::deleteData(Ref* pSender)
{
    sqlite3* pDB = nullptr;
    char* errMsg = nullptr;
    int result;

    result = sqlite3_open(dbfileName.c_str(), &pDB);

    if (result != SQLITE_OK)
    {
        log("Open Error : Code:%d   Msg:%s", result, errMsg);
    }

    // select data
    std::string sqlStr;
    sqlStr = "delete from TestTabel where ID > 1";

    result = sqlite3_exec(pDB, sqlStr.c_str(), nullptr, nullptr, &errMsg);
    if (result != SQLITE_OK)
    {
        log("Delete Error : Code:%d  Msg:%s", result, errMsg);
    }

    sqlite3_close(pDB);
}
