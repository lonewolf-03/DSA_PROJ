#pragma once
#include "../Defs.h"
#include "../Process/Process.h"
#include "../DataStructures/PQueue/PQueue.h"
#include "../DataStructures/List/ListADT.h"

class Scheduler;

class Processor {
protected:
	int exepectedTimeToFinish;
	int numOfProcesses;
	Process* runningProc;
	ProcessorState state;
	ProcessorType type;
	Scheduler* scheduler;
public:
	Processor(ProcessorType t) {
		type = t;
		state = IDLE;
		exepectedTimeToFinish = 0;
		numOfProcesses = 0;
	}

	virtual int getExpectedFinishTime() {
		return this->exepectedTimeToFinish;
	}

	virtual void addProcess(Process* process) = 0;
	// void finishProcess();
	virtual void scheduleAlgo() = 0;

	int getUtilTime() { return 0; }
	int getLoad() { return 0; }

	int getNumOfProcesses() {
		return numOfProcesses;
	}

	string getTypeString() {
		switch (type) {
		case(FCFS):
			return "FCFS";
		case(SJF):
			return "SJF";
		case(RR):
			return "RR";
		}
	}

	Process* getRunningProcPtr() { return runningProc; }

	virtual PriorityQueue<Process*>* getRDYQueue() = 0;
	virtual LinkedList<Process*>* getRDYList() = 0;
};