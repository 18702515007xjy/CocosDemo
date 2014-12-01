#include "MyPlane.h"
#include "bullet.h"
#include "UDLRController.h"

bool MyPlane::init()
{
	_plane = Sprite::create("myplane.png");
	if (!_plane)
	{
		return false;
	}
	_plane->retain();
	// Alive
	isAlive = true;
	addChild(_plane);

	return true;
}

void MyPlane::setController(Node* ctrl)
{
	this->addChild(ctrl);
}

void MyPlane::shootOnce(float dt)
{
	do
	{
		CC_BREAK_IF(!isAlive);
		auto visibleSize = Director::getInstance()->getVisibleSize();

		//auto bu = Sprite::create("bullet2.png");
		auto bu = Bullet::createWithFile("bullet2.png");
		// 这个地方要注意：如果子弹是飞机的子节点，那么子弹会跟随飞机的移动，使【子弹永远和飞机在同一直线上】。
		// 真正的逻辑应该是【子弹发射出去就和飞机无关了】！所以子弹添加到GameMainLayer上。
		this->getParent()->addChild(bu);

		//为子弹设置owner
		bu->setOwner(this);

		auto startPos = Vec2(this->getPositionX(), this->getPositionY() + this->getContentSize().height / 2);
		// 子弹从飞机头部开始飞出去
		bu->launching(startPos);

		// 添加到集合
		_bulletsOnScreen.pushBack(static_cast<Node*>(bu));
	} while (0);
}

void MyPlane::startAttacking()
{
	schedule(schedule_selector(MyPlane::shootOnce), 0.1f);
}

void MyPlane::stopAttacking()
{
	// 这里需要清空所有子弹吗？

	unschedule(schedule_selector(MyPlane::shootOnce));
}

