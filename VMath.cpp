#include "VMath.h"
using namespace sf;


Vector2f VMath::Nor(Vector2f vector)
{
	if (powf(vector.x, 2.0f) + powf(vector.y, 2.0f) == 0)
		return vector;
	else
	{
		vector.x = vector.x / sqrtf(powf(vector.x, 2.0f) + powf(vector.y, 2.0f));
		vector.y = vector.y / sqrtf(powf(vector.x, 2.0f) + powf(vector.y, 2.0f));
		return vector;
	}
}

float VMath::Mag(Vector2f vector)
{
	return sqrtf(powf(vector.x, 2.0f) + powf(vector.y, 2.0f));
}

float VMath::Dot(Vector2f v0, Vector2f v1)
{
	return v0.x * v1.x + v0.y * v1.y;
}

float VMath::Map(float val, Vector2f min, Vector2f max)
{
	return min.y + ((max.y - min.y) * (val - min.x)) / (max.x - min.x);
}

void VMath::Limit(Vector2f &vector, float limit) {
	float mag = sqrt(powf(vector.x,2.0f) + powf(vector.y,2.0f));

	if (mag > limit) {
		vector = vector / mag * limit;
	}
}
float VMath::Rot(Vector2f vector) {
	if (vector.y <= 0) {
		return asin(vector.x / std::sqrt(vector.x * vector.x + vector.y * vector.y)) * 180.f / 3.14f;
	}
	else {
		if (vector.x == 0) {
			return 180.f;
		}
		else if (vector.x > 0) {
			return atan(vector.y / vector.x) * 180.f / 3.14f + 90.f;
		}
		else if (vector.x < 0) {
			return atan(vector.y / vector.x) * 180.f / 3.14f - 90.f;
		}
	}
}