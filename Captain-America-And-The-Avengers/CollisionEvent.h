#pragma once
class CollisionEvent : ISingleton
{
public:
	static CollisionEvent& GetInstance();
	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st,
		float sr,
		float sb,
		float &t,
		float &nx,
		float &ny);



private:
	CollisionEvent() : ISingleton(NULL) {}
};