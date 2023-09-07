#ifndef OBJ2D_H
#define OBJ2D_H
#include <random>
//******************************************************************************
//
//
//      obj2d.h
//
//
//******************************************************************************

//------< \‘¢‘Ì >--------------------------------------------------------------
struct OBJ2D
{

    struct VECTOR2
    {
        float x;
        float y;
    };

    struct VECTOR4
    {
        int r, g, b, a;
    };

    struct COLLISION_COORD
    {
        float left; //x coord
        float right; //x coord +width
        float top;  //y coord 
        float bottom; //y coord+ height
    };

    enum OBJ_TYPE
    {
        PLAYER,
        ENEMY,
        PROJECTILE,
        CONSUMABLE
    };
   
    int timer;
    GameLib::Sprite* spr;
    VECTOR2 pos;
    VECTOR2 scale;
    VECTOR2 texPos;
    VECTOR2 texSize;
    VECTOR2 pivot;
    VECTOR4 color;
    VECTOR2 speed;
    VECTOR2 maxSpeed;   
    COLLISION_COORD collisionCoord;
    VECTOR2 inGameSize;
    OBJ_TYPE objType;
    Sprite* sprImg;
    bool collided = false;

    //TODO collision
    void drawCollision(int posX, int posY, int width, int height);
    //to detect collision
    //this is to compare the collision between enemy and player
    //this function can be used for all dir (top down left right)
    void collisionDetector(OBJ2D* playerCollisionCoord, OBJ2D* enemyCoord);
    void updateCollisionCoord(COLLISION_COORD* playerCollisionCoord, float left, float right, float top, float bottom);
    void processCollision(OBJ2D *obj1, OBJ2D *obj2);
    
};

struct METEOR : public OBJ2D //heinŒN ’S“–
{
    int life;
};

struct ITEM :public OBJ2D //dang ŒN’S“–
{
    enum ITEM_TYPE
    {
        battery,
        repair_kit,
        fuel
    }; 

 void itemInit(float posX,float posY,ITEM_TYPE itemType, Sprite* sprImg);
 void processItem();
};

struct ALIEN :public OBJ2D //‹{–{ŒN’S“–
{
    int life;
};

struct SPACE_SHIP :public OBJ2D //ƒ‚ƒE’S“–
{
    int fuel;
    int battery;
    bool turboMode;
    bool beamFired;
    int beamCount;
    int life;
    VECTOR2 beamFireLoc;

    void spaceShipInit();
};

struct BEAM : public OBJ2D //ƒ‚ƒE’S“–
{
    int visibility;
    bool canFire;
    bool setInitLoc;
    void beamInit();
    void beamTravel();
    void selfDestruct();
};

OBJ2D* searchSet0(OBJ2D arr[], int dataNum, int moveAlg, VECTOR2 pos);
#endif