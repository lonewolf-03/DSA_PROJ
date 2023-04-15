#pragma once
#include "../Defs.h"
#include "../DataStructures/Queue/Queue.h"
/*Each process has the following information in the input file
1-AT
2-PID
3-CT
4-Number of times the process requests I/O
5-I/O_R and I/O_D
*/



class Process {
private:
	int PID;
	int AT;
	int RT;
	int CT;
	int TT;
	int TRT;
	int WT;
	int N; /*I/O Requests*/
	LinkedListQueue<int> IO_R;
	LinkedListQueue<int> IO_D;
	int size;
	ProcessState state;
	/*Processor* processor_ptr;*/ // to be added
	int rm_time;
	bool RT_set;
	bool TT_set;
	bool PID_set;
	bool AT_set;
	bool CT_set;
	bool N_set;
	bool IO_RD_set;
	Process* parent;

public:
	Process() {
		RT_set = false;
		TT_set = false;
		PID_set = false;
		AT_set = false;
		CT_set = false;
		N_set = false;
		IO_RD_set = false;
		state = NEW;
		parent = nullptr;
		RT = PID = AT = CT = TT = TRT = WT = N = size = rm_time = 0;
	}
	int GetPID() { return PID; }
	int GetAT() { return AT; }
	int GetCT() { return CT; }
	int GetTRT() { return (TT - AT); }
	int GetWT() { return (TRT - CT); }

	bool setPID(int PID1)
	{
		if (!PID_set) {
			PID_set = true;
			this->PID = PID;
			return true;
		}

		return false;
	}

	bool setCT(int CT1)
	{
		if (!CT_set) {
			CT_set = true;
			this->CT = CT;
			rm_time = CT;
			return true;
		}

		return false;
	}

	bool setAT(int AT1)
	{
		if (!AT_set) {
			AT_set = true;
			this->AT = AT;
			return true;
		}

		return false;
	}

	bool setIO(int N1)
	{
		if (!N_set) {
			N_set = true;
			this->N = N;
			if (N > 0) {

			}
			return true;
		}

		return false;
	}

	bool setIO_RD(int IOR, int IOD) {
		if (N_set && (IO_R.getCount() <= N) && (IO_D.getCount() <= N)) {
			IO_R.enqueue(IOR);
			IO_D.enqueue(IOD);
			return true;
		}

		return false;
	}

	bool setRT(int time)
	{
		if (!RT_set) {
			RT_set = true;
			this->RT = RT;
			return true;
		}

		return false;
	}

	bool setTT(int time)
	{
		if (!TT_set) {
			TT_set = true;
			this->TT = TT;
			this->TRT = this->TT - this->AT;
			this->WT = this->TRT - this->CT;
			return true;
		}

		return false;
	}

	bool setReq(int Req)
	{
		if (!N_set) {
			N_set = true;
			this->N = Req;
			return true;
		}

		return false;
	}

	int getReq()
	{

		return N;
	}

	ProcessState getState() { return state; }
	
	bool setState(ProcessState state) {
		if ((this->state == NEW) && (state != RDY)) {
			return false;
		}
		else if ((this->state == RDY) && (state != RUN)) {
			return false;
		}
		else if ((this->state == BLK) && (state != RDY)) {
			return false;
		}
		else if ((this->state == RUN) && (state == NEW)) {
			return false;
		}

		this->state = state;
		return true;
	}

	int getRemainingT()
	{
		return rm_time;
	}

	void Dec_RemT()
	{
		if (rm_time >= 0) {
			rm_time--;
		}
	}

	Process* getParent() {
		return parent;
	}

	void setParent(Process* p) {
		this->parent = p;
	}

};


