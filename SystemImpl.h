#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "System.h"
#include "HandleBody.h"

using namespace std;

#ifndef SYSTEM_BODY_H
#define SYSTEM_BODY_H

#define DEBUGING
#ifdef DEBUGING
    extern int numHandleCreated;
	extern int numHandleDeleted;
	extern int numBodyCreated;
	extern int  numBodyDeleted;
#endif

class SystemBody : public Body{
public:
	SystemBody();
	SystemBody(double v);
	virtual ~SystemBody();

	virtual void setValue(double);
	virtual void addValue(double);
	virtual void redValue(double);
    virtual string getName();
    virtual void setName(string);
    virtual double getValue();
	virtual void addResult(double);
	virtual void clearResult();
    virtual vector<double> impress();
    virtual int getID();
	virtual void setID(int);

private:
	SystemBody(const SystemBody&);
	SystemBody& operator=(const SystemBody&);

protected:
    int idsav_;
    string name_;
    double value_;
	vector<double> result_;
};

#endif

#ifndef SYSTEMHANDLE_H_
#define SYSTEMHANDLE_H_

class SystemHandle : public System, public Handle<SystemBody>
{

public:
	SystemHandle(){
		pImpl_->setValue(0);
		pImpl_->attach();
	}

	SystemHandle(double n){
		pImpl_->setValue(n);
        pImpl_->attach();
	}

	virtual ~SystemHandle(){
		pImpl_->detach();
	}

	virtual void setValue(double v){ return pImpl_->setValue(v);}
	virtual void addValue(double v){ return pImpl_->addValue(v);}
	virtual void redValue(double v){ return pImpl_->redValue(v);}
    virtual string getName(){ return pImpl_->getName();}
    virtual void setName(string t) { return pImpl_->setName(t);}
    virtual double getValue(){ return pImpl_->getValue();}
	virtual void addResult(double r){ return pImpl_->addResult(r);}
	virtual void clearResult(){ return pImpl_->clearResult();}
    virtual vector<double> impress(){return pImpl_->impress();}
	virtual int getID(){return pImpl_->getID();}
	virtual void setID(int id){return pImpl_->setID(id);}
	
};

#endif
