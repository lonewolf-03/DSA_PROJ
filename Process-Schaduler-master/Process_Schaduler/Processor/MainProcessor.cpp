#include "MainProcessor.h"

Processor::Processor(ProcessorType t) {
	type = t;
	state = IDLE;
	exepectedTimeToFinish = 0;
}

int Processor::getExpectedFinishTime() {
	return this->exepectedTimeToFinish;
}

void Processor::addProcess(Process* process) {
	readyProcesses.enqueue(process);
	exepectedTimeToFinish += process->GetCT();
}

void Processor::finishProcess() {
	if (!readyProcesses.isEmpty()) {
		Process* p = readyProcesses.top();
		exepectedTimeToFinish -= p->cpuTime;
		readyProcesses.dequeue();
	}
}

void Processor::updateState() {
	if (readyProcesses.isEmpty()) state = IDLE;
	else state = BUSY;
}

int Processor::getUtilTime() {
	return 100;
}