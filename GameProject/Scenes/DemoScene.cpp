#include "DemoScene.h"
#include "../GameDefines/GameDefine.h"

DemoScene::DemoScene()
{
    LoadContent();
}

void DemoScene::LoadContent()
{
    //set mau backcolor cho scene o day la mau xanh
    mBackColor = 0x54acd2;
	string filePath = "Resources/marioworld1-1.tmx";
    mMap = new GameMap(filePath);

    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
    mCamera->SetPosition(GameGlobal::GetWidth() / 2, 
                            mMap->GetHeight() - mCamera->GetHeight());

    mMap->SetCamera(mCamera);

    mPlayer = new Player();

    mPlayer->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
    mPlayer->SetCamera(mCamera);
}

void DemoScene::Update(float dt)
{
    checkCollision();

    mMap->Update(dt);

    mPlayer->HandleKeyboard(keys);

    mPlayer->Update(dt);

    CheckCameraAndWorldMap();
}

void DemoScene::Draw()
{
    mMap->Draw();

    mPlayer->Draw();
}

void DemoScene::OnKeyDown(int keyCode)
{
    keys[keyCode] = true;

    mPlayer->OnKeyPressed(keyCode);
}

void DemoScene::OnKeyUp(int keyCode)
{
    keys[keyCode] = false;

    mPlayer->OnKeyUp(keyCode);
}

void DemoScene::OnMouseDown(float x, float y)
{
}

void DemoScene::CheckCameraAndWorldMap()
{
    mCamera->SetPosition(mPlayer->GetPosition());

    if (mCamera->GetBound().left < 0)
    {
        //vi position cua camera ma chinh giua camera
        //luc nay o vi tri goc ben trai cua the gioi thuc
        mCamera->SetPosition(mCamera->GetWidth() / 2, mCamera->GetPosition().y);
    }

    if (mCamera->GetBound().right > mMap->GetWidth())
    {
        //luc nay cham goc ben phai cua the gioi thuc
        mCamera->SetPosition(mMap->GetWidth() - mCamera->GetWidth() / 2, 
                                mCamera->GetPosition().y);
    }

    if (mCamera->GetBound().top < 0)
    {
        //luc nay cham goc tren the gioi thuc
        mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetHeight() / 2);
    }

    if (mCamera->GetBound().bottom > mMap->GetHeight())
    {
        //luc nay cham day cua the gioi thuc
        mCamera->SetPosition(mCamera->GetPosition().x, 
                                mMap->GetHeight() - mCamera->GetHeight() / 2);
    }
}

void DemoScene::checkCollision()
{
    /*su dung de kiem tra xem khi nao mario khong dung tren 1 object hoac
    dung qua sat mep trai hoac phai cua object do thi se chuyen state la falling*/ 
    int widthBottom = 0;

    vector<Entity*> listCollision;

    mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mPlayer);

    for (size_t i = 0; i < listCollision.size(); i++)
    {
        Entity::CollisionReturn r = GameCollision::RecteAndRect(mPlayer->GetBound(), 
                                                    listCollision.at(i)->GetBound());

        if (r.IsCollided)
        {
            //lay phia va cham cua Entity so voi Player
            Entity::SideCollisions sidePlayer = GameCollision::getSideCollision(mPlayer, r);

            //lay phia va cham cua Player so voi Entity
            Entity::SideCollisions sideImpactor = GameCollision::getSideCollision(listCollision.at(i), r);

            //goi den ham xu ly collision cua Player va Entity
            mPlayer->OnCollision(listCollision.at(i), r, sidePlayer);
            listCollision.at(i)->OnCollision(mPlayer, r, sideImpactor);

            //kiem tra neu va cham voi phia duoi cua Player 
            if (sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft 
                || sidePlayer == Entity::BottomRight)
            {
                //kiem cha do dai ma mario tiep xuc phia duoi day
                int bot = r.RegionCollision.right - r.RegionCollision.left;

                if (bot > widthBottom)
                    widthBottom = bot;
            }
        }
    }

    //Neu mario dung ngoai mep thi luc nay cho mario rot xuong duoi dat    
    if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
    {
        mPlayer->OnNoCollisionWithBottom();
    }
}