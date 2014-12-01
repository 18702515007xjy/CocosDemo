#ifndef _UDLRC_H_
#define _UDLRC_H_

#include "cocos2d.h"
USING_NS_CC;

class UDLRController :public Node
{
public:
	UDLRController(){}
	~UDLRController(){}

	bool initWithTarget(Node* node);
	// ��Ҫע���Լ�д��create�����ǵ�����Ϊ��̬�ģ�
	static UDLRController* createWithTarget(Node* node);

	void onKeyPressed(EventKeyboard::KeyCode c, Event* e);

public:
	void setTatget(Node* tar){ _target = tar; }
	void setSpeed(float speed){ _speed = speed; }

public:
	// ö���������class�ؼ��֣���ô��ֵת����int��Ҫ��static_cast
	enum /*class*/ Direction
	{
		UP = 0,
		DOWN,
		LEFT,
		RIGHT,
	};

private:
	float _speed;
	Size _tarSize;
	Node* _target;
};

#endif