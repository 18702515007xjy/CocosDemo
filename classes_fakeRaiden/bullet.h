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
	// �����ӵ������Ļһ�
	void setOwner(MyPlane* owner){ s_owner = owner; }
private:
	Sprite* _bullet;
	float _speed;

	/*static */MyPlane* s_owner;
	// Ϊɶ�����óɾ�̬�ģ��ӵ���Ȼ���󣬵��ǽ����п������Եл�����Ŀǰû�ел���
};

#endif