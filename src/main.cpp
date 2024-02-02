#include <Geode/Geode.hpp>
#include <Geode/modify/GJGarageLayer.hpp>
#include <Geode/modify/GameManager.hpp>

using namespace geode::prelude;

bool iconhack = false;

CCSprite* box;

class IconHack {
	public:
		void icon_toggle(CCObject*);
};

void IconHack::icon_toggle(CCObject*) {
	if (iconhack){
		iconhack = false;
		box->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GJ_checkOff_001.png"));
	}
	else {
		iconhack = true;
		box->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("GJ_checkOn_001.png"));
	}
}

class $modify(GJGarageLayer) {
	bool init() {
		bool result = GJGarageLayer::init(); // adds code AFTER execution
		auto director = CCDirector::sharedDirector();
		auto size = director->getWinSize(); // -> cuz its a pointer
		CCLabelBMFont* label = CCLabelBMFont::create("Icon Hack", "bigFont.fnt");
		if (iconhack){
			box = CCSprite::createWithSpriteFrameName("GJ_checkOn_001.png");
		}
		else {
			box = CCSprite::createWithSpriteFrameName("GJ_checkOff_001.png");
		}
		auto button = CCMenuItemSpriteExtra::create(box, this, menu_selector(IconHack::icon_toggle)); // this shows its in the garagelayer, (current layer)
		auto menu = CCMenu::create();
		menu->setPosition({size.width/2 - 12,size.height/2});
		menu->setScale(0.6f);
		menu->addChild(button);

		label->setScale(0.45f);
		label->setPosition({menu->getPositionX() + 165.0f, menu->getPositionY() + 64.5f});

		addChild(menu);
		addChild(label);
		return result;
	}
};

class $modify(GameManager) {
	bool isIconUnlocked(int iconID, IconType type) {
		bool result = GameManager::isIconUnlocked(iconID, type);
		if (iconhack) {
			return true;
		}
		return result;
	}
};