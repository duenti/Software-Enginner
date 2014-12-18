#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>
#include "FlowImpl.h"
#include <QMessageBox>

using namespace std;

FlowBody::FlowBody(){
}

FlowBody::FlowBody(const FlowBody &f){
	idsav_ = f.idsav_;
	in_ = f.in_;
	out_ = f.out_;
}

FlowBody& FlowBody::operator=(const FlowBody &f){
	
	if(this == &f) return *this;

	idsav_ = f.idsav_;
	this->setInSystem(f.in_);
	this->setOutSystem(f.out_);

	return *this;
}

FlowBody::~FlowBody(){

}

int FlowBody::getID(){
    return idsav_;
}

double FlowBody::getVal(){
    return val_;
}

double FlowBody::getLimit(){
    return limit_;
}

void FlowBody::setVal(double v){
    val_ = v;
}

void FlowBody::setLimit(double l){
    limit_ = l;
}

double FlowBody::getInTarget(){
	return this->getInSystem()->getValue();
}

double FlowBody::getOutTarget(){
	return this->getOutSystem()->getValue();
}

string FlowBody::getName(){
    return name_;
}

void FlowBody::setName(string s){
    name_ = s;
}

void FlowBody::addTarget(double x){
	this->getOutSystem()->addValue(x);
}

void FlowBody::redTarget(double x){
	this->getInSystem()->redValue(x);
}

void FlowBody::setInSystem(System* s){
	in_ = s;
}

void FlowBody::setOutSystem(System* s){
	out_ = s;
}

System* FlowBody::getInSystem(){
	return in_;
}

System* FlowBody::getOutSystem(){
	return out_;
}


void FlowBody::setID(int x){
	idsav_ = x;
}
