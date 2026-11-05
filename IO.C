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
/*6:*/
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
/*7:*/
#line 65 "io.w"

switch(IORequestBuffer[ip]){
case IOR_READ_CONTROLLERS:
/*8:*/
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

/*:8*/
#line 68 "io.w"

break;
case IOR_SEND_SPRITE_CONTROL:
/*9:*/
#line 110 "io.w"

{
srcptr= *((UCHAR**)(IORequestBuffer+ip+1));
gemsdmastart();
InitDMA((long)srcptr,(long)SPRITE_ATTRIBUTE_VDP_ADDRESS,640L);
gemsdmaend();
}

/*:9*/
#line 71 "io.w"

break;
case IOR_SEND_PALETTES:
/*10:*/
#line 118 "io.w"

{
srcptr= (UCHAR*)((*((ULONG*)(IORequestBuffer+ip+1)))>>1);
VDPPort.control.l= 0x93409400;
VDPPort.control.w= 0x9500+((long)srcptr&0xff);
VDPPort.control.w= 0x9600+(((long)srcptr&0xff00)>>8);
VDPPort.control.w= 0x9700+(((long)srcptr&0x7f0000)>>16);
VDPPort.control.l= 0xc0000080;
}

/*:10*/
#line 74 "io.w"

break;
case IOR_SEND_BLOCK_16:
/*11:*/
#line 128 "io.w"

{
srcptr= (UCHAR*)(0x00ff0000|IORequestBuffer[ip+1]);
dstptr= (UCHAR*)IORequestBuffer[ip+2];
size= IORequestBuffer[ip+3];
gemsdmastart();
InitDMA((long)srcptr,(long)dstptr,(long)size);
gemsdmaend();
}

/*:11*/
#line 77 "io.w"

break;
case IOR_SEND_BLOCK_32:
/*12:*/
#line 138 "io.w"

{
srcptr= *((unsigned char**)(IORequestBuffer+ip+1));
dstptr= (UCHAR*)IORequestBuffer[ip+3];
size= IORequestBuffer[ip+4];
gemsdmastart();
InitDMA((long)srcptr,(long)dstptr,(long)size);
gemsdmaend();
}

/*:12*/
#line 80 "io.w"

break;
case IOR_SEND_SCROLLS:
/*13:*/
#line 148 "io.w"

{
VDPPort.control.l= 0x40000010;
VDPPort.data.w= IORequestBuffer[ip+1];
VDPPort.data.w= IORequestBuffer[ip+2];
SetVDPDest(H_SCROLL_VDP_ADDRESS);
VDPPort.data.w= IORequestBuffer[ip+3];
VDPPort.data.w= IORequestBuffer[ip+4];
}

/*:13*/
#line 83 "io.w"

break;
case IOR_SEND_A_SCROLLS:
/*14:*/
#line 158 "io.w"

{
VDPPort.control.l= 0x40000010;
VDPPort.data.w= IORequestBuffer[ip+1];
SetVDPDest(H_SCROLL_VDP_ADDRESS);
VDPPort.data.w= IORequestBuffer[ip+2];
}

/*:14*/
#line 86 "io.w"

break;
case IOR_SEND_B_SCROLLS:
/*15:*/
#line 166 "io.w"

{
VDPPort.control.l= 0x40020010;
VDPPort.data.w= IORequestBuffer[ip+1];
SetVDPDest(H_SCROLL_VDP_ADDRESS+2);
VDPPort.data.w= IORequestBuffer[ip+2];
}

/*:15*/
#line 89 "io.w"

break;
case IOR_SEND_COLUMN:
/*16:*/
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

/*:16*/
#line 92 "io.w"

break;
default:
break;
}

/*:7*/
#line 56 "io.w"

ip= (ip+IOReqSize)%IOBufferSize;
}
#if TIMING
VDPPort.control.l= 0xc0000000;
VDPPort.data.w= 0x000;
#endif
}

/*:6*/
