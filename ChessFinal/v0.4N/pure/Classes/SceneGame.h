#ifndef SCENEGAME_H
#define SCENEGAME_H
#include "cocos2d.h"
USING_NS_CC;
#include "Stone.h"


class  Step:public CCObject
{
public:
    int _moveid;
    int _killid;
    int _xForm;
    int _yForm;
    int _xTO;
    int _yTO;

    static Step* create(int moveid,int killid,int xForm,int yForm,int xTo,int yTo){
        Step* step=new Step;
        step->_killid=killid;
        step->_moveid=moveid;
        step->_xForm=xForm;
        step->_yForm=yForm;
        step->_xTO=xTo;
        step->_yTO=yTo;
        step->autorelease();
        return step;

    }
};


class SceneGame : public CCLayer
{
public:
    SceneGame();
    ~SceneGame()
    {
        _steps->release();

    }

    static CCScene *scene(bool red);
    //CREATE_FUNC(SceneGame);
    static  SceneGame * create(bool red);
    bool  init(bool red);

    CCPoint _plateOffSet;
    CCPoint _stoneOffSet;/*_s[0] position*/
    float _d;

    bool _redTurn;
    bool _redSide;
     CCSprite *_selectSprite;
     int  _selectid;
    CCArray* _steps;

    Stone * _s[32];


    void setSelectID(int id);
    //move stone!!
     void moveStone(int moveid,int killid,int x,int y);
     void moveComplete(CCNode *,void *);
     bool canMove(int moveid,int killid,int x,int y);
     bool canMoveJiang(int moveid,int killid,int x,int  y);
     bool canMoveShi(int moveid,int x,int y);
     bool canMoveXiang(int moveid,int x,int  y);
     bool canMoveChe(int moveid,int x,int  y);
     bool canMoveMa(int moveid,int x,int  y);
     bool canMovePao(int moveid,int killid,int x,int  y);
     bool canMoveBing(int moveid,int x,int  y);



     //return -1
     int getStoneCount(int x0,int y0,int x,int y);
   bool getClickPos(CCPoint pointWin,int &x,int &y);
    int getStone(int x,int y);
    CCPoint getStonePos(int x,int y);
    void setRealPos(Stone *s);

    //selecting chess stone!!
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    //void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    //back chess
    void back(CCObject *);
};

#endif // SCENEGAME_H
