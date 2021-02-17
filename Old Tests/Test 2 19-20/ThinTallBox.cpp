#include "ThinTallBox.h"
#include "WideFlatBox.h"
#include <algorithm>

ThinTallBox::ThinTallBox(double capacity) : Box(capacity) {
}

ThinTallBox::ThinTallBox(double capacity, stack<Object> objects, double content_size) : Box(capacity) {
	this->objects = objects;
	this->setContentSize(content_size);
}

stack<Object> ThinTallBox::getObjects() const {
    return objects;
}

void ThinTallBox::remove(Object object) {
	Object next_object = next();
	if(!(next_object == object)) {
		throw InaccessibleObjectException(object);
	} else {
		setContentSize(getContentSize() - object.getSize());
		objects.pop();
	}
}

const Object& ThinTallBox::next() const {
	return objects.top();
}


void ThinTallBox::insert(Object object) {
    if ((object.getSize() + getContentSize()) > getCapacity()) {
        throw(ObjectDoesNotFitException());
    }
    else {
        objects.push(object);
        setContentSize(object.getSize() + getContentSize());
    }
}

void ThinTallBox::sortObjects() {
	vector<Object> aux;
	Object aux2;
	while (objects.size() != 0) {
	    aux2 = objects.top();
	    aux.push_back(aux2);
	    objects.pop();
	}
	sort(aux.begin(), aux.end());
	for (int i = 0; i < aux.size(); i++) {
	    objects.push(aux[i]);
	}
}
