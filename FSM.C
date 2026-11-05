#define FSM_RERUN 0x0001 \

/*3:*/
#line 29 "fsm.w"

StatePtr fsm(StatePtr s){
for(;;){
while(!s->test()){
s++;
}
s->attribute();
if(!(s->flags&FSM_RERUN))break;
s= s->next;
}
return s->next;
}

/*:3*//*4:*/
#line 45 "fsm.w"

int True(){
return TRUE;
}

int False(){
return FALSE;
}

void Null(){
return;
}

/*:4*//*6:*/
#line 66 "fsm.w"

State InitialState[]= {
{True,IntroScreen,Initialize,0}
};
State IntroScreen[]= {
{DoneWithIntro,PathPlay,InitGame,0},
{True,IntroScreen,Null,0}
};
State PathPlay[]= {
{Dead,DeathScreen,StartDeathSequence,0},
{Win,VictoryScreen,StartVictorySequence,0},
{AtNode,NodePlay,InitNode,0},
{True,PathPlay,RunPath,0}
};
State VictoryScreen[]= {
{DoneVictory,IntroScreen,Null,0},
{True,VictoryScreen,RunVictoryScreen,0}
};
State DeathScreen[]= {
{DoneDeath,IntroScreen,Null,0},
{True,DeathScreen,RunDeathScreen,0}
};
State NodePlay[]= {
{Dead,DeathScreen,StartDeathSequence,0},
{Win,VictoryScreen,StartVictorySequence,0},
{AtPath,PathPlay,InitPath,0},
{True,NodePlay,RunNode,0}
};

/*:6*//*7:*/
#line 97 "fsm.w"

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

/*:7*//*8:*/
#line 121 "fsm.w"

void Initialize(){}
void StartDeathSequence(){}
void RunDeathScreen(){}
void StartVictorySequence(){}
void RunVictoryScreen(){}
void InitNode(){}
void RunNode(){}

/*:8*//*9:*/
#line 132 "fsm.w"

void InitGame(){

#line 134 "fsm.w"

currentPath= &p1_1;
InitPath();
}

/*:9*/
