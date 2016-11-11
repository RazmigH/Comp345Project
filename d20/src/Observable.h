#pragma once
#include "Observer.h"

using namespace std;

class Observable : oxygine::ObjectBase{
public:
	virtual void attachObserver(Observer*);
	virtual void detachObserver(Observer*);
	virtual void notify();
	Observable();
	~Observable();
private:
	list<Observer*>* _observers;
};