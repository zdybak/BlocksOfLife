#include <stdio.h>
#include <stdlib.h>
#include "../include/raylib.h"

#define XCOORD -10.0f
#define YCOORD -10.0f
#define HALFCUBE 0.5f

void drawLife(float x, float y, Color col)
{
    Vector3 cubePosition;
    float finalX = x+XCOORD;
    float finalY = y+YCOORD;
    
    if(finalX >= 0 && finalY >= 0){
        cubePosition = (Vector3){ finalX-HALFCUBE, 0.5f, finalY-HALFCUBE };
        printf("-x -y\n");
    } else if (finalX <= 0 && finalY >= 0) {
        cubePosition = (Vector3){ finalX+HALFCUBE, 0.5f, finalY-HALFCUBE };
        printf("+x -y\n");
    } else if (finalX <= 0 && finalY <= 0) {
        cubePosition = (Vector3){ finalX+HALFCUBE, 0.5f, finalY+HALFCUBE };
        printf("+x +y\n");
    } else {
        cubePosition = (Vector3){ finalX-HALFCUBE, 0.5f, finalY+HALFCUBE };
        printf("-x +y\n");
    }
    printf("X: %f\n", cubePosition.x);
    printf("Y: %f\n", cubePosition.y);
    printf("Z: %f\n", cubePosition.z);
}

int main(int argc, char **args){
    
    float x = atof(args[1]);
    float y = atof(args[2]);
    
    drawLife(x,y,BLUE);

    return 0;
}