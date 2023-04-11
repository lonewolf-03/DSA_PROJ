#include "FCFS.h"
FCFSProcessor::FCFSProcessor(ProcessorType type) : Processor(type) {

}
void FCFSProcessor::executeNextProcess() {

}

void FCFSProcessor::sceduleAlgo() {
	Process* p = readyProcesses.top();
	runProcesses.insert(p);
	readyProcesses.dequeue();
}
