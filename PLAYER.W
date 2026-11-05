@* Paths---The Player.  This is the code that controls the movement of the
player or players through the path portion of \TT.  Since only one player can
be active at a time, there is no player--player interaction or screen
positioning compromises to deal with.  Basic movement is the same for both
characters, and only differs for attacks and special movement.  (Of course all
the animations are different, but the dynamics are the same.)

@ This is the top-level player controller.  Everything gets done by way of the
state machines, so this code is pretty simple.

@<Move the player@>=
  currentPlayer->fsmState = fsm(currentPlayer->fsmState);

@ @<Global...@>=
State MilesStand[] = {@/
  {CheckJumpNorth, MilesJumpNorth, PrepareMilesJumpNorth, 0},@/
  {CheckJumpSouth, MilesJumpSouth, PrepareMilesJumpSouth, 0},@/
  {CheckJumpWest, MilesJumpWest, PrepareMilesJumpWest, 0},@/
  {CheckJumpEast, MilesJumpEast, PrepareMilesJumpEast, 0},@/
  {TimeToYawn, MilesYawn, BumpCount, 0},@/
  {True, MilesStand, BumpCount, 0}@/
};@#

State MilesJumpEast[] = {@/
  {MilesLanded, MilesCheckLandingEast, MilesFinishJumpEast, FSM_RERUN},@/
  {True, MilesJumpEast, DoMilesJumpEast, 0}@/
};@#

State MilesJumpWest[] = {@/
  {MilesLanded, MilesCheckLandingWest, MilesFinishJumpWest, FSM_RERUN},@/
  {True, MilesJumpWest, DoMilesJumpWest, 0}@/
};@#

State MilesJumpNorth[] = {@/
  {MilesLanded, MilesCheckLandingNorth, MilesFinishJumpNorth, FSM_RERUN},@/
  {True, MilesJumpNorth, DoMilesJumpNorth, 0}@/
};@#

State MilesJumpSouth[] = {@/
  {MilesLanded, MilesCheckLandingSouth, MilesFinishJumpSouth, FSM_RERUN},@/
  {True, MilesJumpSouth, DoMilesJumpSouth, 0}@/
};@#

State MilesYawn[] = {@/
  {True, MilesStand, BumpCount, 0}@/
};@#

State MilesCheckLandingEast[] = {@/
  {MilesNewSquareMissing, MilesFall, Null, 0},@/
  {MilesNewSquareSlippery, MilesSlideEast, Null, 0},@/
  {True, MilesStand, Null, 0}@/
};@#

State MilesCheckLandingWest[] = {@/
  {MilesNewSquareMissing, MilesFall, Null, 0},@/
  {MilesNewSquareSlippery, MilesSlideWest, Null, 0},@/
  {True, MilesStand, Null, 0}@/
};@#

State MilesCheckLandingNorth[] = {@/
  {MilesNewSquareMissing, MilesFall, Null, 0},@/
  {MilesNewSquareSlippery, MilesSlideNorth, Null, 0},@/
  {True, MilesStand, Null, 0}@/
};@#

State MilesCheckLandingSouth[] = {@/
  {MilesNewSquareMissing, MilesFall, Null, 0},@/
  {MilesNewSquareSlippery, MilesSlideSouth, Null, 0},@/
  {True, MilesStand, Null, 0}@/
};@#

State MilesFall[] = {@/
  {True, MilesStand, Null, 0}@/
};@#

State MilesSlideWest[] = {@/
  {MilesSlideDone, MilesCheckLandingWest, MilesFinishJumpWest, 1},@/
  {True, MilesSlideWest, SlideMilesWest, 0}@/
};@#

State MilesSlideEast[] = {@/
  {MilesSlideDone, MilesCheckLandingEast, MilesFinishJumpEast, 1},@/
  {True, MilesSlideEast, SlideMilesEast, 0}@/
};@#

State MilesSlideNorth[] = {@/
  {MilesSlideDone, MilesCheckLandingNorth, MilesFinishJumpNorth, 1},@/
  {True, MilesSlideNorth, SlideMilesNorth, 0}@/
};@#

State MilesSlideSouth[] = {@/
  {MilesSlideDone, MilesCheckLandingSouth, MilesFinishJumpSouth, 1},@/
  {True, MilesSlideSouth, SlideMilesSouth, 0}@/
};@#

