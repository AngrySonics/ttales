#define offsetof(t,f)((size_t)&(((t*)0)->f))
#define TRUE 1
#define FALSE 0
#define NULL ((void*)0)
#define TIMING 1 \

#define HeapBase ((char*)0x00ff0000)
#define HeapLength 0xf000 \

#define VERSION 0xa10001
#define WATCHDOG 0xa14000 \

#define JOYUP 0x0001
#define JOYDOWN 0x0002
#define JOYLEFT 0x0004
#define JOYRIGHT 0x0008 \

#define VCTRLL VDPPort.control.l
#define VCTRLW VDPPort.control.w
#define VDATAW VDPPort.data.w \

#define InitDMA(src,dst,bytes) \
VCTRLL= 0x93009400+(((bytes)>>9)&0xff)+(((bytes)<<15)&0xff0000); \
VCTRLL= 0x95009600+(((src)<<15)&0xff0000)+(((src)>>9)&0xff); \
VCTRLW= 0x9700+(((src)>>17)&0x7f); \
VCTRLL= 0x40000080+(((dst)<<16)&0x3fff0000)+(((dst)>>14)&3); \

#define SetVDPDest(addr)VCTRLL= 0x40000000+(((addr)<<16)&0x3fff0000)+ \
(((addr)>>14)&3) \

#define FG 0xc000
#define SIDEBAR 0xd000
#define BG 0xe000
#define SPRITE_ATTRIBUTES 0xd000
#define HSCROLL 0xd400
#define SPRITE_ATTRIBUTE_VDP_ADDRESS SPRITE_ATTRIBUTES
#define H_SCROLL_VDP_ADDRESS HSCROLL
#define FG_CELLS 0 \

#line 1 "mmgr.w"

#define FSM_RERUN 0x0001 \

#define IOR_READ_CONTROLLERS 1
#define IOR_SEND_SPRITE_CONTROL 2
#define IOR_SEND_PALETTES 3
#define IOR_SEND_BLOCK_16 4
#define IOR_SEND_BLOCK_32 5
#define IOR_SEND_SCROLLS 6
#define IOR_SEND_A_SCROLLS 7
#define IOR_SEND_B_SCROLLS 8
#define IOR_SEND_COLUMN 9 \

#define IOReqSize 8
#define IOBufferCapacity 32
#define IOBufferSize (IOReqSize*IOBufferCapacity) \

#define ReadControllers(addr){ \
IORequestBuffer[IORequestPointer]= IOR_READ_CONTROLLERS; \
*((ULONG**)(IORequestBuffer+IORequestPointer+1))= (ULONG*)(addr); \
IORequestPointer= (IORequestPointer+IOReqSize)%IOBufferSize; \
} \

#define SendSpriteControl(addr){ \
IORequestBuffer[IORequestPointer]= IOR_SEND_SPRITE_CONTROL; \
*((ULONG**)(IORequestBuffer+IORequestPointer+1))= (ULONG*)(addr); \
IORequestPointer= (IORequestPointer+IOReqSize)%IOBufferSize; \
} \

#define SendPalettes(addr){ \
IORequestBuffer[IORequestPointer]= IOR_SEND_PALETTES; \
*((ULONG**)(IORequestBuffer+IORequestPointer+1))= (ULONG*)(addr); \
IORequestPointer= (IORequestPointer+IOReqSize)%IOBufferSize; \
} \

#define SendBlock16(addr,target,size){ \
IORequestBuffer[IORequestPointer]= IOR_SEND_BLOCK_16; \
IORequestBuffer[IORequestPointer+1]= ((short)((long)addr&0xffff)); \
IORequestBuffer[IORequestPointer+2]= (target); \
IORequestBuffer[IORequestPointer+3]= (size); \
IORequestPointer= (IORequestPointer+IOReqSize)%IOBufferSize; \
} \

#define SendBlock32(addr,target,size){ \
IORequestBuffer[IORequestPointer]= IOR_SEND_BLOCK_32; \
*((ULONG**)(IORequestBuffer+IORequestPointer+1))= (ULONG*)(addr); \
IORequestBuffer[IORequestPointer+3]= (target); \
IORequestBuffer[IORequestPointer+4]= (size); \
IORequestPointer= (IORequestPointer+IOReqSize)%IOBufferSize; \
} \

#define SendScrolls(ay,by,ax,bx){ \
IORequestBuffer[IORequestPointer]= IOR_SEND_SCROLLS; \
IORequestBuffer[IORequestPointer+1]= (ay); \
IORequestBuffer[IORequestPointer+2]= (by); \
IORequestBuffer[IORequestPointer+3]= (ax); \
IORequestBuffer[IORequestPointer+4]= (bx); \
IORequestPointer= (IORequestPointer+IOReqSize)%IOBufferSize; \
} \

#define SendAScrolls(ay,ax){ \
IORequestBuffer[IORequestPointer]= IOR_SEND_A_SCROLLS; \
IORequestBuffer[IORequestPointer+1]= (ay); \
IORequestBuffer[IORequestPointer+2]= (ax); \
IORequestPointer= (IORequestPointer+IOReqSize)%IOBufferSize; \
} \

#define SendBScrolls(by,bx){ \
IORequestBuffer[IORequestPointer]= IOR_SEND_B_SCROLLS; \
IORequestBuffer[IORequestPointer+1]= (by); \
IORequestBuffer[IORequestPointer+2]= (bx); \
IORequestPointer= (IORequestPointer+IOReqSize)%IOBufferSize; \
} \

#define SendColumn(addr,target){ \
IORequestBuffer[IORequestPointer]= IOR_SEND_COLUMN; \
*((ULONG**)(IORequestBuffer+IORequestPointer+1))= (ULONG*)(addr); \
IORequestBuffer[IORequestPointer+3]= (target); \
IORequestPointer= (IORequestPointer+IOReqSize)%IOBufferSize; \
}
#line 1 "startup.w"

#define VRAMWR 0x40000000
#define VRAMRD 0x00000000
#define VSRAMWR 0x40000010
#define VSRAMRD 0x00000010
#define CRAMWR 0xc0000000
#define CRAMRD 0x00000020 \
 \

#define LOGO1 (FG+0x61c+0x0000)
#define LOGO2 (FG+0x61c+0x0080)
#define LOGO3 (FG+0x61c+0x0100)
#define LOGO4 (FG+0x61c+0x0180) \

#define DATA_COMPRESSED 0 \

#define yMax (4*32-1)
#define SquareLoc(x,y)(rowOffsets[y]+x) \

#define MilesJumpYImpulse (16+14+12+10+8+6+4+2) \

#define YawnTime 300 \

/*3:*/
#line 20 "ttmain.w"
/*2:*/
#line 14 "ttmain.w"

#include "logo.h"

/*:2*/
#line 20 "ttmain.w"

/*9:*/
#line 96 "ttmain.w"


#pragma dsection .vdp

volatile struct{
union{
short w;
long l;
}data;
union{
short w;
long l;
}control;
unsigned char h_count;
unsigned char v_count;
}VDPPort= 0;

#pragma dsection .data

/*:9*/
#line 21 "ttmain.w"

/*14:*/
#line 26 "mmgr.w"

typedef struct memblock{
unsigned int size;
struct memblock*next;
struct memblock*prev;
}MemBlock,*MemBlockPtr;

/*:14*//*29:*/
#line 10 "ttworld.w"


typedef struct node_t{
struct art_t*artSet;
int puzzle;
struct path_t*paths[4];
}Node,*NodePtr;

typedef struct path_t{
struct art_t*artSet;
struct square_t*map;
NodePtr leftEnd;
NodePtr rightEnd;
short xSize;
short ySize;
short xStart;
short yStart;
}Path,*PathPtr;

/*:29*//*54:*/
#line 12 "fsm.w"

typedef int(*IntFuncPtr)(void);
typedef void(*VoidFuncPtr)(void);
typedef struct state_t{
IntFuncPtr test;
struct state_t*next;
VoidFuncPtr attribute;
short flags;
}State,*StatePtr;

/*:54*//*65:*/
#line 23 "io.w"

typedef unsigned long ULONG;
typedef unsigned char UCHAR;

/*:65*//*135:*/
#line 102 "path.w"

typedef struct square_t{
short type;
short elevation;
}Square,*SquarePtr;

/*:135*//*157:*/
#line 367 "path.w"

typedef struct{
unsigned short vp;
unsigned char size;
unsigned char link;
unsigned short cell;
unsigned short hp;
}SpriteDef,*SpriteDefPtr;

/*:157*//*173:*/
#line 555 "path.w"

typedef struct{
char j;
char i;
char z;
char n;
}CellTest,*CellTestPtr;

/*:173*//*199:*/
#line 425 "player.w"

typedef struct{
StatePtr fsmState;
int xOffset;
int yOffset;
int counter;
short xPosition;
short yPosition;
unsigned short*Frame;
unsigned short chBase;
short anim_time;
struct ans*anim_next;
short behavior;
short type;
short delta_e;
}Creature,*CreaturePtr;

#line 1 "squares.w"
/*:199*//*208:*/
#line 57 "squares.w"

typedef struct activs{
struct activs*next;
struct activs*prev;
short x;
short y;
short type;
short timer;
}ActiveSquare,*ActiveSquarePtr;
#line 1 "anim.w"

/*:208*//*209:*/
#line 5 "anim.w"

typedef struct ans{
unsigned short*frame;
char time;
char flags;
struct ans*next;
}AnimState,*AnimStatePtr;

/*:209*//*222:*/
#line 6 "art.w"

typedef struct art_t{
short*palette;
unsigned long*data;
}ArtSet,*ArtSetPtr;

/*:222*/
#line 22 "ttmain.w"

/*4:*/
#line 34 "ttmain.w"

void main(void);

/*:4*//*12:*/
#line 13 "mmgr.w"

void*AllocMem(unsigned int size);
void FreeMem(void*addr);
void InitHeap(char*addr,int size);

/*:12*//*57:*/
#line 58 "fsm.w"

StatePtr fsm(StatePtr s);
int True(void);
int False(void);
void Null(void);

/*:57*//*62:*/
#line 139 "fsm.w"


State InitialState[];
State IntroScreen[];
State PathPlay[];
State VictoryScreen[];
State DeathScreen[];
State NodePlay[];

int DoneWithIntro(void);
int Dead(void);
int Win(void);
int AtNode(void);
int DoneVictory(void);
int DoneDeath(void);
int AtPath(void);

void Initialize(void);
void InitGame(void);
void StartDeathSequence(void);
void StartVictorySequence(void);
void InitNode(void);
void RunPath(void);
void RunVictoryScreen(void);
void RunDeathScreen(void);
void InitPath(void);
void RunNode(void);

#line 1 "io.w"
/*:62*//*66:*/
#line 27 "io.w"

void DoIO(void);

/*:66*//*94:*/
#line 155 "startup.w"

void VBLHandler(void);
void HBLHandler(void);
void ErrorHandler(void);

/*:94*//*108:*/
#line 318 "startup.w"

void WaitTOF(void);
void SegaLogo(void);
void ReadHWControllers(void);

/*:108*//*118:*/
#line 115 "utils.w"

