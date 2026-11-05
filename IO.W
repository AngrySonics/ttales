@* The Input/Output System.  This system is conceptually a separate,
asynchronous peripheral processor with the responsibility of providing system
I/O services.  The procedure |DoIO()| should be called in some regular fashion
(probably in the vertical blank interrupt) in order to satisfy main process
requests.

@ These are some constants for the internal use of the I/O system.

@d IOR_READ_CONTROLLERS        1
@d IOR_SEND_SPRITE_CONTROL     2
@d IOR_SEND_PALETTES           3
@d IOR_SEND_BLOCK_16           4
@d IOR_SEND_BLOCK_32           5
@d IOR_SEND_SCROLLS            6
@d IOR_SEND_A_SCROLLS          7
@d IOR_SEND_B_SCROLLS          8
@d IOR_SEND_COLUMN             9

@d IOReqSize 8
@d IOBufferCapacity 32
@d IOBufferSize (IOReqSize * IOBufferCapacity)

@ @<Typedef...@>=
typedef unsigned long ULONG;
typedef unsigned char UCHAR;

@ @<Function prototypes@>=
    void DoIO(void);

@ @<Global...@>=
short IORequestBuffer[IOBufferSize];
short IORequestPointer;
int ip;      /* i/o request buffer 'pointer' */
unsigned char bStick1;
unsigned char cStick1;
unsigned char dStick1;
unsigned char bStick2;
unsigned char cStick2;
unsigned char dStick2;

@ This is the procedure that actually performs the input and output that has
been requested and queued up.  If |TIMING| is defined |FALSE|, it will turn
color 0, palette 0 red on entry and black on exit.

@c
void DoIO(){
  short size;
  unsigned char *srcptr;
  unsigned char *dstptr;

#if TIMING
  VDPPort.control.l = 0xc0000000;
  VDPPort.data.w = 0x00f;
#endif
  while(ip != IORequestPointer){
    @<Process the I/O request:iosys@> @;
    ip = (ip + IOReqSize) % IOBufferSize;
  }
#if TIMING
  VDPPort.control.l = 0xc0000000;
  VDPPort.data.w = 0x000;
#endif
}

@ @<Process the I/O request:iosys@>=
  switch(IORequestBuffer[ip]){@/
    case IOR_READ_CONTROLLERS:
      @<Read the controllers:iosys@>@,
      break;@/
    case IOR_SEND_SPRITE_CONTROL:
      @<Send the sprite control block to the VDP:iosys@>@,
      break;@/
    case IOR_SEND_PALETTES:
      @<Send palette data to the VDP:iosys@>@,
      break;@/
    case IOR_SEND_BLOCK_16:
      @<Send block specified by 16 bit address to the VDP:iosys@>@,
      break;@/
    case IOR_SEND_BLOCK_32:
      @<Send block specified by 32 bit address to the VDP:iosys@>@,
      break;@/
    case IOR_SEND_SCROLLS:
      @<Send new scroll values for both playfields to the VDP:iosys@>@,
      break;@/
    case IOR_SEND_A_SCROLLS:
      @<Send new scroll values for playfield A to the VDP:iosys@>@,
      break;@/
    case IOR_SEND_B_SCROLLS:
      @<Send new scroll values for playfield B to the VDP:iosys@>@,
      break;@/
    case IOR_SEND_COLUMN:
      @<Send block to VDP display column:iosys@>@,
      break;@/
    default:
      break;@/
  }

@ @<Read the controllers:iosys@>=
{
  srcptr = *((unsigned char **)(IORequestBuffer+ip+1));
  ReadHWControllers();
  *srcptr++ = bStick1;
  *srcptr++ = cStick1;
  *srcptr++ = dStick1;
  *srcptr++ = bStick2;
  *srcptr++ = cStick2;
  *srcptr = dStick2;
}

@ @<Send the sprite control block to the VDP:iosys@>=
{
  srcptr = *((UCHAR **)(IORequestBuffer+ip+1));
  gemsdmastart();
  InitDMA((long)srcptr, (long)SPRITE_ATTRIBUTE_VDP_ADDRESS, 640L);
  gemsdmaend();
}

