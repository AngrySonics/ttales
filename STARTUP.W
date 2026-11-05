@* System Initialization and Interrupt Handling.

This section contains the data required in the first 512 bytes of the
Genesis' address space.  The first half contains the coldstart and exception
vectors, and the second half is Sega's standard signature record.

@c
#pragma dsection .vectors

VoidFuncPtr vectors[] = {
    (VoidFuncPtr)0xfffff800,     /*  0 initial supervisor stack pointer */
    main,           /*  1 initial program counter */
    ErrorHandler,   /*  2 Bus error */
    ErrorHandler,   /*  3 Address error */
    ErrorHandler,   /*  4 Illegal instruction */
    ErrorHandler,   /*  5 Division by zero */
    ErrorHandler,   /*  6 CHK instruction */
    ErrorHandler,   /*  7 TRAPV instruction */
    ErrorHandler,   /*  8 Privilege violation */
    ErrorHandler,   /*  9 Trace */
    ErrorHandler,   /* 10 Line A emulator */
    ErrorHandler,   /* 11 Line F emulator */
    ErrorHandler,   /* 12 Reserved */
    ErrorHandler,   /* 13 Reserved */
    ErrorHandler,   /* 14 Reserved */
    ErrorHandler,   /* 15 Uninitialized interrupt */
    ErrorHandler,   /* 16 Reserved */
    ErrorHandler,   /* 17 Reserved */
    ErrorHandler,   /* 18 Reserved */
    ErrorHandler,   /* 19 Reserved */
    ErrorHandler,   /* 20 Reserved */
    ErrorHandler,   /* 21 Reserved */
    ErrorHandler,   /* 22 Reserved */
    ErrorHandler,   /* 23 Reserved */
    ErrorHandler,   /* 24 Spurious interrupts */
    ErrorHandler,   /* 25 Level 1 autovector */
    ErrorHandler,   /* 26 Level 2 autovector */
    ErrorHandler,   /* 27 Level 3 autovector */
    HBLHandler,     /* 28 Level 4 autovector */
    ErrorHandler,   /* 29 Level 5 autovector */
    VBLHandler,     /* 30 Level 6 autovector */
    ErrorHandler,   /* 31 Level 7 autovector */
    ErrorHandler,   /* 32 Reserved */
    ErrorHandler,   /* 33 Reserved */
    ErrorHandler,   /* 34 Reserved */
    ErrorHandler,   /* 35 Reserved */
    ErrorHandler,   /* 36 Reserved */
    ErrorHandler,   /* 37 Reserved */
    ErrorHandler,   /* 38 Reserved */
    ErrorHandler,   /* 39 Reserved */
    ErrorHandler,   /* 40 Reserved */
    ErrorHandler,   /* 41 Reserved */
    ErrorHandler,   /* 42 Reserved */
    ErrorHandler,   /* 43 Reserved */
    ErrorHandler,   /* 44 Reserved */
    ErrorHandler,   /* 45 Reserved */
    ErrorHandler,   /* 46 Reserved */
    ErrorHandler,   /* 47 Reserved */
    ErrorHandler,   /* 48 Reserved */
    ErrorHandler,   /* 49 Reserved */
    ErrorHandler,   /* 50 Reserved */
    ErrorHandler,   /* 51 Reserved */
    ErrorHandler,   /* 52 Reserved */
    ErrorHandler,   /* 53 Reserved */
    ErrorHandler,   /* 54 Reserved */
    ErrorHandler,   /* 55 Reserved */
    ErrorHandler,   /* 56 Reserved */
    ErrorHandler,   /* 57 Reserved */
    ErrorHandler,   /* 58 Reserved */
    ErrorHandler,   /* 59 Reserved */
    ErrorHandler,   /* 60 Reserved */
    ErrorHandler,   /* 61 Reserved */
    ErrorHandler,   /* 62 Reserved */
    ErrorHandler,   /* 63 Reserved */
};

