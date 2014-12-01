#include "HUD.h"

bool HUD::init()
{
	if (!LayerColor::initWithColor(Color4B(125, 0, 0, 125)))
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	// 对于LayerColor，设置锚点没有意义。
	//this->setAnchorPoint(Vec2(0, 1));
	this->setContentSize(CCSizeMake(visibleSize.width, 60));

	// 创建一个Label用来调试
	_dbLbl = LabelTTF::create("0000", "Arial", 24);
	_dbLbl->retain();
	_dbLbl->setAnchorPoint(Vec2::ZERO);
	this->addChild(_dbLbl);

	// 创建第二个Label用来调试
	_dbLbl2 = LabelTTF::create("0000", "Arial", 24);
	_dbLbl2->retain();
	_dbLbl2->setAnchorPoint(Vec2(1, 0));
	_dbLbl2->setPosition(Vec2(visibleSize.width, 0));
	this->addChild(_dbLbl2);

	// 创建第三个Label用来调试
	// 要注意，下面这种方式是错的，参数调用错误，会返回NULL，第二个参数是字体文件，别和已经废除的LabelTTF搞混。
	//_dbLbl3 = Label::createWithTTF("Hello", "Arial", 24);
	_dbLbl3 = Label::createWithSystemFont("Hello", "Arial", 24);
	//_dbLbl3->enableGlow(Color4B(0, 255, 0, 125));
	//_dbLbl3->enableOutline(Color4B(0, 255, 0, 255), 2);
	_dbLbl3->retain();
	_dbLbl3->setAnchorPoint(Vec2(0.5, 0));
	_dbLbl3->setPosition(Vec2(visibleSize.width / 2, 0));
	this->addChild(_dbLbl3);


	return true;
}