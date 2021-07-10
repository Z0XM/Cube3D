#include "CubeAnimation.hpp"

CubeAnimation::CubeAnimation()
{
	reset();
}

void CubeAnimation::setup(float speed, float target, float* var)
{
	this->speed = speed;
	this->var = var;
	this->target = target;
	this->animating = true;

}

void CubeAnimation::reset()
{
	dir = 1;
	target = 0;
	speed = 1;
	var = nullptr;
	animating = false;
	angles = { 0,0,0 };

	finish = nullptr;
	work = nullptr;
}

void CubeAnimation::instant()
{
	*var += speed * dir;
}

bool CubeAnimation::isOver()
{
	return *var == target;
}

void CubeAnimation::animate()
{
	if (isOver()) {
		if(finish != nullptr)finish();
		reset();
	}
	else {
		work();
	}
}