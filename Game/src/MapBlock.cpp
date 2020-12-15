#include "../include/MapBlock.h"
#include "../include/TextureManager.h"

namespace gnGame {
	MapBlock::MapBlock()
		: mapTile(MapTile::NONE)
		, pos()
		, tRect()
		, mapSprite()
	{
	}

	void MapBlock::setMapTile(MapTile _mapTile)
	{
		mapTile = _mapTile;
	}

	MapTile MapBlock::getMapTiel()
	{
		return mapTile;
	}

	void MapBlock::setPos(const Vector2& _pos)
	{
		pos = _pos;
	}

	Vector2 MapBlock::getPos()
	{
		return pos;
	}

	void MapBlock::setTextureRect(const TextureRect& _tRect)
	{
		tRect = _tRect;
	}

	EmptyBlock::EmptyBlock()
		: MapBlock()
	{
	}

	void EmptyBlock::draw()
	{
	}

	ICollider* EmptyBlock::getCollider()
	{
		return nullptr;
	}

	NomalBlock::NomalBlock()
		: MapBlock()
	{
		this->mapSprite.setTexture(TextureManager::getTexture("Block"));
	}

	void NomalBlock::draw()
	{
		this->mapSprite.draw(pos, Vector2::One, 0.0f);
	}

	ICollider* NomalBlock::getCollider()
	{
		return nullptr;
	}

	SlidingBlock::SlidingBlock()
		: MapBlock()
	{
		this->mapSprite.setTexture(TextureManager::getTexture("floor"));
	}

	void SlidingBlock::draw()
	{
		this->mapSprite.draw(pos, Vector2::One, 0.0f);
	}

	ICollider* SlidingBlock::getCollider()
	{
		return nullptr;
	}

	MapBlock* createMapBlock(MapTile _mapTile) {
		MapBlock* result = nullptr;;

		switch (_mapTile)
		{
		case gnGame::MapTile::NONE:
			result = new EmptyBlock();
			result->setMapTile(MapTile::NONE);
			return result;
		case gnGame::MapTile::BLOCK:
			result = new NomalBlock();
			result->setMapTile(MapTile::BLOCK);
			return result;
		case gnGame::MapTile::OBJECT:
			result = new SlidingBlock();
			result->setMapTile(MapTile::OBJECT);
			return result;
		default:
			break;
		}

		return nullptr;
	}
}