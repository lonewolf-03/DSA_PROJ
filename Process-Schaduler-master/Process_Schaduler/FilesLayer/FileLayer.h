#pragma once
#include"../Processor/MainProcessor.h"
#include "../DataStructures/List/ListADT.h"
#include "../DataStructures/Queue/Queue.h"

class FileLayer {
public:
	void loadInputFile(string filename, LinkedList<Process*>& new_list);
};