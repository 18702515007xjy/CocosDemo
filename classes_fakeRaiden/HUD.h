#ifndef _HUD_H_
#define _HUD_H_

#include "cocos2d.h"
USING_NS_CC;

class HUD :public LayerColor
{
public:
	bool init();
	CREATE_FUNC(HUD);
public:
	~HUD(){ _dbLbl->release(); _dbLbl2->release(); _dbLbl3->release(); }

	CC_SYNTHESIZE_READONLY(LabelTTF*, _dbLbl, Label);
	CC_SYNTHESIZE_READONLY(LabelTTF*, _dbLbl2, Label2);
	CC_SYNTHESIZE_READONLY(Label*, _dbLbl3, Label3);

};

#endif