
@ @s AnimState int
@s AnimStatePtr int

@<Typedef...@>=
typedef struct ans {
    unsigned short *frame;
    char time;
    char flags;
    struct ans * next;
}AnimState, *AnimStatePtr;

@ Here is a whole bunch of data concerning creature animation

@<Global...@>=
AnimState MilesStandEast[] = {
  {milesshape, 10, 0, &MilesStandEast[0]},@/
  {wierdmilesshape,  2, 0, &MilesStandEast[0]}@/
};@#

unsigned long *CompressedDataPointers[] = {
  NULL@/
};@#

int CreatureShapeLength[] = {
  0@/
};@#

@ @c
void DoAnimFlags(char f, CreaturePtr t){
AnimStatePtr a;

  switch(f){
    case 0:
      break;
    default:
      break;
  }
}

@ @c
void AnimateCreature(CreaturePtr t){
register AnimStatePtr a;
  if(!(t->anim_time--)){
    a = t->anim_next;
    t->anim_time = a->time;
    t->Frame = a->frame;
    t->anim_next = a->next;
    DoAnimFlags(a->flags, t);
  }
}

@ This procedure decompresses a block of compressed data indexed by |a|
(presumably a creature's graphics) and DMAs it to VDP location |b|.  It uses an
allocated intermediate decompression buffer.

@c
int LoadCreature(int a, int b){
  if(a > 1){
    unsigned char *buffer = AllocMem(CreatureShapeLength[a]*32);
    ExpandLZ((unsigned char *)CompressedDataPointers[a], buffer);
    SendBlock32(buffer, b, CreatureShapeLength[a]*32);
    WaitTOF();
    FreeMem(buffer);
    return CreatureShapeLength[a];
  }
  return 0;
}

@ This routine draws a creature's sprites

@c
void DrawCreatures(CreaturePtr c){
short ty, tx;
short n, y;
register short *st;
register SpriteDefPtr sp;

  sp = &spriteAttributes[sprite];
  @<Determine the shape's y position@>@;
  if((ty > 32) && (ty < 380)){
    @<Determine the shape's x position@>@;
    @<Set up attributes for all the sprites in the shape@>@;
  }
}

@ @<Terminate the sprite list@>=
  spriteAttributes[sprite-1].link = 0;

@ @<Determine the shape's x position@>=
  tx = (8 *(c->xPosition*4 + c->yPosition)) - screenScrollX + 128;
  tx += c->xOffset/256;
  if(c == currentPlayer)
    playerX = tx;

@ @<Determine the shape's y position@>=
  ty = (yMax - (2 * c->yPosition +
       pathMap[mapWidth * c->yPosition + c->xPosition].elevation)) * 8 -
         screenScrollY + 135;
  ty -= c->yOffset/256;
  if(c == currentPlayer)
    playerY = ty;

@ @<Set up attributes for all the sprites in the shape@>=
  n = 3;
  st = (short *)c->Frame;
  tx -= st[1];  /* horizontal registration */
  ty -= st[2];  /* vertical registration */
  for(y = 0; y < st[0]; y++){
    sp->vp = ty + st[n++];
    sp->size = st[n++];
    sp->cell = c->chBase + st[n++];
    sp->hp = tx + st[n++];
    sp->link = sprite + 1;
    if(!(sp->hp & 0x1ff)) continue;     /* don't let it sit at 0 */
    sprite++;
    sp++;
  }

@ @<Function prototypes@>=
void DrawCreatures(CreaturePtr c);@/
void AnimateCreature(CreaturePtr t);@/

@ @<Data includes@>=
#include "miles.h"

