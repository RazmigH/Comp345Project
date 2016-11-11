#include "Observable.h"

Observable::Observable() {
	_observers = new list<Observer*>;
}
Observable::~Observable() {
	//delete _observers;
}
void Observable::attachObserver(Observer* o) {
	_observers->push_back(o);
};
void Observable::detachObserver(Observer* o) {
	_observers->remove(o);
};
void Observable::notify() {
	list<Observer*>::const_iterator i;
	for (i = _observers->begin(); i != _observers->end(); ++i)
		(*i)->refresh();
	_observers->end();
};