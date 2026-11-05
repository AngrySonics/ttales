@* Memory Manager.  Memory allocation @^Memory allocation@> and
deallocation @^Memory deallocation@> is provided by these routines.
|AllocMem| uses the first fit algorithm.  It does not initialize the
memory in any way.  FreeMem sorts the free list and merges adjacent
blocks.  No garbage collection or heap compaction is performed.
Information critical to the integrity of the memory management system is
stored immediately adjacent to allocated blocks.  If a client overwrites
the boundaries of an allocation, bad things will happen.
@^Unsafe behavior@>

@ First, some definitions---

@<Function prototypes@>=
void *AllocMem(unsigned int size);@/
void FreeMem(void *addr);@/
void InitHeap(char *addr, int size);@/

@ @<Global...@>=
MemBlockPtr freeList;

@ This is the structure of the header of a free block.

@s MemBlock int
@s MemBlockPtr int

@<Typedef declarations@>=
typedef struct memblock {
    unsigned int size;
    struct memblock *next;
    struct memblock *prev;
}MemBlock, *MemBlockPtr;

@ |AllocMem| proceeds in a simple manner.  First it scans the free list
looking for a block that is at least as large as the client has requested,
plus overhead.  If it fails to find one, it returns |NULL|.  If it
succeeds, it decides whether it can produce a new free block from the
remnant.  If not, it returns the entire block to the client.  If so, it
cuts off a slice and gives it to the client. @^Memory allocation@>

@c void *AllocMem(unsigned int size){@/
MemBlockPtr current = freeList;

  size += sizeof(int);@/
  @<Find an at-least-big-enough piece in the free list:mmgr@>@/
  if(current->size > size + sizeof(MemBlock))
    @<Cut a chunk off the free block and prep it:mmgr@>@/
  else
    @<Remove the block from the free list:mmgr@>@/
  return (void *)(((char *)current)+sizeof(int));@/
}

@ @<Find an at-least-big-enough piece in the free list:mmgr@>=
{
  while(current && (current->size < size))@/
    current = current->next;
  if(!current) return NULL;
}

@ @<Cut a chunk off the free block and prep it:mmgr@>=
{
  current->size -= size;
  current = (MemBlockPtr)(((char *)current) + current->size);
  current->size = size;
}

@ @<Remove the block from the free list:mmgr@>=
{
  if(current->prev)
    current->prev->next = current->next;
  else
    freeList = current->next;
  if(current->next)@/
    current->next->prev = current->prev;
}

@ This routine frees a block by inserting it into the free list, in sorted
position with higher addresses later in the list, and merging it with
adjacent free blocks, if there are any.  The slightly contorted definition
of |block|, below, is to recover the position of the allocation block, as
opposed to the address we told the client.  If the client attempts to free
an address other than what we gave him, expect bad things to happen.
@^Unsafe behavior@> @^Memory deallocation@>

@c void FreeMem(void *addr){
MemBlockPtr block = ((MemBlockPtr)(((char *)addr)-sizeof(int)));

  @<If the free list is empty, make the new block be the free list:mmgr@>@;
  if(block < freeList)
    @<Put block at beginning of free list:mmgr@>@;
  else
    @<Insert the block into the free list:mmgr@>@;
  return;
}

@ @<If the free list is empty, make the new block be the free list:mmgr@>=
  if(!freeList){
    freeList = block;
    block->next = NULL;
    block->prev = NULL;
    return;
  }

@ This module places the new block on the head of the free list, merging
it with the former head of the list if appropriate.

@<Put block at beginning of free list:mmgr@>=
  if(block + block->size == freeList){
    block->size += freeList->size;
    block->next = freeList->next;
    block->prev = NULL;
    freeList = addr;
  } else {
    block->next = freeList;
    freeList->prev = block;
    freeList = block;
  }

@ @<Insert the block into the free list:mmgr@>=
{
MemBlockPtr list = freeList;@/

  /* find where it belongs */
  do {@/
    list = list->next;@/
  } while(list->next && (block > list));@;

  if(list->next)
    @<Splice the block into the free list:mmgr@>@;
  else
    @<Tack the block onto the end of the free list:mmgr@>@;
  @<Try to merge the block with the preceeding block:mmgr@>@;
}

@ @<Splice the block into the free list:mmgr@>=
{
  block->next = list->next;
  list->next = block;
  block->prev = block->next->prev;
  block->next->prev = block;
  @<Try to merge the block with the following block:mmgr@>@;
}

@ @<Try to merge the block with the following block:mmgr@>=
  if((MemBlockPtr)((char *)block + block->size) == block->next){
    block->size += block->next->size;
    block->next = block->next->next;
    if(block->next)@/ block->next->prev = block;
  }

@ @<Tack the block onto the end of the free list:mmgr@>=
{
  list->next = block;
  block->prev = list;
  block->next = NULL;
}

@ @<Try to merge the block with the preceeding block:mmgr@>=
  if((MemBlockPtr)((char *)(block->prev) + block->prev->size) == block){
    block->prev->size += block->size;
    block->prev->next = block->next;
    if(block->next)@/
      block->next->prev = block->prev;
  }

@ @c void InitHeap(char *addr, int size){
    freeList = (MemBlockPtr)addr;
    freeList->next = NULL;
    freeList->prev = NULL;
    freeList->size = size;
}

