/*
 
 MIT License.

 Copyright (c) 2012 Creeng Ltd.
 Copyright (c) 2012 Flightless Ltd.  
 Copyright (c) 2010 Clever Hamster Games.
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 
*/

//
//  vrope.cpp
//
//  Created by patrick on 14/10/2010.
//  Modified by Flightless www.flightless.co.nz 20/4/2012
//  Ported to cocos2d-x by Creeng www.creeng.com 12/7/2012
//  Modified by Jaehwan Lee (gikimirane@naver.com) 20/4/2013
//  Modified by Jaehwan Lee (gikimirane@naver.com) 09/6/2015
//

#include "vrope.h"

using namespace cocos2d;

VRope::VRope(b2Body* body1, b2Body* body2, SpriteBatchNode* ropeBatchNode)
    : bodyA(body1), bodyB(body2), spriteSheet(ropeBatchNode), jointAB(0)
{
    Vec2 pointA = Vec2(bodyA->GetPosition().x*PTM_RATIO, bodyA->GetPosition().y*PTM_RATIO);
    Vec2 pointB = Vec2(bodyB->GetPosition().x*PTM_RATIO, bodyB->GetPosition().y*PTM_RATIO);
//    createRope(pointA, pointB);
}

// Flightless, init rope using a joint between two bodies
VRope::VRope(b2Joint* joint, SpriteBatchNode* ropeBatchNode)
    : jointAB(joint), spriteSheet(ropeBatchNode), bodyA(0), bodyB(0)
{
    Vec2 pointA = Vec2(jointAB->GetAnchorA().x*PTM_RATIO, jointAB->GetAnchorA().y*PTM_RATIO);
    Vec2 pointB = Vec2(jointAB->GetAnchorB().x*PTM_RATIO, jointAB->GetAnchorB().y*PTM_RATIO);
//    createRope(pointA, pointB);
}

VRope::VRope(b2RopeJoint* aJoint, SpriteBatchNode* aRopeBatchNode)
{
    joint = aJoint;
    Vec2 pointA = Vec2(joint->GetAnchorA().x*PTM_RATIO, joint->GetAnchorA().y*PTM_RATIO);
    Vec2 pointB = Vec2(joint->GetAnchorB().x*PTM_RATIO, joint->GetAnchorB().y*PTM_RATIO);
    spriteSheet = aRopeBatchNode;
    createRope(pointA, pointB, joint->GetMaxLength()*PTM_RATIO);
//    vSticks.retain();
}

VRope::VRope(b2RopeJoint* aJoint, SpriteBatchNode* aRopeBatchNode,
             std::vector<VPoint*> points, std::vector<VStick*> sticks,
             std::vector<Sprite*> sprites)
{
    joint = aJoint;
    spriteSheet = aRopeBatchNode;
    vPoints = points;
    vSticks = sticks;
    ropeSprites = sprites;
    numPoints = (int)vPoints.size();
}

VRope::VRope(const Vec2& pointA, const Vec2& pointB, SpriteBatchNode* ropeBatchNode)
    : spriteSheet(ropeBatchNode), bodyA(0), bodyB(0), jointAB(0)
{
//    createRope(pointA, pointB);
}

VRope::~VRope()
{
    for(int i=0; i<numPoints; ++i)
    {
        delete vPoints[i];
        if (i!=numPoints-1) 
        {
            delete vSticks[i];
        }
    }
}

void VRope::update(float dt)
{
    Vec2 pointA, pointB;

    pointA = Vec2(joint->GetAnchorA().x*PTM_RATIO, joint->GetAnchorA().y*PTM_RATIO);
    pointB = Vec2(joint->GetAnchorB().x*PTM_RATIO, joint->GetAnchorB().y*PTM_RATIO);

    updateWithPoints(pointA, pointB, dt);
}

// Flightless, update rope by pre-integrating the gravity each step (optimised for changing gravity)
// nb. uses current global point gravity, should probably be moved to a gravity for each rope
void VRope::updateWithPreIntegratedGravity(float dt)
{
    Vec2 pointA, pointB;
    pointA = Vec2(joint->GetAnchorA().x*PTM_RATIO, joint->GetAnchorA().y*PTM_RATIO);
    pointB = Vec2(joint->GetAnchorB().x*PTM_RATIO, joint->GetAnchorB().y*PTM_RATIO);
    
    // pre-integrate current gravity
    Vec2 gravity = VPoint::getGravity() * dt;
        
    // update points with pre-integrated gravity
    updateWithPoints(pointA, pointB, gravity.x, gravity.y);
}

