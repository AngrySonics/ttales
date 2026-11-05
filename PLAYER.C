#define MilesJumpYImpulse (16+14+12+10+8+6+4+2) \

#define YawnTime 300 \

/*5:*/
#line 144 "player.w"

void ClearCount(){
currentPlayer->counter= 0;
currentPlayer->yOffset= 0;
currentPlayer->xOffset= 0;
return;
}

/*:5*//*6:*/
#line 154 "player.w"

void BumpCount(){
currentPlayer->counter++;
return;
}

/*:6*//*7:*/
#line 162 "player.w"

void PrepareMilesJumpNorth(void){
ClearCount();
currentPlayer->delta_e= 
pathMap[mapWidth*currentPlayer->yPosition+currentPlayer->xPosition].elevation-
pathMap[mapWidth*(currentPlayer->yPosition+1)+currentPlayer->xPosition].elevation;
}

void PrepareMilesJumpSouth(void){
ClearCount();
currentPlayer->delta_e= 
pathMap[mapWidth*currentPlayer->yPosition+currentPlayer->xPosition].elevation-
pathMap[mapWidth*(currentPlayer->yPosition-1)+currentPlayer->xPosition].elevation;
}

void PrepareMilesJumpEast(void){
ClearCount();
currentPlayer->delta_e= 
pathMap[mapWidth*currentPlayer->yPosition+currentPlayer->xPosition].elevation-
pathMap[mapWidth*currentPlayer->yPosition+currentPlayer->xPosition+1].elevation;
}

void PrepareMilesJumpWest(void){
ClearCount();
currentPlayer->delta_e= 
pathMap[mapWidth*currentPlayer->yPosition+currentPlayer->xPosition].elevation-
pathMap[mapWidth*currentPlayer->yPosition+currentPlayer->xPosition-1].elevation;
}

/*:7*//*8:*/
#line 196 "player.w"


short jumpArc[]= {
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
currentPlayer->xOffset+= 0x200;
currentPlayer->yOffset= jumpArc[currentPlayer->counter]-
currentPlayer->delta_e*0x0080*currentPlayer->counter;
currentPlayer->counter++;
return;
}

void DoMilesJumpWest(){
currentPlayer->xOffset-= 0x200;
currentPlayer->yOffset= jumpArc[currentPlayer->counter]-
currentPlayer->delta_e*0x0080*currentPlayer->counter;
currentPlayer->counter++;
return;
}

void DoMilesJumpNorth(){
currentPlayer->xOffset+= 0x080;
currentPlayer->yOffset= jumpArc[currentPlayer->counter]
+(0x100-currentPlayer->delta_e*0x0080)*currentPlayer->counter;
currentPlayer->counter++;
return;
}

void DoMilesJumpSouth(){
currentPlayer->xOffset-= 0x080;
currentPlayer->yOffset= jumpArc[currentPlayer->counter]
-(0x100+currentPlayer->delta_e*0x0080)*currentPlayer->counter;
currentPlayer->counter++;
return;
}

/*:8*//*9:*/
#line 251 "player.w"

void MilesFinishJumpEast(){
currentPlayer->xPosition++;
currentPlayer->xOffset= 0;
currentPlayer->yOffset= 0;
currentPlayer->counter= 0;
ActivateSquare(currentPlayer,currentPlayer->xPosition,currentPlayer->yPosition);
}

void MilesFinishJumpWest(){
currentPlayer->xPosition--;
currentPlayer->xOffset= 0;
currentPlayer->yOffset= 0;
currentPlayer->counter= 0;
ActivateSquare(currentPlayer,currentPlayer->xPosition,currentPlayer->yPosition);
}

void MilesFinishJumpNorth(){
currentPlayer->yPosition++;
currentPlayer->xOffset= 0;
currentPlayer->yOffset= 0;
currentPlayer->counter= 0;
ActivateSquare(currentPlayer,currentPlayer->xPosition,currentPlayer->yPosition);
}

void MilesFinishJumpSouth(){
currentPlayer->yPosition--;
currentPlayer->yOffset= 0;
currentPlayer->xOffset= 0;
currentPlayer->counter= 0;
ActivateSquare(currentPlayer,currentPlayer->xPosition,currentPlayer->yPosition);
}

/*:9*//*10:*/
#line 286 "player.w"

void SlideMilesSouth(){
currentPlayer->xOffset-= 0x100;
currentPlayer->yOffset= -0x200*currentPlayer->counter;
}

void SlideMilesNorth(){
currentPlayer->xOffset+= 0x100;
currentPlayer->yOffset= 0x200*currentPlayer->counter;
}
void SlideMilesEast(){
currentPlayer->xOffset+= 0x400;
}
void SlideMilesWest(){
currentPlayer->xOffset-= 0x400;
}

/*:10*//*11:*/
#line 306 "player.w"

int CheckJumpNorth(){
if(!ControllerUp())return FALSE;
if(currentPlayer->yPosition+1>=currentPath->ySize)return FALSE;
return TRUE;
}

/*:11*//*12:*/
#line 316 "player.w"

int CheckJumpSouth(){
if(!ControllerDown())return FALSE;
if(currentPlayer->yPosition<=0)return FALSE;
return TRUE;
}

/*:12*//*13:*/
#line 326 "player.w"

int CheckJumpEast(){
if(!ControllerRight())return FALSE;
if(currentPlayer->xPosition+1>=currentPath->xSize)return FALSE;
return TRUE;
}

/*:13*//*14:*/
#line 336 "player.w"

int CheckJumpWest(){
if(!ControllerLeft())return FALSE;
if(currentPlayer->xPosition<=0)return FALSE;
return TRUE;
}

/*:14*//*16:*/
#line 351 "player.w"

int ControllerUp(){
return bStick1&JOYUP;
}

/*:16*//*17:*/
#line 358 "player.w"

int ControllerDown(){
return bStick1&JOYDOWN;
}

/*:17*//*18:*/
#line 365 "player.w"

int ControllerLeft(){
return bStick1&JOYLEFT;
}

/*:18*//*19:*/
#line 372 "player.w"

int ControllerRight(){
return bStick1&JOYRIGHT;
}

/*:19*//*20:*/
#line 381 "player.w"

int TimeToYawn(){
return(currentPlayer->counter==YawnTime);
}

/*:20*//*21:*/
#line 388 "player.w"

int MilesLanded(){
return(currentPlayer->counter>15);
}

/*:21*//*22:*/
#line 395 "player.w"

int MilesNewSquareMissing(){
return!pathMap[currentPlayer->yPosition*mapWidth+currentPlayer->xPosition].type;
}

int MilesNewSquareSlippery(){
return(pathMap[currentPlayer->yPosition*mapWidth+currentPlayer->xPosition].type==2);
}

int MilesSlideDone(){
return(++currentPlayer->counter>7);
}

/*:22*/
