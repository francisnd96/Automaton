/*
 * Automaton.cpp
 * Created on: 23/10/2017
 * Author: np183
 *         Department of Informatics
 * 	   University of Leicester
 */
#include <iostream>
#include <string>
#include "Automaton.h"
using namespace std;

Automaton::Automaton() 
{
	name = "";
}

Automaton::Automaton(const std::string& name)
{
	this->name = name;

	
}

Automaton::Automaton(const Automaton& other) 
{
	name = other.name;
	
	transitions = new Transition*[other.arrSizeTrans];
	for(int i = 0; i < arrSizeTrans; ++i){
		transitions[i] = other.transitions[i];
	}
	
	
	
	states = new State*[other.arrSizeStates];
	for (int i=0; i< arrSizeStates; ++i){
		states[i] = other.states[i];
	}
	
	numTrans = other.numTrans;
	
	arrSizeTrans = other.arrSizeTrans;
	arrSizeStates = other.arrSizeStates;
	
}

Automaton::Automaton(Automaton&& other) : states{other.states}, transitions{other.transitions}, name{other.name}, arrSizeStates{other.arrSizeStates}, arrSizeTrans{other.arrSizeTrans}, numStates{other.numStates}, numTrans{other.numTrans}
{
	other.states = nullptr;
	other.transitions = nullptr;
	other.name = "";
	other.arrSizeStates = 0;
	other.arrSizeTrans = 0;
	other.numStates = 0;
	other.numTrans = 0;
}

Automaton::~Automaton() 
{
	if (states) {
		delete [] states;
		states = nullptr;
	}
	if (transitions) {
		delete [] transitions;
		transitions = nullptr;
	}
}

void Automaton::setName(const std::string& name)
{
	this->name = name; 
}

std::string Automaton::getName() const
{
	return this->name;
}

bool Automaton::addState(const std::string& stateName, State*& state)
{

	for(int i = 0; i < arrSizeStates; i++){
		if(states[i]->getName() == stateName){
			return false;
		}
	}
	
	State* s1 = new State(stateName);

	State** temps = new State*[arrSizeStates+1];
	
		for (unsigned int i=0; i<arrSizeStates ; ++i) {
			temps[i] = states[i];
		}
		
		if(states){
		delete[] states;
		states = nullptr;
		}
		
		states = temps;
		states[numStates] = s1;
		state = s1;
		arrSizeStates++;
		numStates++;
		
		
		return true;
	

	
}

bool Automaton::getState(const std::string& stateName, State*& state)
{
	for(int i = 0; i < arrSizeStates; ++i){
		if(states[i]->getName() == stateName){
			state = states[i];
			return true;
		}
	}
return false;
}

bool Automaton::getState(int i, State*& st)
{
	
	if (i < 0 || i >= arrSizeStates){
		return false;
	}else{
		st = states[i];
		return true;
	}
}

bool Automaton::getState(int i, const State*& st) const
{
	
	if (i < 0 || i >= arrSizeStates){
		return false;
	}else{
		st = states[i];
		return true;
	}
}

int Automaton::numberOfStates() const 
{
	return this -> numStates;
}

bool Automaton::addTransition(const std::string& nameSt1, const std::string& nameSt2,
		Transition*& trans)
{
	bool check1 = false;
	bool check2 = false;
	bool isTrue=false;
	for(int i = 0; i < arrSizeStates; ++i){
		if(states[i]->getName() == nameSt1){
			check1 = true;
		}
		if(states[i]->getName() == nameSt2){
			check2 = true;
		}
	}
	
	if(check1 == false || check2 == false){
		return false;
	}
	
	
	if(check1 == true && check2 == true){
		
		State *s1 = new State(nameSt1);
		State *s2 = new State(nameSt2);
		trans= new Transition(s1,s2);
		
		if(numTrans==0){
			
			delete [] transitions;
			numTrans++;
			transitions= new Transition*[numTrans];
			transitions[0]=trans;
			isTrue = true;
			
			}else{
				
				trans = new Transition(s1,s2);
				s1->addTransition(trans);
				Transition** temp = new Transition*[numTrans];
				for (unsigned int i=0 ; i< numTrans ; ++i) {
					temp[i] = transitions[i];
				}
				delete [] transitions;
				numTrans++;
				transitions=new Transition*[numTrans];
				for (unsigned int i=0 ; i< numTrans-1 ; ++i) {
					 transitions[i]=temp[i];
				}
				transitions[numTrans-1]=trans;
				isTrue =true;
			}
		}

	

	return isTrue;
}