// Flightless, update rope by pre-integrating the gravity each step (optimised for changing gravity)
void VRope::updateWithPreIntegratedGravity(float dt, float gravityX, float gravityY)
{
    Vec2 pointA, pointB;
    pointA = Vec2(joint->GetAnchorA().x*PTM_RATIO, joint->GetAnchorA().y*PTM_RATIO);
    pointB = Vec2(joint->GetAnchorB().x*PTM_RATIO, joint->GetAnchorB().y*PTM_RATIO);
    
    // update points with pre-integrated gravity
    updateWithPoints(pointA, pointB, gravityX*dt, gravityY*dt);
}

// Flightless, update rope by pre-integrating the gravity each step (optimised for changing gravity)
// nb. this uses a gravity with origin (0,0) and an average of bodyA and bodyB positions to determine which way is 'down' for each rope.
void VRope::updateWithPreIntegratedOriginGravity(float dt)
{
    Vec2 pointA, pointB;
    pointA = Vec2(joint->GetAnchorA().x*PTM_RATIO, joint->GetAnchorA().y*PTM_RATIO);
    pointB = Vec2(joint->GetAnchorB().x*PTM_RATIO, joint->GetAnchorB().y*PTM_RATIO);
    
    // pre-integrate gravity, based on average position of bodies
    Vec2 gravityAtPoint = Vec2(-0.5f*(pointA.x + pointB.x), -0.5f*(pointA.y + pointB.y));
//    gravityAtPoint = gravityAtPoint.normalize() * -10.0f * dt; // nb. vrope uses negative gravity!
    gravityAtPoint.normalize(); // nb. vrope uses negative gravity!
    gravityAtPoint = gravityAtPoint * -10.0f * dt; // nb. vrope uses negative gravity!

    // update points with pre-integrated gravity
    updateWithPoints(pointA, pointB, gravityAtPoint.x, gravityAtPoint.y);
}

void VRope::reset()
{
    Vec2 pointA, pointB;
    pointA = Vec2(joint->GetAnchorA().x*PTM_RATIO, joint->GetAnchorA().y*PTM_RATIO);
    pointB = Vec2(joint->GetAnchorB().x*PTM_RATIO, joint->GetAnchorB().y*PTM_RATIO);
    resetWithPoints(pointA, pointB);
}


