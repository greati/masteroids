#include "CollisionTools.h"
#include "PhysicalEntity.h"
#include <cmath>


bool CollisionTools::circleCollision(const PhysicalEntity & e1, const PhysicalEntity & e2) {
	double r1 = std::fmax(e1.getWidth() / 2, e1.getHeigth() / 2);
	double r2 = std::fmax(e2.getWidth() / 2, e2.getHeigth() / 2);

	double currentDist = MathVector::size({e1.getPosition().horizontal, e1.getPosition().vertical}, {e2.getPosition().horizontal, e2.getPosition().vertical});
	return (currentDist <= r1 + r2);
}
