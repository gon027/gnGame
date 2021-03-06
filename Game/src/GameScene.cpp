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
#include "../TutorialObject.h"

namespace gnGame {

	namespace Static {
		using MapStageList = std::vector<std::vector<std::string>>;
		static MapStageList mapStageList(4);     // マップステージのファイルリスト
	}

	GameScene::GameScene(SceneManager* _sceneManager)
		: sceneManager(_sceneManager)
		, backGround()
		, gameMap(new Map{ this })
		, player()
		, currentMapNumber(0)
		, stageBgm()
	{

		// ステージを登録
		Static::mapStageList[0].push_back("Tutorial/Tutorial_1");
		Static::mapStageList[0].push_back("Tutorial/Tutorial_2");
		Static::mapStageList[0].push_back("Tutorial/Tutorial_3");
		
		Static::mapStageList[1].push_back("Stage1/Map_1");
		Static::mapStageList[1].push_back("Stage1/Map_2");
		Static::mapStageList[1].push_back("Stage1/Map_3");
		Static::mapStageList[1].push_back("Stage1/Map_4");
		
		Static::mapStageList[2].push_back("Stage2/Map_1");
		Static::mapStageList[2].push_back("Stage2/Map_2");
		Static::mapStageList[2].push_back("Stage2/Map_3");
		Static::mapStageList[2].push_back("Stage2/Map_4");

		Static::mapStageList[3].push_back("BossStage/Stage_1");
		Static::mapStageList[3].push_back("BossStage/Stage_2");
		Static::mapStageList[3].push_back("BossStage/Clear");

		// サウンドを読み込む
		stageBgm.load(global::AudioAsset("bgm.wav"));
		stageBgm.setVolume(-3000);
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
		
		// BGMを再生するのを決める
		stageBgm.play(PlayType::Loop);

	}

	void GameScene::onUpdate()
	{
#if _DEBUG

		// 背景を変更
		if (Input::getKeyDown(Key::S)) {
			backGround.setTexture(1);
		}

		if (Input::getKeyDown(Key::D)) {
			backGround.setTexture(0);
		}

		// セレクトシーンへ戻る
		if (Input::getKeyDown(Key::A)) {
			sceneManager->changeScene(SceneType::Select);
		}

		// ステージを開放する
		if (Input::getKeyDown(Key::W)) {
			currentMapNumber = (currentMapNumber + 1) % 4;
		}

#endif // DEBUG

		// プレイヤーが死亡した場合
		if (!player.getActive()) {
			player.respawn(gameMap->getStartPoint());
		}

		backGround.draw();
		
		gameMap->drawMap();
		
		TutorialObjectList::getIns()->update();

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
		stageBgm.stop();
		stageBgm.setPosition(0);
		resetMap();
	}

	Player* GameScene::getPlayer() 
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
		TutorialObjectList::getIns()->clear();
	}

	void GameScene::initMap()
	{
		// Managerのリストをすべて消去
		resetMap();
 
		backGround.setTexture(0);

		// 現在のマップ番号を0にする
		currentMapNumber = 0;

		// マップをクリアする
		gameMap->claerMap();

		// マップを読み込む
		auto currentStage = StageManager::getIns()->getCurrentStage();
		auto mapFile = global::MapAsset(Static::mapStageList[currentStage][currentMapNumber]);
		gameMap->loadMapFile(mapFile);

		// 背景を変更
		if (currentStage >= 2) {
			backGround.setTexture(1);
		}
		else {
			backGround.setTexture(0);
		}

		// カメラをマップに収める
		Camera::setMapInfo(gameMap->getMapSize());

		// プレイヤーの位置設定
		player.onStart();
		player.setMap(gameMap);
		player.initPosition(gameMap->getStartPoint());
		Camera::setTarget(player.transform.pos);
	}

	void GameScene::nextMap()
	{
		player.setIsMove(false);

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
		Camera::setTarget(player.transform.pos);
	}

	void GameScene::changeSelectScene()
	{
		player.reset();
		sceneManager->changeScene(SceneType::Select);
	}

}