#include "../include/ShotEnemy.h"
#include "../include/Camera.h"
#include "../include/Bullet.h"
#include "../include/TextureManager.h"
#include "../include/BulletManager.h"

namespace gnGame {

	ShotEnemy::ShotEnemy()
		: Enemy()
		, enemyAttack(this)
		, aa(this)
	{
	}

	ShotEnemy::ShotEnemy(const Vector2& _pos)
		: Enemy(_pos)
		, enemyAttack(this)
		, aa(this)
	{
	}

	void ShotEnemy::onStart()
	{
		this->sprite.setTexture(TextureManager::getTexture("Enemy1"));
	
		bounds.minPos.setPos(0, 0);
		bounds.maxPos.setPos(32, 32);
		bounds.size.setPos(bounds.maxPos - bounds.minPos);
		bounds.center.setPos(bounds.size.half());
	}

	void ShotEnemy::onUpdate()
	{
		if (!this->isActive) {
			return;
		}
		
		//enemyAttack.execute();
		aa.execute();

		this->transform.pos = intersectTileMap();

		if (!Camera::isOnScreen(this->transform.pos)) {
			return;
		}

		auto screen(Camera::toScreenPos(this->transform.pos));
		collider.update(screen, 32.0f, 32.0f);
		sprite.draw(screen, transform.scale, transform.angle, true, isFlip);
	}

	EnemyState::BulletAttack1::BulletAttack1(Enemy* _enemyPtr)
		: EnemyAttack(_enemyPtr)
	{
	}

	namespace a {
		constexpr float InterVal = 10.0f;
		float timer = 0.0f;
	}

	void EnemyState::BulletAttack1::execute()
	{
		a::timer += Time::deltaTime();

		auto angle = tau / 10.0f;
		
		if (a::timer > 3.0f) {
			a::timer = 0.0f;

			auto accel = 1.0f;
			for (int _ = 0; _ < 5; ++_) {
				float aaa = 0.0f;
				for (auto i{ 0.0f }; i < 10; ++i) {
					aaa += angle;
					accel += 0.2;
					auto x{ cosf(aaa) * accel };
					auto y{ sinf(aaa) * accel };
					BulletPtr bulletPtr(new Bullet(enemyPtr->transform.pos, Vector2{ x, y }));
					bulletPtr->onStart();
					BulletManager::getIns()->addBullet(bulletPtr);
				}
			}
		}
	}
}


