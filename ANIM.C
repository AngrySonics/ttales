/*3:*/
#line 29 "anim.w"

void DoAnimFlags(char f,CreaturePtr t){
AnimStatePtr a;

switch(f){
case 0:
break;
default:
break;
}
}

/*:3*//*4:*/
#line 41 "anim.w"

void AnimateCreature(CreaturePtr t){
register AnimStatePtr a;
if(!(t->anim_time--)){
a= t->anim_next;
t->anim_time= a->time;
t->Frame= a->frame;
t->anim_next= a->next;
DoAnimFlags(a->flags,t);
}
}

/*:4*//*5:*/
#line 57 "anim.w"

int LoadCreature(int a,int b){
if(a>1){
unsigned char*buffer= AllocMem(CreatureShapeLength[a]*32);
ExpandLZ((unsigned char*)CompressedDataPointers[a],buffer);
SendBlock32(buffer,b,CreatureShapeLength[a]*32);
WaitTOF();
FreeMem(buffer);
return CreatureShapeLength[a];
}
return 0;
}

/*:5*//*6:*/
#line 72 "anim.w"

void DrawCreatures(CreaturePtr c){
short ty,tx;
short n,y;
register short*st;
register SpriteDefPtr sp;

sp= &spriteAttributes[sprite];
/*9:*/
#line 96 "anim.w"

ty= (yMax-(2*c->yPosition+
pathMap[mapWidth*c->yPosition+c->xPosition].elevation))*8-
screenScrollY+135;
ty-= c->yOffset/256;
if(c==currentPlayer)
playerY= ty;

/*:9*/
#line 80 "anim.w"

if((ty>32)&&(ty<380)){
/*8:*/
#line 90 "anim.w"

tx= (8*(c->xPosition*4+c->yPosition))-screenScrollX+128;
tx+= c->xOffset/256;
if(c==currentPlayer)
playerX= tx;

/*:8*/
#line 82 "anim.w"

/*10:*/
#line 104 "anim.w"

n= 3;
st= (short*)c->Frame;
tx-= st[1];
ty-= st[2];
for(y= 0;y<st[0];y++){
sp->vp= ty+st[n++];
sp->size= st[n++];
sp->cell= c->chBase+st[n++];
sp->hp= tx+st[n++];
sp->link= sprite+1;
if(!(sp->hp&0x1ff))continue;
sprite++;
sp++;
}

/*:10*/
#line 83 "anim.w"

}
}

/*:6*/