//Cut the rope..
VRope* VRope::cutRopeInStick(VStick* stick, b2Body* newBodyA, b2Body* newBodyB)
{
    // 1-First, find out where in your array the rope will be cut
    std::vector<VStick *>::iterator nPointStick = std::find(vSticks.begin(), vSticks.end(), stick);
    size_t idx = nPointStick - vSticks.begin() + 1;

    // 3-Keep the sticks in a new array
    std::vector<VStick*> newRopeSticks;

    std::vector<VStick *>::iterator astick;
    for (astick = vSticks.begin()+idx;astick != vSticks.end();++astick)
    {
        newRopeSticks.push_back(*astick);
    }

    // 4-and remove from this object's array
    vSticks.erase(vSticks.begin()+idx, vSticks.end());

    // 5-Same for the sprites
//    std::vector<cocos2d::Sprite*>::iterator nPointSprite = ropeSprites.begin() + idx;
    std::vector<cocos2d::Sprite*> newRopeSprites;

    std::vector<cocos2d::Sprite *>::iterator sprite;
    for(sprite = ropeSprites.begin()+idx;sprite != ropeSprites.end();++sprite)
    {
        newRopeSprites.push_back(*sprite);
    }

    ropeSprites.erase(ropeSprites.begin()+idx, ropeSprites.end());

    // 6-Number of points is always the number of sticks + 1
//    std::vector<VPoint*>::iterator nPoint = vPoints.begin() + idx;
    std::vector<VPoint*> newRopePoints;

    std::vector<VPoint *>::iterator point;
    for(point = vPoints.begin()+idx;point != vPoints.end();++point)
    {
        newRopePoints.push_back(*point);
    }

    vPoints.erase(vPoints.begin()+idx, vPoints.end());

    // 7-The removeObjectsInRange above removed the last point of
    // this rope that now belongs to the new rope. You need to clone
    // that VPoint and add it to this rope, otherwise you'll have a
    // wrong number of points in this rope
    VPoint *pointOfBreak = newRopePoints[0];

    VPoint *newPoint = new VPoint();
    newPoint->setPos(pointOfBreak->x,pointOfBreak->y);
    vPoints.push_back(newPoint);

     // 7-And last: fix the last VStick of this rope to point to this new point
    // instead of the old point that now belongs to the new rope
    int n;
    n = (int)vSticks.size()-1;
    if(n < 0)
        n = 0;

    VStick *lastStick = vSticks[n];

    lastStick->setPointB(newPoint);

    // 8-This will determine how long the rope is now and how long the new rope will be
    float32 cutRatio = (float32)idx / (numPoints - 1);

    // 9-Fix my number of points
    numPoints = (int)idx + 1;

    // Position in Box2d world where the new bodies will initially be
    b2Vec2 newBodiesPosition = b2Vec2(pointOfBreak->x / PTM_RATIO, pointOfBreak->y / PTM_RATIO);

    // Get a reference to the world to create the new joint
    b2World *world = newBodyA->GetWorld();

    // 10-Re-create the joint used in this VRope since bRopeJoint does not allow
    // to re-define the attached bodies
    b2RopeJointDef jd;
    jd.bodyA = joint->GetBodyA();
    jd.bodyB = newBodyB;
    jd.localAnchorA = joint->GetLocalAnchorA();
    jd.localAnchorB = b2Vec2(0, 0);
    jd.maxLength = joint->GetMaxLength() * cutRatio;
    newBodyB->SetTransform(newBodiesPosition, 0.0);

     b2RopeJoint *newJoint1 = (b2RopeJoint *)world->CreateJoint(&jd); //create joint

     // 11-Create the new rope joint
     jd.bodyA = newBodyA;
     jd.bodyB = joint->GetBodyB();
     jd.localAnchorA = b2Vec2(0, 0);
     jd.localAnchorB = joint->GetLocalAnchorB();
     jd.maxLength = joint->GetMaxLength() * (1 - cutRatio);
     newBodyA->SetTransform(newBodiesPosition, 0.0);

     b2RopeJoint *newJoint2 = (b2RopeJoint *)world->CreateJoint(&jd); //create joint

     // 12-Destroy the old joint and update to the new one
     world->DestroyJoint(joint);
     joint = newJoint1;

     VRope *newRope = new VRope(newJoint2, spriteSheet, newRopePoints, newRopeSticks, newRopeSprites);
     return newRope;
}


    
void VRope::createRope(const Vec2& pointA, const Vec2& pointB, float32 distance)
{
//    float distance = ccpDistance(pointA,pointB);
    int segmentFactor = 20; // 16; //12; //increase value to have less segments per rope, decrease to have more segments
    numPoints = (int) distance/segmentFactor;

//    vSticks = new vector<VStick*>;

    Vec2 diffVector = pointB - pointA;
    float multiplier = distance / (numPoints-1);
    antiSagHack = 0.1f; //HACK: scale down rope points to cheat sag. set to 0 to disable, max suggested value 0.1
    for (int i=0;i<numPoints;i++) 
    {
//        Vec2 tmpVector = pointA + diffVector.normalize() * (multiplier*i*(1 - antiSagHack));
        diffVector.normalize();
        Vec2 tmpVector = pointA + diffVector * (multiplier*i*(1 - antiSagHack));
        VPoint *tmpPoint = new VPoint();
        tmpPoint->setPos(tmpVector.x, tmpVector.y);
        vPoints.push_back(tmpPoint);
    }
    for (int i=0;i<numPoints-1;i++) 
    {
        VStick* tmpStick = new VStick(vPoints[i], vPoints[i+1]);
        vSticks.push_back(tmpStick);
    }

    if(spriteSheet) {
        for(int i=0;i<numPoints-1;i++) {
            VPoint* point1 = vSticks[i]->getPointA();
            VPoint* point2 = vSticks[i]->getPointB();
            Point stickVector = Vec2(point1->x, point1->y) - Vec2(point2->x, point2->y);
            float stickAngle = stickVector.getAngle();

            float f = spriteSheet->getTextureAtlas()->getTexture()->getPixelsHigh() / CC_CONTENT_SCALE_FACTOR();
            Rect r = Rect(0, 0, multiplier, f);
            Sprite* tmpSprite = Sprite::createWithTexture(spriteSheet->getTexture(), r);

            Texture2D::TexParams params = { GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT };
            tmpSprite->getTexture()->setTexParameters(params);
            tmpSprite->setPosition(Vec2(point1->x, point1->y).getMidpoint(Vec2(point2->x, point2->y)));
            tmpSprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(stickAngle));
            spriteSheet->addChild(tmpSprite);
            ropeSprites.push_back(tmpSprite);
        }
    }
}

