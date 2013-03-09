#ifndef MEMMANAGER_H
#define MEMMANAGER_H

#include <iostream>
#include <stdio.h>
#include <string.h>
//#include <stdint>
#include <cstdint>
using namespace std;

//#define maxMem 40

#define USED 1
#define FREE 0

//memory manager class,
//it could be implemented using the linklist but since we were avoiding
//any allocation functions provided by the C or C++ {malloc, new,delete, free, etc...}
//I have not used linkedlist to maitain the information of memory allocation
//however the structure used is quite same, 
//whenever a block is allocated the starting location keeps what is ending byte and ending byte knows what is 
//starting byte
//linked list implementation for this is actually much simpler and more cleaner. 

class memManager{
	private:
		const static uint32_t maxMem = 40;
		char memInfoUsed[maxMem];		//flag to say this block of memory is free or used
		uint32_t memNext[maxMem];		//knows the end of the block

		unsigned char memBuff[maxMem];
		uint32_t curFreeLoc;			//used to keep track of something over the top
		uint32_t memAvail;				//total memory avaialable {not the max block size available, that might be more helpful}

	public:
		memManager();

		void *memalloc(size_t size);

		void free(void *ptr);//

		void printMem(void);

	private:
		//findst the next free area
		void *findNext(size_t size);
		//sets up the memrory for the 
		void setUpMem(uint32_t tempLoc, size_t size, char setWhat);

		//merge the free space
		void mregeUp(uint32_t tempLoc);
		void mregeDown(uint32_t tempLoc);
};

#endif