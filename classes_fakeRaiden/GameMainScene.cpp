#include "GameMainScene.h"
#include "MyPlane.h"
#include "UDLRController.h"
#include "bullet.h"

bool GameMainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	auto layer = GameMainLayer::create();
	addChild(layer);

	return true;
}

bool GameMainLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	// ����һ̨�һ�
	_plane = MyPlane::create();
	_plane->retain();

	_plane->setPosition(visibleSize.operator/(2));
	addChild(_plane);

	// Ϊ�ɻ���ӿ�����
	auto ctrl = UDLRController::createWithTarget(_plane);
	_plane->setController(ctrl);
	_plane->startAttacking();

	// ̧ͷ��ʾ
	_hud = HUD::create();
	_hud->retain();
	// LabelTTFò��ê�㲻�ܱ��ı䣬ֻ����ԭ�㡣
	_hud->setPosition(Vec2(0, visibleSize.height - _hud->getContentSize().height));
	addChild(_hud, 2);

	// ����һ��������������һ����
	_enemy = Sprite::create("monster.png");
	_enemy->retain();
	_enemy->setPosition(Vec2(visibleSize.width / 1.5, visibleSize.height / 2 + 200));
	addChild(_enemy);
	// ����scheduleһ�£��ù����ƶ��ƶ�
	srand(time(0));
	scheduleUpdate();

	schedule(schedule_selector(GameMainLayer::gameLogic), 0.1f);

	return true;
}

//static const auto visibleSize = Director::getInstance()->getVisibleSize();

void GameMainLayer::gameLogic(float dt)
{
	static int s_hits = 0;
	_hud->getLabel()->setString(String::createWithFormat("Bullets:%d", _plane->getAllValidBullets().size())->getCString());
	_hud->getLabel2()->setString(String::createWithFormat("Hits:%d", s_hits)->getCString());

	for each (auto bl in _plane->getAllValidBullets())
	{
		bl = dynamic_cast<Bullet*>(bl);
		auto blRangeRect = _getRangeRect(bl);
		auto enemyRangeRect = _getRangeRect(_enemy);
		if (blRangeRect.intersectsRect(enemyRangeRect))
		{
			// ��ʱ�����ӵ���������һ�μ������롰��ײ������������д���ȶ�������ɷɻ���ɣ������ӵ���ɣ�
			// �ɷɻ���ɣ�ǰ������Щ�ӵ���������ɻ���
			_plane->destroyBullet(bl);
			++s_hits; // ���ӵ����е���Ŀ++  

			auto blink = Blink::create(0.1, 9);
			_enemy->runAction(blink);
		}
		else
		{
			_enemy->runAction(Show::create());
		}
	}

	// ���ڹ��ﲻͣ���ƶ���������ͷɻ���ײʱ���÷ɻ�ֹͣ�����ӵ�
	auto planeRect = _getRangeRect(_plane);
	auto enemyRangeRect = _getRangeRect(_enemy);
	if (planeRect.intersectsRect(enemyRangeRect))
	{
		_plane->stopAttacking();
		_plane->runAction()
	}
}

void  GameMainLayer::update(float dt)
{
	// ������ֱ��schedule�����������������û�뵽����������Ref�����Ա������
	// ��schedule_selector�ꡣ
	void _testMoveingMonster(Node* n, float dt);
	_testMoveingMonster(this->_enemy, dt);
}

Rect _getRangeRect(const Node* n)
{
	return Rect(n->getPositionX() - n->getContentSize().width / 2,
				n->getPositionY() - n->getContentSize().height / 2,
				n->getContentSize().width,
				n->getContentSize().height
				);
}

// �Լ򵥴����ù��������ƶ���δ�����ﵥ��д���ࡣ
void _testMoveingMonster(Node* n, float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	static bool isMoving = false;

	if (!isMoving)
	{
		isMoving = true;
		auto callbackAciton = CallFunc::create([&](){
			isMoving = false;
		});
		auto moveAction = MoveTo::create(2, Vec2(CCRANDOM_0_1() * visibleSize.width, CCRANDOM_0_1() * visibleSize.height));
		auto sequenceAction = Sequence::create(moveAction, callbackAciton, nullptr);
		n->runAction(sequenceAction);
	}
}