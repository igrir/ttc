//
//  HelloWorldScene.h
//  ttc
//
//  Created by Giri Putra on 2/4/12.
//  Copyright Universitas Pendidikan Indonesia 2012. All rights reserved.
//

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayerColor
{
protected:
	cocos2d::CCMutableArray<cocos2d::CCSprite*> *_targets;
	cocos2d::CCMutableArray<cocos2d::CCSprite*> *_touchers;
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	//constructor
	HelloWorld();
	
	//destructor
	~HelloWorld();
	
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();
	
	// a selector callback
	virtual void menuCloseCallback(CCObject* pSender);
	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
	
	virtual void spriteMoveFinished(cocos2d::CCSprite* sender);
	
	virtual void update(cocos2d::ccTime dt);
	
	// implement the "static node()" method manually
	LAYER_NODE_FUNC(HelloWorld);
	
	
};

#endif // __HELLOWORLD_SCENE_H__
