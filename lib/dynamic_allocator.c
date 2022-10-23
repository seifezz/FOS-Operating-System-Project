/*
 * dyn_block_management.c
 *
 *  Created on: Sep 21, 2022
 *      Author: HP
 */
#include <inc/assert.h>
#include <inc/string.h>
#include "../inc/dynamic_allocator.h"


//==================================================================================//
//============================== GIVEN FUNCTIONS ===================================//
//==================================================================================//

//===========================
// PRINT MEM BLOCK LISTS:
//===========================

void print_mem_block_lists()
{
	cprintf("\n=========================================\n");
	struct MemBlock* blk ;
	struct MemBlock* lastBlk = NULL ;
	cprintf("\nFreeMemBlocksList:\n");
	uint8 sorted = 1 ;
	LIST_FOREACH(blk, &FreeMemBlocksList)
	{
		if (lastBlk && blk->sva < lastBlk->sva + lastBlk->size)
			sorted = 0 ;
		cprintf("[%x, %x)-->", blk->sva, blk->sva + blk->size) ;
		lastBlk = blk;
	}
	if (!sorted)	cprintf("\nFreeMemBlocksList is NOT SORTED!!\n") ;

	lastBlk = NULL ;
	cprintf("\nAllocMemBlocksList:\n");
	sorted = 1 ;
	LIST_FOREACH(blk, &AllocMemBlocksList)
	{
		if (lastBlk && blk->sva < lastBlk->sva + lastBlk->size)
			sorted = 0 ;
		cprintf("[%x, %x)-->", blk->sva, blk->sva + blk->size) ;
		lastBlk = blk;
	}
	if (!sorted)	cprintf("\nAllocMemBlocksList is NOT SORTED!!\n") ;
	cprintf("\n=========================================\n");

}

//********************************************************************************//
//********************************************************************************//

//==================================================================================//
//============================ REQUIRED FUNCTIONS ==================================//
//==================================================================================//

//===============================
// [1] INITIALIZE AVAILABLE LIST:
//===============================
void initialize_MemBlocksList(uint32 numOfBlocks)
{
	//TODO: [PROJECT MS1] [DYNAMIC ALLOCATOR] initialize_MemBlocksList
	// Write your code here, remove the panic and write your code
	//panic("initialize_MemBlocksList() is not implemented yet...!!");
	LIST_INIT(&AvailableMemBlocksList);
	LIST_INSERT_HEAD(&AvailableMemBlocksList, &MemBlockNodes[0]);
	//struct MemBlock firstAv = LIST_FIRST(&AvailableMemBlocksList);
	int i;
	for (i = 1; i < numOfBlocks; i++) {


		MemBlockNodes[i].size = 0;
		MemBlockNodes[i].sva = 0;
		LIST_INSERT_TAIL(&AvailableMemBlocksList, &MemBlockNodes[i]);





	}

}

//===============================
// [2] FIND BLOCK:
//===============================
struct MemBlock *find_block(struct MemBlock_List *blockList, uint32 va)
{
	//TODO: [PROJECT MS1] [DYNAMIC ALLOCATOR] find_block
	// Write your code here, remove the panic and write your code
	panic("find_block() is not implemented yet...!!");

}

//=========================================
// [3] INSERT BLOCK IN ALLOC LIST [SORTED]:
//=========================================
void insert_sorted_allocList(struct MemBlock *blockToInsert)
{
	//TODO: [PROJECT MS1] [DYNAMIC ALLOCATOR] insert_sorted_allocList
	// Write your code here, remove the panic and write your code
	panic("insert_sorted_allocList() is not implemented yet...!!");
}

//=========================================
// [4] ALLOCATE BLOCK BY FIRST FIT:
//=========================================

struct MemBlock *alloc_block_FF(uint32 size)
{
	cprintf("\n size sent to func. = %d  ",size,"\n");
	struct MemBlock *ptrFreeLooper;
	struct MemBlock *ptrFreeLooperz;
		cprintf(" size of free list  = %d",FreeMemBlocksList.size);


