#include "bullet.h"
#include "MyPlane.h"

// ��̬������ʼ��
//MyPlane* Bullet::s_owner = nullptr;

bool Bullet::initWithFile(const char* path)
{
	if (!Node::init())
	{
		return false;
	}
	_speed = 500; //by default
	//s_owner = nullptr;

	float width = 24, height = 24;
	_bullet = Sprite::create(path, CCRectMake(width / 2, 0, width/2, height * 2 / 3));
	_bullet->retain();
	// ��������ǰ�_bullet��ӵ�node
	addChild(_bullet);

	this->setVisible(false);
	// �����ȥ

	return true;
}

Bullet* Bullet::createWithFile(const char* path)
{
	auto pRet = new Bullet();
	if (pRet && pRet->initWithFile(path))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return(pRet);
	}
}

const Size& Bullet::getContentSize() const
{
	return _bullet->getContentSize();
}

// �����ӵ�
void Bullet::launching(const Vec2& startPoint)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	this->setPosition(startPoint);
	this->setVisible(true);
	float distance = visibleSize.height - startPoint.y;
	float duration = distance / _speed;

	auto moveUp = MoveTo::create(duration, Vec2(startPoint.x, visibleSize.height + _bullet->getContentSize().height / 2));
	auto moveEndCallBack = CallFunc::create([this](){
		//���������˲���Ҫ����ϣ�����Ҫ���Գ����߽���ӵ���ʱ�Ƴ����������������ײ��⡣
		do
		{
			CC_BREAK_IF(nullptr == this->s_owner);
			// �����#include "MyPlane.h"������ʾ��������ָ��ָ�������������͡�
			// Bullet* const this
			this->s_owner->destroyBullet(this);
		} while (0);

		this->removeFromParent();
	});
	auto sequence = Sequence::create(moveUp, moveEndCallBack, nullptr);

	this->runAction(sequence);

	// һ��ʼ�������this�����_bullet������ӵ�ƫ�ơ�
	// �����֡��ݰ�װ����һ��Ҫע�⣺��������this������_bullet
}
