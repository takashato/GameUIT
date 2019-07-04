#pragma once

#include <d3dx9.h>
#include <d3d9.h>
#include <map>

class Entity
{

public:

    Entity();

    enum SideCollisions
    {
        Left, //0
        Right, //1
        Top, //2
        Bottom, //3
        TopLeft, //4
        TopRight, //5
        BottomLeft, //6
        BottomRight, //7
        NotKnow
    };

    struct CollisionReturn
    {
        bool IsCollided;
        RECT RegionCollision;
    };

    enum EntityTypes
    {
        None, Brick, Enemy, Mario, Static, BrickGoldNormal, BrickGoldEated
    };

    EntityTypes Tag; //Tag de nhan vien loai Entity

    virtual RECT GetBound();

    virtual void SetPosition(float x, float y);

    virtual void SetPosition(D3DXVECTOR2 pos);

    virtual void SetPosition(D3DXVECTOR3 pos);

    virtual void AddPosition(D3DXVECTOR3 pos);

    virtual void AddPosition(D3DXVECTOR2 pos);

    virtual void AddPosition(float x, float y);

    virtual void SetWidth(int width);

    virtual int GetWidth();

    virtual void SetHeight(int height);

    virtual int GetHeight();

    virtual float GetVx();

    virtual void SetVx(float vx);

    virtual void AddVx(float vx);

    virtual float GetVy();

    virtual void SetVy(float vy);

    virtual void AddVy(float vy);

    virtual D3DXVECTOR3 GetPosition();

    virtual void Update(float dt);

    //kiem soat viec va cham
    //khi xay ra va cham voi 1 thuc the nao do thi ham nay se dc goi de xu ly
    virtual void OnCollision(Entity *impactor, CollisionReturn data, SideCollisions side);

protected:

    //duoc goi khi set position cua Entity, dung cho ke thua
    virtual void OnSetPosition(D3DXVECTOR3 pos);

    //vi tri tam position x va y
    float posX, posY;

    //phan toc vx, vy
    float vx, vy;

    //size cua entity
    float width, height;
};