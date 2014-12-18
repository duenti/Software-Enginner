#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "Model.h"
#include "FlowImpl.h"
#include "SystemImpl.h"

using namespace std;

#ifndef MODEL_BODY_H
#define MODEL_BODY_H

#define DEBUGING
#ifdef DEBUGING
	extern int numHandleCreated;
	extern int numHandleDeleted;
	extern int numBodyCreated;
	extern int numBodyDeleted;
#endif

class ModelBody : public Body{
public:
	ModelBody();
	ModelBody(int,int,int);
	virtual ~ModelBody();

	virtual int getInitialTime();
	virtual int getFinalTime();
	virtual int getTimeStep();
    virtual void setInitialTime(int);
	virtual void setFinalTime(int);
	virtual void setTimeStep(int);
	virtual void addFlow(Flow*);
    virtual vector<Flow*> getFlows();
	virtual int sizeFlows();
    virtual void deleteFlow(Flow*);
    virtual void execute(System*);

private:
	ModelBody(const ModelBody&);
	ModelBody& operator=(const ModelBody&);	

protected:
	int initialTime_;
    int finalTime_;
    int timeStep_;
	vector<Flow*> flows_;
};

#endif

#ifndef MODELHANDLE_H_
#define MODELHANDLE_H_

class ModelHandle : public Model, public Handle<ModelBody>{

public:
	ModelHandle(){
		pImpl_->setInitialTime(0);
		pImpl_->setFinalTime(100);
		pImpl_->setTimeStep(1);
		pImpl_->attach();
	}

	/// constructor
	ModelHandle(int t0, int tf, int ts){  
		pImpl_->setInitialTime(t0);
		pImpl_->setFinalTime(tf);
		pImpl_->setTimeStep(ts);
        pImpl_->attach();
	}

	virtual ~ModelHandle(){
		pImpl_->detach();
	}

	virtual int getInitialTime(){ return pImpl_->getInitialTime();}
	virtual int getFinalTime(){ return pImpl_->getFinalTime();}
	virtual int getTimeStep(){ return pImpl_->getTimeStep();}
	virtual void setInitialTime(int t){ return pImpl_->setInitialTime(t);}
	virtual void setFinalTime(int t){ return pImpl_->setFinalTime(t);}
	virtual void setTimeStep(int t){ return pImpl_->setTimeStep(t);}
	virtual void addFlow(Flow* f){ return pImpl_->addFlow(f);}
    virtual vector<Flow*> getFlows(){ return pImpl_->getFlows();}
	virtual int sizeFlows(){ return pImpl_->sizeFlows();}
	virtual void deleteFlow(Flow* f){ return pImpl_->deleteFlow(f);}
	virtual void execute(System* s){ return pImpl_->execute(s);}
};
#endif
