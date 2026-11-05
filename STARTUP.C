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

/*1:*/
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

/*:1*//*2:*/
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

/*:2*//*3:*/
#line 134 "startup.w"

void HBLHandler(){
asm(" and.w #$f0ff,(sp)",4);
#if 0
asm(" or.w #$0500,(sp)",4);
#endif
asm(" unlk a6");
asm(" rte",2);
}

/*:3*//*4:*/
#line 146 "startup.w"

void ErrorHandler(){
while(1);
}

/*:4*//*17:*/
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

/*:17*//*18:*/
#line 283 "startup.w"

void ReadHWControllers(){
asm(" move.w  #$2700,SR",4);
gemsholdz80();
asm(" lea $a10003,a0");
/*19:*/
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

/*:19*/
#line 288 "startup.w"

asm(" move.b d0,_bStick1");
asm(" lea $a10005,a0");
/*19:*/
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

/*:19*/
#line 291 "startup.w"

asm(" move.b d0,_bStick2");
asm(" move.w #$2000,SR");
gemsreleasez80();

dStick1= (bStick1^cStick1)&bStick1;
cStick1= bStick1;
dStick2= (bStick2^cStick2)&bStick2;
cStick2= bStick2;
}

/*:18*//*21:*/
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
/*:21*/
