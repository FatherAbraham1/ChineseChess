#include "Ai.h"
#include "SceneGame.h"
//enum TYPE{JIANG,SHI,XIANG,CHE,MA,PAO,BING};
int AI::_score[7]={1500,10,10,100,50,50,20};


AI::AI(SceneGame *game):_game(game)
{

}

int AI::getScore(){
    int blackScore=0;
    int redScore=0;
    for(int i=0;i<32;i++){
        Stone * s=_game->_s[i];
        if(s->getDead())continue;
        if(s->getRed())redScore+=_score[s->getType()];
        else  blackScore+=_score[s->getType()];
    }
    return blackScore-redScore;
}

void  AI::getALLPossibleMove(int idx,CCArray *arr){
    Stone *s =_game->_s[idx];
    if(s->getDead())return;

    for(int x=0;x<=8;x++){
        for (int y=0;y<=9;y++){

            int killid=_game->getStone(x,y);
            if(killid!=-1&&_game->_s[killid]->getRed()==s->getRed())
                continue;

            if(x==s->getX()&&y==s->getY())
                continue;



            if(_game->canMove(s->getID(),killid,x,y)){
               Step *step =Step::create(idx,killid,s->getX(),s->getY(),x,y);
                arr->addObject(step);
            }
        }
    }

}

CCArray * AI::getALLPossibleMove(){
    CCArray *arr=CCArray::create();

    if(_game->_redTurn){
        for(int i=0;i<16;i++){
           getALLPossibleMove(i,arr);
            //Stone *s=_game->_s[i];
        }
    }else{
        for(int i=16;i<32;i++){
           getALLPossibleMove(i,arr);
            //Stone *s=_game->_s[i];
        }
    }


    return arr;
}

int AI::getMaxValue(int level){
     if(level==0) return getScore();

    int maxScore=-1000000;
   //find all possible situation,try every possible,invoke canMove

        CCArray *possibleMove =getALLPossibleMove();
        CCObject *obj;
        CCARRAY_FOREACH(possibleMove,obj){
            Step * step =(Step *)obj;
            _game->fakeMove(step);
            //int score=this->getScore();
            int score=getMinValue(level-1);
            _game->unfakeMove(step);
            if(score>maxScore){
                maxScore=score;
            }
        }
        return maxScore;
}


int AI::getMinValue(int level){
    if(level==0) return getScore();


    int minScore=1000000;
   //find all possible situation,try every possible,invoke canMove

        CCArray *possibleMove =getALLPossibleMove();
        CCObject *obj;
        CCARRAY_FOREACH(possibleMove,obj){
            Step * step =(Step *)obj;
            _game->fakeMove(step);
            //int score=this->getScore();
            int score=getMaxValue(level-1);
            _game->unfakeMove(step);
            if(score<minScore){
                minScore=score;
            }
        }
        return minScore;

}
Step *  AI::GenOneMove(int level){



    int maxScore=-1000000;
    Step * ret;
    //find all possible situation,try every possible,invoke canMove

    CCArray *possibleMove =getALLPossibleMove();
    CCObject *obj;
    CCARRAY_FOREACH(possibleMove,obj){
        Step * step =(Step *)obj;
        _game->fakeMove(step);
        //int score=this->getScore();
        int score=getMinValue(level-1);
        _game->unfakeMove(step);
        if(score>maxScore){
            maxScore=score;
            ret=step;

        }
    }
    return ret;

}
