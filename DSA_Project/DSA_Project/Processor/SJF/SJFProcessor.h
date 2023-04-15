#pragma once
#include "../../Scheduler/Scheduler.h"
#include "../../DataStructures/PQueue/PQueue.h"


class SJFProcessor : public Processor {
private:
	PriorityQueue<Process*> readyProcesses;
public:
	SJFProcessor() : Processor(SJF) {
		runningProc = nullptr;
	}

	Process* FindShortestJob() {
		int min_time = INT_MAX;
		Process* shortest_proc = nullptr;
		for (int i = 0; i < readyProcesses.getCount(); i++) {
			if (readyProcesses.getElementAt(i)->getRemainingT() < min_time) {
				min_time = readyProcesses.getElementAt(i)->getRemainingT();
				shortest_proc = readyProcesses.getElementAt(i);
			}
		}

		return shortest_proc;
	}

	void scheduleAlgo() {
		if (runningProc) {
			if (runningProc->getRemainingT() > 0) {
				runningProc->Dec_RemT();
			}
			else {
				scheduler->toTRM(runningProc);
				numOfProcesses--;
				runningProc = FindShortestJob();
				if (runningProc) {
					runningProc->setState(RUN);
					runningProc->Dec_RemT();
				}
			}
		}
	}

	int getExpectedFinishTime() {
		return this->exepectedTimeToFinish;
	}

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


	void addProcess(Process* process) {
		readyProcesses.enqueue(process, process->GetAT());
		numOfProcesses++;
	}

	void updateState() {
		if (readyProcesses.isEmpty()) state = IDLE;
		else state = BUSY;
	}

	PriorityQueue<Process*>* getRDYQueue() {
		return &(readyProcesses);
	}

	LinkedList<Process*>* getRDYList() {
		return nullptr;
	}
};