@ @<Send palette data to the VDP:iosys@>=
{
  srcptr = (UCHAR *)((*((ULONG *)(IORequestBuffer+ip+1))) >> 1);
  VDPPort.control.l = 0x93409400;    /* R19, R20 (DMA length) */
  VDPPort.control.w = 0x9500 + ((long)srcptr & 0xff);
  VDPPort.control.w = 0x9600 + (((long)srcptr & 0xff00) >> 8);
  VDPPort.control.w = 0x9700 + (((long)srcptr & 0x7f0000) >> 16);
  VDPPort.control.l = 0xc0000080;
}

@ @<Send block specified by 16 bit address to the VDP:iosys@>=
{
  srcptr = (UCHAR *)(0x00ff0000 | IORequestBuffer[ip+1]);
  dstptr = (UCHAR *)IORequestBuffer[ip+2];
  size = IORequestBuffer[ip+3];
  gemsdmastart();
  InitDMA((long)srcptr, (long)dstptr, (long)size);
  gemsdmaend();
}

@ @<Send block specified by 32 bit address to the VDP:iosys@>=
{
  srcptr = *((unsigned char **)(IORequestBuffer+ip+1));
  dstptr = (UCHAR *)IORequestBuffer[ip+3];
  size = IORequestBuffer[ip+4];
  gemsdmastart();
  InitDMA((long)srcptr, (long)dstptr, (long)size);
  gemsdmaend();
}

@ @<Send new scroll values for both playfields to the VDP:iosys@>=
{
  VDPPort.control.l = 0x40000010;
  VDPPort.data.w = IORequestBuffer[ip+1];
  VDPPort.data.w = IORequestBuffer[ip+2];
  SetVDPDest(H_SCROLL_VDP_ADDRESS);
  VDPPort.data.w = IORequestBuffer[ip+3];
  VDPPort.data.w = IORequestBuffer[ip+4];
}

@ @<Send new scroll values for playfield A to the VDP:iosys@>=
{
  VDPPort.control.l = 0x40000010;
  VDPPort.data.w = IORequestBuffer[ip+1];
  SetVDPDest(H_SCROLL_VDP_ADDRESS);
  VDPPort.data.w = IORequestBuffer[ip+2];
}

@ @<Send new scroll values for playfield B to the VDP:iosys@>=
{
  VDPPort.control.l = 0x40020010;
  VDPPort.data.w = IORequestBuffer[ip+1];
  SetVDPDest(H_SCROLL_VDP_ADDRESS+2);
  VDPPort.data.w = IORequestBuffer[ip+2];
}

@ @<Send block to VDP display column:iosys@>=
{
  srcptr = *((unsigned char **)(IORequestBuffer+ip+1));
  dstptr = (UCHAR *)IORequestBuffer[ip+3];
  VDPPort.control.w = 0x8f80;
  gemsdmastart();
  InitDMA((long)srcptr, (long)dstptr, (long)64);
  gemsdmaend();
  VDPPort.control.w = 0x8f02;
}

@* Input/Output System Client Interface.   These are the macro definitions for
the various ways to invoke the I/O system from
within a user program.  It is important to understand that these macros do not
directly cause the requested I/O to occur, they merely queue the request for
later handling.  They also do not test for buffer overflow, so the user must
assure that |IOBufferCapacity| is sufficiently large. @^Unsafe behavior@>  The
buffer is circular, so if an overflow occurs it will not crash the program, but
it will lose many requests.

@ This macro causes the I/O system to read the Genesis joypads and to write the
resulting data into the six bytes at |*addr|  The data is formatted as three
bytes for controller A, then three bytes for controller B.  The three bytes
are, first, the actual button states from the controller, with 1 indicating
that the button is depressed.  Second, the state of the controller in the
previous cycle, and third, a byte containing 1's where the raw data has a
rising edge.

@d ReadControllers(addr) {
  IORequestBuffer[IORequestPointer] = IOR_READ_CONTROLLERS;
  *((ULONG **)(IORequestBuffer+IORequestPointer+1)) = (ULONG *)(addr);
  IORequestPointer = (IORequestPointer + IOReqSize) % IOBufferSize;
  }

