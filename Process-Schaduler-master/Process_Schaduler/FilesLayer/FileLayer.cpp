#include "FileLayer.h"
#include <iostream>
#include <fstream>
#include "../DataStructures/List/List.h"
#include "../Process/Process.h"

void FileLayer::loadInputFile(string filename, LinkedList<Process*>& new_list) {
	fstream stream;
	stream.open(filename);
	int fcfsNum = 0, sjfNum = 0, rrNum = 0;
	int rrTimeSlice; 
	int rtf, maxW, stl, forkProb;
	stream >> 
		fcfsNum >>
		sjfNum >> 
		rrNum >> 
		rrTimeSlice >>
		rtf >>
		maxW >> 
		stl >> 
		forkProb;
	int n; // number of processes
	stream >> n;
	int arrivalTime, pid, cpuTime, numOfIoReqs;
	int IO_R, IO_D;
	char parantheses, comma;
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
		new_list.append(p);
	}
	
	stream.close();
}
