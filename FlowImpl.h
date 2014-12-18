#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include "SystemImpl.h"
#include "Flow.h"

using namespace std;

#ifndef FLOW_BODY_H
#define FLOW_BODY_H

#define DEBUGING
#ifdef DEBUGING
    extern int numHandleCreated;
	extern int numHandleDeleted;
	extern int numBodyCreated;
	extern int  numBodyDeleted;
#endif

class FlowBody : public Body{
public:
	FlowBody();
	virtual ~FlowBody();

	virtual double getInTarget();
	virtual double getOutTarget();
    virtual string getName();
    virtual double getVal();
    virtual double getLimit();
    virtual void setVal(double);
    virtual void setLimit(double);
    virtual void setName(string);
	virtual void addTarget(double);
	virtual void redTarget(double);
	virtual void setInSystem(System*);
	virtual void setOutSystem(System*);
	virtual System* getInSystem();
	virtual System* getOutSystem();
    virtual int getID();
	virtual void setID(int);

private:
	FlowBody(const FlowBody&);
	FlowBody& operator=(const FlowBody&);

protected:
	int idsav_;
    string name_;
    double val_;
    double limit_;
	System* in_;
	System* out_;
};

#endif

#ifndef FLOWHANDLE_H_
#define FLOWHANDLE_H_

class FlowHandle : public Flow, public Handle<FlowBody>{

public:
	FlowHandle(){
		pImpl_->attach();
	}

	virtual ~FlowHandle(){
		pImpl_->detach();
	}

	virtual double getInTarget(){ return pImpl_->getInTarget();}
	virtual double getOutTarget(){ return pImpl_->getOutTarget();}
    virtual string getName(){ return pImpl_->getName();}
    virtual double getVal(){ return pImpl_->getVal();}
    virtual double getLimit(){ return pImpl_->getLimit();}
    virtual void setVal(double t){ return pImpl_->setVal(t);}
    virtual void setLimit(double t){return pImpl_->setLimit(t);}
    virtual void setName(string t) { return pImpl_->setName(t);}
	virtual void addTarget(double t){ return pImpl_->addTarget(t);}
	virtual void redTarget(double t){ return pImpl_->redTarget(t);}
	virtual void setInSystem(System* s){ return pImpl_->setInSystem(s);}
	virtual void setOutSystem(System* s){ return pImpl_->setOutSystem(s);}
	virtual System* getInSystem(){ return pImpl_->getInSystem();}
	virtual System* getOutSystem(){ return pImpl_->getOutSystem();}
	virtual int getID(){ return pImpl_->getID();}
	virtual void setID(int id){return pImpl_->setID(id);}
};



#endif
