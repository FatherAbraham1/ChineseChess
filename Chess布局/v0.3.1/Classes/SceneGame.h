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
    Stone * _s[32];
    bool _redTurn;
    bool _redSide;
    CCArray* _steps;

    //selecting chess stone!!
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    //void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    int  _selectid;
    bool getClickPos(CCPoint pointWin,int &x,int &y);
    int getStone(int x,int y);
    void setSelectID(int id);

    CCSprite *_selectSprite;

    //move stone!!
    void moveStone(int moveid,int killid,int x,int y);
    CCPoint getStonePos(int x,int y);

    //back chess
    void back(CCObject *);
};

#endif // SCENEGAME_H
