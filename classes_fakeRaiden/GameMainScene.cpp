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

	// 创建一台灰机
	_plane = MyPlane::create();
	_plane->retain();

	_plane->setPosition(visibleSize.operator/(2));
	addChild(_plane);

	// 为飞机添加控制器
	auto ctrl = UDLRController::createWithTarget(_plane);
	_plane->setController(ctrl);
	_plane->startAttacking();

	// 抬头显示
	_hud = HUD::create();
	_hud->retain();
	// LabelTTF貌似锚点不能被改变，只能是原点。
	_hud->setPosition(Vec2(0, visibleSize.height - _hud->getContentSize().height));
	addChild(_hud, 2);

	// 创建一个敌人用来测试一下鲜
	_enemy = Sprite::create("monster.png");
	_enemy->retain();
	_enemy->setPosition(Vec2(visibleSize.width / 1.5, visibleSize.height / 2 + 200));
	addChild(_enemy);
	// 还想schedule一下，让怪物移动移动
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
			// 及时销毁子弹，避免下一次继续进入“碰撞”。这里设计有待商榷，销毁由飞机完成，还是子弹完成？
			// 由飞机完成，前提是这些子弹属于这个飞机！
			_plane->destroyBullet(bl);
			++s_hits; // 被子弹打中的数目++  

			auto blink = Blink::create(0.1, 9);
			_enemy->runAction(blink);
		}
		else
		{
			_enemy->runAction(Show::create());
		}
	}

	// 由于怪物不停在移动，当怪物和飞机碰撞时，让飞机停止发射子弹
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
	// 本来想直接schedule下面这个函数，但是没想到函数必须是Ref子类成员函数。
	// 见schedule_selector宏。
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

// 以简单代码让怪物自由移动，未来怪物单独写成类。
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