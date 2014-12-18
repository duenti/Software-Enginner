#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "ModelImpl.h"
#include <set>
#include <QMessageBox>

using namespace std;

ModelBody::ModelBody(){
	initialTime_ = 0;
	finalTime_ = 100;
	timeStep_ = 1;
}

ModelBody::ModelBody(int t0, int tf, int ts){
    initialTime_ = (t0 > 0) ? t0 : 0;
    finalTime_ = (t0 < tf) ? tf : 100;
    timeStep_ = (ts > 0) ? ts : 1;
}

ModelBody::ModelBody(const ModelBody &m){
	initialTime_ = m.initialTime_;
	finalTime_ = m.finalTime_;
	timeStep_ = m.timeStep_;

	for(int i = 0; i < m.flows_.size(); i++){
		flows_.push_back(m.flows_[i]);
	}
}

ModelBody& ModelBody::operator=(const ModelBody &m){
	if(&m == this) return *this;

	this->setInitialTime(m.initialTime_);
	this->setFinalTime(m.finalTime_);
	this->setTimeStep(m.timeStep_);

	for(int i = 0; i < m.flows_.size(); i++){
		this->addFlow(m.flows_[i]);
	}

	return *this;
}

ModelBody::~ModelBody(){
    flows_.clear();
}

int ModelBody::getInitialTime(){
	return initialTime_;
}

int ModelBody::getFinalTime(){
	return finalTime_;
}

int ModelBody::getTimeStep(){
	return timeStep_;
}

void ModelBody::setInitialTime(int t){
	initialTime_ = t;
}

void ModelBody::setFinalTime(int t){
	finalTime_ = t;
}

void ModelBody::setTimeStep(int t){
	timeStep_ = t;
}

void ModelBody::addFlow(Flow* f){
    flows_.push_back(f);
}

vector<Flow*> ModelBody::getFlows(){
    return flows_;
}

void ModelBody::deleteFlow(Flow* f){
    for (int i = 0; i < flows_.size(); i++){
        if (f->getID() == flows_.at(i)->getID())
            flows_.erase(flows_.begin()+i);
    }
}

int ModelBody::sizeFlows(){
	return flows_.size();
}

void ModelBody::execute(System* sys){
    vector<double> flowsExecuted;
    //QMessageBox msg;

	//cout << 0 << " - " << sys->getValue() << endl;
	sys->addResult(sys->getValue());

	//LOOP PRINCIPAL
	for(int t = initialTime_; t < finalTime_; t += timeStep_){

		//para cada fluxo “i” pertencente ao modelo { v[i] = fluxo[i].executa( ); }
		for(int i = 0; i < flows_.size(); i++){
			flowsExecuted.push_back(flows_.at(i)->execute());
		}
		
		for(int i = 0; i < flows_.size(); i++){
			
			flows_.at(i)->redTarget(flowsExecuted[i]);

			flows_.at(i)->addTarget(flowsExecuted[i]);
		}
		flowsExecuted.clear();

		sys->addResult(sys->getValue());
	}
}
