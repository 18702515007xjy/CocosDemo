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
		// ����ط�Ҫע�⣺����ӵ��Ƿɻ����ӽڵ㣬��ô�ӵ������ɻ����ƶ���ʹ���ӵ���Զ�ͷɻ���ͬһֱ���ϡ���
		// �������߼�Ӧ���ǡ��ӵ������ȥ�ͺͷɻ��޹��ˡ��������ӵ���ӵ�GameMainLayer�ϡ�
		this->getParent()->addChild(bu);

		//Ϊ�ӵ�����owner
		bu->setOwner(this);

		auto startPos = Vec2(this->getPositionX(), this->getPositionY() + this->getContentSize().height / 2);
		// �ӵ��ӷɻ�ͷ����ʼ�ɳ�ȥ
		bu->launching(startPos);

		// ��ӵ�����
		_bulletsOnScreen.pushBack(static_cast<Node*>(bu));
	} while (0);
}

void MyPlane::startAttacking()
{
	schedule(schedule_selector(MyPlane::shootOnce), 0.1f);
}

void MyPlane::stopAttacking()
{
	// ������Ҫ��������ӵ���

	unschedule(schedule_selector(MyPlane::shootOnce));
}

