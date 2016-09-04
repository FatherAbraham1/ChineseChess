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
    _redTurn=true;
    _redSide=red;
    _steps=CCArray::create();
    _steps->retain();
    this->_ai=new AI(this);


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
            //_s[i]->setPosition(ccp(_s[i]->getX()*_d,_s[i]->getY()*_d)+_stoneOffSet);
            //_s[i]->setPosition(this->getStonePos(_s[i]->getX(),_s[i]->getY()));
            //setRealPos(_s[i]);
            _s[i]->setPosition(ccp(CCRANDOM_0_1()*winSize.width,//
                                   CCRANDOM_0_1()*winSize.height));
            CCMoveTo * move=CCMoveTo::create(1,this->getStonePos(_s[i]->getX(),_s[i]->getY()));
            _s[i]->runAction(move);

        }
        //and touch,move the ChessStone!!Let's do it!!
        setTouchEnabled(true);
        setTouchMode(kCCTouchesOneByOne);


        //back menu item
        CCMenu *menu=CCMenu::create();
        CCMenuItem * item=CCMenuItemImage::create("regret.jpg","regret.jpg",this,menu_selector(SceneGame::back));
        //CCMenuItemFont * item=CCMenuItemFont::create("huiqi",this,menu_selector(SceneGame::back));
        menu->addChild(item);
        addChild(menu);
        item->setPositionX(item->getPositionX()+200);
        item->setPositionY(item->getPositionY()-120);




        return true;
    }

}
void  SceneGame::moveComplete(CCNode * moveStone, void * _killid){
    int killid=(int)(intptr_t)_killid;


    moveStone->setZOrder(moveStone->getZOrder()-10);
    if(killid!=-1){
        _s[killid]->setDead(true);
        _s[killid]->setVisible(false);

        if(_s[killid]->getType()==Stone::JIANG){
            CCDirector::sharedDirector()->replaceScene(SceneGame::scene(!_redSide));
        }
    }
    _selectid=-1;
    _selectSprite->setVisible(false);
    _redTurn=!_redTurn;


    if(!_redTurn ){

        Step * step=_ai->GenOneMove(4);
        this->moveStone(step->_moveid,step->_killid,step->_xTO,step->_yTO);
       // step->release();
    }


}

void SceneGame::setRealPos(Stone *s){

    s->setPosition(getStonePos(s->getX(),s->getY()));
}

void SceneGame::back(CCObject *){


    if(_steps->count()==0){
        return;
    }
    Step *step=(Step*)_steps->lastObject();

    _s[step->_moveid]->setX(step->_xForm);
    _s[step->_moveid]->setY(step->_yForm);
    _s[step->_moveid]->setPosition(getStonePos(step->_xForm,step->_yForm));


    if(step->_killid!=-1){
        _s[step->_killid]->setVisible(true);
        _s[step->_killid]->setDead(false);
    }

    _redTurn=!_redTurn;
    _steps->removeLastObject();




}