@ This macro causes the I/O system to send the 640 bytes at |*addr| to the VDP
location specified by the constant |SPRITE_ATTRIBUTE_VDP_ADDRESS|.

@d SendSpriteControl(addr) {
  IORequestBuffer[IORequestPointer] = IOR_SEND_SPRITE_CONTROL;
  *((ULONG **)(IORequestBuffer+IORequestPointer+1)) = (ULONG *)(addr);
  IORequestPointer = (IORequestPointer + IOReqSize) % IOBufferSize;
  }

@ This macro causes the I/O system to send the 128 bytes at |*addr| to the VDP
color ram.

@d SendPalettes(addr) {
  IORequestBuffer[IORequestPointer] = IOR_SEND_PALETTES;
  *((ULONG **)(IORequestBuffer+IORequestPointer+1)) = (ULONG *)(addr);
  IORequestPointer = (IORequestPointer + IOReqSize) % IOBufferSize;
  }

@ This macro causes the I/O system to send the |size| bytes at
|*(addr+0x00ff0000)| to the VDP location specified by |target|.

@d SendBlock16(addr, target, size) {
  IORequestBuffer[IORequestPointer] = IOR_SEND_BLOCK_16;
  IORequestBuffer[IORequestPointer+1] = ((short)((long)addr & 0xffff));
  IORequestBuffer[IORequestPointer+2] = (target);
  IORequestBuffer[IORequestPointer+3] = (size);
  IORequestPointer = (IORequestPointer + IOReqSize) % IOBufferSize;
  }

@ This macro causes the I/O system to send the |size| bytes at |*addr| to the
VDP location specified by |target|.

@d SendBlock32(addr, target, size) {
  IORequestBuffer[IORequestPointer] = IOR_SEND_BLOCK_32;
  *((ULONG **)(IORequestBuffer+IORequestPointer+1)) = (ULONG *)(addr);
  IORequestBuffer[IORequestPointer+3] = (target);
  IORequestBuffer[IORequestPointer+4] = (size);
  IORequestPointer = (IORequestPointer + IOReqSize) % IOBufferSize;
  }

@ This macro causes the I/O system to update the scrolling values for both
playfields.  It supports only single-piece scrolling of the playfield, not any
of the per-line or per-cell modes.

@d SendScrolls(ay, by, ax, bx) {
  IORequestBuffer[IORequestPointer] = IOR_SEND_SCROLLS;
  IORequestBuffer[IORequestPointer+1] = (ay);
  IORequestBuffer[IORequestPointer+2] = (by);
  IORequestBuffer[IORequestPointer+3] = (ax);
  IORequestBuffer[IORequestPointer+4] = (bx);
  IORequestPointer = (IORequestPointer + IOReqSize) % IOBufferSize;
  }

@ This macro causes the I/O system to update the scrolling values for
playfield A.  It supports only single-piece scrolling of the playfield, not any
of the per-line or per-cell modes.

@d SendAScrolls(ay, ax) {
  IORequestBuffer[IORequestPointer] = IOR_SEND_A_SCROLLS;
  IORequestBuffer[IORequestPointer+1] = (ay);
  IORequestBuffer[IORequestPointer+2] = (ax);
  IORequestPointer = (IORequestPointer + IOReqSize) % IOBufferSize;
  }

@ This macro causes the I/O system to update the scrolling values for
playfield B.  It supports only single-piece scrolling of the playfield, not any
of the per-line or per-cell modes.

@d SendBScrolls(by, bx) {
  IORequestBuffer[IORequestPointer] = IOR_SEND_B_SCROLLS;
  IORequestBuffer[IORequestPointer+1] = (by);
  IORequestBuffer[IORequestPointer+2] = (bx);
  IORequestPointer = (IORequestPointer + IOReqSize) % IOBufferSize;
  }

@ This macro causes the I/O system to update a column of VDP display memory.

@d SendColumn(addr, target) {
  IORequestBuffer[IORequestPointer] = IOR_SEND_COLUMN;
  *((ULONG **)(IORequestBuffer+IORequestPointer+1)) = (ULONG *)(addr);
  IORequestBuffer[IORequestPointer+3] = (target);
  IORequestPointer = (IORequestPointer + IOReqSize) % IOBufferSize;
  }
