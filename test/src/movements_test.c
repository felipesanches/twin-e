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

TEST(MovementsTest,getAngleAndSetTargetActorDistance){
  int32 x1, z1, x2, z2;

  for (x1=0; x1<100; x1++){
    for (z1=0; z1<100; z1++){
      for (x2=0; x2<100; x2++){
        for (z2=0; z2<100; z2++){
          EXPECT_EQ(
            original_getAngleAndSetTargetActorDistance(x1, z1, x2, z2),
                     getAngleAndSetTargetActorDistance(x1, z1, x2, z2)
          );
        }
      }
    }
  }
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