@ @<Function prototypes@>=
State MilesStand[];@/
State MilesJumpEast[];@/
State MilesJumpWest[];@/
State MilesJumpNorth[];@/
State MilesJumpSouth[];@/
State MilesYawn[];@/
State MilesCheckLandingEast[];@/
State MilesCheckLandingWest[];@/
State MilesCheckLandingNorth[];@/
State MilesCheckLandingSouth[];@/
State MilesFall[];@/
State MilesSlideSouth[];@/
State MilesSlideNorth[];@/
State MilesSlideWest[];@/
State MilesSlideEast[];@/
@#
void ClearCount(void);@/
void BumpCount(void);@/
void DoMilesJumpEast(void);@/
void DoMilesJumpWest(void);@/
void DoMilesJumpNorth(void);@/
void DoMilesJumpSouth(void);@/
void MilesFinishJumpEast(void);@/
void MilesFinishJumpWest(void);@/
void MilesFinishJumpNorth(void);@/
void MilesFinishJumpSouth(void);@/
void SlideMilesSouth(void);@/
void SlideMilesNorth(void);@/
void SlideMilesEast(void);@/
void SlideMilesWest(void);@/
void PrepareMilesJumpNorth(void);@/
void PrepareMilesJumpSouth(void);@/
void PrepareMilesJumpEast(void);@/
void PrepareMilesJumpWest(void);@/
@#
int ControllerUp(void);@/
int ControllerDown(void);@/
int ControllerLeft(void);@/
int ControllerRight(void);@/
int TimeToYawn(void);@/
int MilesLanded(void);@/
int MilesNewSquareMissing(void);@/
int MilesNewSquareSlippery(void);@/
int MilesSlideDone(void);@/

@ This routine clears a player's auxiliary counter.

@c
void ClearCount(){
  currentPlayer->counter = 0;
  currentPlayer->yOffset = 0;
  currentPlayer->xOffset = 0;
  return;
}

@ This routine increments a player's auxiliary counter.

@c
void BumpCount(){
  currentPlayer->counter++;
  return;
}

@ These routines prepare for Miles' jump by initializing some values.

@c
void PrepareMilesJumpNorth(void){
  ClearCount();
  currentPlayer->delta_e =
 pathMap[mapWidth*currentPlayer->yPosition+currentPlayer->xPosition].elevation -
  pathMap[mapWidth*(currentPlayer->yPosition+1)+currentPlayer->xPosition].elevation;
}

void PrepareMilesJumpSouth(void){
  ClearCount();
  currentPlayer->delta_e =
 pathMap[mapWidth*currentPlayer->yPosition+currentPlayer->xPosition].elevation -
  pathMap[mapWidth*(currentPlayer->yPosition-1)+currentPlayer->xPosition].elevation;
}

void PrepareMilesJumpEast(void){
  ClearCount();
  currentPlayer->delta_e =
 pathMap[mapWidth*currentPlayer->yPosition+currentPlayer->xPosition].elevation -
  pathMap[mapWidth*currentPlayer->yPosition+currentPlayer->xPosition+1].elevation;
}

void PrepareMilesJumpWest(void){
  ClearCount();
  currentPlayer->delta_e =
 pathMap[mapWidth*currentPlayer->yPosition+currentPlayer->xPosition].elevation -
  pathMap[mapWidth*currentPlayer->yPosition+currentPlayer->xPosition-1].elevation;
}

@ These routines manipulate Miles' display position to produce a proper jump
trajectory.

@d MilesJumpYImpulse (16+14+12+10+8+6+4+2)

@c

short jumpArc[] = {
 0,
 0x0147,
 0x07bb,
 0x0d1d,
 0x116a,
 0x14a4,
 0x16ca,
 0x17de,
 0x17de,
 0x16ca,
 0x14a4,
 0x116a,
 0x0d1d,
 0x07bb,
 0x0147,
 0
};

void DoMilesJumpEast(){
  currentPlayer->xOffset += 0x200;
  currentPlayer->yOffset = jumpArc[currentPlayer->counter] -
    currentPlayer->delta_e * 0x0080 *currentPlayer->counter;
  currentPlayer->counter++;
  return;
}

void DoMilesJumpWest(){
  currentPlayer->xOffset -= 0x200;
  currentPlayer->yOffset = jumpArc[currentPlayer->counter] -
    currentPlayer->delta_e * 0x0080 *currentPlayer->counter;
  currentPlayer->counter++;
  return;
}

void DoMilesJumpNorth(){
  currentPlayer->xOffset += 0x080;
  currentPlayer->yOffset = jumpArc[currentPlayer->counter]
    + (0x100 - currentPlayer->delta_e * 0x0080) * currentPlayer->counter;
  currentPlayer->counter++;
  return;
}

void DoMilesJumpSouth(){
  currentPlayer->xOffset -= 0x080;
  currentPlayer->yOffset = jumpArc[currentPlayer->counter]
    - (0x100 + currentPlayer->delta_e * 0x0080) * currentPlayer->counter;
  currentPlayer->counter++;
  return;
}

@ These routines do necessary cleanup after a jump.

@c
void MilesFinishJumpEast(){
  currentPlayer->xPosition++;
  currentPlayer->xOffset = 0;
  currentPlayer->yOffset = 0;
  currentPlayer->counter = 0;
  ActivateSquare(currentPlayer, currentPlayer->xPosition, currentPlayer->yPosition);
}

