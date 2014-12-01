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

	//����ط������controller����ָ�룡����ӿڻ��д��Ľ���
	void setController(Node* ctrl);

	//Nodeû�д�С��������д���������
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

	Sprite* _plane; //����ֻ�ܱ���ָ��Ŷ��
	bool isAlive;
	
	// ��ɺ���һ��Ƭ��������û���ݡ��������������仰��˵Bulletδ����������ʵ���Ѿ������ͷ�ļ�������Bullet�̳���Node������
	//cocos2d::Vector<Bullet*> _bulletsOnScreen;
	cocos2d::Vector<Node*> _bulletsOnScreen;

};

// ע�⣺ͷ�ļ��зź������壬Ҫô������Ҫôstatic������ᱨLNKERR���ظ����壩��һ����˵�������cpp��ͷ��
// �����ǹ�������
inline MyPlane::MyPlane() :
	_plane(nullptr)
{
}

inline MyPlane::~MyPlane()
{
	_plane->release();
}

// Ҫע�⣬���������ġ��������͡����塿����Ҫinline�ؼ���
inline void MyPlane::destroyBullet(Node* bl)
{
	// �ӵ������߽���Զ��ӡ�������ɾ��������ֻҪ����������
	bl->setVisible(false);
	// ɾ��ʹ�䲻�ٲ�����ײ���
	_bulletsOnScreen.eraseObject(/*static_cast<Node*>*/(bl), false);
}

#endif