void InterpolateColor
(short target,short time,short duration,short*color);
void InterpolatePalette
(short target,short time,short duration,short*palette);
void InterpolateFullPalette
(short target,short time,short duration,short*palette);
void Interpolate2Palettes
(short*target,short time,short duration,short*palette);
void Interpolate2FullPalettes
(short*target,short time,short duration,short*palette);

void FadeIn(short*palette,short time);
void FadeOut(short*palette,short time);
#line 1 "expand.w"

/*:118*//*169:*/
#line 467 "path.w"

void BuildNewRow(short row,short column);
void BuildNewColumn(short column);

/*:169*//*178:*/
#line 96 "player.w"

State MilesStand[];
State MilesJumpEast[];
State MilesJumpWest[];
State MilesJumpNorth[];
State MilesJumpSouth[];
State MilesYawn[];
State MilesCheckLandingEast[];
State MilesCheckLandingWest[];
State MilesCheckLandingNorth[];
State MilesCheckLandingSouth[];
State MilesFall[];
State MilesSlideSouth[];
State MilesSlideNorth[];
State MilesSlideWest[];
State MilesSlideEast[];

void ClearCount(void);
void BumpCount(void);
void DoMilesJumpEast(void);
void DoMilesJumpWest(void);
void DoMilesJumpNorth(void);
void DoMilesJumpSouth(void);
void MilesFinishJumpEast(void);
void MilesFinishJumpWest(void);
void MilesFinishJumpNorth(void);
void MilesFinishJumpSouth(void);
void SlideMilesSouth(void);
void SlideMilesNorth(void);
void SlideMilesEast(void);
void SlideMilesWest(void);
void PrepareMilesJumpNorth(void);
void PrepareMilesJumpSouth(void);
void PrepareMilesJumpEast(void);
void PrepareMilesJumpWest(void);

int ControllerUp(void);
int ControllerDown(void);
int ControllerLeft(void);
int ControllerRight(void);
int TimeToYawn(void);
int MilesLanded(void);
int MilesNewSquareMissing(void);
int MilesNewSquareSlippery(void);
int MilesSlideDone(void);

/*:178*//*189:*/
#line 343 "player.w"

int CheckJumpWest(void);
int CheckJumpEast(void);
int CheckJumpSouth(void);
int CheckJumpNorth(void);

/*:189*//*201:*/
#line 5 "squares.w"

void UpdateSquares(void);
void ActivateSquare(CreaturePtr c,short x,short y);

/*:201*//*219:*/
#line 120 "anim.w"

void DrawCreatures(CreaturePtr c);
void AnimateCreature(CreaturePtr t);

/*:219*//*226:*/
#line 43 "art.w"

ArtSet round1PathArt;
short round1PathPalette[];
unsigned long round1CellData[];
#line 1 "display.w"
/*:226*//*230:*/
#line 51 "display.w"

void DisplayShort(short n,int x,int y);
void DisplayLong(long n,int x,int y);
#line 66 "c:\ttales\ttales.w"

/*:230*/
#line 23 "ttmain.w"

/*5:*/
#line 37 "ttmain.w"

/*220:*/
#line 124 "anim.w"

#include "miles.h"

#line 1 "art.w"
/*:220*//*225:*/
#line 39 "art.w"

#include "l1path.h"
#include "digits.h"

/*:225*/
#line 38 "ttmain.w"

long Player1_score;
long Player2_score;
unsigned short seed;
StatePtr mainState;
int playerDead;
int currentRound;
extern char sampbank[];
extern char seqbank[];
extern char envbank[];
extern char patchbank[];

/*:5*//*13:*/
#line 18 "mmgr.w"

MemBlockPtr freeList;

/*:13*//*30:*/
#line 32 "ttworld.w"

/*31:*/
#line 36 "ttworld.w"

/*32:*/
#line 43 "ttworld.w"

Node n1_1,n1_2,n1_3,n1_4,n1_5,n1_6,n1_7,n1_8;
Path p1_1,p1_2,p1_3,p1_4,p1_5,p1_6,p1_7;
Path p1_8,p1_9,p1_10,p1_11,p1_12;

/*:32*/
#line 37 "ttworld.w"

/*33:*/
#line 48 "ttworld.w"

Node n2_1,n2_2,n2_3,n2_4,n2_5,n2_6,n2_7,n2_8,n2_9,n2_10,n2_11;
Path p2_1,p2_2,p2_3,p2_4,p2_5,p2_6,p2_7,p2_8,p2_9,p2_10;
Path p2_11,p2_12,p2_13,p2_14,p2_15,p2_16,p2_17;

/*:33*/
#line 38 "ttworld.w"

/*34:*/
#line 53 "ttworld.w"

Node n3_1,n3_2,n3_3,n3_4,n3_5,n3_6,n3_7,n3_8,n3_9,n3_10,n3_11;
Path p3_1,p3_2,p3_3,p3_4,p3_5,p3_6,p3_7;
Path p3_8,p3_9,p3_10,p3_11,p3_12,p3_13;

/*:34*/
#line 39 "ttworld.w"

/*35:*/
#line 58 "ttworld.w"

Node n4_1,n4_2,n4_3,n4_4,n4_5,n4_6,n4_7,n4_8;
Node n4_9,n4_10,n4_11,n4_12,n4_13,n4_14,n4_15;
Path p4_1,p4_2,p4_3,p4_4,p4_5,p4_6,p4_7,p4_8,p4_9,p4_10;
Path p4_11,p4_12,p4_13,p4_14,p4_15,p4_16,p4_17;

/*:35*/
#line 40 "ttworld.w"

/*36:*/
#line 64 "ttworld.w"

Node n5_1,n5_2,n5_3,n5_4,n5_5,n5_6,n5_7,n5_8;
Node n5_9,n5_10,n5_11,n5_12,n5_13,n5_14,n5_15;
Path p5_1,p5_2,p5_3,p5_4,p5_5,p5_6,p5_7,p5_8,p5_9,p5_10;
Path p5_11,p5_12,p5_13,p5_14,p5_15,p5_16,p5_17,p5_18,p5_19,p5_20;
Path NormalExit;
Path SpecialExit;

/*:36*/
#line 41 "ttworld.w"


/*:31*/
#line 33 "ttworld.w"

/*37:*/
#line 72 "ttworld.w"

/*38:*/
#line 79 "ttworld.w"

/*39:*/
#line 83 "ttworld.w"

Path p1_1= {&round1PathArt,&round1Path1Map,NULL,&n1_1,20,20,3,0};
Path p1_2= {&round1PathArt,NULL,&n1_1,&n1_2,0,0,0,0};
Path p1_3= {&round1PathArt,NULL,&n1_2,&n1_3,0,0,0,0};
Path p1_4= {&round1PathArt,NULL,&n1_3,&n1_4,0,0,0,0};
Path p1_5= {&round1PathArt,NULL,&n1_4,&n1_5,0,0,0,0};
Path p1_6= {&round1PathArt,NULL,&n1_4,&n1_6,0,0,0,0};
Path p1_7= {&round1PathArt,NULL,&n1_5,&n1_6,0,0,0,0};
Path p1_8= {&round1PathArt,NULL,&n1_5,&n1_6,0,0,0,0};
Path p1_9= {&round1PathArt,NULL,&n1_5,&n1_7,0,0,0,0};
Path p1_10= {&round1PathArt,NULL,&n1_6,&n1_7,0,0,0,0};
Path p1_11= {&round1PathArt,NULL,&n1_3,&n1_8,0,0,0,0};
Path p1_12= {&round1PathArt,NULL,&n1_8,&n1_4,0,0,0,0};

/*:39*/
#line 80 "ttworld.w"

/*40:*/
#line 97 "ttworld.w"

Node n1_1= {NULL,0,NULL,&p1_2,NULL,NULL};
Node n1_2= {NULL,0,&p1_2,&p1_3,NULL,NULL};
Node n1_3= {NULL,0,&p1_3,&p1_4,&p1_11,NULL};
Node n1_4= {NULL,0,&p1_4,&p1_5,&p1_6,&p1_12};
Node n1_5= {NULL,0,&p1_5,&p1_7,&p1_8,&p1_9};
Node n1_6= {NULL,0,&p1_6,&p1_7,&p1_8,&p1_10};
Node n1_7= {NULL,0,&p1_9,&p1_10,&p2_1,NULL};
Node n1_8= {NULL,0,&p1_11,&p1_12,NULL,NULL};

/*:40*/
#line 81 "ttworld.w"


/*:38*/
#line 73 "ttworld.w"

/*41:*/
#line 107 "ttworld.w"

/*42:*/
#line 111 "ttworld.w"

Path p2_1= {NULL,NULL,&n1_7,&n2_1,0,0,0,0};
Path p2_2= {NULL,NULL,&n2_1,&n2_2,0,0,0,0};
Path p2_3= {NULL,NULL,&n2_2,&n2_3,0,0,0,0};
Path p2_4= {NULL,NULL,&n2_2,&n2_4,0,0,0,0};
Path p2_5= {NULL,NULL,&n2_3,&n2_3,0,0,0,0};
Path p2_6= {NULL,NULL,&n2_3,&n2_5,0,0,0,0};
Path p2_7= {NULL,NULL,&n2_4,&n2_5,0,0,0,0};
Path p2_8= {NULL,NULL,&n2_5,&n2_6,0,0,0,0};
Path p2_9= {NULL,NULL,&n2_5,&n2_7,0,0,0,0};
Path p2_10= {NULL,NULL,&n2_6,&n2_7,0,0,0,0};
Path p2_11= {NULL,NULL,&n2_6,&n2_8,0,0,0,0};
Path p2_12= {NULL,NULL,&n2_7,&n2_9,0,0,0,0};
Path p2_13= {NULL,NULL,&n2_8,&n2_10,0,0,0,0};
Path p2_14= {NULL,NULL,&n2_9,&n2_10,0,0,0,0};
Path p2_15= {NULL,NULL,&n2_4,&n2_7,0,0,0,0};
Path p2_16= {NULL,NULL,&n2_6,&n2_11,0,0,0,0};
Path p2_17= {NULL,NULL,&n2_11,&n2_10,0,0,0,0};

/*:42*/
#line 108 "ttworld.w"

/*43:*/
#line 130 "ttworld.w"

Node n2_1= {NULL,0,&p2_1,&p2_2,NULL,NULL};
Node n2_2= {NULL,0,&p2_2,&p2_3,&p2_4,NULL};
Node n2_3= {NULL,0,&p2_3,&p2_5,&p2_6,NULL};
Node n2_4= {NULL,0,&p2_3,&p2_5,&p2_7,&p2_15};
Node n2_5= {NULL,0,&p2_6,&p2_7,&p2_8,&p2_9};
Node n2_6= {NULL,0,&p2_8,&p2_10,&p2_11,&p2_16};
Node n2_7= {NULL,0,&p2_15,&p2_9,&p2_10,&p2_12};
Node n2_8= {NULL,0,&p2_11,&p2_13,NULL,NULL};
Node n2_9= {NULL,0,&p2_12,&p2_14,NULL,NULL};
Node n2_10= {NULL,0,&p2_14,&p2_13,&p2_17,&p3_1};
Node n2_11= {NULL,0,&p2_16,&p2_17,NULL,NULL};

