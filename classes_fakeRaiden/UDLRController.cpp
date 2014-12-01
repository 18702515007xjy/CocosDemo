#include "UDLRController.h"
#include "MyPlane.h"

bool UDLRController::initWithTarget(Node* tar)
{
	if (!Node::init())
	{
		return false;
	}
	_speed = 160.0f;
	_target = tar;
	_tarSize = _target->getContentSize();
	//_target->retain();
	//_target->autorelease();

	auto listener = EventListenerKeyboard::create();
	//listener->onKeyPressed = std::bind(&UDLRController::onKeyPressed, this);
	listener->onKeyPressed = CC_CALLBACK_2(UDLRController::onKeyPressed, this); //ʹ��CCCALLBACKʱ����Ҫ���ú���ȡ��ַ����
	listener->onKeyReleased = [this](EventKeyboard::KeyCode c, Event* e){
		//this->_target->stopAllActions();
		switch (c)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
		{
			this->_target->stopActionByTag(UP);
		}	break; //break�����Ǽ���
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		{
			this->_target->stopActionByTag(LEFT);
		}	break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		{
			this->_target->stopActionByTag(RIGHT);
		}	break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		{
			this->_target->stopActionByTag(DOWN);
		}	break;
		//case EventKeyboard::KeyCode::KEY_SPACE:
		//	(dynamic_cast<MyPlane*>(_target))->stopAttacking(); break;
		default:
			break;
		}
	};
	// ��ӵ��ַ���Ҳ��������,��˵�ڶ���Ҳ�����ˣ�
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

UDLRController* UDLRController::createWithTarget(Node* tar)
{
	auto pRet = new UDLRController();
	if (pRet && pRet->initWithTarget(tar))
	{
		pRet->autorelease(); //Don't Forgot
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return pRet;
	}
}

void UDLRController::onKeyPressed(EventKeyboard::KeyCode c, Event* e)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto pos = _target->getPosition();

	switch (c)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	{
		float distance = -pos.y + visibleSize.height - _tarSize.height / 2;
		float duration = distance / _speed;
		auto moveUp = MoveTo::create(duration, Vec2(pos.x, visibleSize.height - _tarSize.height / 2));
		moveUp->setTag(UP);
		_target->runAction(moveUp);
	}	break; //break�����Ǽ���
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	{
		float distance = pos.x - 0 - _tarSize.width/2;
		float duration = distance / _speed;
		auto moveLeft = MoveTo::create(duration, Vec2(_tarSize.width / 2, pos.y));
		moveLeft->setTag(LEFT);
		_target->runAction(moveLeft);
	}	break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	{
		float distance = -pos.x + visibleSize.width - _tarSize.width / 2;
		float duration = distance / _speed;
		auto moveRight = MoveTo::create(duration, Vec2(visibleSize.width - _tarSize.width / 2, pos.y));
		moveRight->setTag(RIGHT);
		_target->runAction(moveRight);
	}	break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	{
		float distance = pos.y - 0 -_tarSize.height/2;
		float duration = distance / _speed;
		auto moveDown = MoveTo::create(duration, Vec2(pos.x, _tarSize.height / 2));
		moveDown->setTag(DOWN);
		_target->runAction(moveDown);
	}	break;
	//case EventKeyboard::KeyCode::KEY_SPACE:
	//	(dynamic_cast<MyPlane*>(_target))->startAttacking(); break;
	default:
		break;
	}
}