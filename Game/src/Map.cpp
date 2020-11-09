#include "../include/Map.h"
#include "../include/Camera.h"
#include <fstream>

using std::fstream;

namespace gnGame {

	Map::Map()
		//: camera(_camera)
		//, mapData()
	{
	}

	void Map::loadMapFile(const string& _fileName)
	{
		fstream mapFile{ _fileName };

		// �}�b�v�t�@�C����ǂݍ��߂Ȃ������Ƃ�
		if (!mapFile) {
			exit(-1);
		}

		int my = 0;
		string line;
		while (std::getline(mapFile, line)) {

			int mx = 0;
			for (int x = 0; x < line.size(); ++x) {
				if (line[x] == ',') continue;

				map[my][mx] = line[x] - '0';
				++mx;
			}

			++my;
		}

		mapFile.close();
	}

	void Map::drawMap()
	{
		for (int y = 0; y < MapInfo::MapHeight; ++y) {
			for (int x = 0; x < MapInfo::MapWidth; ++x) {
				if (map[y][x] == 0) continue;

				Vector2 pos{
					(float)(MapInfo::MapHSize + x * MapInfo::MapSize),
					(float)(MapInfo::MapHSize + y * MapInfo::MapSize)
				};

				auto screen = CameraIns->toScreenPos(pos);

				sprite.setPos(screen);
				sprite.draw();
				
				//mapData.mapSprite.setPos(screen);
				//mapData.mapSprite.draw(mapData.spriteTexture[0]);
			}
		}
	}

	void Map::setTile(int _x, int _y, MapTile _mapInfo)
	{
		map[_y][_x] = (int)_mapInfo;
	}

	bool Map::checkTile(int _x, int _y)
	{
		auto tile = getTile(_x / 32, _y / 32);

		switch (tile)
		{
		case gnGame::MapTile::NONE:
			return false;
			break;
		case gnGame::MapTile::BLOCK:
			return true;
			break;
		case gnGame::MapTile::OBJECT:
			return true;
			break;
		default:
			return false;
			break;
		}

		return false;
	}

	MapTile Map::getTile(int _x, int _y)
	{
		// �z��O�̓Y������n���ꂽ��None��Ԃ�
		if (_x >= MapInfo::MapWidth || _x < 0 
			|| _y >= MapInfo::MapHeight || _y < 0) {
			return MapTile::NONE;
		}

		return (MapTile)map[_y][_x];
	}

}