#pragma once
#include "../../Scheduler/Scheduler.h"


class RRProcessor : public Processor {
private:
	int timeSlice;
	int RTF;
	int CurrProcTime; // to track for how long has the process been in the processor
	LinkedList<Process*> readyProcesses;
public:
	RRProcessor() : Processor(RR), CurrProcTime(0) {
		runningProc = nullptr;
	}

	void scheduleAlgo() {
		Process* p;
		if (runningProc) {
			if (runningProc->getRemainingT() > 0) {
				if (CurrProcTime == RTF) {
					p->setState(RDY);
					readyProcesses.insert_beginning(p);
					CurrProcTime = 0;
					runningProc = nullptr;
				}
				else {
					runningProc->Dec_RemT();
				}
			}
			else {
				scheduler->toTRM(runningProc);
				runningProc = nullptr;
				numOfProcesses--;
				if (readyProcesses.pop(p)) {
					p->setState(RUN);
					runningProc = p;
					p->Dec_RemT();
					CurrProcTime++;
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
	
	int getTimeSlice() { return timeSlice; }

	int getRTF() { return RTF; }

	void setTimeSlice(int n) { this->timeSlice = n; }

	void setRTF(int n) { this->RTF = n; }
	
	void updateState() {
		if (readyProcesses.isEmpty()) state = IDLE;
		else state = BUSY;
	}

	LinkedList<Process*>* getRDYList() {
		return &(readyProcesses);
	}

	PriorityQueue<Process*>* getRDYQueue() {
		return nullptr;
	}
};