/*:43*/
#line 109 "ttworld.w"


/*:41*/
#line 74 "ttworld.w"

/*44:*/
#line 143 "ttworld.w"

/*45:*/
#line 147 "ttworld.w"

Path p3_1= {NULL,NULL,&n2_10,&n3_1,0,0,0,0};
Path p3_2= {NULL,NULL,&n3_1,&n3_2,0,0,0,0};
Path p3_3= {NULL,NULL,&n3_2,&n3_3,0,0,0,0};
Path p3_4= {NULL,NULL,&n3_3,&n3_5,0,0,0,0};
Path p3_5= {NULL,NULL,&n3_3,&n3_4,0,0,0,0};
Path p3_6= {NULL,NULL,&n3_5,&n3_6,0,0,0,0};
Path p3_7= {NULL,NULL,&n3_6,&n3_7,0,0,0,0};
Path p3_8= {NULL,NULL,&n3_4,&n3_7,0,0,0,0};
Path p3_9= {NULL,NULL,&n3_5,&n3_8,0,0,0,0};
Path p3_10= {NULL,NULL,&n3_7,&n3_8,0,0,0,0};
Path p3_11= {NULL,NULL,&n3_6,&n3_9,0,0,0,0};
Path p3_12= {NULL,NULL,&n3_9,&n3_10,0,0,0,0};
Path p3_13= {NULL,NULL,&n3_10,&n3_11,0,0,0,0};

/*:45*/
#line 144 "ttworld.w"

/*46:*/
#line 162 "ttworld.w"

Node n3_1= {NULL,0,&p3_1,&p3_2,NULL,NULL};
Node n3_2= {NULL,0,&p3_2,&p3_3,NULL,NULL};
Node n3_3= {NULL,0,&p3_3,&p3_4,&p3_5,NULL};
Node n3_4= {NULL,0,&p3_5,&p3_8,NULL,NULL};
Node n3_5= {NULL,0,&p3_4,&p3_6,&p3_9,NULL};
Node n3_6= {NULL,0,&p3_6,&p3_7,&p3_11,NULL};
Node n3_7= {NULL,0,&p3_8,&p3_7,&p3_10,NULL};
Node n3_8= {NULL,0,&p3_9,&p3_10,&p4_1,NULL};
Node n3_9= {NULL,0,&p3_11,&p3_12,NULL,NULL};
Node n3_10= {NULL,0,&p3_12,&p3_13,NULL,NULL};
Node n3_11= {NULL,0,&p3_13,&p4_13,NULL,NULL};

/*:46*/
#line 145 "ttworld.w"


/*:44*/
#line 75 "ttworld.w"

/*47:*/
#line 175 "ttworld.w"

/*48:*/
#line 179 "ttworld.w"

Path p4_1= {NULL,NULL,&n3_8,&n4_1,0,0,0,0};
Path p4_2= {NULL,NULL,&n4_1,&n4_3,0,0,0,0};
Path p4_3= {NULL,NULL,&n4_2,&n4_5,0,0,0,0};
Path p4_4= {NULL,NULL,&n4_3,&n4_6,0,0,0,0};
Path p4_5= {NULL,NULL,&n4_5,&n4_7,0,0,0,0};
Path p4_6= {NULL,NULL,&n4_6,&n4_7,0,0,0,0};
Path p4_7= {NULL,NULL,&n4_6,&n4_8,0,0,0,0};
Path p4_8= {NULL,NULL,&n4_8,&n4_9,0,0,0,0};
Path p4_9= {NULL,NULL,&n4_8,&n4_10,0,0,0,0};
Path p4_10= {NULL,NULL,&n4_9,&n4_12,0,0,0,0};
Path p4_11= {NULL,NULL,&n4_10,&n4_11,0,0,0,0};
Path p4_12= {NULL,NULL,&n4_11,&n4_12,0,0,0,0};
Path p4_13= {NULL,NULL,&n3_11,&n4_2,0,0,0,0};
Path p4_14= {NULL,NULL,&n4_2,&n4_13,0,0,0,0};
Path p4_15= {NULL,NULL,&n4_13,&n4_14,0,0,0,0};
Path p4_16= {NULL,NULL,&n4_14,&n4_15,0,0,0,0};
Path p4_17= {NULL,NULL,&n4_15,&n4_12,0,0,0,0};

/*:48*/
#line 176 "ttworld.w"

/*49:*/
#line 198 "ttworld.w"

Node n4_1= {NULL,0,&p4_1,&p4_2,NULL,NULL};
Node n4_2= {NULL,0,&p4_13,&p4_14,&p4_3,NULL};
Node n4_3= {NULL,0,&p4_2,&p4_4,NULL,NULL};
Node n4_4= {NULL,0,NULL,NULL,NULL,NULL};
Node n4_5= {NULL,0,&p4_3,&p4_5,NULL,NULL};
Node n4_6= {NULL,0,&p4_4,&p4_6,&p4_7,NULL};
Node n4_7= {NULL,0,&p4_5,&p4_6,NULL,NULL};
Node n4_8= {NULL,0,&p4_7,&p4_8,&p4_9,NULL};
Node n4_9= {NULL,0,&p4_8,&p4_10,NULL,NULL};
Node n4_10= {NULL,0,&p4_9,&p4_11,NULL,NULL};
Node n4_11= {NULL,0,&p4_11,&p4_12,NULL,NULL};
Node n4_12= {NULL,0,&p4_10,&p4_12,&p5_1,&p4_17};
Node n4_13= {NULL,0,&p4_14,&p4_15,NULL,NULL};
Node n4_14= {NULL,0,&p4_15,&p4_16,NULL,NULL};
Node n4_15= {NULL,0,&p4_16,&p4_17,NULL,NULL};

/*:49*/
#line 177 "ttworld.w"


/*:47*/
#line 76 "ttworld.w"

/*50:*/
#line 215 "ttworld.w"

/*51:*/
#line 219 "ttworld.w"

Path p5_1= {NULL,NULL,&n4_12,&n5_1,0,0,0,0};
Path p5_2= {NULL,NULL,&n5_1,&n5_2,0,0,0,0};
Path p5_3= {NULL,NULL,&n5_1,&n5_3,0,0,0,0};
Path p5_4= {NULL,NULL,&n5_3,&n5_7,0,0,0,0};
Path p5_5= {NULL,NULL,&n5_2,&n5_4,0,0,0,0};
Path p5_6= {NULL,NULL,&n5_2,&n5_5,0,0,0,0};
Path p5_7= {NULL,NULL,&n5_2,&n5_6,0,0,0,0};
Path p5_8= {NULL,NULL,&n5_5,&n5_6,0,0,0,0};
Path p5_9= {NULL,NULL,&n5_6,&n5_7,0,0,0,0};
Path p5_10= {NULL,NULL,&n5_4,&n5_8,0,0,0,0};
Path p5_11= {NULL,NULL,&n5_6,&n5_9,0,0,0,0};
Path p5_12= {NULL,NULL,&n5_7,&n5_11,0,0,0,0};
Path p5_13= {NULL,NULL,&n5_8,&n5_11,0,0,0,0};
Path p5_14= {NULL,NULL,&n5_9,&n5_10,0,0,0,0};
Path p5_15= {NULL,NULL,&n5_10,&n5_12,0,0,0,0};
Path p5_16= {NULL,NULL,&n5_11,&n5_12,0,0,0,0};
Path p5_17= {NULL,NULL,&n5_7,&n5_13,0,0,0,0};
Path p5_18= {NULL,NULL,&n5_13,&n5_12,0,0,0,0};
Path p5_19= {NULL,NULL,&n5_8,&n5_14,0,0,0,0};
Path p5_20= {NULL,NULL,&n5_14,&n5_15,0,0,0,0};

Path NormalExit= {NULL,NULL,NULL,NULL,0,0,0,0};
Path SpecialExit= {NULL,NULL,NULL,NULL,0,0,0,0};

/*:51*/
#line 216 "ttworld.w"

/*52:*/
#line 244 "ttworld.w"

Node n5_1= {NULL,0,&p5_1,&p5_2,&p5_3,NULL};
Node n5_2= {NULL,0,&p5_2,&p5_7,&p5_6,&p5_5};
Node n5_3= {NULL,0,&p5_1,&p5_3,NULL,NULL};
Node n5_4= {NULL,0,&p5_5,&p5_10,NULL,NULL};
Node n5_5= {NULL,0,&p5_6,&p5_8,NULL,NULL};
Node n5_6= {NULL,0,&p5_7,&p5_8,&p5_9,&p5_11};
Node n5_7= {NULL,0,&p5_4,&p5_9,&p5_12,&p5_17};
Node n5_8= {NULL,0,&p5_10,&p5_13,&p5_19,NULL};
Node n5_9= {NULL,0,&p5_11,&p5_14,NULL,NULL};
Node n5_10= {NULL,0,&p5_14,&p5_15,NULL,NULL};
Node n5_11= {NULL,0,&p5_12,&p5_13,&p5_16,NULL};
Node n5_12= {NULL,0,&p5_15,&p5_16,&p5_18,&NormalExit};
Node n5_13= {NULL,0,&p5_17,&p5_18,NULL,NULL};
Node n5_14= {NULL,0,&p5_19,&p5_20,NULL,NULL};
Node n5_15= {NULL,0,&p5_20,&SpecialExit,NULL,NULL};

#line 1 "fsm.w"

/*:52*/
#line 217 "ttworld.w"


/*:50*/
#line 77 "ttworld.w"


/*:37*/
#line 34 "ttworld.w"


/*:30*//*67:*/
#line 30 "io.w"

short IORequestBuffer[IOBufferSize];
short IORequestPointer;
int ip;
unsigned char bStick1;
unsigned char cStick1;
unsigned char dStick1;
unsigned char bStick2;
unsigned char cStick2;
unsigned char dStick2;

/*:67*//*93:*/
#line 151 "startup.w"

volatile long tickCounter;
volatile int vblFlag;

/*:93*//*97:*/
#line 180 "startup.w"

short vdpRegisters[]= {
0x8004,
0x8174,
0x8200+(FG>>10),
0x8300+(SIDEBAR>>10),
0x8400+(BG>>13),
0x8500+(SPRITE_ATTRIBUTES>>9),
0x8600,
0x8700,
0x8800,
0x8900,
0x8a00,
0x8b08,
0x8c81,
0x8d00+(HSCROLL>>10),
0x8e00,
0x8f02,
0x9001,
0x9100,
0x9200,
};


/*:97*//*134:*/
#line 93 "path.w"

PathPtr currentPath;
SquarePtr pathMap;
int mapWidth;
short rowOffsets[64];

/*:134*//*156:*/
#line 354 "path.w"

SpriteDef spriteAttributes[80];
short sprite;
short screenScrollX;
short screenScrollY;
short playerX;
short playerY;

/*:156*//*163:*/
#line 410 "path.w"

short lineUpdateBufferA[64];
short colUpdateBufferA[32];
short lineUpdateBufferB[64];
short colUpdateBufferB[32];

/*:163*//*174:*/
#line 566 "path.w"

