#include "Stone.h"

Stone::Stone()
{
}


Stone::InitPos Stone::_initPos[16]={
    {0,0,Stone::CHE},
    {1,0,Stone::MA},
    {2,0,Stone::XIANG},
    {3,0,Stone::SHI},
    {4,0,Stone::JIANG},
    {5,0,Stone::SHI},
    {6,0,Stone::XIANG},
    {7,0,Stone::MA},
    {8,0,Stone::CHE},

    {1,2,Stone::PAO},
    {7,2,Stone::PAO},

    {0,3,Stone::BING},
    {2,3,Stone::BING},
    {4,3,Stone::BING},
    {6,3,Stone::BING},
    {8,3,Stone::BING},


};


void Stone::reset(bool red){
    this->setDead(false);
    if(red){
        if(_id<16 ){

            this->setX(_initPos[_id]._x);
            this->setY(_initPos[_id]._y);

        }else{//rotate
            this->setX(8-_initPos[_id-16]._x);
            this->setY(9-_initPos[_id-16]._y);
        }

    }else{

        if(_id<16 ){

            this->setX(8-_initPos[_id]._x);
            this->setY(9-_initPos[_id]._y);

        }else{//rotate
            this->setX(_initPos[_id-16]._x);
            this->setY(_initPos[_id-16]._y);
        }
    }




}
