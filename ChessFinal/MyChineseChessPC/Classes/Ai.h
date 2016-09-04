#ifndef AI_H
#define AI_H
#include "cocos2d.h"

USING_NS_CC;

class SceneGame;
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

class AI
{
public:
    AI();
    SceneGame * _game;
    AI(SceneGame *game);
    static int _score[7];

    int getScore();

     CCArray * getALLPossibleMove();
      void getALLPossibleMove(int idx,CCArray * arr);



      int getMinValue(int level,int maxScore);
      int getMaxValue(int level,int minScore);
      Step * GenOneMove(int level=2);

      Step * _setp;

};



#endif // AI_H