CellTest screenTranslate[4][8][400]= {
{
{
{0,-3,5,3+0*5+1},
{0,-3,6,3+1*5+1},
{0,-3,7,3+2*5+1},
{0,-3,8,3+3*5+1},
{0,-3,9,3+4*5+1},
{0,-3,20,3+5*5+1},
{0,-3,21,3+6*5+1},
{0,-3,12,3+7*5+1},
{0,-3,13,3+8*5+1},
{0,-3,14,3+9*5+1},
{0,-3,15,3+10*5+1},
{0,-3,16,3+11*5+1},
{0,-3,17,3+12*5+1},
{0,-3,18,3+13*5+1},
{0,-3,19,3+14*5+1},
{0,-3,20,3+15*5+1},

{0,-2,3,2+0*5+1},
{0,-2,4,2+1*5+1},
{0,-2,5,2+2*5+1},
{0,-2,6,2+3*5+1},
{0,-2,7,2+4*5+1},
{0,-2,8,2+5*5+1},
{0,-2,9,2+6*5+1},
{0,-2,10,2+7*5+1},
{0,-2,11,2+8*5+1},
{0,-2,12,2+9*5+1},
{0,-2,13,2+10*5+1},
{0,-2,14,2+11*5+1},
{0,-2,15,2+12*5+1},
{0,-2,16,2+13*5+1},
{0,-2,17,2+14*5+1},
{0,-2,18,2+15*5+1},
{0,-2,19,2+16*5+1},
{0,-2,20,2+17*5+1},

{0,-1,1,1+0*5+1},
{0,-1,2,1+1*5+1},
{0,-1,3,1+2*5+1},
{0,-1,4,1+3*5+1},
{0,-1,5,1+4*5+1},
{0,-1,6,1+5*5+1},
{0,-1,7,1+6*5+1},
{0,-1,8,1+7*5+1},
{0,-1,9,1+8*5+1},
{0,-1,10,1+9*5+1},
{0,-1,11,1+10*5+1},
{0,-1,12,1+11*5+1},
{0,-1,13,1+12*5+1},
{0,-1,14,1+13*5+1},
{0,-1,15,1+14*5+1},
{0,-1,16,1+15*5+1},
{0,-1,17,1+16*5+1},
{0,-1,18,1+17*5+1},
{0,-1,19,1+18*5+1},
{0,-1,20,1+19*5+1},

{0,0,0,0+1*5+1},
{0,0,1,0+2*5+1},
{0,0,2,0+3*5+1},
{0,0,3,0+4*5+1},
{0,0,4,0+5*5+1},
{0,0,5,0+6*5+1},
{0,0,6,0+7*5+1},
{0,0,7,0+8*5+1},
{0,0,8,0+9*5+1},
{0,0,9,0+10*5+1},
{0,0,10,0+11*5+1},
{0,0,11,0+12*5+1},
{0,0,12,0+13*5+1},
{0,0,13,0+14*5+1},
{0,0,14,0+15*5+1},
{0,0,15,0+16*5+1},
{0,0,16,0+17*5+1},
{0,0,17,0+18*5+1},
{0,0,18,0+19*5+1},
{0,0,19,0+20*5+1},
{0,0,20,0+21*5+1},

{0,1,0,0+3*5+1},
{0,1,1,0+4*5+1},
{0,1,2,0+5*5+1},
{0,1,3,0+6*5+1},
{0,1,4,0+7*5+1},
{0,1,5,0+8*5+1},
{0,1,6,0+9*5+1},
{0,1,7,0+10*5+1},
{0,1,8,0+11*5+1},
{0,1,9,0+12*5+1},
{0,1,10,0+13*5+1},
{0,1,11,0+14*5+1},
{0,1,12,0+15*5+1},
{0,1,13,0+16*5+1},
{0,1,14,0+17*5+1},
{0,1,15,0+18*5+1},
{0,1,16,0+19*5+1},
{0,1,17,0+20*5+1},

},
{
{0,-3,5,3+0*5+1},
{0,-3,6,3+1*5+1},
{0,-3,7,3+2*5+1},
{0,-3,8,3+3*5+1},
{0,-3,9,3+4*5+1},
{0,-3,20,3+5*5+1},
{0,-3,21,3+6*5+1},
{0,-3,12,3+7*5+1},
{0,-3,13,3+8*5+1},
{0,-3,14,3+9*5+1},
{0,-3,15,3+10*5+1},
{0,-3,16,3+11*5+1},
{0,-3,17,3+12*5+1},
{0,-3,18,3+13*5+1},
{0,-3,19,3+14*5+1},
{0,-3,20,3+15*5+1},

{0,-2,3,2+0*5+1},
{0,-2,4,2+1*5+1},
{0,-2,5,2+2*5+1},
{0,-2,6,2+3*5+1},
{0,-2,7,2+4*5+1},
{0,-2,8,2+5*5+1},
{0,-2,9,2+6*5+1},
{0,-2,10,2+7*5+1},
{0,-2,11,2+8*5+1},
{0,-2,12,2+9*5+1},
{0,-2,13,2+10*5+1},
{0,-2,14,2+11*5+1},
{0,-2,15,2+12*5+1},
{0,-2,16,2+13*5+1},
{0,-2,17,2+14*5+1},
{0,-2,18,2+15*5+1},
{0,-2,19,2+16*5+1},
{0,-2,20,2+17*5+1},

{0,-1,2,1+0*5+1},
{0,-1,3,1+1*5+1},
{0,-1,4,1+2*5+1},
{0,-1,5,1+3*5+1},
{0,-1,6,1+4*5+1},
{0,-1,7,1+5*5+1},
{0,-1,8,1+6*5+1},
{0,-1,9,1+7*5+1},
{0,-1,10,1+8*5+1},
{0,-1,11,1+9*5+1},
{0,-1,12,1+10*5+1},
{0,-1,13,1+11*5+1},
{0,-1,14,1+12*5+1},
{0,-1,15,1+13*5+1},
{0,-1,16,1+14*5+1},
{0,-1,17,1+15*5+1},
{0,-1,18,1+16*5+1},
{0,-1,19,1+17*5+1},
{0,-1,20,1+18*5+1},

{0,0,0,0+0*5+1},
{0,0,1,0+1*5+1},
{0,0,2,0+2*5+1},
{0,0,3,0+3*5+1},
{0,0,4,0+4*5+1},
{0,0,5,0+5*5+1},
{0,0,6,0+6*5+1},
{0,0,7,0+7*5+1},
{0,0,8,0+8*5+1},
{0,0,9,0+9*5+1},
{0,0,10,0+10*5+1},
{0,0,11,0+11*5+1},
{0,0,12,0+12*5+1},
{0,0,13,0+13*5+1},
{0,0,14,0+14*5+1},
{0,0,15,0+15*5+1},
{0,0,16,0+16*5+1},
{0,0,17,0+17*5+1},
{0,0,18,0+18*5+1},
{0,0,19,0+19*5+1},
{0,0,20,0+20*5+1},

{0,1,0,0+2*5+1},
{0,1,1,0+3*5+1},
{0,1,2,0+4*5+1},
{0,1,3,0+5*5+1},
{0,1,4,0+6*5+1},
{0,1,5,0+7*5+1},
{0,1,6,0+8*5+1},
{0,1,7,0+9*5+1},
{0,1,8,0+10*5+1},
{0,1,9,0+11*5+1},
{0,1,10,0+12*5+1},
{0,1,11,0+13*5+1},
{0,1,12,0+14*5+1},
{0,1,13,0+15*5+1},
{0,1,14,0+16*5+1},
{0,1,15,0+17*5+1},
{0,1,16,0+18*5+1},
{0,1,17,0+19*5+1},

},
},
};
#line 1 "player.w"
/*:174*//*177:*/
#line 14 "player.w"

State MilesStand[]= {
{CheckJumpNorth,MilesJumpNorth,PrepareMilesJumpNorth,0},
{CheckJumpSouth,MilesJumpSouth,PrepareMilesJumpSouth,0},
{CheckJumpWest,MilesJumpWest,PrepareMilesJumpWest,0},
{CheckJumpEast,MilesJumpEast,PrepareMilesJumpEast,0},
{TimeToYawn,MilesYawn,BumpCount,0},
{True,MilesStand,BumpCount,0}
};

State MilesJumpEast[]= {
{MilesLanded,MilesCheckLandingEast,MilesFinishJumpEast,FSM_RERUN},
{True,MilesJumpEast,DoMilesJumpEast,0}
};

State MilesJumpWest[]= {
{MilesLanded,MilesCheckLandingWest,MilesFinishJumpWest,FSM_RERUN},
{True,MilesJumpWest,DoMilesJumpWest,0}
};

State MilesJumpNorth[]= {
{MilesLanded,MilesCheckLandingNorth,MilesFinishJumpNorth,FSM_RERUN},
{True,MilesJumpNorth,DoMilesJumpNorth,0}
};

State MilesJumpSouth[]= {
{MilesLanded,MilesCheckLandingSouth,MilesFinishJumpSouth,FSM_RERUN},
{True,MilesJumpSouth,DoMilesJumpSouth,0}
};

State MilesYawn[]= {
{True,MilesStand,BumpCount,0}
};

State MilesCheckLandingEast[]= {
{MilesNewSquareMissing,MilesFall,Null,0},
{MilesNewSquareSlippery,MilesSlideEast,Null,0},
{True,MilesStand,Null,0}
};

State MilesCheckLandingWest[]= {
{MilesNewSquareMissing,MilesFall,Null,0},
{MilesNewSquareSlippery,MilesSlideWest,Null,0},
{True,MilesStand,Null,0}
};

State MilesCheckLandingNorth[]= {
{MilesNewSquareMissing,MilesFall,Null,0},
{MilesNewSquareSlippery,MilesSlideNorth,Null,0},
{True,MilesStand,Null,0}
};

State MilesCheckLandingSouth[]= {
{MilesNewSquareMissing,MilesFall,Null,0},
{MilesNewSquareSlippery,MilesSlideSouth,Null,0},
{True,MilesStand,Null,0}
};

State MilesFall[]= {
{True,MilesStand,Null,0}
};

State MilesSlideWest[]= {
{MilesSlideDone,MilesCheckLandingWest,MilesFinishJumpWest,1},
{True,MilesSlideWest,SlideMilesWest,0}
};

State MilesSlideEast[]= {
{MilesSlideDone,MilesCheckLandingEast,MilesFinishJumpEast,1},
{True,MilesSlideEast,SlideMilesEast,0}
};

State MilesSlideNorth[]= {
{MilesSlideDone,MilesCheckLandingNorth,MilesFinishJumpNorth,1},
{True,MilesSlideNorth,SlideMilesNorth,0}
};

State MilesSlideSouth[]= {
{MilesSlideDone,MilesCheckLandingSouth,MilesFinishJumpSouth,1},
{True,MilesSlideSouth,SlideMilesSouth,0}
};

/*:177*//*197:*/
#line 411 "player.w"

CreaturePtr currentPlayer;
Creature player1;
Creature player2;

/*:197*//*207:*/
#line 49 "squares.w"

ActiveSquarePtr activeSquareList;

/*:207*//*210:*/
#line 15 "anim.w"

