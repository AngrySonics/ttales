@* Debugging---Display Routines.  Here are some routines to display data on the
screen.  Numeric data is displayed using a font stored at location |0xf000| in
the VDP, and in palette 3, color 1.

@ This routine displays a |long| at sprite location |x|, |y|.

@c
void DisplayLong(long n, int x, int y){
register SpriteDefPtr sp;
int i;

  sp = &spriteAttributes[sprite];
  x += 64;
  for(i = 8; i > 0; i--){
    sp->vp = y;
    sp->size = 0;
    sp->cell = 0xe780+(n & 0xf);
    sp->hp = x;
    sp->link = sprite + 1;
    n >>= 4;
    x -= 8;
    if(!(sp->hp & 0x1ff)) continue;     /* don't let it sit at 0 */
    sprite++;
    sp++;
  }
}

@ This routine displays a |short| at sprite location |x|, |y|.

@c
void DisplayShort(short n, int x, int y){
register SpriteDefPtr sp;
int i;

  sp = &spriteAttributes[sprite];
  x += 32;
  for(i = 4; i > 0; i--){
    sp->vp = y;
    sp->size = 0;
    sp->cell = 0xe780+(n & 0xf);
    sp->hp = x;
    sp->link = sprite + 1;
    n >>= 4;
    x -= 8;
    if(!(sp->hp & 0x1ff)) continue;     /* don't let it sit at 0 */
    sprite++;
    sp++;
  }
}

@ @<Function prototypes@>=
void DisplayShort(short n, int x, int y);@/
void DisplayLong(long n, int x, int y);@/