		int count=0;
							LIST_FOREACH (ptrFreeLooperz,&FreeMemBlocksList)
							{
								cprintf(" \nto see sva %d",ptrFreeLooperz->sva);
								cprintf(" \nto see size %d",ptrFreeLooperz->size);
								count++;
								cprintf("\n%d",count);
							}
	LIST_FOREACH (ptrFreeLooper,&FreeMemBlocksList)
	{
		cprintf(" size of list block = %d",ptrFreeLooper->size);
		//case no free available
		if(ptrFreeLooper->size<size)
		{
				cprintf("\t in size smaller \n");
			if(ptrFreeLooper==FreeMemBlocksList.lh_last)
			{
				cprintf("\n no ava block size");
				ptrFreeLooper= NULL;
				break;
			}
			else{
				continue;
			}
		}
		//case grater size
			 if (ptrFreeLooper->size>size)
				{
					cprintf("\tin greater size case ");
					 struct MemBlock *ptrToBeKept;
					 uint32 sva=0;
					 sva=ptrFreeLooper->sva;
					 cprintf("\n block size before updating = %d",ptrFreeLooper->size);
					 ptrToBeKept=ptrFreeLooper;
					 //updating remaining free block size
					ptrFreeLooper->size=ptrFreeLooper->size-size;
					ptrFreeLooper->sva=ptrFreeLooper->sva+size;
					cprintf("block size after update to remaining %d",ptrFreeLooper->size);
					//update returned block size
					ptrToBeKept->size=size;
					ptrToBeKept->sva=sva;
					AvailableMemBlocksList.size--;

					return ptrToBeKept;
				}
		//case if size is equal to given size
			 if(ptrFreeLooper->size==size)
					{
						cprintf("\n in size equal \n");
						LIST_REMOVE(&FreeMemBlocksList, ptrFreeLooper);
						cprintf("\n size of Free list after removal=%d",LIST_SIZE(&FreeMemBlocksList),"\n");
						cprintf("\n size of All list after insertion=%d",LIST_SIZE(&AllocMemBlocksList),"\n");
						break;
					}

	}
	return ptrFreeLooper;
}



//=========================================
// [5] ALLOCATE BLOCK BY BEST FIT:
//=========================================
struct MemBlock *alloc_block_BF(uint32 size)
{
	//TODO: [PROJECT MS1] [DYNAMIC ALLOCATOR] alloc_block_BF
	// Write your code here, remove the panic and write your code
	panic("alloc_block_BF() is not implemented yet...!!");
}


//=========================================
// [7] ALLOCATE BLOCK BY NEXT FIT:
//=========================================
struct MemBlock *alloc_block_NF(uint32 size)
{
	//TODO: [PROJECT MS1 - BONUS] [DYNAMIC ALLOCATOR] alloc_block_NF
	// Write your code here, remove the panic and write your code
	panic("alloc_block_NF() is not implemented yet...!!");

}