bool Automaton::getTransition(const std::string& nameSt1, const std::string& nameSt2,
		Transition*& trans)
{
	State *s1 = new State(nameSt1);
	State *s2 = new State(nameSt2);
	trans = new Transition(s1,s2);
	
	for(int i = 0; i < numTrans; ++i){
		if(transitions[i] == trans){
			trans = transitions[i];
			return true;
		}else{
		return false;
		}
			
	}
	return false;
}

bool Automaton::getTransition(int location,Transition*& trans) 
{
	
	for(int i = 0; i < numTrans; ++i){
		if(i == location){
			trans = transitions[i];
			return true;
		}
	}
}

bool Automaton::getTransition(int location,const Transition*& trans) const
{
	
	for(int i = 0; i < numTrans; ++i){
		if(i == location){
			trans = transitions[i];
			return true;
		}
	}
}

int Automaton::numberOfTransitions() const
{
	return this -> numTrans;
}

void Automaton::print(std::ostream& stream) const
{
	stream << "Automaton(" << getName() << "):" << std::endl;
	if (numberOfStates()>0) {
		stream << "States:" << std::endl;
		for (int i=0 ; i< numberOfStates() ; i++) {
			const State* s=nullptr;
			getState(i,s);
			stream << *s << std::endl;
		}

		if (numberOfTransitions()>0) {
			stream << "Transitions:" << std::endl;
			for (int j=0 ; j<numberOfTransitions() ; j++) {
				const Transition* t=nullptr;
				getTransition(j,t);
				stream << *t << std::endl;
			}
		}
	}
}

Automaton& Automaton::operator=(const Automaton& other)
{
	name = other.name;
	
	transitions = new Transition*[other.arrSizeTrans];
	for(int i = 0; i < arrSizeTrans; ++i){
		transitions[i] = other.transitions[i];
	}
	
	
	
	states = new State*[other.arrSizeStates];
	for (int i=0; i< arrSizeStates; ++i){
		states[i] = other.states[i];
	}
	
	numTrans = other.numTrans;
	
	arrSizeTrans = other.arrSizeTrans;
	arrSizeStates = other.arrSizeStates;
	
	return *this;
}

Automaton& Automaton::operator=(Automaton&& other)
{
	if(this != &other){
	name = other.name;
	
	transitions = new Transition*[other.arrSizeTrans];
	for(int i = 0; i < arrSizeTrans; ++i){
		transitions[i] = other.transitions[i];
	}
	
	
	
	states = new State*[other.arrSizeStates];
	for (int i=0; i< arrSizeStates; ++i){
		states[i] = other.states[i];
	}
	
	numTrans = other.numTrans;
	
	arrSizeTrans = other.arrSizeTrans;
	arrSizeStates = other.arrSizeStates;
	
	other.states = nullptr;
	other.transitions = nullptr;
	other.name = "";
	other.arrSizeStates = 0;
	other.arrSizeTrans = 0;
	other.numTrans = 0;
	
	return *this;
}
}

bool Automaton::operator==(const Automaton& other) const
{
	return false;
}

bool Automaton::operator!=(const Automaton& other) const
{
	return false;
}

std::ostream& operator<<(std::ostream& stream, const Automaton& aut)
{
	aut.print(stream);
	return stream;
}

