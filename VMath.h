#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

static class VMath
{
public:
	Vector2f static Nor(Vector2f vector);
	float static Mag(Vector2f vector);
	float static Dot(Vector2f v0, Vector2f v1);
	float static Map(float val, Vector2f min, Vector2f max);
	float static Rot(Vector2f vector);
	void static Limit(Vector2f &vector, float limit);
};