//===================================================
// [8] INSERT BLOCK (SORTED WITH MERGE) IN FREE LIST:
//===================================================
void insert_sorted_with_merge_freeList(struct MemBlock *blockToInsert)
{
	//cprintf("BEFORE INSERT with MERGE: insert [%x, %x)\n=====================\n", blockToInsert->sva, blockToInsert->sva + blockToInsert->size);
	//print_mem_block_lists() ;

	//TODO: [PROJECT MS1] [DYNAMIC ALLOCATOR] insert_sorted_with_merge_freeList
	// Write your code here, remove the panic and write your code
	//panic("insert_sorted_with_merge_freeList() is not implemented yet...!!");
	//LIST_INIT(&FreeMemBlocksList);
//	LIST_INSERT_HEAD(&FreeMemBlocksList, LIST_LAST(&AvailableMemBlocksList));
//	LIST_REMOVE(&FreeMemBlocksList, LIST_LAST(&AvailableMemBlocksList));
//	LIST_INSERT_TAIL(&FreeMemBlocksList, LIST_LAST(&AvailableMemBlocksList));
//	LIST_REMOVE(&FreeMemBlocksList, LIST_LAST(&AvailableMemBlocksList));



	// Merge Both Comments Draft

	//					struct MemBlock *tmp;
	//					cprintf("================================\n");
	//					LIST_FOREACH(tmp, &FreeMemBlocksList) {
	//						cprintf("%d \n", tmp->sva);
	//					}
	//					cprintf("================================\n");

						//cprintf("%d %x\t \n", blockToInsert->size, LIST_NEXT(freeBlock)->size);


						// Pointer to the fourth
	//cprintf("freeSize: %d \n", firstBlockSize);
	//cprintf("totalSize: %d \n", totalSize);
	//cprintf("freeBlock: %d \n", freeBlock->size);

	//cprintf("%x \t %d \n", freeBlock->sva, freeBlock->size);
//					cprintf("%d -> %d -> %d \n", freeBlock->sva,
//					freeBlock->prev_next_info.le_next->sva,
//					freeBlock->prev_next_info.le_next->prev_next_info.le_next->sva,
//					freeBlock->prev_next_info.le_next->prev_next_info.le_next->prev_next_info.le_next->sva
//					);

	//					cprintf("%d -> %d -> %d \n", freeBlock->sva,
	//					freeBlock->prev_next_info.le_next->sva
	//					);
						// Zeroing
	//					blockToInsert->size = 0;
	//					blockToInsert->sva = 0;
	//					freeBlock->prev_next_info.le_next->size = 0;
	//					freeBlock->prev_next_info.le_next->sva = 0;

	//					cprintf("================================\n");
	//					struct MemBlock *tmpp;
	//					LIST_FOREACH(tmpp, &FreeMemBlocksList) {
	//						cprintf("%d \n", tmpp->sva);
	//					}
	//
	//					cprintf("================================\n");


	int freeListSize = LIST_SIZE(&FreeMemBlocksList);
	cprintf("START PROCESS %d\n", freeListSize);
	if(freeListSize == 0){
		cprintf("EMPTY \n");
		LIST_INSERT_HEAD(&FreeMemBlocksList, blockToInsert);
	}
	else {
			struct MemBlock *freeBlock;

			LIST_FOREACH(freeBlock, &FreeMemBlocksList) {

				if(
						freeBlock->prev_next_info.le_next != NULL &&
						freeBlock->sva + freeBlock->size == blockToInsert->sva &&
						blockToInsert->sva + blockToInsert->size == freeBlock->prev_next_info.le_next->sva
				) {
					// Adding Sizes
					uint32 firstBlockSize = freeBlock->size;
					uint32 totalSize = firstBlockSize + blockToInsert->size + LIST_NEXT(freeBlock)->size;
					freeBlock->size = totalSize;

					// Zeroing
					blockToInsert->size = 0;
					blockToInsert->sva = 0;
					freeBlock->prev_next_info.le_next->size = 0;
					freeBlock->prev_next_info.le_next->sva = 0;

					// Remove the next to freeBlock
					LIST_REMOVE(&FreeMemBlocksList, freeBlock->prev_next_info.le_next);
					//Insert Elements to AvailableMemBlockList
					LIST_INSERT_HEAD(&AvailableMemBlocksList, LIST_NEXT(freeBlock));
					LIST_INSERT_HEAD(&AvailableMemBlocksList, blockToInsert);


					break;
				}
				if(freeBlock->sva + freeBlock->size == blockToInsert->sva) {
					cprintf("MERGE WITH PREV \n");
					freeBlock->size += blockToInsert->size;
					blockToInsert->size = 0;
					blockToInsert->sva = 0;
					//blockToInsert->prev_next_info.le_next = LIST_FIRST(&AvailableMemBlocksList);
					LIST_INSERT_HEAD(&AvailableMemBlocksList, blockToInsert);
					break;
				}
				else if(blockToInsert->sva + blockToInsert->size == freeBlock->sva) {
					cprintf("MERGE WITH NEXT \n");
					freeBlock->sva = blockToInsert->sva;
					freeBlock->size += blockToInsert->size;
					blockToInsert->size = 0;
					blockToInsert->sva = 0;
					//blockToInsert->prev_next_info.le_next = LIST_FIRST(&AvailableMemBlocksList);
					LIST_INSERT_HEAD(&AvailableMemBlocksList, blockToInsert);
					break;
				}

				else{
					//cprintf("ENTER ELSE \n");
					if (freeBlock->prev_next_info.le_next == NULL && blockToInsert->sva > LIST_FIRST(&FreeMemBlocksList)->sva) {
						cprintf("AT TAIL \n");
						LIST_INSERT_TAIL(&FreeMemBlocksList, blockToInsert);
						break;
					}
					else if (blockToInsert->sva < LIST_FIRST(&FreeMemBlocksList)->sva) {
						cprintf("AT HEAD \n");
						LIST_INSERT_HEAD(&FreeMemBlocksList, blockToInsert);
						break;
					}
					else if(
						freeBlock->prev_next_info.le_next != NULL &&
						blockToInsert->sva + blockToInsert->size > freeBlock->sva &&
						blockToInsert->sva + blockToInsert->size < freeBlock->prev_next_info.le_next->sva
					) {
						cprintf("AFTER \n");

						LIST_INSERT_AFTER(&FreeMemBlocksList, freeBlock, blockToInsert);
						break;
					}

				}

			}

		}





	//cprintf("\nAFTER INSERT with MERGE:\n=====================\n");
	//print_mem_block_lists();

}

