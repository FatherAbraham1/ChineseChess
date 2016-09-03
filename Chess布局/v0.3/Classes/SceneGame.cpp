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


      _selectid=-1;
        _selectSprite=CCSprite::create("selected.png");
        this->addChild(_selectSprite);
        _selectSprite->setVisible(false);
        _selectSprite->setZOrder(1000);
        _selectSprite->setScale(.8f);

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

            _s[i]=Stone::create(i,red);
            addChild(_s[i]);
          _s[i]->setPosition(ccp(_s[i]->getX()*_d,_s[i]->getY()*_d)+_stoneOffSet);

        }
//and touch,move the ChessStone!!Let's do it!!
        setTouchEnabled(true);
        setTouchMode(kCCTouchesOneByOne);


        return true;
    }

}

void SceneGame::setSelectID(int id){
    if(id==-1)return ;
    _selectid=id;
 _selectSprite->setVisible(true);
 _selectSprite->setPosition(_s[_selectid]->getPosition());


}

int SceneGame::getStone(int x, int y){

    Stone *s;
    for(int i=0;i<32;i++){
        s=_s[i];
        if(!s->getDead()&&s->getX()==x&&s->getY()==y){
            return s->getID();
        }

    }

    return -1;
}



bool SceneGame::getClickPos(CCPoint pointWin, int &x, int &y){

        for(x=0;x<=8;x++){
            for(y=0;y<=9;y++){
                CCPoint pIntPlate=ccp(x*_d,y*_d)+_stoneOffSet;
                if(pointWin.getDistance(pIntPlate)<_d/2){
                    return true;
                }
            }
        }
    return false;

}

bool SceneGame::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){

    CCPoint pointWin=pTouch->getLocation();
    int x,y;
    if(!getClickPos(pointWin,x,y)){

        return false;

    }

    CCLog("x=%d,y=%d",x,y);
    int ClickedId=getStone(x,y);
        CCLog("11clickedid=%d",ClickedId);


    if(_selectid==-1){
        setSelectID(ClickedId);


    }else{


    }
#if 0
    int ClickedId=getClickID(pTouch);
        if(_selectid==-1){
            _selectid=ClickedId;
        }else{
            move(_selectid,ClickedId);
        }
 #endif
            return true;
}


