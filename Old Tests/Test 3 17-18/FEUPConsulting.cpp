/*
 * FEUPConsulting.cpp
 *
 *  Created on: 10/12/2017
 *      Author: CS
 */

#include "FEUPConsulting.h"

FEUPConsulting::FEUPConsulting(): expertizes(Expertize("", 0)) {
}

FEUPConsulting::FEUPConsulting(vector<Project*> projects): expertizes(Expertize("", 0)) {
	this->projects = projects;
}

void FEUPConsulting::addProjects(vector<Project*> projects) {
	this->projects = projects;
}

vector<Project*> FEUPConsulting::getProjects() const{
	return this->projects;
}


// get the expertize objet with the given name, including all students with the corresponding skills
Expertize FEUPConsulting::getExpertize(string name, unsigned cost) {
	Expertize itemNotFound("", 0);
	Expertize expertize(name, cost);
	Expertize search = expertizes.find(expertize);

	return search;
}


void FEUPConsulting::addProject(Project* project) {
	//TODO
	Expertize itemNotFound("", 0);
	Expertize expertize(project->getExpertize(), project->getCost());
	Expertize search = expertizes.find(expertize);

	if(search == itemNotFound) {
		this->expertizes.insert(expertize);
	}

	projects.push_back(project);
}

BST<Expertize> FEUPConsulting::getExpertizes() const {
	return this->expertizes;
}

void FEUPConsulting::addNewExpertize(const Expertize & expertize1) {
	this->expertizes.insert(expertize1);
}

vector<StudentPtr> FEUPConsulting::getStudents() const {
	vector<StudentPtr> ptrs;
	HashTabStudentPtr::const_iterator it1 = this->students.begin();
	HashTabStudentPtr::const_iterator it2 = this->students.end();
	for (; it1 != it2; it1++) {
		ptrs.push_back(*it1); //We can make it a bit more complex by considering only records with a condition!
	}
	return ptrs;
}

void FEUPConsulting::setStudents(vector<StudentPtr>& newStudents) {
	for (int i = 0; i < newStudents.size(); i++) students.insert(newStudents[i]);
}

priority_queue<Student> FEUPConsulting::getActiveStudents() const {
	return activeStudents;
}
void FEUPConsulting::setActiveStudents(priority_queue<Student>& students) {
	activeStudents = students;
}


//
// TODO: Part I   - BST
//

void FEUPConsulting::addAvailability(Student* student, string expertizeAvailable, unsigned cost) {
	Expertize temp(expertizeAvailable, cost);
	auto it = expertizes.find(temp);

	if (it.getName().empty && it.retrieve().getCost == 0) {
		temp.addConsultant(student);
		expertizes.insert(temp);
	}
	else {
		temp.setConsultants(it.getConsultants);
		expertizes.remove(it);
		temp.addConsultant(student);
		expertizes.insert(temp);
	}
}


vector<Student*> FEUPConsulting::getCandidateStudents(Project* project) const {
	vector<Student*> temp;
	Expertize aux(project->getExpertize, project->getCost);
	auto it = expertizes.find(aux);
	if (it.getCost != 0 && !it.getName().empty()) {
		for (auto it1 = it.getConsultants(); it1 != it.getConsultants; it1++) {
			if ((*it1).getCurrentProject.empty()) {
				temp.push_back(it);
			}
		}
	}
	return temp;

}


bool FEUPConsulting::assignProjectToStudent(Project* project, Student* student) {
	if (project->getConsultant()) return false;;
	if (!student->getCurrentProject().empty()) return false;
	Expertize aux(project->getExpertize, project->getCost);
	auto it = getCandidateStudents(project);
	for (auto it1 : it) {
		if (it1 == student) {
			student->addProject(project->getTitle);
			project->setConsultant(student);
			return true;
		}
	}
	return false;

}

//
// TODO: Part II  - Hash Table
//

void FEUPConsulting::addStudent(Student* student) {
	students.insert(student);
}

void FEUPConsulting::changeStudentEMail(Student* student, string newEMail) {
	for (auto it = students.begin(); it != students.end(); it++) {
		if ((*it).getEMail() == student->getEMail()) {
			students.erase(it);
			student->setEMail(newEMail);
			students.insert(student);
		}
	}
}


//
// TODO: Part III - Priority Queue
//

void FEUPConsulting::addActiveStudents(const vector<Student>& candidates, int min) {
	for (auto it = candidates.begin(); it != candidates.end(); it++) {
		if ((*it).getPastProjects.size() > min) {
			activeStudents.push(*it);
		}
	}

}


int FEUPConsulting::mostActiveStudent(Student& studentMaximus) {
	if (activeStudents.empty()) return 0;
	Student aux = activeStudents.top();
	activeStudents.pop();
	if (activeStudents.top().getPastProjects().size() == aux.getPastProjects().size()) {
		activeStudents.push(aux);
		return 0;
	}
	activeStudents.push(aux);
	return activeStudents.size();
}





















