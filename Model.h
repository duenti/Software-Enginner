#ifndef MODEL_H_
#define MODEL_H_

#include <iostream>
#include <vector>
#include "Flow.h"

using namespace std;

class Model {
public:
	virtual int getInitialTime() = 0;
	virtual int getFinalTime() = 0;
	virtual int getTimeStep() = 0;
    virtual void setInitialTime(int) = 0;
	virtual void setFinalTime(int) = 0;
	virtual void setTimeStep(int) = 0;
	virtual void addFlow(Flow*) = 0;
    virtual vector<Flow*> getFlows() = 0;
	virtual int sizeFlows() = 0;
    virtual void deleteFlow(Flow*) = 0;
    virtual void execute(System*) = 0;
};

#endif /* MODEL_H_ */
