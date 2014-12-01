#ifndef _MYPLANE_H_
#define _MYPLANE_H_

#include "cocos2d.h"
USING_NS_CC;
//#include "bullet.h"

class MyPlane: public Node
{
public:
	MyPlane();
	~MyPlane();

	bool init();
	CREATE_FUNC(MyPlane);

	//这个地方最好用controller基类指针！这个接口还有待改进！
	void setController(Node* ctrl);

	//Node没有大小，所以重写这个方法。
	const Size& getContentSize()const override
	{
		return _plane->getContentSize();
	}

	Vector<Node*> getAllValidBullets(){ return _bulletsOnScreen; }

	inline void destroyBullet(Node* bl);

	void shootOnce(float dt);
	void startAttacking();
	void stopAttacking();

private:

	Sprite* _plane; //这里只能保存指针哦！
	bool isAlive;
	
	// 造成后面一大片错误，无奈没备份。最后发现是下面这句话，说Bullet未声明，但其实我已经添加了头文件，并且Bullet继承自Node。无语
	//cocos2d::Vector<Bullet*> _bulletsOnScreen;
	cocos2d::Vector<Node*> _bulletsOnScreen;

};

// 注意：头文件中放函数定义，要么内联，要么static，否则会报LNKERR（重复定义）。一般来说定义放在cpp里头。
// 哪怕是构造器！
inline MyPlane::MyPlane() :
	_plane(nullptr)
{
}

inline MyPlane::~MyPlane()
{
	_plane->release();
}

// 要注意，内联函数的【声明】和【定义】都需要inline关键字
inline void MyPlane::destroyBullet(Node* bl)
{
	// 子弹超出边界会自动从【树】中删除。这里只要让其隐身即可
	bl->setVisible(false);
	// 删除使其不再参与碰撞检测
	_bulletsOnScreen.eraseObject(/*static_cast<Node*>*/(bl), false);
}

#endif