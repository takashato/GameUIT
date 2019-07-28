#pragma once

class Entity;

struct CollisionEvent
{
	Entity* entity;
	float t, nx, ny;

	CollisionEvent(float t, float nx, float ny, Entity* entity);

	static void SweptAABB(
		float ml, float mt, float mr, float mb, // Moving box
		float dx, float dy, // Delta X, delta Y
		float sl, float st, float sr, float sb, // Static box
		float &t, float &nx, float &ny ); // Time, n(nx, ny) collision vector

	static bool compare(CollisionEvent* &a, CollisionEvent* &b);
};