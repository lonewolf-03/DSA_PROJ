#pragma once
#include "../Processor/MainProcessor.h"
#include "../DataStructures/List/ListADT.h"
#include "../DataStructures/Queue/Queue.h"
#include "../DataStructures/PQueue/PQueue.h"

class Scheduler {
private:
	string input_filename;
	string output_filename;
public:
	
	Scheduler();
	LinkedList<Process*> NEWList;
	LinkedList<Process*> TRMList;
	LinkedList<Process*> BLKList;
	LinkedList<Processor*> processors;

	void nextTimeStep();
	Processor* getShortestProcessor();

	void loadProcess(); // Load From InputFile To NEW List
	void NEWToRDY(Processor* p);
	void RUNtoBLK(Process* p);
	void BLKtoRDY(Process* p);
	void toTRM(Process* p);
};