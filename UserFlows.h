//CRIADO PELO USUÁRIO

#ifndef USERFLOWS_H
#define USERFLOWS_H

#include "FlowImpl.h"

using namespace std;

class Flow1 : public FlowHandle{
    public:
        Flow1();
		Flow1(FlowHandle &);
		//~Flow1();
        double execute();
};

class Flow2 : public FlowHandle{
    public:
        Flow2();
        Flow2(FlowHandle &);
		//~Flow2();
		double execute();
};

#endif
