#include "MenuLayer.h"
#include "DataDefine.h"
#include "MapLayer.h"

bool MenuLayer::init()
{
	bool bSucceed = false;
	do 
	{
		CC_BREAK_IF(!CCLayer::init());
		setView();
		bSucceed = true;
	}while(false);
	return bSucceed;
}

CCScene* MenuLayer::scene()
{
	CCScene* sc = NULL;
	do
	{
		sc = CCScene::create();
		CC_BREAK_IF( !sc );
		MenuLayer* layer = MenuLayer::create();
		CC_BREAK_IF( !layer );
		sc->addChild( layer );
	} while(0);
	return sc;
}

cocos2d::CCSize MenuLayer::getWinSize()
{
	return CCDirector::sharedDirector()->getWinSize();
}

void MenuLayer::setView()
{
	setBackgroundImage(BACKGROUND_IMAGE_PATH);
	addMenu();
	//PlayMusic(BACKGROUND_MUSIC_PATH);
}

void MenuLayer::setBackgroundImage(const char* back_image_name)
{
	CCSprite* bcSprite = CCSprite::create(back_image_name);
	// set anchorPoint
	//bcSprite->setAnchorPoint(ccp(getWinSize().width / 2, getWinSize().height / 2));
	bcSprite->setPosition(ccp(getWinSize().width / 2, getWinSize().height / 2));
	this->addChild(bcSprite);
}

void MenuLayer::PlayMusic(const char* musicPath)
{
	// 	bool flag = CCUserDefault::sharedUserDefault()->getBoolForKey("music_not_playing" );
	// 	if(!flag )
	// 	{
	if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
	{
		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(musicPath, true );
	}
	// 	}
	// 	else
	// 	{
	// 		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	// 	}
}

void MenuLayer::addMenu()
{
	//  add start button
	CCSprite* pStartNormal = CCSprite::create( "menu.png" ,CCRectMake(0, 0, 126, 33));
	CCSprite* pStartPressed = CCSprite::create( "menu.png" ,CCRectMake(0, 33, 126, 33));
	CCSprite* pStartDisabled = CCSprite::create( "menu.png" ,CCRectMake(0, 66, 126, 33));
	CCMenuItemSprite* startGame = CCMenuItemSprite::create(pStartNormal, pStartPressed, pStartDisabled, this, menu_selector(MenuLayer::onClickStart));
	// add about button
	CCSprite* pAboutNormal = CCSprite::create( "menu.png" ,CCRectMake(252, 0, 126, 33));
	CCSprite* pAboutPressed = CCSprite::create( "menu.png" ,CCRectMake(252, 33, 126, 33));
	CCSprite* pAboutDisabled = CCSprite::create( "menu.png" ,CCRectMake(252, 66, 126, 33));
	CCMenuItemSprite* aboutGame = CCMenuItemSprite::create(pAboutNormal, pAboutPressed, pAboutDisabled, this, menu_selector(MenuLayer::onClickAbout));
	// add option button
	CCSprite* pOptionNormal = CCSprite::create( "menu.png" ,CCRectMake(126, 0, 126, 33));
	CCSprite* pOptionPressed = CCSprite::create( "menu.png" ,CCRectMake(126, 33, 126, 33));
	CCSprite* pOptionDisabled = CCSprite::create( "menu.png" ,CCRectMake(126, 66, 126, 33));
	CCMenuItemSprite* optionGame = CCMenuItemSprite::create(pOptionNormal, pOptionPressed, pOptionDisabled, this, menu_selector(MenuLayer::onClickOption));
	// create menu
	CCMenu* pMenu = CCMenu::create( startGame,optionGame,aboutGame,NULL);
	pMenu->setPosition( ccp(getWinSize().width / 2 ,getWinSize().height / 2 - 20 ) );
	pMenu->alignItemsVerticallyWithPadding( 10 );
	this->addChild( pMenu );
}

void MenuLayer::onClickStart(CCObject* pSender)
{
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, MapLayer::scene()));
}

void MenuLayer::onClickAbout(CCObject* pSender)
{
	CCLOG("start game");
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5f, AboutLayer::scene()));
}

void MenuLayer::onClickOption(CCObject* pSender)
{

}

bool AboutLayer::init()
{
	bool sRect = false;
	do
	{
		CC_BREAK_IF(!BasicLayer::init());
		setupViews();
		sRect = true;
	}while (0);
	return sRect;
}

CCScene* AboutLayer::scene()
{
	CCScene* sc = NULL;
	do
	{
		sc = CCScene::create();
		CC_BREAK_IF(!sc);
		AboutLayer* layer = AboutLayer::create();
		CC_BREAK_IF(!layer);
		sc->addChild(layer);
	}while(0);
	return sc;
}

void AboutLayer::setupViews()
{
	setBackgroundImage("loading.png");
	//  加入title
	CCSprite* title = CCSprite::create( "menuTitle.png",CCRectMake(0, 34, 130, 38) );
	title->setAnchorPoint( ccp(0.5, 1) );
	title->setPosition( ccp( getWinSize().width / 2 ,getWinSize().height -20 ) );
	this->addChild( title );
	//  加入文字说明
	CCLabelBMFont* pDes = CCLabelBMFont::create("copy right acmercyj@gmail.com", "arial-14.fnt");
	pDes->setPosition( ccp(getWinSize().width / 2, getWinSize().height / 2) );
	this ->addChild(pDes);
	CCLabelBMFont* fontOfBack = CCLabelBMFont::create("Go Back", "arial-14.fnt" );
	fontOfBack->setScale(1.5f);
	CCMenuItemLabel* backLabel = CCMenuItemLabel::create(fontOfBack, this, menu_selector(AboutLayer::back_callback));
	backLabel->setAnchorPoint( ccp( 0.5, 0 ) );
	backLabel->setPosition( ccp( getWinSize().width / 2, 30) );
	CCMenu* menu = CCMenu::create( backLabel, NULL );;
	menu->setPosition( CCPointZero );
	this->addChild( menu );
}

void AboutLayer::back_callback(CCObject* pSender)
{
	CCLOG("back");
	CCDirector::sharedDirector()->pushScene( CCTransitionFade::create( 0.5f, MenuLayer::scene()));
}
