#include <cstdlib>

#include "Factory.h"

Factory* Factory::singleton = NULL;

Factory::Factory() {

}

Model* Factory::modelCreator(int ti, int tf, int ts){
	Model* m = new ModelHandle(ti, tf, ts);
	models_.push_back(m);
	return m;
}

Model* Factory::modelCreator(){
	Model* m = new ModelHandle();
	models_.push_back(m);
	return m;
}

void Factory::destroyModels(){
	for(int i = 0; i < models_.size(); i++){
		models_.at(i);
	}

	models_.clear();
}

System* Factory::systemCreator(double n){
	System* s = new SystemHandle(n);
	sysID_++;
	s->setID(sysID_);
	systens_.push_back(s);
	return s;
}

System* Factory::systemCreator(){
	System* s = new SystemHandle();
	
	sysID_++;
	s->setID(sysID_);

	systens_.push_back(s);
	
	return s;
}

void Factory::destroySystens(){
	for(int i = 0; i < systens_.size(); i++){
		delete [] systens_.at(i);
	}
	systens_.clear();
}

void Factory::destroyFlows(){
	for(int i = 0; i < flows_.size(); i ++){
		delete[] flows_.at(i);
	}
	flows_.clear();
}

vector<Flow*> Factory::getAllFlows(){
    return flows_;
}

vector<System*> Factory::getAllSystens(){
    return systens_;
}

Factory* Factory::getInstance(){
	if (singleton == NULL)
		singleton = new Factory();
	return singleton;
}

Factory::~Factory() {
	free(singleton);
	delete this;
}

