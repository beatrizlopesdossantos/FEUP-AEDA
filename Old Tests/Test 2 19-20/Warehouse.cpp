#include "Warehouse.h"
#include <algorithm>

Warehouse::Warehouse()  {
}

queue<ThinTallBox> Warehouse::getBoxes() {
	return boxes;
}

queue<Object> Warehouse::getObjects() {
    return objects;
}

void Warehouse::setBoxes(queue<ThinTallBox> q) {
    while (!q.empty()) {
        boxes.push(q.front());
        q.pop();
    }
}

void Warehouse::addObject(Object o1) {
    objects.push(o1);
}

bool ord(Object o1, Object o2) {
    return o1.getSize() > o2.getSize();
}

int Warehouse::InsertObjectsInQueue(vector <Object> obj){
    int count = 0;
    sort(obj.begin(), obj.end(), ord);
    for (int i = 0; i < obj.size(); i++) {
        count++;
        objects.push(obj[i]);
    }
    return count;
}

/*Object Warehouse::RemoveObjectQueue(int maxSize) {
    Object aux = find(objects.front(), objects.back(), maxSize);
    vector<Object> aux2;
    while (objects.size() != 0) {
        aux = objects.front();
        aux2.push_back(aux);
        objects.pop();
    }
    for (auto i = aux2.begin(); i < aux2.end(); i++) {
        if ((*i).getSize() == maxSize) {
            aux = (*i);
            aux2.erase(i);
            break;
        }
    }
    vector<Object>::iterator obj = aux2.begin();
    while (obj < aux2.size()) {
        if (obj->getSize() != maxSize && obj == aux2.end()) {

        }
        aux = *obj;
        aux.setName("dummy");
        aux.setSize(maxSize);
        return aux;
    }
    aux = *obj;
    aux2.erase(obj);
    for (int i = 0; i < aux2.size(); i++) {
        objects.push(aux2[i]);
    }
    return aux;
}*/

int Warehouse::addPackOfBoxes(vector <ThinTallBox> boV) {
    int count = 0;
    for (int i = 0; i < boV.size(); i++) {
        count++;
        boxes.push(boV[i]);
    }
    return boxes.size();
}


vector<ThinTallBox> Warehouse::DailyProcessBoxes(){
    //TODO
    vector<ThinTallBox> res;
    return res;
}

