#pragma once

#include <set>
#include <SFML/Graphics.hpp>

#include "../GameObject.h"
#include "../Math/Rect.h"
#include "Prototype.h"

namespace OT {
	namespace Item {
		
		class Item : public GameObject, public sf::Drawable
		{
		public:
			AbstractPrototype * const prototype;
			Item(Game * game, AbstractPrototype * prototype) : GameObject(game), sf::Drawable(), prototype(prototype), size(prototype->size.x*8, prototype->size.y*32) {}
			virtual void init() {}
			
			typedef std::set<sf::Sprite *> SpriteSet;
			SpriteSet sprites;
			void addSprite(sf::Sprite * sprite);
			void removeSprite(sf::Sprite * sprite);
			
			int2 position;
			const int2 size;
			void setPosition(int2 p);
			recti getRect() { return recti(position, size); }
			
			virtual void Render(sf::RenderTarget & target) const;
			sf::Vector2f GetSize() const { return sf::Vector2f(size.x, size.y); }
		};
	}
}

#define OT_ITEM_PROTOTYPE(cls)\
	static AbstractPrototype * makePrototype() {\
		AbstractPrototype * p = new Prototype<cls>;\
		initPrototype(p);\
		return p;\
	}\
	static void initPrototype(AbstractPrototype * p)

#define OT_ITEM_CONSTRUCTOR(cls) cls(Game * game, AbstractPrototype * prototype) : Item(game, prototype) { init(); }

#include "../Application.h"
