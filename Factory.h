#ifndef FACTORY_H_
#define FACTORY_H_

#include "ModelImpl.h"
#include "SystemImpl.h"
#include "FlowImpl.h"
#include "UserFlows.h"
#include "HandleBody.h"

class Factory {
public:
	Model* modelCreator(int, int, int);
	Model* modelCreator();
	void destroyModels();
	System* systemCreator(double);
	System* systemCreator();
	void destroySystens();
	void destroyFlows();
	template <class T> Flow* flowCreator();
	static Factory* getInstance();
	virtual ~Factory();
    vector<Flow*> getAllFlows();
    vector<System*> getAllSystens();
private:
	static int sysID_;
	static int flowID_;
	vector<Model*> models_;
	vector<System*> systens_;
	vector<Flow*> flows_;
	Factory();
	static Factory* singleton;
};

template <class T> 
Flow* Factory::flowCreator(){
	Flow* f = new T();
	
	flowID_++;
	f->setID(flowID_);

    flows_.push_back(f);

	return f;
}

#endif /* FACTORY_H_ */