AnimState MilesStandEast[]= {
{milesshape,10,0,&MilesStandEast[0]},
{wierdmilesshape,2,0,&MilesStandEast[0]}
};

unsigned long*CompressedDataPointers[]= {
NULL
};

int CreatureShapeLength[]= {
0
};

/*:210*//*223:*/
#line 14 "art.w"

ArtSet round1PathArt= {
round1PathPalette,
round1CellData
};

/*:223*//*224:*/
#line 22 "art.w"

short round1PathPalette[]= {
0x000,0x488,0x4c4,0x800,0xa44,0x000,0x000,0x000,
0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,

0x000,0x000,0x444,0x888,0xaaa,0xeee,0x008,0x00e,
0x46a,0x08e,0x0ae,0xfff,0xfff,0xfff,0xfff,0x220,

0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,

0x000,0xeee,0x000,0x000,0x000,0x000,0x000,0x000,
0x000,0x000,0x000,0x000,0x000,0x000,0x000,0x000,
};

/*:224*/
#line 24 "ttmain.w"


void main(){
/*103:*/
#line 245 "startup.w"

asm(" move.w #$2700,SR",4);
if(*(unsigned char*)VERSION&0x0f)
*((unsigned long*)WATCHDOG)= 0x53454741;
/*104:*/
#line 255 "startup.w"

asm(" moveq #$40,d0");
asm(" move.b d0,$a10009");
asm(" move.b d0,$a1000b");
asm(" move.b #$9f,$a1000d");
asm(" move.b #$7f,$a10007");

/*:104*/
#line 249 "startup.w"

/*99:*/
#line 210 "startup.w"

{
register int i;
for(i= 0;i<16384;i++){
((long*)0x00ff0000)[i]= 0;
}
}

/*:99*/
#line 250 "startup.w"

/*98:*/
#line 204 "startup.w"

/*96:*/
#line 169 "startup.w"

{
int i;

for(i= 0;i<19;i++){
VDPPort.control.w= vdpRegisters[i];
}
}

/*:96*/
#line 205 "startup.w"

/*100:*/
#line 218 "startup.w"

{
register int i;
VDPPort.control.l= VRAMWR;
for(i= 0;i<32768;i++){
VDPPort.data.w= 0;
}
}

/*:100*/
#line 206 "startup.w"

/*101:*/
#line 227 "startup.w"

{
register int i;
VDPPort.control.l= CRAMWR;
for(i= 0;i<64;i++){
VDPPort.data.w= 0;
}
}

/*:101*/
#line 207 "startup.w"

/*102:*/
#line 236 "startup.w"

{
register int i;
VDPPort.control.l= VSRAMWR;
for(i= 0;i<40;i++){
VDPPort.data.w= 0;
}
}

/*:102*/
#line 208 "startup.w"


/*:98*/
#line 251 "startup.w"

gemsinit(patchbank,envbank,seqbank,sampbank);
asm(" move.w #$2000,SR");

/*:103*/
#line 27 "ttmain.w"

SegaLogo();
/*6:*/
#line 56 "ttmain.w"

mainState= InitialState;
InitHeap(HeapBase,HeapLength);

/*:6*/
#line 29 "ttmain.w"

while(TRUE)
mainState= fsm(mainState);
}

/*:3*//*15:*/
#line 40 "mmgr.w"
void*AllocMem(unsigned int size){
MemBlockPtr current= freeList;

size+= sizeof(int);
/*16:*/
#line 52 "mmgr.w"

{
while(current&&(current->size<size))
current= current->next;
if(!current)return NULL;
}

/*:16*/
#line 44 "mmgr.w"

if(current->size>size+sizeof(MemBlock))
/*17:*/
#line 59 "mmgr.w"

{
current->size-= size;
current= (MemBlockPtr)(((char*)current)+current->size);
current->size= size;
}

/*:17*/
#line 46 "mmgr.w"

else
/*18:*/
#line 66 "mmgr.w"

{
if(current->prev)
current->prev->next= current->next;
else
freeList= current->next;
if(current->next)
current->next->prev= current->prev;
}

/*:18*/
#line 48 "mmgr.w"

return(void*)(((char*)current)+sizeof(int));
}

/*:15*//*19:*/
#line 84 "mmgr.w"
void FreeMem(void*addr){
MemBlockPtr block= ((MemBlockPtr)(((char*)addr)-sizeof(int)));

/*20:*/
#line 95 "mmgr.w"

if(!freeList){
freeList= block;
block->next= NULL;
block->prev= NULL;
return;
}

/*:20*/
#line 87 "mmgr.w"

if(block<freeList)
/*21:*/
#line 106 "mmgr.w"

if(block+block->size==freeList){
block->size+= freeList->size;
block->next= freeList->next;
block->prev= NULL;
freeList= addr;
}else{
block->next= freeList;
freeList->prev= block;
freeList= block;
}

/*:21*/
#line 89 "mmgr.w"

else
/*22:*/
#line 118 "mmgr.w"

{
MemBlockPtr list= freeList;


do{
list= list->next;
}while(list->next&&(block>list));

if(list->next)
/*23:*/
#line 134 "mmgr.w"

{
block->next= list->next;
list->next= block;
block->prev= block->next->prev;
block->next->prev= block;
/*24:*/
#line 143 "mmgr.w"

if((MemBlockPtr)((char*)block+block->size)==block->next){
block->size+= block->next->size;
block->next= block->next->next;
if(block->next)block->next->prev= block;
}

/*:24*/
#line 140 "mmgr.w"

}

/*:23*/
#line 128 "mmgr.w"

else
/*25:*/
#line 150 "mmgr.w"

{
list->next= block;
block->prev= list;
block->next= NULL;
}

/*:25*/
#line 130 "mmgr.w"

/*26:*/
#line 157 "mmgr.w"

if((MemBlockPtr)((char*)(block->prev)+block->prev->size)==block){
block->prev->size+= block->size;
block->prev->next= block->next;
if(block->next)
block->next->prev= block->prev;
}

/*:26*/
#line 131 "mmgr.w"

}

/*:22*/
#line 91 "mmgr.w"

return;
}

/*:19*//*27:*/
#line 165 "mmgr.w"
void InitHeap(char*addr,int size){
freeList= (MemBlockPtr)addr;
freeList->next= NULL;
freeList->prev= NULL;
freeList->size= size;
}

#line 1 "ttworld.w"

/*:27*//*55:*/
#line 29 "fsm.w"

StatePtr fsm(StatePtr s){
for(;;){
while(!s->test()){
s++;
}
s->attribute();
if(!(s->flags&FSM_RERUN))break;
s= s->next;
}
return s->next;
}

/*:55*//*56:*/
#line 45 "fsm.w"

int True(){
return TRUE;
}

int False(){
return FALSE;
}

void Null(){
return;
}

/*:56*//*58:*/
#line 66 "fsm.w"

State InitialState[]= {
{True,IntroScreen,Initialize,0}
};
State IntroScreen[]= {
{DoneWithIntro,PathPlay,InitGame,0},
{True,IntroScreen,Null,0}
};
State PathPlay[]= {
{Dead,DeathScreen,StartDeathSequence,0},
{Win,VictoryScreen,StartVictorySequence,0},
{AtNode,NodePlay,InitNode,0},
{True,PathPlay,RunPath,0}
};
State VictoryScreen[]= {
{DoneVictory,IntroScreen,Null,0},
{True,VictoryScreen,RunVictoryScreen,0}
};
State DeathScreen[]= {
{DoneDeath,IntroScreen,Null,0},
{True,DeathScreen,RunDeathScreen,0}
};
State NodePlay[]= {
{Dead,DeathScreen,StartDeathSequence,0},
{Win,VictoryScreen,StartVictorySequence,0},
{AtPath,PathPlay,InitPath,0},
{True,NodePlay,RunNode,0}
};

/*:58*//*59:*/
#line 97 "fsm.w"

int DoneWithIntro(){
return TRUE;
}
int Dead(){
return FALSE;
}
int Win(){
return FALSE;
}
int AtNode(){
return FALSE;
}
int DoneVictory(){
return FALSE;
}
int DoneDeath(){
return FALSE;
}
int AtPath(){
return FALSE;
}

/*:59*//*60:*/
#line 121 "fsm.w"

void Initialize(){}
void StartDeathSequence(){}
void RunDeathScreen(){}
void StartVictorySequence(){}
void RunVictoryScreen(){}
void InitNode(){}
void RunNode(){}

/*:60*//*61:*/
#line 132 "fsm.w"

void InitGame(){
/*7:*/
#line 60 "ttmain.w"

playerDead= FALSE;
Player1_score= 0L;
Player2_score= 0L;
currentRound= 0;

/*:7*//*198:*/
#line 416 "player.w"

currentPlayer= &player1;
player1.fsmState= MilesStand;

/*:198*/
#line 134 "fsm.w"

currentPath= &p1_1;
InitPath();
}

/*:61*//*68:*/
#line 45 "io.w"

