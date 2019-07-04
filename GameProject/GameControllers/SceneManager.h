#ifndef __SCENE_MANAGER__
#define __SCENE_MANAGER__

#include "../GameComponents/Scene.h"

class SceneManager
{
public:
    static SceneManager *GetInstance();
    ~SceneManager();

    Scene* GetCurrentScene();
    void Update(float dt);
    void ReplaceScene(Scene *scene);

private:
    SceneManager();
    static SceneManager     *mInstace;
    Scene                   *mCurrentScene;    
};

#endif