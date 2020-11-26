#ifndef ACTORMOVE_H
#define ACTORMOVE_H

namespace gnGame {

	class Actor;

	class ActorMove {
	public:
		ActorMove()
			: velocity()
		{}

		virtual ~ActorMove() = default;

		// Actorを動かす
		virtual void moveActor() = 0;

		// 外部から加速度を加算したいときに呼び出す
		//virtual void addVelocity(const Vector2& _velocity);

	protected:
		Vector2 velocity;
	};

}

#endif // !ACTORMOVE_H