void DoIO(){
short size;
unsigned char*srcptr;
unsigned char*dstptr;

#if TIMING
VDPPort.control.l= 0xc0000000;
VDPPort.data.w= 0x00f;
#endif
while(ip!=IORequestPointer){
/*69:*/
#line 65 "io.w"

switch(IORequestBuffer[ip]){
case IOR_READ_CONTROLLERS:
/*70:*/
#line 98 "io.w"

{
srcptr= *((unsigned char**)(IORequestBuffer+ip+1));
ReadHWControllers();
*srcptr++= bStick1;
*srcptr++= cStick1;
*srcptr++= dStick1;
*srcptr++= bStick2;
*srcptr++= cStick2;
*srcptr= dStick2;
}

/*:70*/
#line 68 "io.w"

break;
case IOR_SEND_SPRITE_CONTROL:
/*71:*/
#line 110 "io.w"

{
srcptr= *((UCHAR**)(IORequestBuffer+ip+1));
gemsdmastart();
InitDMA((long)srcptr,(long)SPRITE_ATTRIBUTE_VDP_ADDRESS,640L);
gemsdmaend();
}

/*:71*/
#line 71 "io.w"

break;
case IOR_SEND_PALETTES:
/*72:*/
#line 118 "io.w"

{
srcptr= (UCHAR*)((*((ULONG*)(IORequestBuffer+ip+1)))>>1);
VDPPort.control.l= 0x93409400;
VDPPort.control.w= 0x9500+((long)srcptr&0xff);
VDPPort.control.w= 0x9600+(((long)srcptr&0xff00)>>8);
VDPPort.control.w= 0x9700+(((long)srcptr&0x7f0000)>>16);
VDPPort.control.l= 0xc0000080;
}

/*:72*/
#line 74 "io.w"

break;
case IOR_SEND_BLOCK_16:
/*73:*/
#line 128 "io.w"

{
srcptr= (UCHAR*)(0x00ff0000|IORequestBuffer[ip+1]);
dstptr= (UCHAR*)IORequestBuffer[ip+2];
size= IORequestBuffer[ip+3];
gemsdmastart();
InitDMA((long)srcptr,(long)dstptr,(long)size);
gemsdmaend();
}

/*:73*/
#line 77 "io.w"

break;
case IOR_SEND_BLOCK_32:
/*74:*/
#line 138 "io.w"

{
srcptr= *((unsigned char**)(IORequestBuffer+ip+1));
dstptr= (UCHAR*)IORequestBuffer[ip+3];
size= IORequestBuffer[ip+4];
gemsdmastart();
InitDMA((long)srcptr,(long)dstptr,(long)size);
gemsdmaend();
}

/*:74*/
#line 80 "io.w"

break;
case IOR_SEND_SCROLLS:
/*75:*/
#line 148 "io.w"

{
VDPPort.control.l= 0x40000010;
VDPPort.data.w= IORequestBuffer[ip+1];
VDPPort.data.w= IORequestBuffer[ip+2];
SetVDPDest(H_SCROLL_VDP_ADDRESS);
VDPPort.data.w= IORequestBuffer[ip+3];
VDPPort.data.w= IORequestBuffer[ip+4];
}

/*:75*/
#line 83 "io.w"

break;
case IOR_SEND_A_SCROLLS:
/*76:*/
#line 158 "io.w"

{
VDPPort.control.l= 0x40000010;
VDPPort.data.w= IORequestBuffer[ip+1];
SetVDPDest(H_SCROLL_VDP_ADDRESS);
VDPPort.data.w= IORequestBuffer[ip+2];
}

/*:76*/
#line 86 "io.w"

break;
case IOR_SEND_B_SCROLLS:
/*77:*/
#line 166 "io.w"

{
VDPPort.control.l= 0x40020010;
VDPPort.data.w= IORequestBuffer[ip+1];
SetVDPDest(H_SCROLL_VDP_ADDRESS+2);
VDPPort.data.w= IORequestBuffer[ip+2];
}

/*:77*/
#line 89 "io.w"

break;
case IOR_SEND_COLUMN:
/*78:*/
#line 174 "io.w"

{
srcptr= *((unsigned char**)(IORequestBuffer+ip+1));
dstptr= (UCHAR*)IORequestBuffer[ip+3];
VDPPort.control.w= 0x8f80;
gemsdmastart();
InitDMA((long)srcptr,(long)dstptr,(long)64);
gemsdmaend();
VDPPort.control.w= 0x8f02;
}

/*:78*/
#line 92 "io.w"

break;
default:
break;
}

/*:69*/
#line 56 "io.w"

ip= (ip+IOReqSize)%IOBufferSize;
}
#if TIMING
VDPPort.control.l= 0xc0000000;
VDPPort.data.w= 0x000;
#endif
}

/*:68*//*89:*/
#line 7 "startup.w"

#pragma dsection .vectors

VoidFuncPtr vectors[]= {
(VoidFuncPtr)0xfffff800,
main,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
HBLHandler,
ErrorHandler,
VBLHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
ErrorHandler,
};

#pragma dsection .coding
char codingblock1[]= 
"SEGA MEGA DRIVE "
"(C)SEGA 1993 AUG"
"TREASURE TALES  "
"                "
"                "
"TREASURE TALES  "
"                "
"                "
"GM 00001014-00\0";
char codingblock3[]= 
"J              ";
long codingblock4[]= {
0x00000000,
0x0007ffff,
0x00ff0000,
0x00ffffff};
char codingblock5[]= 
"                "
"                "
"                "
"                "
"JUE            ";


#pragma dsection .text

/*:89*//*90:*/
#line 119 "startup.w"

void VBLHandler(){
asm(" movem.l a0-a6/d0-d7,-(sp)",4);
tickCounter++;
vblFlag= 1;
DoIO();
asm(" movem.l (sp)+,a0-a6/d0-d7",4);
asm(" unlk a6");
asm(" rte",2);
}

/*:90*//*91:*/
#line 134 "startup.w"

void HBLHandler(){
asm(" and.w #$f0ff,(sp)",4);
#if 0
asm(" or.w #$0500,(sp)",4);
#endif
asm(" unlk a6");
asm(" rte",2);
}

/*:91*//*92:*/
#line 146 "startup.w"

void ErrorHandler(){
while(1);
}

/*:92*//*105:*/
#line 265 "startup.w"

void WaitTOF(){
#if TIMING
VCTRLL= 0xc0000000;
VDATAW= 0x000;
#endif
vblFlag= 0;
while(!vblFlag)
asm(" stop #$2500",4);
#if TIMING
VCTRLL= 0xc0000000;
VDATAW= 0x888;
#endif
}

/*:105*//*106:*/
#line 283 "startup.w"

void ReadHWControllers(){
asm(" move.w  #$2700,SR",4);
gemsholdz80();
asm(" lea $a10003,a0");
/*107:*/
#line 302 "startup.w"

asm(" move.b #0,(a0)");
asm(" nop");
asm(" nop");
asm(" move.b (a0),d0");
asm(" lsl.b #2,d0");
asm(" andi.b #$c0,d0");

asm(" move.b #$40,(a0)");
asm(" nop");
asm(" nop");
asm(" move.b (a0),d1");
asm(" andi.b #$3f,d1");
asm(" or.b d1,d0");
asm(" not.b d0");

/*:107*/
#line 288 "startup.w"

asm(" move.b d0,_bStick1");
asm(" lea $a10005,a0");
/*107:*/
#line 302 "startup.w"

asm(" move.b #0,(a0)");
asm(" nop");
asm(" nop");
asm(" move.b (a0),d0");
asm(" lsl.b #2,d0");
asm(" andi.b #$c0,d0");

asm(" move.b #$40,(a0)");
asm(" nop");
asm(" nop");
asm(" move.b (a0),d1");
asm(" andi.b #$3f,d1");
asm(" or.b d1,d0");
asm(" not.b d0");

/*:107*/
#line 291 "startup.w"

asm(" move.b d0,_bStick2");
asm(" move.w #$2000,SR");
gemsreleasez80();

dStick1= (bStick1^cStick1)&bStick1;
cStick1= bStick1;
dStick2= (bStick2^cStick2)&bStick2;
cStick2= bStick2;
}

/*:106*//*109:*/
#line 329 "startup.w"

void SegaLogo(){
short*palette;
int i,j;

SendBlock32(logoData,FG_CELLS+32,1600);
palette= AllocMem(128);
for(i= logoColors[0];i<logoColors[1];i++){
palette[i]= logoColors[i+2];
}
SendBlock32(logoMap,LOGO1,24);
SendBlock32(logoMap+12,LOGO2,24);
SendBlock32(logoMap+24,LOGO3,24);
SendBlock32(logoMap+36,LOGO4,24);
WaitTOF();
FadeIn(palette,45);
for(i= 0;i<31;i++)
WaitTOF();
for(i= 20;i>0;i--){
for(j= 0;j<11;j++){
palette[2+j]= logoColors[4+i+j];
}
SendPalettes(palette);
WaitTOF();
WaitTOF();
WaitTOF();
WaitTOF();
}
for(i= 0;i<27;i++)
WaitTOF();
FadeOut(palette,45);
FreeMem(palette);
}

#line 1 "utils.w"
/*:109*//*111:*/
#line 9 "utils.w"

void InterpolateColor(short target,short time,short duration,short*color){
short dr,dg,db;
short tr,tg,tb;
short r,g,b;
int i;

r= *color&0x00e;
g= (*color&0x0e0)>>4;
b= (*color&0xe00)>>8;
tr= target&0x00e;
tg= (target&0x0e0)>>4;
tb= (target&0xe00)>>8;
dr= r-tr+1;
dg= g-tg+1;
db= b-tb+1;
r= tr+(dr*time)/duration;
g= tg+(dg*time)/duration;
b= tb+(db*time)/duration;
*color= (r&0x00e)|((g&0x00e)<<4)|((b&0x00e)<<8);
}

/*:111*//*112:*/
#line 34 "utils.w"

void InterpolatePalette(short target,short time,short duration,short*palette){
int i;

for(i= 0;i<16;i++){
InterpolateColor(target,time,duration,&palette[i]);
}
}

/*:112*//*113:*/
#line 46 "utils.w"

void InterpolateFullPalette(short target,short time,short duration,short*palette){
int i;

for(i= 0;i<64;i++){
InterpolateColor(target,time,duration,&palette[i]);
}
}

/*:113*//*114:*/
#line 58 "utils.w"

void Interpolate2Palettes(short*target,short time,short duration,short*palette){
int i;

for(i= 0;i<16;i++){
InterpolateColor(target[i],time,duration,&palette[i]);
}
}

/*:114*//*115:*/
#line 70 "utils.w"

void Interpolate2FullPalettes(short*target,short time,short duration,short*palette){
int i;

for(i= 0;i<64;i++){
InterpolateColor(target[i],time,duration,&palette[i]);
}
}

/*:115*//*116:*/
#line 82 "utils.w"

void FadeIn(short*palette,short time){
int i,j;
short workpal[64];

for(i= 1;i<=time;i++){
for(j= 0;j<64;j++){
workpal[j]= palette[j];
}
InterpolateFullPalette(0,i,time,workpal);
SendPalettes(workpal);
WaitTOF();
}
}

/*:116*//*117:*/
#line 100 "utils.w"

void FadeOut(short*palette,short time){
int i,j;
short workpal[64];

for(i= time-1;i>=0;i--){
for(j= 0;j<64;j++){
workpal[j]= palette[j];
}
InterpolateFullPalette(0,i,time,&workpal);
SendPalettes(workpal);
WaitTOF();
}
}

/*:117*//*119:*/
#line 18 "expand.w"

int ExpandLZ(unsigned char*in,unsigned char*out){
unsigned char*bytes;
unsigned char*temp;
unsigned long shifter;
int offset;
int count;
int shift_count= 0;
int done= 0;

/*127:*/
#line 106 "expand.w"

bytes= in+*(unsigned short*)in;
bytes+= 2;
in+= 2;

/*:127*/
#line 28 "expand.w"

/*128:*/
#line 111 "expand.w"

shifter= *(unsigned long*)in;
in+= 4;
#line 1 "path.w"

/*:128*/
#line 29 "expand.w"

while(!done){
if(0x80000000&shifter){
/*122:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:122*/
#line 32 "expand.w"

/*125:*/
#line 100 "expand.w"

*out++= *bytes++;

/*:125*/
#line 33 "expand.w"

}else{
/*122:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:122*/
#line 35 "expand.w"

if(0x80000000&shifter)
/*121:*/
#line 56 "expand.w"

{
/*122:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:122*/
#line 58 "expand.w"

offset= (shifter&0xe0000000)>>21;
/*124:*/
#line 95 "expand.w"

/*122:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:122*/
#line 96 "expand.w"

/*122:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:122*/
#line 97 "expand.w"

/*122:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:122*/
#line 98 "expand.w"


/*:124*/
#line 60 "expand.w"

offset+= *bytes++;
switch(shifter&0xc0000000){
case 0x00000000:
count= 3;
break;
case 0x40000000:
count= 4;
break;
case 0x80000000:
count= 5;
break;
case 0xc0000000:
count= *bytes++;
if((count==0)&&(offset==0))done= 1;
if((count==1)&&(offset==0))count= 0;
break;
}
/*123:*/
#line 91 "expand.w"

/*122:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:122*/
#line 92 "expand.w"

/*122:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:122*/
#line 93 "expand.w"


/*:123*/
#line 78 "expand.w"

temp= out-offset;
while(count--)/*126:*/
#line 103 "expand.w"

*out++= *temp++;

/*:126*/
#line 80 "expand.w"

}

/*:121*/
#line 37 "expand.w"

else
/*120:*/
#line 44 "expand.w"

{
/*122:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:122*/
#line 46 "expand.w"

temp= out-*bytes++;
if(0x80000000&shifter){
/*126:*/
#line 103 "expand.w"

*out++= *temp++;

/*:126*/
#line 49 "expand.w"

}
/*126:*/
#line 103 "expand.w"

*out++= *temp++;

/*:126*/
#line 51 "expand.w"

/*126:*/
#line 103 "expand.w"

*out++= *temp++;

/*:126*/
#line 52 "expand.w"

/*122:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:122*/
#line 53 "expand.w"

}

/*:120*/
#line 39 "expand.w"

}
}
}

