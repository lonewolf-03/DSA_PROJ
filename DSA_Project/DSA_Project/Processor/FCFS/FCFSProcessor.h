#pragma once
#include "../../Scheduler/Scheduler.h"


class FCFSProcessor : public Processor {
private:
	int MaxW;
	int fork_probability;
	LinkedList<Process*> readyProcesses;
public:
	FCFSProcessor() : Processor(FCFS) {
		this->MaxW = MaxW;
		runningProc = nullptr;
	}

	void scheduleAlgo() {
		Process* p;
		if (runningProc) {
			if (runningProc->getRemainingT() > 0) {
				runningProc->Dec_RemT();
			}
			else {
				scheduler->toTRM(runningProc);
				numOfProcesses--;
				runningProc = nullptr;
				if (readyProcesses.pop(p)) {
					p->setState(RUN);
					runningProc = p;
					p->Dec_RemT();
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

	void addProcess(Process* process) {
		readyProcesses.insert_beginning(process);
		numOfProcesses++;
	}

	int getMaxW() {
		return MaxW;
	}

	int getForkProb() {
		return fork_probability;
	}

	void updateState() {
		if (readyProcesses.isEmpty()) state = IDLE;
		else state = BUSY;
	}

	void setMaxW(int m) { this->MaxW = m; }

	void setForkProb(int m) { this->fork_probability = m; }

	Process* getRunningProcess() { return runningProc; }

	LinkedList<Process*>* getRDYList() {
		return &(readyProcesses);
	}

	PriorityQueue<Process*>* getRDYQueue() {
		return nullptr;
	}
};