#include "SJF.h"
SJFProcessor::SJFProcessor(ProcessorType type) : Processor(type) {

}
void SJFProcessor::executeNextProcess(){

}

void SJFProcessor::sceduleAlgo() {
	Process* p = readyProcesses.top();
	runProcesses.insert(p);
	readyProcesses.dequeue();
}
