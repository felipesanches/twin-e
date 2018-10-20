#include "gtest/gtest.h"
#include "sys.h"

//#include "movements.h"
//#include "scene.h"
//#include "gamestate.h"

//////////////////////////////////
// FAKE IT ALL FOR NOW:
extern int32 getAngleAndSetTargetActorDistance(int, int, int, int);

int32 initAnim(int32 newAnim, int16 animType, uint8 animExtra, int32 actorIdx){
  //FOO
  return 0;
}

void initModelActor(int, short){
//FOO
}

//#include "lbaengine.h"
volatile int32 lbaTime;
int32 loopPressedKey;
int32 previousLoopPressedKey;

//#include "renderer.h"
#include "original_shadeangletab.h"
int16* original_shadeAngleTab3 = &original_shadeAngleTable[384];
int16* shadeAngleTab3 = &original_shadeAngleTable[384];
int16 destX;
int16 destZ;

//#include "grid.h"
uint8 *blockBuffer;
uint8* getBlockLibrary(int32 /* index */){
	//FOO
	return NULL;
}

//#include "keyboard.h"
int16 skipIntro;
int32 heroPressedKey;
int32 heroPressedKey2;

//#include "collision.h"
int32 collisionX;
int32 collisionY;
int32 collisionZ;
void reajustActorPosition(int32 brickShape){
//FOO
}
//////////////////////////////////

int32 original_getAngleAndSetTargetActorDistance(int32 x1, int32 z1, int32 x2, int32 z2);

/*
TEST(MovementsTest,getAngleAndSetTargetActorDistance){
  int32 x1=100, z1=100, x2, z2;
  int32 expected, actual;
  int step = 3;

  fprintf(stderr, "data = [\n");
  for (x2=0; x2<200; x2+=step){
    for (z2=0; z2<200; z2+=step){
      expected = original_getAngleAndSetTargetActorDistance(x1, z1, x2, z2);
      actual = getAngleAndSetTargetActorDistance(x1, z1, x2, z2);
      fprintf(stderr, "  [%d, %d, %d, %d, %d, %d],\n", x1, z1, x2, z2, expected, actual);
      EXPECT_EQ(expected, actual);
    }
  }
  fprintf(stderr, "]\n");
}
*/
#define PI 3.141592
TEST(MovementsTest,getAngleAndSetTargetActorDistance){
  int32 x1=100, z1=100, x2, z2;
  int32 expected, actual;

  float L = 3;
  float angle=0, radius=10;
  float angle_step = L/radius; // = 2*PI/(2*PI*radius/L);
  int radius_step = L;
  int num_loops = 100/radius_step;

  fprintf(stderr, "data = [\n");
  for (angle=0; angle<2*PI*num_loops; angle+=angle_step){
    radius = radius_step * (angle/2*PI + 1); //update
    angle_step = L/radius; //update
    x2 = (int) floor(x1 + radius * cos(angle));
    z2 = (int) floor(z1 + radius * sin(angle));
    expected = original_getAngleAndSetTargetActorDistance(x1, z1, x2, z2);
    actual = getAngleAndSetTargetActorDistance(x1, z1, x2, z2);
    if (abs(actual-expected)<1000){
      fprintf(stderr, "  [%d, %d, %d, %d, %d, %d, %d],\n", x1, z1, x2, z2, actual-expected, actual, expected);
      EXPECT_EQ(expected, actual);
    }
  }
  fprintf(stderr, "]\n");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

extern int32 targetActorDistance;
int32 original_getAngleAndSetTargetActorDistance(int32 x1, int32 z1, int32 x2, int32 z2) {
        int32 newX, newZ, difX, difZ, tmpX, tmpZ, tmpEx, flag, destAngle, startAngle, finalAngle;

        difZ = tmpZ = z2 - z1;
        newZ = tmpZ * tmpZ;

        difX = tmpX = x2 - x1;
        newX = tmpX * tmpX;

        // Exchange X and Z
        if (newX < newZ) {
                tmpEx = difX;
                difX = difZ;
                difZ = tmpEx;

                flag = 1;
        } else {
                flag = 0;
        }

        targetActorDistance = (int32)sqrt((int64)(newX + newZ));

        if (!targetActorDistance) {
                return 0;
        }

        destAngle = (difZ << 14) / targetActorDistance;

        startAngle = 0;
//      stopAngle  = 0x100;

        while (original_shadeAngleTab3[startAngle] > destAngle) {
                startAngle++;
        }

        if (original_shadeAngleTab3[startAngle] != destAngle) {
                if ((original_shadeAngleTab3[startAngle - 1] + original_shadeAngleTab3[startAngle]) / 2 <= destAngle) {
                        startAngle--;
                }
        }

        finalAngle = 128 + startAngle;

        if (difX <= 0) {
                finalAngle = -finalAngle;
        }

        if (flag & 1) {
                finalAngle = -finalAngle + 0x100;
        }

        return finalAngle & 0x3FF;
}

