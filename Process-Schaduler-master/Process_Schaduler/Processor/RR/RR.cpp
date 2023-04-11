#pragma once
#include "RR.h"
RRProcessor::RRProcessor(ProcessorType type) : Processor(type) {
	timeSlice = 0;
}
void RRProcessor::executeNextProcess() {

}

void RRProcessor::sceduleAlgo() {
	Process* p = readyProcesses.top();
	runProcesses.insert(p);
	readyProcesses.dequeue();
}
