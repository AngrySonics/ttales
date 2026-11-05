/*1:*/
#line 18 "expand.w"

int ExpandLZ(unsigned char*in,unsigned char*out){
unsigned char*bytes;
unsigned char*temp;
unsigned long shifter;
int offset;
int count;
int shift_count= 0;
int done= 0;

/*9:*/
#line 106 "expand.w"

bytes= in+*(unsigned short*)in;
bytes+= 2;
in+= 2;

/*:9*/
#line 28 "expand.w"

/*10:*/
#line 111 "expand.w"

shifter= *(unsigned long*)in;
in+= 4;/*:10*/
#line 29 "expand.w"

while(!done){
if(0x80000000&shifter){
/*4:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:4*/
#line 32 "expand.w"

/*7:*/
#line 100 "expand.w"

*out++= *bytes++;

/*:7*/
#line 33 "expand.w"

}else{
/*4:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:4*/
#line 35 "expand.w"

if(0x80000000&shifter)
/*3:*/
#line 56 "expand.w"

{
/*4:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:4*/
#line 58 "expand.w"

offset= (shifter&0xe0000000)>>21;
/*6:*/
#line 95 "expand.w"

/*4:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:4*/
#line 96 "expand.w"

/*4:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:4*/
#line 97 "expand.w"

/*4:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:4*/
#line 98 "expand.w"


/*:6*/
#line 60 "expand.w"

offset+= *bytes++;
switch(shifter&0xc0000000){
case 0x00000000:
count= 3;
break;
case 0x40000000:
count= 4;
break;
case 0x80000000:
count= 5;
break;
case 0xc0000000:
count= *bytes++;
if((count==0)&&(offset==0))done= 1;
if((count==1)&&(offset==0))count= 0;
break;
}
/*5:*/
#line 91 "expand.w"

/*4:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:4*/
#line 92 "expand.w"

/*4:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:4*/
#line 93 "expand.w"


/*:5*/
#line 78 "expand.w"

temp= out-offset;
while(count--)/*8:*/
#line 103 "expand.w"

*out++= *temp++;

/*:8*/
#line 80 "expand.w"

}

/*:3*/
#line 37 "expand.w"

else
/*2:*/
#line 44 "expand.w"

{
/*4:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:4*/
#line 46 "expand.w"

temp= out-*bytes++;
if(0x80000000&shifter){
/*8:*/
#line 103 "expand.w"

*out++= *temp++;

/*:8*/
#line 49 "expand.w"

}
/*8:*/
#line 103 "expand.w"

*out++= *temp++;

/*:8*/
#line 51 "expand.w"

/*8:*/
#line 103 "expand.w"

*out++= *temp++;

/*:8*/
#line 52 "expand.w"

/*4:*/
#line 83 "expand.w"

shifter<<= 1;
shift_count++;
if(shift_count==8){
shifter|= *in++;
shift_count= 0;
}

/*:4*/
#line 53 "expand.w"

}

/*:2*/
#line 39 "expand.w"

}
}
}

/*:1*/