/*:119*//*131:*/
#line 49 "path.w"

void InitPath(){
int i,j;
unsigned char*buffer;
unsigned short*bufferA;
unsigned short*bufferB;

#if DATA_COMPRESSED
buffer= (unsigned char*)AllocMem(4096);
ExpandLZ(currentPath->artSet->data,buffer);
SendBlock32(buffer,FG_CELLS,4096);
WaitTOF();
FreeMem(buffer);
#else
SendBlock32(currentPath->artSet->data,FG_CELLS,4096);
WaitTOF();
#endif
SendBlock32(digitData,0xf000,4096);
/*133:*/
#line 88 "path.w"

pathMap= currentPath->map;
screenScrollY= 800;
screenScrollX= 0;

/*:133*/
#line 67 "path.w"

/*132:*/
#line 74 "path.w"

currentPlayer->xPosition= currentPath->xStart;
currentPlayer->yPosition= currentPath->yStart;
currentPlayer->chBase= 0xa300;
currentPlayer->Frame= milesshape;
currentPlayer->anim_next= MilesStandEast;
currentPlayer->xOffset= 0;
currentPlayer->yOffset= 0;
currentPlayer->counter= 0;
currentPlayer->Frame= milesshape;
currentPlayer->anim_time= 0;
currentPlayer->behavior= 0;
currentPlayer->type= 1;

/*:132*/
#line 68 "path.w"

SendBlock32(milescells,768*32,4096);
/*136:*/
#line 108 "path.w"

/*137:*/
#line 115 "path.w"

bufferA= (unsigned short*)AllocMem(2*32*64);
memset(bufferA,0,2*32*64);
bufferB= (unsigned short*)AllocMem(2*32*64);
memset(bufferB,0,2*32*64);

/*:137*/
#line 109 "path.w"

/*138:*/
#line 121 "path.w"

mapWidth= currentPath->xSize;
j= 0;
for(i= 0;i<currentPath->ySize;i++){
rowOffsets[i]= j;
j+= mapWidth;
}
for(i= 13;i>=0;i--)
for(j= 0;j<11;j++)
if(pathMap[SquareLoc(j,i)].type)
/*139:*/
#line 140 "path.w"

{
unsigned short*ba,*bb;
int y,alpha,beta,theta,phi,offset;

y= (i<<1);
alpha= (j<<2)+i;
y+= pathMap[SquareLoc(j,i)].elevation;
beta= yMax-y;
theta= alpha%64;
phi= beta%32;
offset= 64*phi+theta;
offset+= 64;
ba= bufferA+offset;
bb= bufferB+offset;
switch(theta){
case 63:
/*141:*/
#line 195 "path.w"

bb[0]= 0x0007;
bb[1-64]= 0x0007;
bb[2-64]= 0x0007;
bb[3-64]= 0x0007;
bb[4-64]= 0x0008;
ba-= 64;
bb-= 64;
ba[0]= 0x0004;
ba[1-64]= 0x0005;
bb[2-64]= 0x0005;
bb[3-64]= 0x0005;
bb[4-64]= 0x0006;
ba-= 64;
bb-= 64;
ba[0]= 0x0001;
ba[1-64]= 0x0002;
ba[2-64]= 0x0002;
ba[3-64]= 0x0002;
bb[4-64]= 0x0003;

/*:141*/
#line 157 "path.w"

break;
case 62:
/*142:*/
#line 216 "path.w"

bb[0]= 0x0007;
bb[1]= 0x0007;
bb[2-64]= 0x0007;
bb[3-64]= 0x0007;
bb[4-64]= 0x0008;
ba-= 64;
bb-= 64;
ba[0]= 0x0004;
ba[1]= 0x0005;
bb[2-64]= 0x0005;
bb[3-64]= 0x0005;
bb[4-64]= 0x0006;
ba-= 64;
bb-= 64;
ba[0]= 0x0001;
ba[1]= 0x0002;
ba[2-64]= 0x0002;
ba[3-64]= 0x0002;
bb[4-64]= 0x0003;

/*:142*/
#line 160 "path.w"

break;
case 61:
/*143:*/
#line 237 "path.w"

bb[0]= 0x0007;
bb[1]= 0x0007;
bb[2]= 0x0007;
bb[3-64]= 0x0007;
bb[4-64]= 0x0008;
ba-= 64;
bb-= 64;
ba[0]= 0x0004;
ba[1]= 0x0005;
bb[2]= 0x0005;
bb[3-64]= 0x0005;
bb[4-64]= 0x0006;
ba-= 64;
bb-= 64;
ba[0]= 0x0001;
ba[1]= 0x0002;
ba[2]= 0x0002;
ba[3-64]= 0x0002;
bb[4-64]= 0x0003;

/*:143*/
#line 163 "path.w"

break;
case 60:
/*144:*/
#line 258 "path.w"

bb[0]= 0x0007;
bb[1]= 0x0007;
bb[2]= 0x0007;
bb[3]= 0x0007;
bb[4-64]= 0x0009;
ba-= 64;
bb-= 64;
ba[0]= 0x0004;
ba[1]= 0x0005;
bb[2]= 0x0005;
bb[3]= 0x0005;
bb[4-64]= 0x0006;
ba-= 64;
bb-= 64;
ba[0]= 0x0001;
ba[1]= 0x0002;
ba[2]= 0x0002;
ba[3]= 0x0002;
bb[4-64]= 0x0003;

/*:144*/
#line 166 "path.w"

break;
default:
/*140:*/
#line 174 "path.w"

bb[0]= 0x0007;
bb[1]= 0x0007;
bb[2]= 0x0007;
bb[3]= 0x0007;
bb[4]= 0x0008;
ba-= 64;
bb-= 64;
ba[0]= 0x0004;
ba[1]= 0x0005;
bb[2]= 0x0005;
bb[3]= 0x0005;
bb[4]= 0x0006;
ba-= 64;
bb-= 64;
ba[0]= 0x0001;
ba[1]= 0x0002;
ba[2]= 0x0002;
bb[3]= 0x0002;
bb[4]= 0x0003;

/*:140*/
#line 169 "path.w"

break;
}
}

/*:139*/
#line 131 "path.w"


/*:138*/
#line 110 "path.w"

/*145:*/
#line 279 "path.w"

SendBlock32(bufferA,FG,2*32*64);
SendBlock32(bufferB,BG,2*32*64);

/*:145*/
#line 111 "path.w"

WaitTOF();
/*146:*/
#line 283 "path.w"

FreeMem(bufferA);
FreeMem(bufferB);

/*:146*/
#line 113 "path.w"


/*:136*/
#line 70 "path.w"

FadeIn(currentPath->artSet->palette,32);
}

/*:131*//*147:*/
#line 289 "path.w"

void RunPath(){
sprite= 0;
/*148:*/
#line 300 "path.w"

/*176:*/
#line 11 "player.w"

currentPlayer->fsmState= fsm(currentPlayer->fsmState);

/*:176*/
#line 301 "path.w"

/*149:*/
#line 304 "path.w"

AnimateCreature(currentPlayer);
DrawCreatures(currentPlayer);
SendSpriteControl(spriteAttributes);

/*:149*/
#line 302 "path.w"


/*:148*/
#line 292 "path.w"

/*150:*/
#line 309 "path.w"


/*:150*/
#line 293 "path.w"

/*151:*/
#line 311 "path.w"

SendScrolls(screenScrollY,screenScrollY,-screenScrollX,-screenScrollX);
{
short oldX= screenScrollX;
short oldY= screenScrollY;

/*152:*/
#line 321 "path.w"

/*153:*/
#line 328 "path.w"

if(playerY>0xff)screenScrollY++;
if(playerY<0xff)screenScrollY--;
if(playerX>0x101)screenScrollX++;
if(playerX>0x100)screenScrollX++;
if(playerX<0x0ff)screenScrollX--;
if(playerX<0x100)screenScrollX--;

/*:153*/
#line 322 "path.w"

/*154:*/
#line 339 "path.w"

if(playerY>0x117)screenScrollY++;
if(playerY<0xe7)screenScrollY--;
if(playerX>0x128)screenScrollX+= 2;
if(playerX<0x0d8)screenScrollX-= 2;

/*:154*/
#line 323 "path.w"

/*155:*/
#line 348 "path.w"

if(screenScrollX<0)screenScrollX= 0;
if(screenScrollX>7*40*8)screenScrollX= 7*40*8;
if(screenScrollY<0)screenScrollY= 0;
if(screenScrollY>(yMax*8-216))screenScrollY= (yMax*8-216);

/*:155*/
#line 324 "path.w"


/*:152*/
#line 317 "path.w"

/*158:*/
#line 380 "path.w"

{
short target;

/*159:*/
#line 390 "path.w"

if(((oldX^screenScrollX)&0x8)&&(screenScrollX>oldX))
/*164:*/
#line 416 "path.w"

{
short column= screenScrollX+320;

BuildNewColumn(column);
target= (column>>2)&126;
SendColumn(&colUpdateBufferA,target+FG);
SendColumn(&colUpdateBufferB,target+BG);
}

/*:164*/
#line 392 "path.w"


/*:159*/
#line 384 "path.w"

/*160:*/
#line 394 "path.w"

if(((oldX^screenScrollX)&0x8)&&(screenScrollX<oldX))
/*165:*/
#line 426 "path.w"

{
short column= screenScrollX-8;

BuildNewColumn(column);
target= (column>>2)&126;
SendColumn(&colUpdateBufferA,target+FG);
SendColumn(&colUpdateBufferB,target+BG);
}

/*:165*/
#line 396 "path.w"


/*:160*/
#line 385 "path.w"

/*161:*/
#line 398 "path.w"

if(((oldY^screenScrollY)&0x8)&&(screenScrollY<oldY))
/*166:*/
#line 436 "path.w"

{
short column= screenScrollX-8;
short row= screenScrollY;

BuildNewRow(row,column);
target= (((screenScrollY)>>3)*128)&4095;
SendBlock32(&lineUpdateBufferA,target+FG,128);
SendBlock32(&lineUpdateBufferB,target+BG,128);
}

/*:166*/
#line 400 "path.w"


/*:161*/
#line 386 "path.w"

/*162:*/
#line 402 "path.w"

if(((oldY^screenScrollY)&0x8)&&(screenScrollY>oldY))
/*167:*/
#line 447 "path.w"

{
short column= screenScrollX-8;
short row= screenScrollY+232;

BuildNewRow(row,column);
target= (((screenScrollY+232)>>3)*128)&4095;
SendBlock32(&lineUpdateBufferA,target+FG,128);
SendBlock32(&lineUpdateBufferB,target+BG,128);
}

/*:167*/
#line 404 "path.w"


/*:162*/
#line 387 "path.w"

}

/*:158*/
#line 318 "path.w"

}

/*:151*/
#line 294 "path.w"

ReadControllers(&bStick1);
/*215:*/
#line 87 "anim.w"

spriteAttributes[sprite-1].link= 0;

/*:215*/
#line 296 "path.w"

WaitTOF();
}

