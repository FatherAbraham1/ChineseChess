#include "SceneGame.h"

SceneGame::SceneGame()
{
}

CCScene *SceneGame::scene(bool red){

    CCScene *scene=CCScene::create();
    SceneGame *layer=SceneGame::create(red);
    scene->addChild(layer);
    return scene;
}

SceneGame *SceneGame::create(bool red){

    SceneGame *pRet=new SceneGame();
    if(pRet){
        if(pRet->init(red)){
            pRet->autorelease();
        }
        else{
                pRet->release();
                return NULL;
            }
    }else{

        return NULL;
    }

    return pRet;

}


bool SceneGame::init(bool red){
 CCSize winSize=CCDirector::sharedDirector()->getWinSize();
 this->_plateOffSet=ccp(20,10);//init plate offset
 this->_stoneOffSet=ccp(63,33);
 this->_d=46;


    if(!CCLayer::init()){
        return false;


    }else{
        //desktop
        CCSprite *desk=CCSprite::create("floor.jpg");
         this->addChild(desk);
        desk->setPosition(ccp(winSize.width/2,winSize.height/2));
        desk->setScaleX(winSize.width/desk->getContentSize().width);
        desk->setScaleY(winSize.height/desk->getContentSize().height);

         //add plane
        CCSprite *plate=CCSprite::create("background.png");
        this->addChild(plate);
        plate->setAnchorPoint(CCPointZero);
        plate->setPosition(_plateOffSet);
        plate->setScale((winSize.height-_plateOffSet.y*2)/plate->getContentSize().height);


        //add stone
//        _s[i]=Stone::create();
//        _s[i]->setDead(false);
//        _s[i]->setType(Stone::CHE);

        /*
        for(int i=0;i<16;i++){

            Stone[i]=Stone::create(Stone::_initPos[i]._type,true,i);
        }
        for(int i=16;i<32;i++){

            Stone[i]=Stone::create(Stone::_initPos[i-16]._type,false,i);

        }
        */
        for(int i=0;i<32;i++){

            _s[i]=Stone::create(i);
            addChild(_s[i]);
          _s[i]->setPosition(ccp(_s[i]->getX()*_d,_s[i]->getY()*_d)+_stoneOffSet);

        }



        return true;
    }

}
