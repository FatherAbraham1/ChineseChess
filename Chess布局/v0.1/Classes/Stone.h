#ifndef STONE_H
#define STONE_H
#include "cocos2d.h"

USING_NS_CC;
#include "Stone.h"



class Stone : public CCSprite
{
public:
    Stone();

    enum TYPE{JIANG,SHI,XIANG,CHE,MA,PAO,BING};
/*
    static Stone *create(TYPE type,bool red,int id){
        Stone *s =new Stone();
        s->init(type,red);
        s->autorelease();
        return s;

    }*/
    static Stone *create(int id){
        Stone *s =new Stone();
     //   s->init(type,red,id);
         s->init(id);
        s->autorelease();
        return s;

    }

    void reset();


      //  bool init(TYPE type,bool red,int id){
    bool init(int id){
           // CCSprite::init();
           // _type=type;
           // _red=red;
            _id=id;
            _red=_id<16;
            if(_id<16){
                _type=_initPos[_id]._type;

            }else{
                 _type=_initPos[_id-16]._type;

            }

            const char * stonePic[14]={
                            "rshuai.png",
                           "rshi.png",
                           "rxiang.png",
                           "rche.png",
                           "rma.png",
                           "rpao.png",
                           "rbing.png",

                           "bjiang.png",
                           "bshi.png",
                           "bxiang.png",
                           "bche.png",
                           "bma.png",
                           "bpao.png",
                           "bzu.png"
            };

        //int idx=(red?0:1)*7+type;
            int idx=(_red?0:1)*7+_type;
        CCSprite::initWithFile(stonePic[idx]);
        setScale(.8f);

        reset();
            return true;


/*
            //chess init once
            switch(type){

                case CHE:
//
//                if(red){
//                    CCSprite::initWithFile("rr.png");
//                }else{
//                    CCSprite::initWithFile("br.png");
//                }
//
                break;
            case MA:
                break;
            case JIANG:
                break;
              case XIANG:
                break;
             case SHI:
                break;
               case PAO:
                break;
            case BING:
                break;

            }
 */


        }



    static struct InitPos{

        int _x;
        int _y;
        Stone::TYPE _type;

    } _initPos[16];

    CC_SYNTHESIZE(TYPE,_type,Type)
/* protected:
    Type _type;
 public:
    void setType(Type var){
        _type=type;
    }
    Type getType()const{

        return _type;
    }
  */
    CC_SYNTHESIZE(int,_x,X)
    CC_SYNTHESIZE(int,_y,Y)
    CC_SYNTHESIZE(int ,_id,ID)
    CC_SYNTHESIZE( bool,_dead,Dead)
    CC_SYNTHESIZE(bool,_red,Red)

   /*
     int _x;//code in Plate
    int _y;


    int _id;//0-31
    bool _dead;
    bool _red;//chess color
   */

};


#endif // STONE_H
