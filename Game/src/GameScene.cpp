#include "../include/GameScene.h"
#include "../include/Global.h"
#include "../include/WindowInfo.h"
#include "../include/TextureManager.h"
#include "../include/EnemyManager.h"
#include "../include/BulletManager.h"
#include "../include/ItemManager.h"
#include "../include/EventManager.h"
#include "../include/SceneManager.h"
#include "../include/StageManager.h"
#include "../include/UIDrawer.h"
#include "../include/Camera.h"
#include "../include/Map.h"

namespace gnGame {

	namespace Static {
		using MapStageList = std::vector<std::vector<std::string>>;

		static MapStageList mapStageList(5);     // マップステージのファイルリスト
	}

	GameScene::GameScene(SceneManager* _sceneManager)
		: sceneManager(_sceneManager)
		, backGround()
		, gameMap(new Map{ this })
		, player()
		, currentMapNumber(0)
	{
		Static::mapStageList[0].push_back("Tutorial/Tutorial_1");
		Static::mapStageList[0].push_back("Tutorial/Tutorial_2");
		Static::mapStageList[0].push_back("Tutorial/Tutorial_3");

		Static::mapStageList[1].push_back("TestMap_1");
		Static::mapStageList[1].push_back("TestMap_2");
		Static::mapStageList[1].push_back("TestMap_3");
		Static::mapStageList[1].push_back("TestMap_4");

		Static::mapStageList[2].push_back("TestMap_1");
		Static::mapStageList[2].push_back("TestMap_2");
		Static::mapStageList[2].push_back("TestMap_3");
		Static::mapStageList[2].push_back("TestMap_4");

		Static::mapStageList[3].push_back("TestMap_1");
		Static::mapStageList[3].push_back("TestMap_2");
		Static::mapStageList[3].push_back("TestMap_3");
		Static::mapStageList[3].push_back("TestMap_4");

		Static::mapStageList[4].push_back("TestMap_1");
		Static::mapStageList[4].push_back("TestMap_2");
		Static::mapStageList[4].push_back("TestMap_3");
		Static::mapStageList[4].push_back("TestMap_4");
	}

	GameScene::~GameScene()
	{
		if (gameMap) {
			delete gameMap;
			gameMap = nullptr;
		}
	}

	void GameScene::onStart()
	{
		initMap();
	}

	void GameScene::onUpdate()
	{

		if (Input::getKeyDown(Key::S)) {
			backGround.setTexture(1);
		}

		if (Input::getKeyDown(Key::D)) {
			backGround.setTexture(0);
		}

		if (Input::getKeyDown(Key::A)) {
			sceneManager->changeScene(SceneType::Select);
		}

		backGround.draw();
		gameMap->drawMap();
		player.onUpdate();

		EnemyManager::getIns()->onUpdateEnemyList();
		EnemyManager::getIns()->collisionPlayer(player);

		BulletManager::getIns()->onUpdateBulletList();
		BulletManager::getIns()->collisionMap(*gameMap);
		BulletManager::getIns()->collisionActor(player, this);

		ItemManager::getIns()->onUpdateItemList();
		ItemManager::getIns()->collisionPlayer(player);

		EventManager::getIns()->collisionPlayer(player);
		EventManager::getIns()->onUpdateEventList();

		UIDrawer::getIns()->OndrawUIList();
	}

	void GameScene::onFinal()
	{
		resetMap();
	}

	const Player* GameScene::getPlayer() const 
	{
		return &player;
	}

	Map* GameScene::getMap()
	{
		return gameMap;
	}

	void GameScene::resetMap()
	{
		EnemyManager::getIns()->claerList();
		BulletManager::getIns()->claerList();
		ItemManager::getIns()->claerList();
		EventManager::getIns()->claerList();
		//UIDrawer::getIns()->claerUIList();
	}

	void GameScene::initMap()
	{
		// Managerのリストをすべて消去
		resetMap();

		// 
		backGround.setTexture(0);

		// 現在のマップ番号を0にする
		currentMapNumber = 0;

		// マップをクリアする
		gameMap->claerMap();

		// マップを読み込む
		auto currentStage = StageManager::getIns()->getCurrentStage();
		auto mapFile = global::MapAsset(Static::mapStageList[currentStage][currentMapNumber]);
		//auto mapFile = "Asset/MapData/Test/TestFeild";
		//auto mapFile = "Asset/MapData/Test/tMap";
		gameMap->loadMapFile(mapFile);

		// カメラをマップに収める
		Camera::setMapInfo(gameMap->getMapSize());

		// プレイヤーの位置設定
		player.onStart();
		player.setMap(gameMap);
		player.initPosition(gameMap->getStartPoint());
	}

	void GameScene::nextMap()
	{
		// Managerのリストをすべて消去
		resetMap();

		// マップの数を1つ進める
		currentMapNumber = (currentMapNumber + 1) % 4;

		// マップをクリアする
		gameMap->claerMap();

		// マップを読み込む
		auto currentStage = StageManager::getIns()->getCurrentStage();
		auto mapFile = global::MapAsset(Static::mapStageList[currentStage][currentMapNumber]);
		gameMap->loadMapFile(mapFile);

		// カメラをマップに収める
		Camera::setMapInfo(gameMap->getMapSize());

		// プレイヤーの位置設定
		player.setMap(gameMap);
		player.initPosition(gameMap->getStartPoint());
	}

	void GameScene::changeSelectScene()
	{
		sceneManager->changeScene(SceneType::Select);
	}

}