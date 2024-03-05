#include "utils.h"

float random_float01()
{
	return rand() / static_cast<float>(RAND_MAX);
}

float random_float_in_range(float min, float max)
{
	return random_float01() * (max - min) + min;
}

bool operator==(Vector2 a, Vector2 const& b)
{
	return a.x == b.x && a.y == b.y;
};