void SceneGame::setSelectID(int id){
    if(id==-1)
        return ;

    if(_s[id]->getRed()!=_redTurn)
        return;

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

        moveStone(_selectid,ClickedId,x,y);
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

CCPoint SceneGame::getStonePos(int x, int y){
    int xx=x*_d;
    int yy=y*_d;
    return ccp(xx,yy)+_stoneOffSet;

}

int SceneGame::getStoneCount(int x0, int y0, int x, int y){
    int ret=0;
    if(x0!=x&&y0!=y)return -1;
    if(x0==x&&y0==y)return -1;

    if(x0==x){
        int min=y0<y?y0:y;
        int max=y0>y?y0:y;
        for(int yy=min+1;yy<max;yy++){
            if(getStone(x,yy)!=-1)++ret;
        }
    }else{
        int min=x0<x?x0:x;
        int max=x0>x?x0:x;
        for(int xx=min+1;xx<max;xx++){
            if(getStone(xx,y)!=-1)++ret;
        }
    }
    return ret;
}

bool SceneGame::canMoveJiang(int moveid, int killid, int x, int y){

    //xiou gai le
    if(killid!=-1){
        Stone *skill=_s[killid];
        if(skill->getType()==Stone::JIANG){
            return canMoveChe(moveid,x,y);
        }

    }



    Stone * s=_s[moveid];
    int x0=s->getX();
    int y0=s->getY();
    int xoff=abs(x0-x);
    int yoff=abs(y0-y);
    //1.zou yi ge
/*
 * first write:
   if(xoff>1) return false;
    if(yoff>1)return false;
    if((xoff+yoff)!=1) return false;
 */
    int d=xoff*10+yoff;
    if(d!=1&&d!=10)return false;

    //2.buneng chu jiugong
    if(x<3||x>5)return false;
    if(_redSide==s->getRed()){
        if(y<0||y>2)return false;
    }else{
        if(y<7||y>9)return false;
    }

    //3.dui sha laojiang

    return true;
}

bool SceneGame::canMoveShi(int moveid, int x, int y){
    Stone * s=_s[moveid];
    int x0=s->getX();
    int y0=s->getY();
    int xoff=abs(x0-x);
    int yoff=abs(y0-y);
    //1.zou yi ge
/*
     if(xoff!=1) return false;
    if(yoff!=1)return false;
 */
    int d=xoff*10+yoff;
    if(d!=11)return false;

    //2.buneng chu jiugong
    if(x<3||x>5)return false;
    if(_redSide==s->getRed()){
        if(y<0||y>2)return false;
    }else{
        if(y<7||y>9)return false;
    }
    return true;
}

bool SceneGame::canMoveXiang(int moveid, int x, int y){
    Stone * s=_s[moveid];
    int x0=s->getX();
    int y0=s->getY();
    int xoff=abs(x0-x);
    int yoff=abs(y0-y);
    //1.zou yi ge
 /*   if(xoff!=2) return false;
    if(yoff!=2)return false;
*/
    int d=xoff*10+yoff;
    if(d!=22)return false;

    //2.fei tian,tian xiang eye
    int xm=(x0+x)/2;
    int ym=(y0+y)/2;
    int id=getStone(xm,ym);
    if(id!=-1)return false;

    //3.pan duan shi fou neng guo revier;
    if(_redSide==s->getRed()){
        if(y>4)return false;
    }else{
        if(y<5)return false;
    }

    return true;
}

bool SceneGame::canMoveMa(int moveid, int x, int y){
    Stone * s=_s[moveid];
    int x0=s->getX();
    int y0=s->getY();
    int xoff=abs(x0-x);
    int yoff=abs(y0-y);
    //1.zou yi ge
 /*   if(xoff!=2) return false;
    if(yoff!=2)return false;
*/
    int d=xoff*10+yoff;
    if(d!=12&&d!=21)return false;

     //2.MA  bie jiao
    int xm=0;
    int ym=0;
    if(d==12){
        xm=x0;
        ym=(y0+y)/2;

    }else{

        xm=(x0+x)/2;
        ym=y0;
    }

    if(getStone(xm,ym)!=-1)return false;

    return true;
}

bool SceneGame::canMoveChe(int moveid, int x, int y){
    Stone * s=_s[moveid];
    int x0=s->getX();
    int y0=s->getY();

    if(getStoneCount(x0,y0,x,y)!=0)return false;

    return true;
}

bool SceneGame::canMovePao(int moveid, int killid, int x, int y){
    Stone * s=_s[moveid];
    int x0=s->getX();
    int y0=s->getY();

    if(this->getStoneCount(x0,y0,x,y)==1&& killid!=-1)return true;
    if(this->getStoneCount(x0,y0,x,y)==0&& killid==-1)return true;
    //return canMoveChe(moveid,x,y);
    return false;
}
bool SceneGame::canMoveBing(int moveid, int x, int y){
    Stone * s=_s[moveid];
    int x0=s->getX();
    int y0=s->getY();
    int xoff=abs(x0-x);
    int yoff=abs(y0-y);
    //1.zou yi ge

    int d=xoff*10+yoff;
    if(d!=1&&d!=10)return false;

    //2.BING zhi neng wangqian zhou

    if(_redSide==s->getRed()){
        if(y<y0)return false;

        if(y0<=4&&y==y0)return false;

    }else{
        if(y>y0)return false;

        if(y0>=5&&y==y0)return false;
    }

    return true;
}

bool SceneGame::canMove(int moveid, int killid, int x, int y){
    Stone * s=_s[moveid];
    switch(s->getType()){
    case Stone::JIANG:
        return  canMoveJiang(moveid,killid,x,y);
        //break;
    case Stone::SHI:
        return canMoveShi(moveid,x,y);
       // break;
    case Stone::XIANG:
        return canMoveXiang(moveid,x,y);
       // break;
    case Stone::CHE:
        return canMoveChe(moveid,x,y);
      //  break;
    case Stone::MA:
        return canMoveMa(moveid,x,y);
        //break;
    case Stone::PAO:
        return canMovePao(moveid,killid,x,y);
       // break;
    case Stone::BING:
        return canMoveBing(moveid,x,y);
        //break;

    }

    return false;


}
void SceneGame::moveStone(int moveid, int killid, int x, int y){

    if(killid!=-1&&_s[moveid]->getRed()==_s[killid]->getRed()){

        setSelectID(killid);
        return ;
    }

    bool bCanMove=canMove(moveid,killid,x,y);
    if(!bCanMove){
        return ;
    }

/*#if 0
    //set Step
    Step *step=Step::create(moveid,killid,_s[moveid]->getX(),_s[moveid]->getY(),x,y);
    _steps->addObject(step);
#endif
*/
    Step *step=Step::create(moveid,killid,_s[moveid]->getX(),_s[moveid]->getY(),x,y);
    _steps->addObject(step);
    /*
    if(killid!=-1){
        _s[killid]->setDead(true);
        _s[killid]->setVisible(false);

        if(_s[killid]->getType()==Stone::JIANG){


            CCDirector::sharedDirector()->replaceScene(SceneGame::scene(!_redSide));

        }

    }
*/
    _s[moveid]->setX(x);
    _s[moveid]->setY(y);
    //_s[moveid]->setPosition(getStonePos(x,y));
    // setRealPos(_s[moveid]);

    CCMoveTo * move=CCMoveTo ::create(.5f,getStonePos(x,y));
    CCCallFuncND * call=CCCallFuncND::create(this,//
                                             callfuncND_selector(SceneGame::moveComplete),//
                                             (void *)(intptr_t)killid);
    CCSequence *seq=CCSequence::create(move,call,NULL);

    _s[moveid]->setZOrder(_s[moveid]->getZOrder()+10);
    _s[moveid]->runAction(seq);
    /*
    _selectid=-1;
    _selectSprite->setVisible(false);
    _redTurn=!_redTurn;
*/

}

void SceneGame::fakeMove(Step *step){
    Stone * move=_s[step->_moveid];
    Stone * kill=NULL;
    if(step->_killid!=-1) kill=_s[step->_killid];

    move->setX(step->_xTO);
    move->setY(step->_yTO);
    if(kill) kill->setDead(true);
    this->_redTurn=!this->_redTurn;
}

void SceneGame::unfakeMove(Step * step){
    Stone * move=_s[step->_moveid];
    Stone * kill=NULL;
    if(step->_killid!=-1) kill=_s[step->_killid];

    move->setX(step->_xForm);
    move->setY(step->_yForm);
    if(kill) kill->setDead(false);
    this->_redTurn=!this->_redTurn;

}

