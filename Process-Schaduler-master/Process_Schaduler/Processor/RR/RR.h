#pragma once
#include "../MainProcessor.h"
class RRProcessor : public Processor {
	int timeSlice;

	RRProcessor(ProcessorType type);
	virtual void executeNextProcess();
	virtual void sceduleAlgo();
};