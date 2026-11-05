
@* Introduction.  This is the \TT\ program.  \TT\ has a fairly
straightforward outline, as one might expect.  The reset autovector sets the
stack pointer to |0x00fff800| and sends control to |main()|, with the processor
in supervisor mode.  Nothing else is known about the machine's state (except
what Motorola and Sega guarantee at power-on).

@d offsetof(t, f) ((size_t)&(((t *)0)->f))
@d TRUE 1
@d FALSE 0
@d NULL ((void *)0)
@d TIMING 1

@ @<Header files@>=
#include "logo.h"

@ Here we initialize the hardware, run the logo, initialize the game, and then
loop forever through the main state machine.

@c @<Header files@>@/
@<Hardware-specific definitions@>@/
@<Typedef declarations@>@/
@<Function prototypes@>@/
@<Global variables@>@/

void main(){
  @<Hardware initialization@>@;
  SegaLogo();
  @<Set initial values@>@;
  while(TRUE)
    mainState = fsm(mainState);
}

@ @<Function prototypes@>=
void main(void);

@ @<Global...@>=
@<Data includes@>@;
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

@ This section does basic program initialization after the machine is alive,
the logo has run, and the sound system has been initialized.

@d HeapBase ((char *)0x00ff0000)
@d HeapLength 0xf000

@<Set initial values@>=
  mainState = InitialState;
  InitHeap(HeapBase, HeapLength);

@ @<Initialize the game@>=
playerDead = FALSE;
Player1_score = 0L;
Player2_score = 0L;
currentRound = 0;

@ @<Randomizer@>=
{seed=seed*521+40001;}

@ some Genesis-specific definitions

@d VERSION              0xa10001
@d WATCHDOG             0xa14000

@d JOYUP    0x0001
@d JOYDOWN  0x0002
@d JOYLEFT  0x0004
@d JOYRIGHT 0x0008

@d VCTRLL VDPPort.control.l
@d VCTRLW VDPPort.control.w
@d VDATAW VDPPort.data.w

@d InitDMA(src, dst, bytes)
  VCTRLL = 0x93009400 + (((bytes) >> 9) & 0xff) + (((bytes) << 15) & 0xff0000);
  VCTRLL = 0x95009600 + (((src) << 15) & 0xff0000) + (((src) >> 9) & 0xff);
  VCTRLW = 0x9700 + (((src) >> 17) & 0x7f);
  VCTRLL = 0x40000080 + (((dst) << 16) & 0x3fff0000) + (((dst) >> 14) & 3);

@d SetVDPDest(addr) VCTRLL = 0x40000000 + (((addr) << 16) & 0x3fff0000) +
                             (((addr) >> 14) & 3)

@s volatile int
@s pragma int
@s dsection int

@<Hardware-specific definitions@>=

#pragma dsection .vdp

volatile struct {
        union {
                short w;
                long l;
        } data;
        union {
                short w;
                long l;
        } control;
        unsigned char h_count;
        unsigned char v_count;
} VDPPort = 0;

#pragma dsection .data

@*VDP layout.

@d FG                           0xc000
@d SIDEBAR                      0xd000
@d BG                           0xe000
@d SPRITE_ATTRIBUTES            0xd000
@d HSCROLL                      0xd400
@d SPRITE_ATTRIBUTE_VDP_ADDRESS SPRITE_ATTRIBUTES
@d H_SCROLL_VDP_ADDRESS         HSCROLL
@d FG_CELLS                     0

