#include "memManager.h"

void main(void){

	memManager mem;
	char *abc = (char *)mem.memalloc(10);
	strcpy(abc, "HOW is");
	char *abc2 = (char *)mem.memalloc(5);
	strcpy(abc2, "ab");
	char *abc3 = (char *)mem.memalloc(10);
	strcpy(abc3, "woe");	
	char *abc4 = (char *)mem.memalloc(4);
	strcpy(abc4, "CD");
	std::cout <<endl << "CURRENT meory contents are as follow" <<endl;
	mem.printMem();
	std::cout <<endl << "Deleting 2nd allocation" <<endl;
	mem.free(abc2);
	std::cout <<endl << "Deleting 3rd allocation" <<endl;
	mem.free(abc3);
	std::cout <<endl << "Following cannot be allocated if the previous two free mem are not merged" <<endl;
	
	char *abc5 = (char *)mem.memalloc(15);
	if(abc5!=NULL){
		strcpy(abc5, "*How Are** ");
	}
	std::cout <<endl << "CURRENT meory contents are as follow" <<endl;
	mem.printMem();


	mem.free(abc);
	mem.free(abc4);
	mem.free(abc5);
}//end of main