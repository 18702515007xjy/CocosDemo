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
	// 还要注意自己写的create方法记得声明为静态的！
	static UDLRController* createWithTarget(Node* node);

	void onKeyPressed(EventKeyboard::KeyCode c, Event* e);

public:
	void setTatget(Node* tar){ _target = tar; }
	void setSpeed(float speed){ _speed = speed; }

public:
	// 枚举如果加上class关键字，那么其值转换成int需要用static_cast
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