/*:147*//*168:*/
#line 460 "path.w"

void BuildNewColumn(short column)
/*170:*/
#line 471 "path.w"

{
short i,j;
short a;
short e;
short y= yMax-((screenScrollY-8)>>3);
short b= 31-(y%32);
short x= column>>3;
short z;
short k,l;
short ua,ub;
short ch;
SquarePtr currentSquare;
CellTestPtr test;

for(a= b;a<32;a++){
ua= 0;
ub= 0;
/*172:*/
#line 533 "path.w"

{
CellTestPtr test;
short ib= y>>3;
short jb= (x>>2)-ib;
ib<<= 2;
test= screenTranslate[x%4][y%8];
for(k= 0;k<400;k++){
if(test[k].j+jb<0)continue;
if(test[k].i+ib<0)continue;
if(!pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].type)continue;
if(test[k].z==pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].elevation){
if(ua){
ub= l1cells[pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].type][test[k].n];
if(ub)break;
}else{
ua= l1cells[pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].type][test[k].n];
}
}
}
}

/*:172*/
#line 489 "path.w"

colUpdateBufferA[a]= ua;
colUpdateBufferB[a]= ub;
y--;
}
for(a= 0;a<b;a++){
ua= 0;
ub= 0;
/*172:*/
#line 533 "path.w"

{
CellTestPtr test;
short ib= y>>3;
short jb= (x>>2)-ib;
ib<<= 2;
test= screenTranslate[x%4][y%8];
for(k= 0;k<400;k++){
if(test[k].j+jb<0)continue;
if(test[k].i+ib<0)continue;
if(!pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].type)continue;
if(test[k].z==pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].elevation){
if(ua){
ub= l1cells[pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].type][test[k].n];
if(ub)break;
}else{
ua= l1cells[pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].type][test[k].n];
}
}
}
}

/*:172*/
#line 497 "path.w"

colUpdateBufferA[a]= ua;
colUpdateBufferB[a]= ub;
y--;
}
}

/*:170*/
#line 462 "path.w"


void BuildNewRow(short row,short column)
/*171:*/
#line 504 "path.w"

{
short i,j,z,n;
short x= column>>3;
short y= yMax-(row>>3);
short a;
short b= x%64;
short k;
short ua,ub;
CellTestPtr test;

for(a= b;a<64;a++){
ua= 0;
ub= 0;
/*172:*/
#line 533 "path.w"

{
CellTestPtr test;
short ib= y>>3;
short jb= (x>>2)-ib;
ib<<= 2;
test= screenTranslate[x%4][y%8];
for(k= 0;k<400;k++){
if(test[k].j+jb<0)continue;
if(test[k].i+ib<0)continue;
if(!pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].type)continue;
if(test[k].z==pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].elevation){
if(ua){
ub= l1cells[pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].type][test[k].n];
if(ub)break;
}else{
ua= l1cells[pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].type][test[k].n];
}
}
}
}

/*:172*/
#line 518 "path.w"

lineUpdateBufferA[a]= ua;
lineUpdateBufferB[a]= ub;
x++;
}
for(a= 0;a<b;a++){
ua= 0;
ub= 0;
/*172:*/
#line 533 "path.w"

{
CellTestPtr test;
short ib= y>>3;
short jb= (x>>2)-ib;
ib<<= 2;
test= screenTranslate[x%4][y%8];
for(k= 0;k<400;k++){
if(test[k].j+jb<0)continue;
if(test[k].i+ib<0)continue;
if(!pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].type)continue;
if(test[k].z==pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].elevation){
if(ua){
ub= l1cells[pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].type][test[k].n];
if(ub)break;
}else{
ua= l1cells[pathMap[SquareLoc(test[k].j+jb,test[k].i+ib)].type][test[k].n];
}
}
}
}

/*:172*/
#line 526 "path.w"

lineUpdateBufferA[a]= ua;
lineUpdateBufferB[a]= ub;
x++;
}
}

/*:171*/
#line 465 "path.w"


/*:168*//*179:*/
#line 144 "player.w"

void ClearCount(){
currentPlayer->counter= 0;
currentPlayer->yOffset= 0;
currentPlayer->xOffset= 0;
return;
}

/*:179*//*180:*/
#line 154 "player.w"

void BumpCount(){
currentPlayer->counter++;
return;
}

/*:180*//*181:*/
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

/*:181*//*182:*/
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

/*:182*//*183:*/
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

/*:183*//*184:*/
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

/*:184*//*185:*/
#line 306 "player.w"

int CheckJumpNorth(){
if(!ControllerUp())return FALSE;
if(currentPlayer->yPosition+1>=currentPath->ySize)return FALSE;
return TRUE;
}

/*:185*//*186:*/
#line 316 "player.w"

int CheckJumpSouth(){
if(!ControllerDown())return FALSE;
if(currentPlayer->yPosition<=0)return FALSE;
return TRUE;
}

/*:186*//*187:*/
#line 326 "player.w"

int CheckJumpEast(){
if(!ControllerRight())return FALSE;
if(currentPlayer->xPosition+1>=currentPath->xSize)return FALSE;
return TRUE;
}

/*:187*//*188:*/
#line 336 "player.w"

int CheckJumpWest(){
if(!ControllerLeft())return FALSE;
if(currentPlayer->xPosition<=0)return FALSE;
return TRUE;
}

/*:188*//*190:*/
#line 351 "player.w"

int ControllerUp(){
return bStick1&JOYUP;
}

/*:190*//*191:*/
#line 358 "player.w"

int ControllerDown(){
return bStick1&JOYDOWN;
}

/*:191*//*192:*/
#line 365 "player.w"

int ControllerLeft(){
return bStick1&JOYLEFT;
}

/*:192*//*193:*/
#line 372 "player.w"

int ControllerRight(){
return bStick1&JOYRIGHT;
}

/*:193*//*194:*/
#line 381 "player.w"

int TimeToYawn(){
return(currentPlayer->counter==YawnTime);
}

/*:194*//*195:*/
#line 388 "player.w"

int MilesLanded(){
return(currentPlayer->counter>15);
}

/*:195*//*196:*/
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

/*:196*//*202:*/
#line 14 "squares.w"

void ActivateSquare(CreaturePtr c,short x,short y){
ActiveSquarePtr as;
/*203:*/
#line 27 "squares.w"

as= AllocMem(sizeof(ActiveSquare));

/*:203*/
#line 17 "squares.w"

/*204:*/
#line 30 "squares.w"

as->x= x;
as->y= y;
as->type= pathMap[y*mapWidth+x].type;
as->timer= 0;

/*:204*/
#line 18 "squares.w"

/*205:*/
#line 36 "squares.w"

switch(as->type){
case 0:
default:
break;
}

/*:205*/
#line 19 "squares.w"

if(as)
/*206:*/
#line 43 "squares.w"

as->next= activeSquareList;
as->prev= NULL;
activeSquareList->prev= as;
activeSquareList= as;

/*:206*/
#line 21 "squares.w"

}

void UpdateSquares(){
}

/*:202*//*211:*/
#line 29 "anim.w"

void DoAnimFlags(char f,CreaturePtr t){
AnimStatePtr a;

switch(f){
case 0:
break;
default:
break;
}
}

/*:211*//*212:*/
#line 41 "anim.w"

void AnimateCreature(CreaturePtr t){
register AnimStatePtr a;
if(!(t->anim_time--)){
a= t->anim_next;
t->anim_time= a->time;
t->Frame= a->frame;
t->anim_next= a->next;
DoAnimFlags(a->flags,t);
}
}

/*:212*//*213:*/
#line 57 "anim.w"

int LoadCreature(int a,int b){
if(a>1){
unsigned char*buffer= AllocMem(CreatureShapeLength[a]*32);
ExpandLZ((unsigned char*)CompressedDataPointers[a],buffer);
SendBlock32(buffer,b,CreatureShapeLength[a]*32);
WaitTOF();
FreeMem(buffer);
return CreatureShapeLength[a];
}
return 0;
}

/*:213*//*214:*/
#line 72 "anim.w"

void DrawCreatures(CreaturePtr c){
short ty,tx;
short n,y;
register short*st;
register SpriteDefPtr sp;

sp= &spriteAttributes[sprite];
/*217:*/
#line 96 "anim.w"

ty= (yMax-(2*c->yPosition+
pathMap[mapWidth*c->yPosition+c->xPosition].elevation))*8-
screenScrollY+135;
ty-= c->yOffset/256;
if(c==currentPlayer)
playerY= ty;

/*:217*/
#line 80 "anim.w"

if((ty>32)&&(ty<380)){
/*216:*/
#line 90 "anim.w"

tx= (8*(c->xPosition*4+c->yPosition))-screenScrollX+128;
tx+= c->xOffset/256;
if(c==currentPlayer)
playerX= tx;

/*:216*/
#line 82 "anim.w"

/*218:*/
#line 104 "anim.w"

n= 3;
st= (short*)c->Frame;
tx-= st[1];
ty-= st[2];
for(y= 0;y<st[0];y++){
sp->vp= ty+st[n++];
sp->size= st[n++];
sp->cell= c->chBase+st[n++];
sp->hp= tx+st[n++];
sp->link= sprite+1;
if(!(sp->hp&0x1ff))continue;
sprite++;
sp++;
}

/*:218*/
#line 83 "anim.w"

}
}

/*:214*//*228:*/
#line 7 "display.w"

void DisplayLong(long n,int x,int y){
register SpriteDefPtr sp;
int i;

sp= &spriteAttributes[sprite];
x+= 64;
for(i= 8;i>0;i--){
sp->vp= y;
sp->size= 0;
sp->cell= 0xe780+(n&0xf);
sp->hp= x;
sp->link= sprite+1;
n>>= 4;
x-= 8;
if(!(sp->hp&0x1ff))continue;
sprite++;
sp++;
}
}

/*:228*//*229:*/
#line 30 "display.w"

void DisplayShort(short n,int x,int y){
register SpriteDefPtr sp;
int i;

sp= &spriteAttributes[sprite];
x+= 32;
for(i= 4;i>0;i--){
sp->vp= y;
sp->size= 0;
sp->cell= 0xe780+(n&0xf);
sp->hp= x;
sp->link= sprite+1;
n>>= 4;
x-= 8;
if(!(sp->hp&0x1ff))continue;
sprite++;
sp++;
}
}

/*:229*/
