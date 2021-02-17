#include "packagingMachine.h"
#include <sstream>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap)
{}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}


// TODO
unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
    unsigned  count = 0;
    auto it = objs.begin();
	while (it != objs.end()) {
	    if (it->getWeight() <= boxCapacity) {
	        count++;
            objects.push(*it);
	        objs.erase(it);
	    }
	    else {
	        it++;
	    }
	}
	return count;
}

// TODO
Box PackagingMachine::searchBox(Object& obj) {

	Box b;
	vector<Box> aux;
	while (!boxes.empty()) {
        b = boxes.top();
        boxes.pop();
        if (b.getFree() >= obj.getWeight()) {

            for (int i = 0; i < aux.size(); i++) {
                boxes.push(aux[i]);

            }
            return b;
        }
	    else aux.push_back(b);
	}
	for (int i = 0; i < aux.size(); i++) {
	    boxes.push(aux[i]);
	}
	return b;

     /*vector<Box> temp;

    //procura caixa mais cheia, ainda com espaco para obj
    while ( !boxes.empty() )
    {
        Box bx = boxes.top();
        boxes.pop();
        if ( bx.getFree() >= obj.getWeight() ) {

            for (unsigned i=0; i<temp.size(); i++) //repoe na fila de boxes as boxes retiradas da frente.
                boxes.push(temp[i]);
            return bx;
        }
        else temp.push_back(bx); //coloca as boxes nao utilizadas num vetor temporario
    }
    for (unsigned i=0; i<temp.size(); i++) //repoe as boxes nao utilizadas de volta, caso nenhuma sirva
        boxes.push(temp[i]);

    return Box(boxCapacity); //e retorna uma nova caixa*/
}

// TODO
unsigned PackagingMachine::packObjects() {
	while(!objects.empty()) {
        Object o = objects.top();
        objects.pop();
        Box aux = searchBox(o);
        aux.addObject(o);
        boxes.push(aux);
	}
	return boxes.size();
}

// TODO
string PackagingMachine::printObjectsNotPacked() const {
    stringstream ss;
    if (objects.size() == 0) return "No objects!\n";
    HeapObj obj = objects;
    while(!obj.empty()) {
        Object o = obj.top();
        obj.pop();
        ss << o << endl;
    }
    return ss.str();
}

// TODO
Box PackagingMachine::boxWithMoreObjects() const {
	Box b;
	HeapBox aux = boxes;
	unsigned count = -1;
	if (boxes.size() == 0) throw MachineWithoutBoxes();
	else {
        while (!aux.empty()) {
            if (aux.top().getSize() > count) {
                count = aux.top().getSize();
                b = aux.top();
            }
            aux.pop();
        }
        return b;
    }
}