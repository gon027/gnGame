#ifndef ACTOR_H
#define ACTOR_H

#include "Lib.h"

namespace gnGame {

	class IScene;

	/// <summary>
	/// 方向(向いている方向, 移動する方向)
	/// </summary>
	enum class Direction {
		Up,
		Down,
		Left,
		Right,
	};

	struct IntersectPoint {
		static const int Size = 2;

		vector<Vector2> right;
		vector<Vector2> left;
		vector<Vector2> top;
		vector<Vector2> bottom;

		IntersectPoint()
			: right(Size)
			, left(Size)
			, top(Size)
			, bottom(Size)
		{}
	};

	// キャラクターの基底クラス
	class IActor : public Object {
	public:
		IActor();
		~IActor() = default;

		virtual void onStart() = 0;
		virtual void onUpdate() = 0;

		virtual bool isOnScreen();

		// マップとの当たり判定
		virtual Vector2 intersectTileMap() = 0;

		// 初期位置を設定
		void initPosition(const Vector2& _initPos) {
			this->transform.pos.setPos(_initPos);
		}

		// 加速ベクトルを取得する
		inline const Vector2& getVelocity() {
			return velocity;
		}

	protected:
		Vector2 velocity;                // 速度
		Bounds bounds;                   // バウンディングボックス
		IntersectPoint intersectPoint;   // 床との当たり判定
		bool isFlip = false;
	};

}

#endif // !ACTOR_H
