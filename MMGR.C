/*5:*/
#line 40 "mmgr.w"
void*AllocMem(unsigned int size){
MemBlockPtr current= freeList;

size+= sizeof(int);
/*6:*/
#line 52 "mmgr.w"

{
while(current&&(current->size<size))
current= current->next;
if(!current)return NULL;
}

/*:6*/
#line 44 "mmgr.w"

if(current->size>size+sizeof(MemBlock))
/*7:*/
#line 59 "mmgr.w"

{
current->size-= size;
current= (MemBlockPtr)(((char*)current)+current->size);
current->size= size;
}

/*:7*/
#line 46 "mmgr.w"

else
/*8:*/
#line 66 "mmgr.w"

{
if(current->prev)
current->prev->next= current->next;
else
freeList= current->next;
if(current->next)
current->next->prev= current->prev;
}

/*:8*/
#line 48 "mmgr.w"

return(void*)(((char*)current)+sizeof(int));
}

/*:5*//*9:*/
#line 84 "mmgr.w"
void FreeMem(void*addr){
MemBlockPtr block= ((MemBlockPtr)(((char*)addr)-sizeof(int)));

/*10:*/
#line 95 "mmgr.w"

if(!freeList){
freeList= block;
block->next= NULL;
block->prev= NULL;
return;
}

/*:10*/
#line 87 "mmgr.w"

if(block<freeList)
/*11:*/
#line 106 "mmgr.w"

if(block+block->size==freeList){
block->size+= freeList->size;
block->next= freeList->next;
block->prev= NULL;
freeList= addr;
}else{
block->next= freeList;
freeList->prev= block;
freeList= block;
}

/*:11*/
#line 89 "mmgr.w"

else
/*12:*/
#line 118 "mmgr.w"

{
MemBlockPtr list= freeList;


do{
list= list->next;
}while(list->next&&(block>list));

if(list->next)
/*13:*/
#line 134 "mmgr.w"

{
block->next= list->next;
list->next= block;
block->prev= block->next->prev;
block->next->prev= block;
/*14:*/
#line 143 "mmgr.w"

if((MemBlockPtr)((char*)block+block->size)==block->next){
block->size+= block->next->size;
block->next= block->next->next;
if(block->next)block->next->prev= block;
}

/*:14*/
#line 140 "mmgr.w"

}

/*:13*/
#line 128 "mmgr.w"

else
/*15:*/
#line 150 "mmgr.w"

{
list->next= block;
block->prev= list;
block->next= NULL;
}

/*:15*/
#line 130 "mmgr.w"

/*16:*/
#line 157 "mmgr.w"

if((MemBlockPtr)((char*)(block->prev)+block->prev->size)==block){
block->prev->size+= block->size;
block->prev->next= block->next;
if(block->next)
block->next->prev= block->prev;
}

/*:16*/
#line 131 "mmgr.w"

}

/*:12*/
#line 91 "mmgr.w"

return;
}

/*:9*//*17:*/
#line 165 "mmgr.w"
void InitHeap(char*addr,int size){
freeList= (MemBlockPtr)addr;
freeList->next= NULL;
freeList->prev= NULL;
freeList->size= size;
}
/*:17*/
