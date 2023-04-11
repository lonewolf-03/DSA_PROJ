#pragma once
#include "../Process/Process.h"
#include "../DataStructures/List/ListADT.h"



enum ProcessorState {
	BUSY,
	IDLE,
};

enum ProcessorType {
	FCFS,
	SJF,
	RR,
};

class Processor {
private:
	int exepectedTimeToFinish;
	LinkedList<Process*> runProcesses;
	Queue<Process*> readyProcesses;
	ProcessorState state;
	ProcessorType type;
public:
	Processor(ProcessorType t);

	int getExpectedFinishTime();
	void addProcess(Process* process);
	void finishProcess();
	virtual void executeNextProcess() = 0;
	virtual void sceduleAlgo() = 0;
	void updateState();
	int getUtilTime();
	
};