#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include "../GameObjects/Entity.h"

class GameCollision
{
public:
    
    GameCollision();
    //kiem tra va cham giua 2 hinh chu nhat
    static Entity::CollisionReturn RecteAndRect(RECT rect, RECT rect2);

    static bool isCollide(RECT rect1, RECT rect2);

    //neu rectagle qua to thi va cham co the bi sai
    static Entity::SideCollisions getSideCollision(Entity *e1, Entity *e2);

    //kiem tra vi tri va cham dua vao vung va cham cua 2 vat the
    static Entity::SideCollisions getSideCollision(Entity *e1, Entity::CollisionReturn data);

    //kiem tra 1 diem co nam trong hinh chu nhat hay khong
    static bool PointAndRectangle(float x, float y, RECT rect);

    //hinh chu nhat va hinh tron
    static bool RectangleAndCircle(RECT rect, int circlex, int circley, int circleRadius);
    ~GameCollision();
};