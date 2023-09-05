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
        VECTOR2 startCoord;
        VECTOR2 endCoord;
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
     /*   if (playerCollisionCoord.startCoord.x > enemyCoord.startCoord.x && playerCollisionCoord.startCoord.y<)
        {

        }*/
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
};
#endif