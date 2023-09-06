#ifndef OBJ2D_H
#define OBJ2D_H

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
};

struct METEOR : public OBJ2D //heinŒN ’S“–
{

};

struct ITEM :public OBJ2D //dang ŒN’S“–
{

};

struct ALIEN :public OBJ2D //‹{–{ŒN’S“–
{

};

struct SPACE_SHIP :public OBJ2D //ƒ‚ƒE’S“–
{
    float fuel;
    bool turboMode;

    void spaceShipInit();
};

struct BEAM : public OBJ2D //ƒ‚ƒE’S“–
{
    void beamInit();
};
#endif