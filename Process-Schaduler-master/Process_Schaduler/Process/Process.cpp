#include "Process.h"


Process::Process() {
	RT_set = false;
	TT_set = false;
	PID_set = false;
	AT_set = false;
	CT_set = false;
	N_set = false;
	IO_RD_set = false;
	state = NEW;
}

int Process::GetPID()
{
	return PID; /*Assuming I have PID from input file*/
}

int Process::GetAT()
{
	return AT; /*Assuming I have AT from input file*/
}

int Process::GetCT()
{
	return CT; /*Assuming I have CT from input file*/
}

int Process::GetTRT()
{

	return (TT - AT);
}

int Process::GetWT()
{
	return (TRT - CT);
}



bool Process::setPID(int PID1)
{
	if (!PID_set) {
		PID_set = true;
		this->PID = PID;
		return true;
	}

	return false;
}

bool Process::setCT(int CT1)
{
	if (!CT_set) {
		CT_set = true;
		this->CT = CT;
		rm_time = CT;
		return true;
	}

	return false;
}

bool Process::setAT(int AT1)
{
	if (!AT_set) {
		AT_set = true;
		this->AT = AT;
		return true;
	}

	return false;
}

bool Process::setIO(int N1)
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

bool Process::setIO_RD(int IOR, int IOD) {
	if (N_set && (IO_R.getCount() <= N) && (IO_D.getCount() <= N)){
		IO_R.enqueue(IOR);
		IO_D.enqueue(IOD);
		return true;
	}

	return false
}

bool Process::setRT(int time)
{
	if (!RT_set) {
		RT_set = true;
		this->RT = RT;
		return true;
	}

	return false;
}

bool Process::setTT(int time)
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


bool Process::setReq(int Req)
{
	if (!N_set) {
		N_set = true;
		this->N = Req;
		return true;
	}

	return false;
}
int Process::getReq()
{

	return N;
}

ProcessState Process::getState() { return state; }

bool Process::setState(ProcessState state) {
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

int Process::getRemainingT()
{

	return rm_time;
}

void Process::Dec_RemT()
{
	if (rm_time >= 0) {
		rm_time--;
	}
}
