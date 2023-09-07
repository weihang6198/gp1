#ifndef OBJ2D_H
#define OBJ2D_H

//******************************************************************************
//
//
//      obj2d.h
//
//
//******************************************************************************

//------< \’Μ >--------------------------------------------------------------
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
    //TODO collision
    void drawCollision(int posX,int posY,int width,int height )
    {
        //to draw top line
        primitive::line(
            posX, posY, posX + width, posY, //pos
            1, 1, 1, 1, //rgba
            1); //thicness

        //to draw bottom line
        primitive::line(
            posX, posY+height, posX + width, posY+height, //pos
            1, 1, 1, 1, //rgba
            1); //thicness

        //to draw right line
        primitive::line(
            posX+width, posY , posX + width, posY + height, //pos
            1, 1, 1, 1, //rgba
            1); //thicness
        //to draw left line
        primitive::line(
            posX , posY, posX , posY + height, //pos
            1, 1, 1, 1, //rgba
            1); //thicness
    }

    //to detect collision
    //this is to compare the collision between enemy and player
    //this function can be used for all dir (top down left right)
    void collisionDetector(COLLISION_COORD playerCollisionCoord,COLLISION_COORD enemyCoord)
    {
       //right side of the plane hitting left side of the rock
        if (playerCollisionCoord.right > enemyCoord.left && playerCollisionCoord.right < enemyCoord.right
            && playerCollisionCoord.top <enemyCoord.bottom && playerCollisionCoord.bottom >enemyCoord.top
            )
        {
            debug::setString("collided the left side ");
        }
      
        //right side of the rock hitting the left side of the plane
        else if (enemyCoord.right > playerCollisionCoord.left && enemyCoord.right < playerCollisionCoord.right
            && enemyCoord.top <playerCollisionCoord.bottom && enemyCoord.bottom >playerCollisionCoord.top
            )
        {
            debug::setString("collided the right side ");
        }
        else
        {
            debug::setString("did not collided");
        }
    }

    void updateCollisionCoord(COLLISION_COORD *playerCollisionCoord,float left,float right,float top,float bottom)
    {
        playerCollisionCoord->left = left;
        playerCollisionCoord->right = right;
        playerCollisionCoord->top = top ;
        playerCollisionCoord->bottom = bottom;

    }

    void processCollision(OBJ2D obj1, OBJ2D obj2);
            
};

struct METEOR : public OBJ2D //heinN S
{
    int life;
};

struct ITEM :public OBJ2D //dang NS
{
    enum ITEM_TYPE
    {
        battery,
        fuelPack
    };
    ITEM_TYPE itemType;
};

struct ALIEN :public OBJ2D //{{NS
{
    int life;
};

struct SPACE_SHIP :public OBJ2D //ES
{
    float fuel;
    bool turboMode;
    bool beamFired;
    int beamCount;
    int life;
    VECTOR2 beamFireLoc;
    void spaceShipInit();
};

struct BEAM : public OBJ2D //ES
{
    int visibility;
    bool canFire;
    bool setInitLoc;
    void beamInit();
    void beamTravel();
    void selfDestruct();
};
#endif