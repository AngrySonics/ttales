OBJ=    ttales.o gems.o

DRV=    c:
SIERRA= $(DRV)\sierra\bin
WDIR=   $(DRV)\ttales
CDIR=   $(DRV)\ttales
INCDIR= $(DRV)\ttales
ASMDIR= $(DRV)\ttales
ARTDIR= $(DRV)\ttales
OBJDIR= $(DRV)\ttales
#TMPDIR= d:\
TMPDIR= c:\

#LIST=   -l
LIST=   -p80 -w132

.PATH.w=$(WDIR)
.PATH.c=$(CDIR)
.PATH.h=$(INCDIR)
.PATH.s=$(ASMDIR)
.PATH.i=$(ASMDIR)
.PATH.o=$(OBJDIR)
.PATH.asm=$(ASMDIR)
.PATH.dgt=$(ARTDIR)

.w.c:
        =:ctangle $(WDIR)\$[r,$*].w

.w.s:
        =:ctangle $(WDIR)\$[r,$*].w
        =:$(SIERRA)\com68 $(CDIR)\$[r,$*].c $(TMPDIR)\$[r,$*].s -I$(INCDIR) -Q -fC3 -l -OAa2f0l4p1r2x1 -g1
        del $(CDIR)\$[r,$*].c

.w.o:
        =:ctangle $(WDIR)\$[r,$*].w
        =:$(SIERRA)\com68 $(CDIR)\$[r,$*].c $(TMPDIR)\$[r,$*].s -I$(INCDIR) -Q -fC3 -l -OAa2f0l4p1r2x1 -g1
        =:$(SIERRA)\asm68 $(LIST) -Q -k $(TMPDIR)\$[r,$*].s -o$(OBJDIR)\$[r,$*].o
        del $(TMPDIR)\$[r,$*].s

.c.o:
        =:$(SIERRA)\com68 $(CDIR)\$[r,$*].c $(TMPDIR)\$[r,$*].s -I$(INCDIR) -Q -fC3 -l -OAa2f0l4p1r2x1 -g1
        =:$(SIERRA)\asm68 $(LIST) -Q -k $(TMPDIR)\$[r,$*].s -o$(OBJDIR)\$[r,$*].o
        del $(TMPDIR)\$[r,$*].s

.s.o:
        =:$(SIERRA)\asm68 $(LIST) -Q -k $(ASMDIR)\$[r,$*].s -o$(OBJDIR)\$[r,$*].o

.c.s:
        =:$(SIERRA)\com68 $(CDIR)\$[r,$*].c $(ASMDIR)\$[r,$*].s -I$(INCDIR) -Q -fC3 -l -OAa2f0l4p1r2x1 -g1

.w.dvi:
        =:cweave $(CDIR)\$[r,$*].w
        =:tex $[r,$*].tex
        del $[r,$*].toc
        del $[r,$*].log
        del $[r,$*].tex

paper:  ttales.dvi
        dvi2ps -n ttales.dvi
        del ttales.dvi

all:    tt loadall

rom:    tt.out
        =:$(SIERRA)\sldr -S -t bb.out bb.s19
        =:s2bin bb.s19 bb.bin

loadall:
        segaload tt.out

tt:     tt.out

tt.out: $(OBJ)
        =:$(SIERRA)\link68 -i < <
$**
-lc
-o $@
-m
MEMORY {
        rom:    ORG(0) LEN(0x080000)
        ram:    ORG(0x00fff800) LEN(0x000800)
}
SECTIONS {
        .vectors: {} > rom
        .coding: {} > rom
        .text: {} > rom
        .data: {} > rom
        .bss: {} > ram
        .vdp: ORG(0xc00000) DSECT {}
}
<

ttales.o:       [ \
                ttales.w \
                mmgr.w \
                io.w \
                startup.w \
                utils.w \
                path.w \
                expand.w \
                art.w \
                ttworld.w \
                ttmain.w \
                fsm.w \
                player.w \
                display.w \
                anim.w \
                logo.h \
                l1path.h \
                miles.h \
                ]

gems.o:         [ \
                gems.asm \
                z80.asm \
                pbank.asm \
                mbank.asm \
                sbank.asm \
                dbank.asm \
                ]
        =:$(SIERRA)\asm68k $(LIST) -Q -k $(ASMDIR)\$[r,$*].asm -o$(OBJDIR)\$[r,$*].o

