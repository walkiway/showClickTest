#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

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
    if ( !CCLayer::init() )
    {
        return false;
    }

    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


#pragma mark - enter,exit
//进入响应函数
void HelloWorld::onEnter()
{
    CCLayer::onEnter();
    //进入开启触摸
    this->setTouchEnabled(true);
}
//退出响应函数
void HelloWorld::onExit()
{
    CCLayer::onExit();
}

#pragma mark - 触摸事件

void HelloWorld::registerWithTouchDispatcher()
{
	//kCCMenuHandlerPriority=-128，将这个值设置为-128的二倍，可以比下边的层的优先级高
	//而且ccTouchBegan的返回值为true，说明其他的层将接受不到这个触摸消息了，只有这个层上边的
	//菜单的优先级比他还要打，所以它上边的菜单是可以接收到触摸消息的
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,
                                                                            kCCMenuHandlerPriority*2,true);
}
//触摸事件
bool HelloWorld::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //获得触摸点坐标
    CCPoint touchLocation = pTouch->getLocation();
    
    CCParticleSystemQuad *mParticle =  CCParticleSystemQuad::create("showClick.plist");
    mParticle->setScale(0.5f);
    mParticle->setPosition(touchLocation);
    //如果不设置,粒子播放后内存不释放
    mParticle->setAutoRemoveOnFinish(true);
    this->addChild(mParticle);
    
    return false;
}