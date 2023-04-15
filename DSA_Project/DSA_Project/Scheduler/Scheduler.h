#pragma once
#include "../DataStructures/List/ListADT.h"
#include "../DataStructures/PQueue/PQueue.h"
#include "../Process/Process.h"
#include "../Processor/FCFS/FCFSProcessor.h"
#include "../Processor/SJF/SJFProcessor.h"
#include "../Processor/RR/RRProcessor.h"
#include "../Processor/Processor.h"
#include <fstream>

using namespace std;



class Scheduler {
private:
	string output_filename;
	int curr_time_step;
	int stl;
	LinkedList<Process*> NEWList;
	LinkedList<Process*> TRMList;
	LinkedList<Process*> BLKList;
	LinkedList<Processor*> processors;
	float getWorkStealPercentage() { return 0; }
	float getForkedProcessPercentage() { return 0; }
	float getKilledProcessPercentage() { return 0; }
	float getRTF() { return 0; }
	Processor* getShortestProcessor() {
		Processor* minProcessor = nullptr;
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
public:

	Scheduler() : output_filename("output.txt"), curr_time_step(1) {}

	void update() {
		curr_time_step++;
		Process* proc;
		if (NEWList.pop(proc)) {
			Processor* p = getShortestProcessor();
			p->addProcess(proc);
			int processors_count = processors.getLength();
			for (int i = 0; i < processors_count; i++) {
				processors.getEntry(i)->scheduleAlgo();
			}
		}
	}

	int getTimeStep() {
		return curr_time_step;
	}


	void loadProcess(string filename) { // and processors
		ifstream stream;
		stream.open("C:\\Users\\noname\\Desktop\\DSA_Project\\DSA_Project\\DSA_Project\\" + filename);
		stream.seekg(0, ios::beg);
		int fcfsNum = 0, sjfNum = 0, rrNum = 0;
		int rrTimeSlice;
		int rtf, maxW, stl, forkProb;
		stream >> fcfsNum;
		stream >> sjfNum;
		stream >> rrNum;
		stream >> rrTimeSlice;
		stream >> rtf;
		stream >> maxW;
		stream >> stl;
		stream >> forkProb;
		int n; // number of processes
		stream >> n;
		int arrivalTime, pid, cpuTime, numOfIoReqs;
		int IO_R, IO_D;
		char parantheses, comma;

		// set stl
		this->stl = stl;

		// load processors
		for (int i = 0; i < fcfsNum; i++) {
			FCFSProcessor* p = new FCFSProcessor();
			p->setMaxW(maxW);
			p->setForkProb(forkProb);
			processors.append(p);
		}

		for (int i = 0; i < rrNum; i++) {
			RRProcessor* p = new RRProcessor();
			p->setRTF(rtf);
			p->setTimeSlice(rrTimeSlice);
			processors.append(p);
		}

		for (int i = 0; i < sjfNum; i++) {
			SJFProcessor* p = new SJFProcessor();
			processors.append(p);
		}


		// load processes
		for (int i = 0; i < n; i++) {
			Process* p = new Process();
			stream >> arrivalTime >> pid >> cpuTime >> numOfIoReqs;
			p->setAT(arrivalTime);
			p->setPID(pid);
			p->setCT(cpuTime);
			p->setIO(numOfIoReqs);
			for (int i = 0; i < numOfIoReqs - 1; i++) {
				stream >> parantheses >> IO_R >> comma >> IO_D >> parantheses;
				p->setIO_RD(IO_R, IO_D);
				stream >> comma;
			}
			stream >> parantheses >> IO_R >> comma >> IO_D >> parantheses;
			p->setIO_RD(IO_R, IO_D);
			NEWList.append(p);
		}

		stream.close();



	}

	void NEWToRDY(Processor* p) {
		if (NEWList.getLength() == 0) return;

		// finding the process with the  earliest arrival time
		int min = 0;
		Process* minProc = nullptr;
		for (int i = 0; i < NEWList.getLength(); i++) {
			if (NEWList.getEntry(i)->GetAT() < min) {
				minProc = NEWList.getEntry(i);
				min = minProc->GetAT();
			}
		}
		Processor* prr = getShortestProcessor();
		prr->addProcess(minProc);
		minProc->setState(RDY);
		NEWList.remove_entry(minProc);
	}

	void RUNtoBLK(Process* p) {
		// Call UI To Get Input
		BLKList.append(p);
		p->setState(BLK);
	}

	void BLKtoRDY(Process* p) {
		Processor* proc = getShortestProcessor();
		proc->addProcess(p);
		p->setState(RDY);
		BLKList.remove_entry(p);
	}

	void toTRM(Process* p) {
		TRMList.insert_beginning(p);
		p->setState(TERM);
	}

	// methods used for statistics needed for output file
	bool isDone() {
		return (NEWList.getLength() == 0);
	}

	LinkedList<Process*>* getTRMPtr() {
		LinkedList<Process*>* ptr = &TRMList;
		return ptr;
	}

	LinkedList<Process*>* getBLKPtr() {
		LinkedList<Process*>* ptr = &BLKList;
		return ptr;
	}

	LinkedList<Processor*>* getProcessorsPtr() {
		LinkedList<Processor*>* ptr = &processors;
		return ptr;
	}
};