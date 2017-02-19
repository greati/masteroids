#include "MathVector.h"
#include <cmath>

double MathVector::size() const {
	return std::sqrt(horizontal * horizontal + vertical * vertical);
}

double MathVector::size(Point origin, Point end) { 
	return std::sqrt(std::pow((origin.x - end.x), 2) + std::pow((origin.y - end.y), 2));
}
