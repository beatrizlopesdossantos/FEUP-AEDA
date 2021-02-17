#include "REAgency.h"
#include <algorithm>


REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//
void REAgency::generateCatalog() {
    vector<PropertyTypeItem> temp;
	for (auto it = properties.begin(); it != properties.end(); it++) {
	    PropertyTypeItem p((*it)->getAddress(), (*it)->getPostalCode(), (*it)->getTypology(), (*it)->getPrice());
	    auto it1 = find(temp.begin(), temp.end(), p);
	    if (it1 == temp.end()) {
	        p.setItems({*it});
            temp.push_back(p);
	    }
	    else {
	        vector<Property*> vp = it1->getItems();
	        vp.push_back(*it);
	        it1->setItems(vp);
	    }
	}
	for (auto it = temp.begin(); it != temp.end(); it++) {
	    catalogItems.insert(*it);
	}
}

vector<Property*> REAgency::getAvailableProperties(Property* property) const {
	vector<Property*> temp;
	PropertyTypeItem p(property->getAddress(), property->getPostalCode(), property->getTypology(), property->getPrice());
	BSTItrLevel<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd()) {
	    if (it.retrieve() == p) {
	        for (auto it1:it.retrieve().getItems()) {
                if (get<1>((*it1).getReservation()) == 0) {
                    temp.push_back(it1);
                }
	        }
	    }
	    it.advance();
	}
	return temp;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {
    BSTItrLevel<PropertyTypeItem> it(catalogItems);
    PropertyTypeItem p(property->getAddress(), property->getPostalCode(), property->getTypology(), property->getPrice());
    while (!it.isAtEnd()) {
        if (it.retrieve() == p) {
            for (auto &elem:it.retrieve().getItems()) {
                if (get<1>(elem->getReservation()) == 0) {
                    int newPrice = property->getPrice() * percentage / 100;
                    elem->setReservation(make_tuple(client, property->getPrice() - newPrice));
                    client->addVisiting(property->getAddress(), property->getPostalCode(), property->getTypology(),
                                        to_string(property->getPrice()));
                    return true;
                }
            }
        }
        it.advance();
    }
	return false;
}

//
// TODO: Part II  - Hash Table
//
void REAgency::addClientRecord(Client* client) {
    ClientRecord c(client);
    listingRecords.insert(c);
}

void REAgency::deleteClients() {
	for (auto it = listingRecords.begin(); it != listingRecords.end(); it++) {
	    if (it->getClientPointer()->getVisitedProperties().size() == 0) {
	        listingRecords.erase(it);
	    }
	}
}

//
// TODO: Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {

	for (auto it = candidates.begin(); it != candidates.end(); it++) {
	    int count = 0;
        for (auto it1 = properties.begin(); it1 != properties.end(); it1++) {
            if (it->getEMail() == get<0>((*it1)->getReservation())->getEMail()) {
                count++;
            }
        }
        if (float(count)/it->getVisitedProperties().size() > float(min)) {
            clientProfiles.push(*it);
        }
	}

}

vector<Property*> REAgency::suggestProperties() {
	vector<Property*> tempProperties;
	priority_queue<Client> temp = clientProfiles;
	Client *c;
	int i = 0;
	while (!temp.empty()) {
        i++;
        tempProperties.resize(i);
        *c = temp.top();
        if (get<1>(c->getVisiting()).empty()) {
            temp.pop();
            continue;
        }
        int postal = stoi(get<1>(c->getVisiting()));
        Property *p;
        bool first = true;
        for (auto it = properties.begin(); it != properties.end(); it++) {
            if (first) {
                if (get<1>((*it)->getReservation()) == 0 && stoi((*it)->getPostalCode()) != postal) {
                    p = *it;
                    first = false;
                }
            }
            else {
                if (get<1>((*it)->getReservation()) == 0 && stoi((*it)->getPostalCode()) != postal) {
                    if (stoi((*it)->getPostalCode()) - postal < stoi(p->getPostalCode()) - postal) {
                        p = *it;
                    }
                }
            }
        }
        tempProperties[i - 1] = p;
        temp.pop();
	}

	return tempProperties;
}
