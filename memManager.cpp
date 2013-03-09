#include "memManager.h"



memManager::memManager(void){
	//clean the memory
	memset((void *) memNext, 100000, maxMem*sizeof(uint32_t));
	curFreeLoc			  = 0;
	memInfoUsed[0]		  = FREE; 
	memNext[0]		  =  maxMem-1; 
	memInfoUsed[maxMem-1] = FREE;
	memNext[maxMem-1]	  = 0;
	memAvail = maxMem;
};

void *memManager::memalloc(size_t size){
	if(memAvail < size){
		return NULL;
	}
	return findNext(size);
};

void memManager::free(void *ptr){

	uint32_t curLoc = (unsigned char *)ptr - memBuff;
	if(ptr == NULL || ((unsigned char *)ptr - memBuff) < 0){
		return;
	}
	//curLoc = curLoc + 1;
	setUpMem(curLoc, -1, FREE);
	mregeUp(curLoc);
	mregeDown(curLoc);
};//

void memManager::printMem(void){
	cout << endl;
	for(uint32_t i=0; i < maxMem; i++){
		cout << memBuff[i];
	}
	cout << endl;
};

//findst the next free area
void *memManager::findNext(size_t size){
	char flag = 0;
	uint32_t tempLoc = 0;
	tempLoc = curFreeLoc;
	if(memInfoUsed[tempLoc]==FREE && ((memNext[tempLoc]-tempLoc+1) > size)){//if the memory is avialable and object fits in 
		flag = 1;
	}
	else{
		//if the memory is availabe on the top good otherwise search from start				
		tempLoc = 0;
		while(tempLoc < maxMem){
			if(memInfoUsed[tempLoc]==FREE && ((memNext[tempLoc]-tempLoc+1) >= size)){//if the memory is avialable and object fits in 				
				flag = 1;
				break;					
			}
			else
			{tempLoc = memNext[tempLoc]+1;}
		}//end of while
	}//end of if on top

	if(flag){
		setUpMem(tempLoc, size,USED);
		return (memBuff+tempLoc);
	}
	return NULL;
};

//sets up the memrory for the 
void memManager::setUpMem(uint32_t tempLoc, size_t size, char setWhat){
	if(setWhat == USED){//it is free set it up to used
		uint32_t temp			= memNext[tempLoc];
		memNext[tempLoc]		= tempLoc+size-1;
		memNext[tempLoc+size-1] = tempLoc;
		memInfoUsed[tempLoc] = USED;
		memInfoUsed[tempLoc+size-1] = USED;				
		this->memAvail = memAvail-size;
		if( (tempLoc+size-1) != temp){
			memNext[tempLoc+size] = temp;
			memNext[temp]		  = tempLoc+size;
			memInfoUsed[tempLoc+size] = FREE;
			memInfoUsed[temp] = FREE;
			curFreeLoc = tempLoc+size;
		}
	}///if used
	else{
		uint32_t temp			= memNext[tempLoc];
		memInfoUsed[tempLoc] = FREE;
		memInfoUsed[temp] = FREE;
		memAvail = memAvail + temp-tempLoc+1;
	}
};//end of setupMem

void memManager::mregeUp(uint32_t tempLoc){
	uint32_t temp1			= memNext[tempLoc];
	if(temp1+1< maxMem && memInfoUsed[temp1+1] == FREE){
		memNext[tempLoc] = memNext[temp1+1];
		memNext[memNext[temp1+1]] = tempLoc;
		//setUpMem(tempLoc, -1, FREE);
	}
};//end of mergeUp
void memManager::mregeDown(uint32_t tempLoc){			
	if(tempLoc>=0){
		uint32_t prev = tempLoc-1;
		uint32_t temp1		 = memNext[tempLoc];
		if(memInfoUsed[prev] == FREE){//check if previous is free
			memNext[memNext[prev]] = temp1;//in the previous add the current
			memNext[temp1] = memNext[prev];			// in the end of the current make it know the start of previous
			//setUpMem(prev, -1, FREE);
		}			
	}
};//end of mergeUp