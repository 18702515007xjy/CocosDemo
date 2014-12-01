#ifndef _BULLET_H_
#define _BULLET_H_

#include "cocos2d.h"
USING_NS_CC;
//#include "MyPlane.h"
class MyPlane;

class Bullet :public Node
{
public:
	~Bullet(){ _bullet->release(); }
public:
	bool initWithFile(const char* path);
	static Bullet* createWithFile(const char* path);
	
	const Size& getContentSize() const override;
	void setSpeed(float s){ _speed = s; }
	void launching(const Vec2& startPoint);
	// 设置子弹所属的灰机
	void setOwner(MyPlane* owner){ s_owner = owner; }
private:
	Sprite* _bullet;
	float _speed;

	/*static */MyPlane* s_owner;
	// 为啥不设置成静态的？子弹虽然量大，但是将来有可能来自敌机。（目前没有敌机）
};

#endif