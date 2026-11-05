
@* Data Decompression.  This does a decompression based on an algorithm
developed by Mark Cerny and modified by Scott Chandler.  Compression is done by
lz.exe.  The expansion is described by:

$1+$ the next byte

$00+ 1$ bit $(=0 => 2$ byte run, $=1 => 3$ byte run$)$

$01+ 3$ bits high order offset$+1$ byte low order offset$+11+1$ byte count

$01+ 3$ bits high order offset$+1$byte low order offset$+2$ bits $(count-3)$

$01000+$zero byte $+ 11 +$ zero byte$ =>$ end

$01000+$zero byte $+ 11 +$ byte $= 1 => 4k$ break, eat and emit nothing

@c
int ExpandLZ(unsigned char *in, unsigned char *out){
unsigned char *bytes;
unsigned char *temp;
unsigned long shifter;
int offset;
int count;
int shift_count = 0;
int done = 0;

  @<Find the byte stream and the bit stream@>@;
  @<Preload the bit stream shifter@>@;
  while(!done){
    if(0x80000000 & shifter){
      @<Shift the bit stream one place@>@;
      @<Send out the next byte@>@;
    } else {
      @<Shift the bit stream one place@>@;
      if(0x80000000 & shifter)
        @<Repeat many bytes@>@;
      else
        @<Repeat two or three bytes@>@;
    }
  }
}

@ @<Repeat two or three bytes@>=
{
  @<Shift the bit stream one place@>@;
  temp = out - *bytes++;
  if(0x80000000 & shifter){
    @<Send out the byte at |*temp|@>@;
  }
  @<Send out the byte at |*temp|@>@;
  @<Send out the byte at |*temp|@>@;
  @<Shift the bit stream one place@>@;
}

@ @<Repeat many bytes@>=
{
  @<Shift the bit stream one place@>@;
  offset = (shifter & 0xe0000000) >> 21;
  @<Shift the bit stream three places@>@;
  offset += *bytes++;
  switch(shifter & 0xc0000000){
    case 0x00000000:
      count = 3;
      break;
    case 0x40000000:
      count = 4;
      break;
    case 0x80000000:
      count = 5;
      break;
    case 0xc0000000:
      count = *bytes++;
      if((count == 0) && (offset == 0)) done = 1;
      if((count == 1) && (offset == 0)) count = 0;
      break;
  }
  @<Shift the bit stream two places@>@;
  temp = out - offset;
  while(count--) @<Send out the byte at |*temp|@>@;
}

@ @<Shift the bit stream one place@>=
  shifter <<= 1;
  shift_count++;
  if(shift_count==8){
    shifter |= *in++;
    shift_count=0;
  }

@ @<Shift the bit stream two places@>=
  @<Shift the bit stream one place@>@;
  @<Shift the bit stream one place@>@;

@ @<Shift the bit stream three places@>=
  @<Shift the bit stream one place@>@;
  @<Shift the bit stream one place@>@;
  @<Shift the bit stream one place@>@;

@ @<Send out the next byte@>=
  *out++ = *bytes++;

@ @<Send out the byte at |*temp|@>=
  *out++ = *temp++;

@ @<Find the byte stream and the bit stream@>=
  bytes = in + *(unsigned short *)in;
  bytes += 2;
  in += 2;

@ @<Preload the bit stream shifter@>=
  shifter = *(unsigned long *)in;
  in += 4;
