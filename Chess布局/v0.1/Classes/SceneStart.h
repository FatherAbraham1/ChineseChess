#ifndef SCENESTART_H
#define SCENESTART_H

#include "cocos2d.h"
USING_NS_CC;

class SceneStart : public CCLayer
{
public:
    SceneStart();

    static CCScene *scene();
    CREATE_FUNC(SceneStart)
    bool init();


    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void update(float delta);



  private:
    CCSprite * _red;
    CCSprite * _black;
    bool _select;

};

#endif // SCENESTART_H
