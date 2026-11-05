@* Paths---The Squares.  This is the code that controls the behavior of
playfield squares and their interaction with the creatures that roam around on
them.

@ @<Function prototypes@>=
void UpdateSquares(void);
void ActivateSquare(CreaturePtr c, short x, short y);

@ Here is the routine to call when a creature lands on a square.  Call it with
a pointer to the creature involved and the coordinates of the square and it
takes care of the rest.  (Well, you still have to call |UpdateSquares()| to
keep it going, but...)

@c
void ActivateSquare(CreaturePtr c, short x, short y){
ActiveSquarePtr as;
  @<Allocate an active square record@>@;
  @<Fill up the active square record@>@;
  @<Perform the activated square's immediate behavior@>@;
  if(as)
    @<Put the record into the active square list@>@;
}

void UpdateSquares(){
}

@ @<Allocate an active square record@>=
  as = AllocMem(sizeof(ActiveSquare));

@ @<Fill up the active square record@>=
  as->x = x;
  as->y = y;
  as->type = pathMap[y*mapWidth+x].type;
  as->timer = 0;

@ @<Perform the activated square's immediate behavior@>=
  switch(as->type){
    case 0:
    default:
      break;
  }

@ @<Put the record into the active square list@>=
  as->next = activeSquareList;
  as->prev = NULL;
  activeSquareList->prev = as;
  activeSquareList = as;

@ @<Global...@>=
ActiveSquarePtr activeSquareList;

@ This is the structure for a square that is up to something

@s ActiveSquare int
@s ActiveSquarePtr int

@<Typedef...@>=
typedef struct activs {
  struct activs *next;
  struct activs *prev;
  short x;
  short y;
  short type;
  short timer;
}ActiveSquare, *ActiveSquarePtr;
