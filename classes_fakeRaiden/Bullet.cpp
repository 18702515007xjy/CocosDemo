#include "bullet.h"
#include "MyPlane.h"

// 静态变量初始化
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
	// 这里别忘记把_bullet添加到node
	addChild(_bullet);

	this->setVisible(false);
	// 发射出去

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

// 发射子弹
void Bullet::launching(const Vec2& startPoint)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();

	this->setPosition(startPoint);
	this->setVisible(true);
	float distance = visibleSize.height - startPoint.y;
	float duration = distance / _speed;

	auto moveUp = MoveTo::create(duration, Vec2(startPoint.x, visibleSize.height + _bullet->getContentSize().height / 2));
	auto moveEndCallBack = CallFunc::create([this](){
		//由于增加了不必要的耦合，还需要：对超出边界的子弹及时移除，避免继续参与碰撞检测。
		do
		{
			CC_BREAK_IF(nullptr == this->s_owner);
			// 如果不#include "MyPlane.h"，会提示【不允许指针指向不完整的类类型】
			// Bullet* const this
			this->s_owner->destroyBullet(this);
		} while (0);

		this->removeFromParent();
	});
	auto sequence = Sequence::create(moveUp, moveEndCallBack, nullptr);

	this->runAction(sequence);

	// 一开始把这里的this都搞成_bullet。造成子弹偏移。
	// 用这种【瘦包装器】一定要注意：到底是用this还是用_bullet
}
