#define offsetof(t,f)((size_t)&(((t*)0)->f))
#define TRUE 1
#define FALSE 0
#define NULL ((void*)0)
#define TIMING 0 \

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
#define FG_CELLS 0
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


#line 22 "ttmain.w"

/*4:*/
#line 34 "ttmain.w"

void main(void);

/*:4*/
#line 23 "ttmain.w"

/*5:*/
#line 37 "ttmain.w"


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

/*:5*/
#line 24 "ttmain.w"


void main(){

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

/*:3*/
