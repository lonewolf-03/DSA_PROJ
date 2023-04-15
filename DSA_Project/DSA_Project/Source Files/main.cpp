#include <iostream>
#include "../UILayer/UI.h"

using namespace std;

int main() {
	Scheduler* s = new Scheduler;
	UI u(s);
	u.Start(1);
}