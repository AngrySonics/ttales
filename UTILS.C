/*2:*/
#line 9 "utils.w"

void InterpolateColor(short target,short time,short duration,short*color){
short dr,dg,db;
short tr,tg,tb;
short r,g,b;
int i;

r= *color&0x00e;
g= (*color&0x0e0)>>4;
b= (*color&0xe00)>>8;
tr= target&0x00e;
tg= (target&0x0e0)>>4;
tb= (target&0xe00)>>8;
dr= r-tr+1;
dg= g-tg+1;
db= b-tb+1;
r= tr+(dr*time)/duration;
g= tg+(dg*time)/duration;
b= tb+(db*time)/duration;
*color= (r&0x00e)|((g&0x00e)<<4)|((b&0x00e)<<8);
}

/*:2*//*3:*/
#line 34 "utils.w"

void InterpolatePalette(short target,short time,short duration,short*palette){
int i;

for(i= 0;i<16;i++){
InterpolateColor(target,time,duration,&palette[i]);
}
}

/*:3*//*4:*/
#line 46 "utils.w"

void InterpolateFullPalette(short target,short time,short duration,short*palette){
int i;

for(i= 0;i<64;i++){
InterpolateColor(target,time,duration,&palette[i]);
}
}

/*:4*//*5:*/
#line 58 "utils.w"

void Interpolate2Palettes(short*target,short time,short duration,short*palette){
int i;

for(i= 0;i<16;i++){
InterpolateColor(target[i],time,duration,&palette[i]);
}
}

/*:5*//*6:*/
#line 70 "utils.w"

void Interpolate2FullPalettes(short*target,short time,short duration,short*palette){
int i;

for(i= 0;i<64;i++){
InterpolateColor(target[i],time,duration,&palette[i]);
}
}

/*:6*//*7:*/
#line 82 "utils.w"

void FadeIn(short*palette,short time){
int i,j;
short workpal[64];

for(i= 1;i<=time;i++){
for(j= 0;j<64;j++){
workpal[j]= palette[j];
}
InterpolateFullPalette(0,i,time,workpal);
SendPalettes(workpal);
WaitTOF();
}
}

/*:7*//*8:*/
#line 100 "utils.w"

void FadeOut(short*palette,short time){
int i,j;
short workpal[64];

for(i= time-1;i>=0;i--){
for(j= 0;j<64;j++){
workpal[j]= palette[j];
}
InterpolateFullPalette(0,i,time,&workpal);
SendPalettes(workpal);
WaitTOF();
}
}

/*:8*/