void VRope::resetWithPoints(const Vec2& pointA, const Vec2& pointB)
{
    float distance = pointA.getDistance(pointB);
    Vec2 diffVector = pointB - pointA;
    float multiplier = distance / (numPoints - 1);
    for(int i=0;i<numPoints;i++) {
//        Vec2 tmpVector = pointA + (diffVector.normalize() * (multiplier*i*(1 - antiSagHack)));
        diffVector.normalize();
        Vec2 tmpVector = pointA + (diffVector * (multiplier*i*(1 - antiSagHack)));
        VPoint *tmpPoint = vPoints[i];
        tmpPoint->setPos(tmpVector.x, tmpVector.y);
    }
}

void VRope::updateWithPoints(const Vec2& pointA, const Vec2& pointB, float dt)
{
    //manually set position for first and last point of rope
    vPoints[0]->setPos(pointA.x, pointA.y);
    vPoints[numPoints -1]->setPos(pointB.x, pointB.y);
    
    //update points, apply gravity
    for(int i=1;i<numPoints-1;i++) {
        vPoints[i]->applyGravity(dt);
        vPoints[i]->update();
    }
    
    //contract sticks
    int iterations = 4;
    for(int j=0;j<iterations;j++) {
        for(int i=0;i<numPoints-1;i++) {
            vSticks[i]->contract();
        }
    }
}

void VRope::updateWithPoints(const Vec2& pointA, const Vec2& pointB, float gxdt, float gydt)
{
    //manually set position for first and last point of rope
    vPoints[0]->setPos(pointA.x, pointA.y);
    vPoints[numPoints-1]->setPos(pointB.x, pointB.y);
    
    //update points, apply pre-integrated gravity
    for(int i=1;i<numPoints-1;i++) {
        vPoints[i]->applyGravityxdt(gxdt, gydt);
        vPoints[i]->update();
    }
    
    //contract sticks
    int iterations = 4;
    for(int j=0;j<iterations;j++) {
        for(int i=0;i<numPoints-1;i++) {
            vSticks[i]->contract();
        }
    }
}

/*
void VRope::debugDraw()
{
    //Depending on scenario, you might need to have different Disable/Enable of Client States
    //glDisableClientState(GL_TEXTURE_2D);
    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    //glDisableClientState(GL_COLOR_ARRAY);
    //set color and line width for ccDrawLine

    DrawPrimitives::setDrawColor4B(0.0f, 0.0f, 1.0f, 1.0f);
    glLineWidth(5.0f);

    for(int i=0;i<numPoints-1;i++) {
        //"debug" draw
        VPoint *pointA = vSticks[i]->getPointA();
        VPoint *pointB = vSticks[i]->getPointB();
        DrawPrimitives::drawPoint(Vec2(pointA->x, pointA->y));
        DrawPrimitives::drawPoint(Vec2(pointB->x, pointB->y));
        //DrawPrimitives::drawLine(Point(pointA.x, pointA.y), Point(pointB.x, pointB.y));
    }

    //restore to white and default thickness
    DrawPrimitives::setDrawColor4B(1.0f, 1.0f, 1.0f, 1.0f);
    glLineWidth(1);
    //glEnableClientState(GL_TEXTURE_2D);
    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);
}
*/

void VRope::updateSprites()
{
    if(spriteSheet) {
        for(int i=0;i<numPoints-1;i++) {
            VPoint *point1 = vSticks[i]->getPointA();
            VPoint *point2 = vSticks[i]->getPointB();
            Vec2 point1_ = Vec2(point1->x, point1->y);
            Vec2 point2_ = Vec2(point2->x, point2->y);
            float stickAngle = (point1_ - point2_).getAngle();
            Sprite *tmpSprite = ropeSprites[i];
            tmpSprite->setPosition(point1_.getMidpoint(point2_));
            tmpSprite->setRotation(-CC_RADIANS_TO_DEGREES(stickAngle));
        }
    }
}

void VRope::removeSprites()
{
    for(int i=0;i<numPoints-1;i++) {
        Sprite *tmpSprite = ropeSprites[i];
        spriteSheet->removeChild(tmpSprite, true);
    }
    ropeSprites.clear();
}
