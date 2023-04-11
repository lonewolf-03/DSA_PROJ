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

class IO_Pair {
public:
	int IO_R;
	int IO_D;
};

class Process
{
private:
	int PID;
	int AT;
	int RT;
	int CT;
	int TT;
	int TRT;
	int WT;
	int N; /*I/O Requests*/
	Queue<int> IO_R;
	Queue<int> IO_D;
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

public:
	int GetPID();
	int GetAT();
	int GetCT();
	int GetTRT();
	int GetWT();

	bool setPID(int PID);
	bool setCT(int CT);
	bool setAT(int AT);
	bool setIO(int N);
	bool setIO_RD(int IOR, int IOD);
	bool setTT(int time);
	bool setRT(int time);

	bool setReq(int Req);

	int getReq();
	ProcessState getState();
	bool setState(ProcessState state);

	int getRemainingT();
	void Dec_RemT();


};


