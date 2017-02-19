#ifndef _COLLISIONT_
#define _COLLISIONT_

class PhysicalEntity;

class CollisionTools {
	public:
		CollisionTools() = delete;
		CollisionTools(const CollisionTools &) = delete;
		CollisionTools & operator=(const CollisionTools &) = delete;
		
		static bool circleCollision(const PhysicalEntity &, const PhysicalEntity &);
};

#endif
