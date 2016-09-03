#ifndef SCENEGAME_H
#define SCENEGAME_H
#include "cocos2d.h"
USING_NS_CC;
#include "Stone.h"


class SceneGame : public CCLayer
{
public:
    SceneGame();

    static CCScene *scene(bool red);
    //CREATE_FUNC(SceneGame);
    static  SceneGame * create(bool red);
    bool  init(bool red);

    CCPoint _plateOffSet;
    CCPoint _stoneOffSet;/*_s[0] position*/

    float _d;
    Stone * _s[32];
};

#endif // SCENEGAME_H
