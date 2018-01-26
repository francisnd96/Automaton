#include <string>
#include <sstream>
#include <iostream>
// #include <cstdlib>
#include "State.h"

using std::string;
using std::ostream;
using std::endl;

State::State()
{
	name = "";
	transitions = new Transition*[arrSizeTrans];
	labels = new string[arrSizeLabels];
}  

State::State(const string& name) {
	this->name = name;
	
}

State::State(const State& other) {
	
	arrSizeLabels = other.arrSizeLabels;
	arrSizeTrans = other.arrSizeTrans;
	numTrans = other.numTrans;
	numLabels = other.numLabels;
	transitions = new Transition*[other.arrSizeTrans];
	for(int i = 0; i < arrSizeTrans; ++i){
		transitions[i] = other.transitions[i];
	}
	

	name = other.name;
	
	labels = new string[arrSizeLabels];
		for (int i=0; i< arrSizeLabels; ++i){
			labels[i] = other.labels[i];
		}
	numStates = other.numStates;
	
}

State::State(State&& other) : labels{other.labels}, transitions{other.transitions}, name{other.name}, numTrans{numTrans}, numLabels{numLabels}, arrSizeLabels{other.arrSizeLabels}, arrSizeTrans{other.arrSizeTrans} {
	other.labels = nullptr;
	other.transitions = nullptr;
	other.name = "";
	other.numTrans = 0;
	other.numLabels = 0;
	other.arrSizeLabels = 0;
	other.arrSizeTrans = 0;
	
}

State::~State() 
{
	if (transitions) {
		delete [] transitions;
	}
	if (labels) {
		delete [] labels;
	}

}

void State::setName(const string& name){
	this->name = name; 
}

string State::getName() const 
{
  return this->name;
}

bool State::addTransition(Transition* trans) 
{
	
	State *s1 = {nullptr};
	State *s2 = {nullptr};
	trans -> getState1(s1);
	trans -> getState2(s2);
	
	for(int i = 0; i < numTrans; ++i){
		
		State* s2_current;
		transitions[i]->getState2(s2_current);
		
		if(s2_current == s2){ return false; }
	}

	if(this == s1){
		Transition** temp = new Transition*[arrSizeTrans+1];
		for (unsigned int i=0 ; i< numTrans ; ++i) {
			temp[i] = transitions[i];
		}
		delete [] transitions;
		transitions = temp;
		transitions[numTrans] = trans;
		temp = nullptr;
		numTrans++;
		arrSizeTrans++;
		
		return true;
	}else{
		return false;
	}
	

}

bool State::getTransition(const string& targetStateName, Transition*& result)
{
	
	for(int i = 0; i < numTrans; ++i){
		State* s2_current;
		transitions[i]->getState2(s2_current); 
		if(s2_current->getName() == targetStateName){
			result = transitions[i];
			return true;
		}
	}
return false;
}

bool State::getTransition(const string& targetStateName, const Transition*& result) const
{
	
	for(int i = 0; i < numTrans; ++i){
		State* s2_current;
		transitions[i]->getState2(s2_current); 
		if(s2_current->getName() == targetStateName){
			result = transitions[i];
			return true;
		}
	}
return false;
}
bool State::getTransition(int location, Transition*& result)
{
	
	if (location < 0 || location >= arrSizeTrans){
		return false;
	}else{
			result = transitions[location];
		return true;
	}
	
}

bool State::getTransition(int location, const Transition*& result) const
{
	if (location < 0 || location > arrSizeTrans)
		return false;
	
	for(int i = 0; i < numTrans; ++i){
		if(i == location){
			result = transitions[i];
			return true;
		}
	}
return false;
}

int State::numberOfTransitions() const 
{
	return this -> numTrans;
}

bool State::addLabel(const string& label){
	

	for(unsigned int i = 0; i < arrSizeLabels; ++i){
		if(labels[i] == label)
			return false;
	}
	
	
			string* temp = new string[arrSizeLabels+1];
			for (unsigned int i=0 ; i< arrSizeLabels ; ++i) {
				temp[i] = labels[i];
			}
			delete [] labels;
			labels = temp;
			labels[numLabels] = label;
			numLabels++;
			arrSizeLabels++;
			
			return true;
	
}

int State::numberOfLabels() const
{
	return this -> numLabels; 
}

bool State::getLabel(int location, string& label) const
{
	if(location < 0 || location >= arrSizeLabels){
	return false;
	}else{

label = labels[location];

return true;
}
}

State& State::operator=(const State& other)
{
	arrSizeLabels = other.arrSizeLabels;
	arrSizeTrans = other.arrSizeTrans;
	numTrans = other.numTrans;
	numLabels = other.numLabels;
	transitions = new Transition*[other.arrSizeTrans];
	for(int i = 0; i < arrSizeTrans; ++i){
		transitions[i] = other.transitions[i];
	}
	

	name = other.name;
	
	labels = new string[arrSizeLabels];
		for (int i=0; i< arrSizeLabels; ++i){
			labels[i] = other.labels[i];
		}
		
		return *this;
}

State& State::operator=(State&& other){
	
	this -> arrSizeLabels = other.arrSizeLabels;
	this -> arrSizeTrans = other.arrSizeTrans;
	this -> numTrans = other.numTrans;
	this -> numLabels = other.numLabels;
	transitions = new Transition*[other.arrSizeTrans];
	for(int i = 0; i < arrSizeTrans; ++i){
		transitions[i] = other.transitions[i];
	}
	
	this -> name = other.name;
	
	labels = new string[this -> arrSizeLabels];
		for (int i=0; i< this -> arrSizeLabels; ++i){
			labels[i] = other.labels[i];
		}
		
	
	other.labels = nullptr;
	other.transitions = nullptr;
	other.name = "";
	other.numTrans = 0;
	other.numLabels = 0;
	other.arrSizeLabels = 0;
	other.arrSizeTrans = 0;
		
		return *this;

}

bool State::operator==(const State& other) const {
	
	//if(this.getName != other.getName){
	//	return false;
	//}
	
	//if(numLabels == other->numLabels)
	
	
}

void State::print(ostream& stream) const
{
  bool first = true;
  stream << getName() << "(";
 
  for (int i=0 ; i<this->numberOfLabels() ; i++) {
    if (first) {
      first = false;
    }
    else {
      stream << ",";
    }
    string s;
    getLabel(i,s);
    stream << s;
  }
  stream << ")";
}

ostream& operator<< (ostream& stream, const State& st) 
{
  st.print(stream);
  return stream;
}

