#pragma once
#include"../Processor/Processor.h"
#include "../DataStructures/List/ListADT.h"
#include "../DataStructures/Queue/Queue.h"
#include "../Scheduler/Scheduler.h"
#include <iostream>

class UI {
private:
	int mode;
	Scheduler* schedular;
	void getInputFile() {
		std::cout << "Enter filename: ";
		string filename;
		std::cin >> filename;
		schedular->loadProcess(filename);
	}

	void RunInteractiveMode() {
		while (!schedular->isDone()) {
			cin.get();
			std::cout << "Current Timestep: " << schedular->getTimeStep() << "\n";
			PrintRDYLists();
			PrintBLKList();
			PrintRUNProcesses();
			PrintTRMList();
			std::cout << "PRESS ANY KEY TO CONTINUE\n";
			schedular->update();
		}
	}

	void RunSilentMode() {}
	void RunStpByStpMode() {}

	void PrintRDYLists() {
		LinkedList<Processor*>* processors_list = schedular->getProcessorsPtr();
		Processor* curr_processor;
		std::cout << "--------------------  RDY Processes  --------------------\n";
		for (int i = 0; i < processors_list->getLength(); i++) {
			curr_processor = processors_list->getEntry(i);
			std::cout << "Processor " << i + 1 << " [ " << curr_processor->getTypeString() << " ]: " << curr_processor->getNumOfProcesses() << " RDY: ";
			if (curr_processor->getTypeString() == "FCFS" || curr_processor->getTypeString() == "RR") {
				for (int i = 0; i < curr_processor->getNumOfProcesses(); i++) {
					std::cout << curr_processor->getRDYList()->getEntry(i)->GetPID() << " ";
				}
			}
			else {
				for (int i = 0; i < curr_processor->getNumOfProcesses(); i++) {
					std::cout << curr_processor->getRDYQueue()->getElementAt(i)->GetPID() << " ";
				}
			}

			std::cout << '\n';

		}
	}

	void PrintBLKList() {
		std::cout << "--------------------  BLK Processes  --------------------\n";
		std::cout << endl;
	}

	void PrintRUNProcesses() {
		LinkedList<Processor*>* processors_list = schedular->getProcessorsPtr();
		std::cout << "--------------------  RUN Processes  --------------------\n";
		int processors_count = processors_list->getLength();
		std::cout << processors_count << " RUN: ";
		for (int i = 0; i < processors_count; i++) {
			std::cout << processors_list->getEntry(i)->getRunningProcPtr()->GetPID() << "P(" << i + 1 << "), ";
		}
		std::cout << '\n';
	}

	void PrintTRMList() {
		LinkedList<Process*>* processors_list = schedular->getTRMPtr();
		std::cout << "--------------------  TRM Processes  --------------------\n";
		int trm_count = processors_list->getLength();
		for (int i = 0; i < trm_count; i++) {
			std::cout << processors_list->getEntry(i)->GetPID() << ", ";
		}
		std::cout << '\n';
	}
public:
	UI(Scheduler* s) : schedular(s) {}

	void Start(int mode) {
		this->mode = mode;
		std::cout << "Choose one of the three modes (Interactive(1)\\ step-by-step(2)\\ silent(3)): ";
		std::cin >> mode;
		switch (mode) {
		case(1):
			getInputFile();
			RunInteractiveMode();
			break;
		case(2):
			getInputFile();
			RunStpByStpMode();
			break;
		case(3):
			getInputFile();
			RunSilentMode();
			break;
		default:
			std::cout << "Invalid Choice \n";
			break;
		}
	}
};