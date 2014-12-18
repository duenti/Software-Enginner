//CRIADO PELO USUÁRIO

#include <iostream>
#include "UserFlows.h"
#include <QMessageBox>

using namespace std;

Flow1::Flow1() : FlowHandle(){} //LOGISTICO
Flow1::Flow1(FlowHandle &f) : FlowHandle(f){}
//Flow1::~Flow1() : ~FlowHandle(){};
double Flow1::execute(){
    return this->getVal()*getOutTarget()*(1-getOutTarget()/this->getLimit());
}

Flow2::Flow2() : FlowHandle(){} //EXPONENCIAL
Flow2::Flow2(FlowHandle &f) : FlowHandle(f){}
double Flow2::execute(){
    return this->getVal() * getInTarget();
}
