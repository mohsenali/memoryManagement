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

class memManager{
	private:
		const static uint32_t maxMem = 40;
		char memInfoUsed[maxMem];
		uint32_t memNext[maxMem];

		unsigned char memBuff[maxMem];
		uint32_t curFreeLoc;//used to keep track of something over the top
		uint32_t memAvail;

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

		void mregeUp(uint32_t tempLoc);
		void mregeDown(uint32_t tempLoc);
};

#endif