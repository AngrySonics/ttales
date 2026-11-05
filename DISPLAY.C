/*2:*/
#line 7 "display.w"

void DisplayLong(long n,int x,int y){
register SpriteDefPtr sp;
int i;

sp= &spriteAttributes[sprite];
x+= 64;
for(i= 8;i>0;i--){
sp->vp= y;
sp->size= 0;
sp->cell= 0xe780+(n&0xf);
sp->hp= x;
sp->link= sprite+1;
n>>= 4;
x-= 8;
if(!(sp->hp&0x1ff))continue;
sprite++;
sp++;
}
}

/*:2*//*3:*/
#line 30 "display.w"

void DisplayShort(short n,int x,int y){
register SpriteDefPtr sp;
int i;

sp= &spriteAttributes[sprite];
x+= 32;
for(i= 4;i>0;i--){
sp->vp= y;
sp->size= 0;
sp->cell= 0xe780+(n&0xf);
sp->hp= x;
sp->link= sprite+1;
n>>= 4;
x-= 8;
if(!(sp->hp&0x1ff))continue;
sprite++;
sp++;
}
}

/*:3*/
