#include "SceneStart.h"
#include "SceneGame.h"

SceneStart::SceneStart()
{

}

CCScene * SceneStart::scene(){

    CCScene *scene=CCScene::create();
    SceneStart *layer=SceneStart::create();
    scene->addChild(layer);
    return scene;

}


bool SceneStart::init(){

    CCLayer::init();
    CCSize winSize=CCDirector::sharedDirector()->getWinSize();


//init two chess
    CCSprite * bkr=CCSprite::create("bkg2.png");
    addChild(bkr);
    CCSprite * bkb=CCSprite::create("bkg1.png");
    this->addChild(bkb);

    _red=bkr;
    _black=bkb;
//cal position
    bkr->setPosition(ccp(winSize.width/2-100,winSize.height/2));
     bkb->setPosition(ccp(winSize.width/2+100,winSize.height/2));

//SceneMove
     setTouchEnabled(true);
     setTouchMode(kCCTouchesOneByOne);

    return true;

}

//must have!!
bool SceneStart::ccTouchBegan(CCTouch *pTouch, CCEvent * pEvent){

    return true;

}

void SceneStart::ccTouchEnded(CCTouch *pTouch, CCEvent * pEvent){
 CCSize winSize=CCDirector::sharedDirector()->getWinSize();
    CCPoint ptClick=pTouch->getLocation();
    bool bClickStone=false;
    if(_red->boundingBox().containsPoint(ptClick)){
        this->_select=true;
        bClickStone=true;

    }else if(_black->boundingBox().containsPoint(ptClick))
    {

        this->_select=false;
        bClickStone=true;
    }
    if(bClickStone){
        //Move Action
        CCMoveTo * moveTo1=CCMoveTo::create(1,ccp(winSize.width/2,winSize.height/2));
        CCMoveTo * moveTo2=CCMoveTo::create(1,ccp(winSize.width/2,winSize.height/2));
        CCRotateBy *rotate1=CCRotateBy::create(1,360);
        CCRotateBy *rotate2=CCRotateBy::create(1,-360);

        CCSpawn * spawn1=CCSpawn::create(moveTo1,rotate1,NULL);
        CCSpawn * spawn2=CCSpawn::create(moveTo2,rotate2,NULL);
        _red->runAction(spawn1);
        _black->runAction(spawn2);

        //set a schedule
        scheduleUpdate();

    }

}


void SceneStart::update(float delta){//collision detection
    float x1=_red->getPositionX();
     float x2=_black->getPositionX();
     if(abs(x1-x2)<_red->getContentSize().width){
         //startGame();
         CCDirector::sharedDirector()->replaceScene(SceneGame::scene(this->_select));
     }

}
