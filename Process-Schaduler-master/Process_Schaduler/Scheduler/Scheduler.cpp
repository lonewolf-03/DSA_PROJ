#include "Scheduler.h"
#include "../Processor/MainProcessor.h"
#include "../FilesLayer/FileLayer.h"

Scheduler::Scheduler(): input_filename("input.txt"), output_filename("output.txt") {}

void Scheduler::nextTimeStep() {
	
}

Processor* Scheduler::getShortestProcessor() {
	Processor* minProcessor = null;
	int minTime = INT_MAX;
	int count = processors.getLength();
	for (int i = 0; i < count; i++) {
		if (processors.getEntry(i)->getExpectedFinishTime() < minTime) {
			minTime = processors.getEntry(i)->getExpectedFinishTime();
			minProcessor = processors.getEntry(i);
		}
	}
	return minProcessor;
}

void Scheduler::loadProcess() {
	FileLayer f;
	f.loadInputFile(input_filename, NEWList);
	int count = NEWList.getLength();
}

void Scheduler::NEWToRDY(Processor* p) {
	if (NEWList.getLength() == 0) return;

	// finding the process with the  earliest arrival time
	int min = 0;
	Process* minProc = null;
	for (int i = 0; i < NEWList.getLength(); i++) {
		if (NEWList.getEntry(i)->GetAT() < min) {
			min = NEWList.getEntry(i)->GetAT();
			minProc = NEWList.getEntry(i);
		}
	}
	Processor* prr = getShortestProcessor();
	prr->addProcess(minProc);
	minProc->setState(RDY);
	NEWList.remove_entry(minProc);
}


// modifcation stops here
void Scheduler::RUNtoBLK(Process* p) {
	// Call UI To Get Input
	BLKList.insert(p);
	p->state = BLK;
}

// System Process and User Process. 
// Page 7 .
void Scheduler::BLKtoRDY(Process* p) {
	Processor* proc = getShortestProcessor();
	proc->readyProcesses.enQueue(p);
	p->state = RDY;
	BLKList.Delete(p);
}

void Scheduler::toTRM(Process* p) {
	TRMList.insert(p);
	p->state = TRM;
}
