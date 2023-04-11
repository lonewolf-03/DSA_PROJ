#pragma once
#include "../MainProcessor.h"
class SJFProcessor : public Processor {
	SJFProcessor(ProcessorType type);
	virtual void executeNextProcess();
	virtual void sceduleAlgo();
};