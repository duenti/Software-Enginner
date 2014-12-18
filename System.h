#if ! defined(SYSTEM_H)
#define SYSTEM_H

#include <iostream>

using namespace std;

class System {
public:
	virtual void setValue(double) = 0;
	virtual void addValue(double) = 0;
	virtual void redValue(double) = 0;
    virtual void setName(string) = 0;
    virtual string getName() = 0;
    virtual double getValue() = 0;
	virtual void addResult(double) = 0;
	virtual void clearResult() = 0;
    virtual vector<double> impress() = 0;
    virtual int getID() = 0;
	virtual void setID(int) = 0;
};

#endif /* SYSTEM_H_ */
