#pragma once
#include "../MainProcessor.h"
class FCFSProcessor : public Processor {
	FCFSProcessor(ProcessorType type);
	virtual void executeNextProcess();
	virtual void sceduleAlgo();
};
