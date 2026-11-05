/*3:*/
#line 14 "squares.w"

void ActivateSquare(CreaturePtr c,short x,short y){
ActiveSquarePtr as;
/*4:*/
#line 27 "squares.w"

as= AllocMem(sizeof(ActiveSquare));

/*:4*/
#line 17 "squares.w"

/*5:*/
#line 30 "squares.w"

as->x= x;
as->y= y;
as->type= pathMap[y*mapWidth+x].type;
as->timer= 0;

/*:5*/
#line 18 "squares.w"

/*6:*/
#line 36 "squares.w"

switch(as->type){
case 0:
default:
break;
}

/*:6*/
#line 19 "squares.w"

if(as)
/*7:*/
#line 43 "squares.w"

as->next= activeSquareList;
as->prev= NULL;
activeSquareList->prev= as;
activeSquareList= as;

/*:7*/
#line 21 "squares.w"

}

void UpdateSquares(){
}

/*:3*/
