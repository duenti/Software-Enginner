#if ! defined(FLOW_H_)
#define FLOW_H_

#include <iostream>
#include "System.h"

using namespace std;

class Flow {
public:
	virtual double getInTarget() = 0;
	virtual double getOutTarget() = 0;
    virtual void setName(string) = 0;
    virtual string getName() = 0;
    virtual double getVal() = 0;
    virtual double getLimit() = 0;
    virtual void setVal(double) = 0;
    virtual void setLimit(double) = 0;
	virtual void addTarget(double) = 0;
	virtual void redTarget(double) = 0;
	virtual void setInSystem(System*) = 0;
	virtual void setOutSystem(System*) = 0;
	virtual System* getInSystem() = 0;
	virtual System* getOutSystem() = 0;
    virtual double execute() = 0;
    virtual int getID() = 0;
	virtual void setID(int) = 0;
};

#endif /* FLOW_H_ */
