//
//  HelloWorldScene.cpp
//  ttc
//
//  Created by Giri Putra on 2/4/12.
//  Copyright Universitas Pendidikan Indonesia 2012. All rights reserved.
//

#include "HelloWorldScene.h"
#include <ctime>


USING_NS_CC;

CCScene* HelloWorld::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();
	
	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)) )
	{
		return false;
	}

	
	if (CCLayer::init()) {
		//initialize array
		_targets = new CCMutableArray<CCSprite*>;
		_touchers = new CCMutableArray<CCSprite*>;
		
		//enabling the touch
		this->setIsTouchEnabled(true);
		
		//setting the collision checking
		this->schedule(schedule_selector(HelloWorld::update));
		
		//initialize random seed
		srand(time(0));
		
		for (int i=0; i<5; i++) {
			CCSprite *sprite = CCSprite::spriteWithFile("circle.png", CCRectMake(0,0,98,98));
						
			//get the size of the display
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
									
			int positionY = rand()%(int)(winSize.height);
			int positionX = rand()%(int)(winSize.width);
			
			
			sprite->setPosition(ccp(positionX, positionY));

			//add sprites to _targets array
			sprite->setTag(1);
			_targets->addObject(sprite);
			
			
			this->addChild(sprite);
		}
		
		for(int i=0;i<5;i++){
			//adding the square
			CCSprite *sprite = CCSprite::spriteWithFile("rectangle.png", CCRectMake(0,0,98,98));
			
			//get the size of the display
			CCSize winSize = CCDirector::sharedDirector()->getWinSize();
			
			int positionX = rand()%(int)(winSize.width);
			int positionY = rand()%(int)(winSize.height);
			
			sprite->setPosition(ccp(positionX, positionY));
			
			
			//3 is reserved for square
			sprite->setTag(3);
			_targets->addObject(sprite);
			
			this->addChild(sprite);
			
			
		}
		
		
	}
	
		return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event){
	CCTouch* touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->locationInView(touch->view());
	location = CCDirector::sharedDirector()->convertToGL(location);
	
	
	CCPoint realDest = ccp(location.x, location.y);
	
	//making the touchers for hitting the objects
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSprite *bulatong = CCSprite::spriteWithFile("circle_bullet.png", CCRectMake(0, 0, 1,1));
	bulatong->setPosition(realDest);
	
	//if(offX <= 0) return;
	
	this->addChild(bulatong);

	//add bulatongs to _touchers array
	bulatong->setTag(2);
	_touchers->addObject(bulatong);
	
	
	//animate the bulatong (the small circle)
	bulatong->runAction(CCSequence::actions(CCMoveTo::actionWithDuration(0, realDest), CCCallFuncN::actionWithTarget(this, callfuncN_selector(HelloWorld::spriteMoveFinished)), NULL));
}


void HelloWorld::spriteMoveFinished(CCSprite* sender){
	CCSprite *sprite = (CCSprite *)sender;
	this->removeChild(sprite, true);
	
	if(sprite->getTag() == 1)
	{
		_targets->removeObject(sprite);
	}
	else if(sprite->getTag() == 2){
		_touchers->removeObject(sprite);
	}
}

//destructor

HelloWorld::~HelloWorld()
{
	if (_targets) {
		_targets->release();
		_targets = NULL;
	}
	
	if (_touchers) {
		_touchers->release();
		_touchers = NULL;
	}
}

//constructor
HelloWorld::HelloWorld():_targets(NULL),_touchers(NULL){}

void HelloWorld::update(ccTime dt){
	CCMutableArray<CCSprite*> *touchersToDelete = new CCMutableArray<CCSprite*>;
	CCMutableArray<CCSprite*>::CCMutableArrayIterator it, jt;
	
	for(it = _touchers->begin(); it != _touchers->end(); it++)
	{
		CCSprite *touchers = *it;
		CCRect touchersRect = CCRectMake(
							  touchers->getPosition().x - (touchers->getContentSize().width/2),
							  touchers->getPosition().y - (touchers->getContentSize().height/2),
							  touchers->getContentSize().width,
							  touchers->getContentSize().height);
		
		CCMutableArray<CCSprite*>*targetsToDelete = new CCMutableArray<CCSprite*>;
		
		for (jt = _targets->begin(); jt != _targets->end(); jt++) {
			CCSprite *target = *jt;
			CCRect targetRect = CCRectMake(
								target->getPosition().x - (target->getContentSize().width/2),
								target->getPosition().y - (target->getContentSize().height/2),
								target->getContentSize().width,
								target->getContentSize().height);
			
			//delete the object
			if (CCRect::CCRectIntersectsRect(touchersRect, targetRect)) {
				targetsToDelete->addObject(target);
			}
			
		}
		
		for (jt = targetsToDelete->begin(); jt != targetsToDelete->end(); jt++){
			CCSprite *target = *jt;
			_targets->removeObject(target);
			this->removeChild(target, true);
		}
		
		if (targetsToDelete->count() > 0) {
			touchersToDelete->addObject(touchers);
		}
		targetsToDelete->release();
		
	}
	
	for(it = touchersToDelete->begin(); it != touchersToDelete->end();it++){
		CCSprite* touchers = *it;
		_touchers->removeObject(touchers);
		this->removeChild(touchers, true);
	}
	touchersToDelete->release();
	
}