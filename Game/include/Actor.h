#ifndef ACTOR_H
#define ACTOR_H

#include "Lib.h"

namespace gnGame {

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

	// �L�����N�^�[�̊��N���X
	class IActor : public Object {
	public:
		IActor() 
			: pos()
			, velocity()
			, bounds()
			, intersectPoint()
		{}

		~IActor() = default;

		virtual void onStart() = 0;
		virtual void onUpdate() = 0;

		// �}�b�v�Ƃ̓����蔻��
		virtual Vector2 intersectTileMap() = 0;

		inline const Vector2& getPos() {
			return pos;
		}

		inline const Vector2& getVelocity() {
			return velocity;
		}

	protected:
		Vector2 pos;                     // ���W
		Vector2 velocity;                // ���x
		Bounds bounds;                   // �o�E���f�B���O�{�b�N�X
		IntersectPoint intersectPoint;   // ���Ƃ̓����蔻��
	};

}

#endif // !ACTOR_H