void MilesFinishJumpWest(){
  currentPlayer->xPosition--;
  currentPlayer->xOffset = 0;
  currentPlayer->yOffset = 0;
  currentPlayer->counter = 0;
  ActivateSquare(currentPlayer, currentPlayer->xPosition, currentPlayer->yPosition);
}

void MilesFinishJumpNorth(){
  currentPlayer->yPosition++;
  currentPlayer->xOffset = 0;
  currentPlayer->yOffset = 0;
  currentPlayer->counter = 0;
  ActivateSquare(currentPlayer, currentPlayer->xPosition, currentPlayer->yPosition);
}

void MilesFinishJumpSouth(){
  currentPlayer->yPosition--;
  currentPlayer->yOffset = 0;
  currentPlayer->xOffset = 0;
  currentPlayer->counter = 0;
  ActivateSquare(currentPlayer, currentPlayer->xPosition, currentPlayer->yPosition);
}

@ These routines handle Miles' behavior on a slippery square

@c
void SlideMilesSouth(){
  currentPlayer->xOffset -= 0x100;
  currentPlayer->yOffset = - 0x200 * currentPlayer->counter;
}

void SlideMilesNorth(){
  currentPlayer->xOffset += 0x100;
  currentPlayer->yOffset = 0x200 * currentPlayer->counter;
}
void SlideMilesEast(){
  currentPlayer->xOffset += 0x400;
}
void SlideMilesWest(){
  currentPlayer->xOffset -= 0x400;
}

@ This routine dete mines whether the player has requested a jump north, and if
so, whether it is legal.

@c
int CheckJumpNorth(){
    if(!ControllerUp()) return FALSE;
    if(currentPlayer->yPosition+1 >= currentPath->ySize) return FALSE;
    return TRUE;
}

@ This routine determines whether the player has requested a jump south, and if
so, whether it is legal.

@c
int CheckJumpSouth(){
    if(!ControllerDown()) return FALSE;
    if(currentPlayer->yPosition <= 0) return FALSE;
    return TRUE;
}

@ This routine determines whether the player has requested a jump east, and if
so, whether it is legal.

@c
int CheckJumpEast(){
    if(!ControllerRight()) return FALSE;
    if(currentPlayer->xPosition+1 >= currentPath->xSize) return FALSE;
    return TRUE;
}

@ This routine determines whether the player has requested a jump west, and if
so, whether it is legal.

@c
int CheckJumpWest(){
    if(!ControllerLeft()) return FALSE;
    if(currentPlayer->xPosition <= 0) return FALSE;
    return TRUE;
}

@ @<Function prototypes@>=
int CheckJumpWest(void);@/
int CheckJumpEast(void);@/
int CheckJumpSouth(void);@/
int CheckJumpNorth(void);@/

@ This routine determines whether the controller is in the `up' position.

@c
int ControllerUp(){
  return bStick1 & JOYUP;
}

@ This routine determines whether the controller is in the `down' position.

@c
int ControllerDown(){
  return bStick1 & JOYDOWN;
}

@ This routine determines whether the controller is in the `left' position.

@c
int ControllerLeft(){
  return bStick1 & JOYLEFT;
}

@ This routine determines whether the controller is in the `right' position.

@c
int ControllerRight(){
  return bStick1 & JOYRIGHT;
}

@ This routine determines whether Miles has been waiting long enough to yawn.

@d YawnTime 300

@c
int TimeToYawn(){
  return (currentPlayer->counter == YawnTime);
}

@ This routine determines whether Miles has landed after a jump.

@c
int MilesLanded(){
  return (currentPlayer->counter > 15);
}

@ this routine determines whether the square Miles landed in is missing.

@c
int MilesNewSquareMissing(){
  return !pathMap[currentPlayer->yPosition*mapWidth+currentPlayer->xPosition].type;
}

int MilesNewSquareSlippery(){
  return (pathMap[currentPlayer->yPosition*mapWidth+currentPlayer->xPosition].type == 2);
}

int MilesSlideDone(){
  return (++currentPlayer->counter > 7);
}

@ We've been talking a lot about |currentPlayer|, so I suppose I should define
it.

@<Global...@>=
CreaturePtr currentPlayer;
Creature player1;
Creature player2;

@ @<Initialize the game@>=
currentPlayer = &player1;
player1.fsmState = MilesStand;

@ And here is the type

@s Creature int
@s CreaturePtr int

@<Typedef...@>=
typedef struct {
  StatePtr fsmState;
  int xOffset;
  int yOffset;
  int counter;
  short xPosition;
  short yPosition;
  unsigned short *Frame;
  unsigned short chBase;
  short anim_time;
  struct ans *anim_next;
  short behavior;
  short type;
  short delta_e;
}Creature, *CreaturePtr;

