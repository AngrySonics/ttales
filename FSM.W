
@* The State Machine Engine.  This module implements a general purpose
attributed finite state machine.  It executes attributes on transitions.

@ More typedefs

@s IntFuncPtr int
@s VoidFuncPtr int
@s State int
@s StatePtr int

@<Typedef...@>=
typedef int (*IntFuncPtr)(void);@#
typedef void (*VoidFuncPtr)(void);@#
typedef struct state_t {
  IntFuncPtr test;
  struct state_t *next;
  VoidFuncPtr attribute;
  short flags;
}State, *StatePtr;

@ This is the actual code that runs the state machines.  It works its way
down through the list of states that |s| points to, running test
conditions until one returns |TRUE|.  Then it runs the attribute
and returns the state associated with that test.

@d FSM_RERUN    0x0001

@c
StatePtr fsm(StatePtr s){
  for(;;){
    while(!s->test()){
      s++;
    }
    s->attribute();
    if(!(s->flags & FSM_RERUN)) break;
    s = s->next;
  }
  return s->next;
}

@ This section contains some simple universally useful tests and
attributes.

@c
int True(){
  return TRUE;
}

int False(){
  return FALSE;
}

void Null(){
  return;
}

@ @<Function prototypes@>=
StatePtr fsm(StatePtr s);@/
int True(void);@/
int False(void);@/
void Null(void);@/

@ Here is the top-level state machine for \TT .

@c
State InitialState[] = {@;
        {True, IntroScreen, Initialize, 0}@;
};@#
State IntroScreen[] = {@/
        {DoneWithIntro, PathPlay, InitGame, 0},@/
        {True, IntroScreen, Null, 0}@/
};@#
State PathPlay[] = {@/
        {Dead, DeathScreen, StartDeathSequence, 0},@/
        {Win, VictoryScreen, StartVictorySequence, 0},@/
        {AtNode, NodePlay, InitNode, 0},@/
        {True, PathPlay, RunPath, 0}@/
};@#
State VictoryScreen[] = {@/
        {DoneVictory, IntroScreen, Null, 0},@/
        {True, VictoryScreen, RunVictoryScreen, 0}@/
};@#
State DeathScreen[] = {@/
        {DoneDeath, IntroScreen, Null, 0},@/
        {True, DeathScreen, RunDeathScreen, 0}@/
};@#
State NodePlay[] = {@/
        {Dead, DeathScreen, StartDeathSequence, 0},@/
        {Win, VictoryScreen, StartVictorySequence, 0},@/
        {AtPath, PathPlay, InitPath, 0},@/
        {True, NodePlay, RunNode, 0}@/
};@#

@ Here are the tests that go with it.

@c
int DoneWithIntro(){
  return TRUE;
}
int Dead(){
  return FALSE;
}
int Win(){
  return FALSE;
}
int AtNode(){
  return FALSE;
}
int DoneVictory(){
  return FALSE;
}
int DoneDeath(){
  return FALSE;
}
int AtPath(){
  return FALSE;
}

@ And here are the attributes
@c
void Initialize(){}
void StartDeathSequence(){}
void RunDeathScreen(){}
void StartVictorySequence(){}
void RunVictoryScreen(){}
void InitNode(){}
void RunNode(){}

@ This attribute does initialization for a new game.

@c
void InitGame(){
  @<Initialize the game@>@;
  currentPath = &p1_1;
  InitPath();
}

@ @<Function prototypes@>=

State InitialState[];
State IntroScreen[];
State PathPlay[];
State VictoryScreen[];
State DeathScreen[];
State NodePlay[];@#

int DoneWithIntro(void);@/
int Dead(void);@/
int Win(void);@/
int AtNode(void);@/
int DoneVictory(void);@/
int DoneDeath(void);@/
int AtPath(void);@#

void Initialize(void);@/
void InitGame(void);@/
void StartDeathSequence(void);@/
void StartVictorySequence(void);@/
void InitNode(void);@/
void RunPath(void);@/
void RunVictoryScreen(void);@/
void RunDeathScreen(void);@/
void InitPath(void);@/
void RunNode(void);@/

