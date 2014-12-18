#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "SystemImpl.h"

using namespace std;

SystemBody::SystemBody(){
	this->setValue(0);
}

SystemBody::SystemBody(double n){
    setValue(n);
}

SystemBody::SystemBody(const SystemBody& s){
	idsav_ = s.idsav_;
	value_ = s.value_;

	result_.clear();
	for(int i = 0; i < s.result_.size(); i++){
		result_.push_back(s.result_[i]);
	}
}

SystemBody& SystemBody::operator=(const SystemBody &s){
	if(&s == this) return *this;

	this->setID(s.idsav_);
	this->setValue(s.value_);

	this->result_.clear();
	for(int i = 0; i < s.result_.size(); i++){
		this->result_.push_back(s.result_[i]);
	}

	return *this;
}

SystemBody::~SystemBody(){

}

void SystemBody::setValue(double v){
    value_ = v;
}

void SystemBody::addValue(double x){
	value_ += x;
}

void SystemBody::redValue(double x){
	value_ -= x;
}

string SystemBody::getName(){
    return name_;
}

void SystemBody::setName(string s){
    name_ = s;
}

double SystemBody::getValue(){
	return value_;
}

void SystemBody::addResult(double i){
	result_.push_back(i);
}

void SystemBody::clearResult(){
	result_.clear();
}

vector<double> SystemBody::impress(){
    return result_;
    //for(int i = 0; i < result_.size(); i++){
      //  cout << i << " - " << result_.at(i) << endl;
    //}

}

int SystemBody::getID(){
    return idsav_;
}

void SystemBody::setID(int x){
	idsav_ = x;
}
