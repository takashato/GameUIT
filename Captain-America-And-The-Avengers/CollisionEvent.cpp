#include "pch.h"
#include "CollisionEvent.h"

CollisionEvent::CollisionEvent(float t, float nx, float ny, Entity* entity)
{
	this->t = t;
	this->nx = nx;
	this->ny = ny;
	this->entity = entity;
}

void CollisionEvent::SweptAABB(
	float ml, float mt, float mr, float mb,			//move box 
	float dx, float dy,			                    //dx, dy
	float sl, float st, float sr, float sb,			//static box
	float &t, float &nx, float &ny)					//time, toa do x vector phap tuyen noi va cham, toa do y vector phap
{
	//dx_entry, dy_entry la khoang cach can di , tx_entry ty_entry la thoi gian can di de bat dau va cham
	//exit la khoang cach va thoi gian de thoat khoi va cham
	float dx_entry, dx_exit, tx_entry, tx_exit;
	float dy_entry, dy_exit, ty_entry, ty_exit;

	float t_entry;
	float t_exit;

	t = -1.0f;			// no collision
	nx = ny = 0;

	//
	// Broad-phase test (vung dien rong va cham)
	//

	float bl = dx > 0 ? ml : ml + dx;
	float bt = dy > 0 ? mt : mt + dy;
	float br = dx > 0 ? mr + dx : mr;
	float bb = dy > 0 ? mb + dy : mb;

	if (br < sl || bl > sr || bb < st || bt > sb) return; //AABBcheck


	if (dx == 0 && dy == 0) return;		// moving object is not moving > obvious no collision

	if (dx > 0)
	{
		dx_entry = sl - mr;
		dx_exit = sr - ml;
	}
	else if (dx < 0)
	{
		dx_entry = sr - ml;
		dx_exit = sl - mr;
	}


	if (dy > 0)
	{
		dy_entry = st - mb;
		dy_exit = sb - mt;
	}
	else if (dy < 0)
	{
		dy_entry = sb - mt;
		dy_exit = st - mb;
	}

	if (dx == 0)
	{
		tx_entry = -99999999999;//Vo cuc
		tx_exit = 99999999999;
	}
	else
	{
		tx_entry = dx_entry / dx;
		tx_exit = dx_exit / dx;
	}

	if (dy == 0)
	{
		ty_entry = -99999999999;
		ty_exit = 99999999999;
	}
	else
	{
		ty_entry = dy_entry / dy;
		ty_exit = dy_exit / dy;
	}

	//Thoi gian va cham luon >=0 va <=1
	if ((tx_entry < 0.0f && ty_entry < 0.0f) || tx_entry > 1.0f || ty_entry > 1.0f) return;

	t_entry = max(tx_entry, ty_entry);
	t_exit = min(tx_exit, ty_exit);

	if (t_entry > t_exit) return;

	t = t_entry;

	if (tx_entry > ty_entry)
	{
		ny = 0.0f;
		dx > 0 ? nx = -1.0f : nx = 1.0f;
	}
	else
	{
		nx = 0.0f;
		dy > 0 ? ny = -1.0f : ny = 1.0f;
	}
}

void CollisionEvent::compare(const CollisionEvent*& a, const CollisionEvent*& b)
{
	return a->t < b->t;
}
