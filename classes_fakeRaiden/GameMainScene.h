#ifndef _GAMEMAIN_H_
#define _GAMEMAIN_H_

#include "cocos2d.h"
#include "MyPlane.h"
#include "HUD.h"
USING_NS_CC;

class GameMainScene :public Scene
{
public: //这儿的public不能忘记--！
	bool init();
	CREATE_FUNC(GameMainScene);

};

class GameMainLayer :public LayerColor
{
public:
	bool init();
	CREATE_FUNC(GameMainLayer);

	virtual void update(float dt) override;

	void gameLogic(float dt);

	virtual ~GameMainLayer(){ _plane->release(); _hud->release(); _enemy->release(); }

private:
	MyPlane* _plane;
	HUD* _hud;
	Sprite* _enemy;
};

Rect _getRangeRect(const Node* n);

#endif