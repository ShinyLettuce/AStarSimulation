#pragma once
#include "raylib.h"
#include <cmath>

float random_float01();

float random_float_in_range(float min, float max);

bool operator==(Vector2 a, Vector2 const& b);