#pragma dsection .coding
char codingblock1[] = @/
  "SEGA MEGA DRIVE " @/
  "(C)SEGA 1993 AUG" @/
  "TREASURE TALES  " @/
  "                " @/
  "                " @/
  "TREASURE TALES  " @/
  "                " @/
  "                " @/
  "GM 00001014-00\0";
char codingblock3[] =@/
  "J              ";
long codingblock4[] = {
  0x00000000,
  0x0007ffff,
  0x00ff0000,
  0x00ffffff };
char codingblock5[] =@/
  "                "@/
  "                "@/
  "                "@/
  "                "@/
  "JUE            ";


#pragma dsection .text

@ This is the system's main vertical blank interrupt handler.  In its present
life it just bumps the system timer, sets the flag to indicate that it has run,
and invokes the I/O system.  The startup code {\it must} be sure to have all
the necessary initialization for the I/O system before interrupts are enabled.
@^Unsafe behavior@>

  The Sierra C compiler (which we are compiling this with)
doesn't support any special syntax for procedures that are invoked by processor
exceptions, so we need to maintain stack coherence and provide an RTE by hand.
Fortunately, the compiler does provide a pass-through assembly language
construct.

@s asm while

@c
void VBLHandler(){
  asm(" movem.l a0-a6/d0-d7,-(sp)",4);
  tickCounter++;
  vblFlag = 1;
  DoIO();
  asm(" movem.l (sp)+,a0-a6/d0-d7",4);
  asm(" unlk a6");
  asm(" rte",2);
}

@ This is the system horizontal interrupt handler.  Its only function at
present is to set the processor interrupt mask to prevent itself from being
invoked again.

@c
void HBLHandler(){
  asm(" and.w #$f0ff,(sp)",4);
#if 0
  asm(" or.w #$0500,(sp)",4);
#endif
  asm(" unlk a6");
  asm(" rte",2);
}

@ This is the system error handler.  It doesn't do much.

@c
void ErrorHandler(){
  while(1);
}

@ @<Global...@>=
volatile long tickCounter;
volatile int vblFlag;

@ @<Function prototypes@>=
void VBLHandler(void);
void HBLHandler(void);
void ErrorHandler(void);

@ Here are some constants to ease working with the VDP
@d VRAMWR   0x40000000
@d VRAMRD   0x00000000
@d VSRAMWR  0x40000010
@d VSRAMRD  0x00000010
@d CRAMWR   0xc0000000
@d CRAMRD   0x00000020


@ @<Initialize VDP registers@>=
{
int i;

  for(i = 0; i < 19; i++){
    VDPPort.control.w = vdpRegisters[i];
  }
}

@ These are the initial settings for the VDP registers,

@<Global...@>=
short vdpRegisters[] = {
  0x8004,   /* 0x8014, */
  0x8174,
  0x8200+(FG>>10),
  0x8300+(SIDEBAR>>10),
  0x8400+(BG>>13),
  0x8500+(SPRITE_ATTRIBUTES >> 9),
  0x8600,
  0x8700,
  0x8800,
  0x8900,
  0x8a00,
  0x8b08, /* 0x8b00, */
  0x8c81,
  0x8d00+(HSCROLL>>10),
  0x8e00,
  0x8f02,
  0x9001,
  0x9100,
  0x9200,
};


@ @<Initialize the VDP@>=
  @<Initialize VDP registers@>@;
  @<Clear VRAM@>@;
  @<Clear color RAM@>@;
  @<Clear vertical scroll RAM@>@;

@ @<Clear work RAM@>=
{
register int i;
  for(i = 0; i < 16384; i++){
    ((long *)0x00ff0000)[i] = 0;
  }
}

@ @<Clear VRAM@>=
{
register int i;
  VDPPort.control.l = VRAMWR;
  for(i = 0; i < 32768; i++){
    VDPPort.data.w = 0;
  }
}

@ @<Clear color RAM@>=
{
register int i;
  VDPPort.control.l = CRAMWR;
  for(i = 0; i < 64; i++){
    VDPPort.data.w = 0;
  }
}

@ @<Clear vertical scroll RAM@>=
{
register int i;
  VDPPort.control.l = VSRAMWR;
  for(i = 0; i < 40; i++){
    VDPPort.data.w = 0;
  }
}

@ @<Hardware initialization@>=
  asm(" move.w #$2700,SR",4);    /* Disable interrupts */
  if(*(unsigned char *)VERSION & 0x0f)@/
    *((unsigned long *)WATCHDOG) = 0x53454741;   /* Make the extortion circuit happy */
  @<Initialize the controller ports@>@;
  @<Clear work RAM@>@;
  @<Initialize the VDP@>@;
  gemsinit(patchbank, envbank, seqbank, sampbank);
  asm(" move.w #$2000,SR");     /* Enable interrupts */

@ @<Initialize the controller ports@>=
  asm(" moveq #$40,d0");
  asm(" move.b d0,$a10009");        /* JOY1DDR */
  asm(" move.b d0,$a1000b");        /* JOY2DDR */
  asm(" move.b #$9f,$a1000d");       /* COMDDR */
  asm(" move.b #$7f,$a10007");      /* COMPORT */

@ This routine causes the processor to halt until an interrupt is received, and
then to check whether it was VBlank.

@c
void WaitTOF(){
#if TIMING
    VCTRLL=0xc0000000;
    VDATAW=0x000;
#endif
    vblFlag = 0;
    while(!vblFlag)
      asm(" stop #$2500",4);
#if TIMING
    VCTRLL=0xc0000000;
    VDATAW=0x888;
#endif
}

@ This routine reads the hardware controller ports and puts the results in
|bStick|, |cStick|, and |dStick|.

@c
void ReadHWControllers(){
  asm(" move.w  #$2700,SR",4);
  gemsholdz80();
  asm(" lea $a10003,a0");        /* JOY1PORT */
  @<Read one controller@>@;
  asm(" move.b d0,_bStick1");
  asm(" lea $a10005,a0");        /* JOY2PORT */
  @<Read one controller@>@;
  asm(" move.b d0,_bStick2");
  asm(" move.w #$2000,SR");
  gemsreleasez80();

  dStick1 = (bStick1 ^ cStick1) & bStick1;
  cStick1 = bStick1;
  dStick2 = (bStick2 ^ cStick2) & bStick2;
  cStick2 = bStick2;
}

@ @<Read one controller@>=
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

@ @<Function prototypes@>=
void WaitTOF(void);
void SegaLogo(void);
void ReadHWControllers(void);

@* The SEGA logo.
@d LOGO1 (FG+0x61c+0x0000)
@d LOGO2 (FG+0x61c+0x0080)
@d LOGO3 (FG+0x61c+0x0100)
@d LOGO4 (FG+0x61c+0x0180)

@c
void SegaLogo(){
short *palette;
int i, j;

  SendBlock32(logoData, FG_CELLS+32, 1600);
  palette = AllocMem(128);
  for(i = logoColors[0]; i < logoColors[1]; i++){
    palette[i] = logoColors[i+2];
  }
  SendBlock32(logoMap, LOGO1, 24);
  SendBlock32(logoMap+12, LOGO2, 24);
  SendBlock32(logoMap+24, LOGO3, 24);
  SendBlock32(logoMap+36, LOGO4, 24);
  WaitTOF();
  FadeIn(palette, 45);
  for(i = 0; i < 31; i++)
    WaitTOF();
  for(i = 20; i > 0; i--){
    for(j = 0; j < 11; j++){
      palette[2+j] = logoColors[4+i+j];
    }
    SendPalettes(palette);
    WaitTOF();
    WaitTOF();
    WaitTOF();
    WaitTOF();
  }
  for(i = 0; i < 27; i++)
    WaitTOF();
  FadeOut(palette,45);
  FreeMem(palette);
}

