#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "ModelState.h"
#include "ModelAutomaton.h"

using std::ofstream;
using std::ifstream;
using std::ostringstream;
using std::cout;
using std::endl;
using std::string;
using std::getline;

const char* FILENAME="aut.txt";
const char LEFT_PAREN = '(';
const char RIGHT_PAREN = ')';
const char NEWLINE = '\n';
const char COLON = ':';
const char COMMA = ',';

bool readFromFile(Automaton&,ifstream&);
bool getLineUntilDelimOrNewline(ifstream& inFile, string& buffer,
		char delimiter);


int main() {
	// Test of State
	if (true) {
		bool nothing = true;
		State s;
		{
			State scopy(s);
			if (scopy.getName() != "" ||
				scopy.numberOfLabels() != 0 ||
				scopy.numberOfTransitions() != 0) {
				cout << "Something went wrong 0" << endl;
				nothing = false;
			}
		}
		s.setName("Blah");
		{
			State scopy(s);
			if (scopy.getName() != "Blah" ||
				scopy.numberOfLabels() != 0 ||
				scopy.numberOfTransitions() != 0) {
				cout << "Something went wrong 1" << endl;
				nothing = false;
			}
		}
		Transition t(&s,&s);
		if (!s.addTransition(&t) ||
			s.numberOfTransitions() != 1) {
			cout << "Something went wrong 2" << endl;
			nothing = false;
		}
		State other("other");
		State other1("other1");
		State other2("other2");
		Transition t1(&s,&other);
		Transition t2(&s,&other1);
		Transition t3(&s,&other2);
		Transition t4(&other,&other1);

		if (s.addTransition(&t) ||
				s.addTransition(&t4) ||
				!s.addTransition(&t1) ||
				!s.addTransition(&t2) ||
				!s.addTransition(&t3) ||
				s.numberOfTransitions() != 4) {
			cout << "Something went wrong 3" << endl;
			nothing = false;
		}

		Transition *tp=nullptr;
		if (!s.getTransition(0,tp) || tp != &t ||
				!s.getTransition(1,tp) || tp != &t1 ||
				!s.getTransition(2,tp) || tp != &t2 ||
				!s.getTransition(3,tp) || tp != &t3 ||
				!s.getTransition("other",tp) || tp != &t1 ||
				!s.getTransition("other1",tp) || tp != &t2 ||
				!s.getTransition("other2",tp) || tp != &t3 ||
				s.getTransition(4,tp)) {
			cout << "Something went wrong 4" << endl;
			nothing = false;
		}

		s.addLabel("label");
		s.addLabel("label1");
		s.addLabel("label2");
		s.addLabel("label3");

		string str;
		if (s.numberOfLabels() != 4 ||
				!s.getLabel(0,str) || str != "label" ||
				!s.getLabel(3,str) || str != "label3" ||
				s.getLabel(4,str)) {
			cout << "Something went wrong 5" << endl;
			nothing = false;
		}
		{
			State scopy(s);
			if (scopy.numberOfTransitions() != 4 ||
					scopy.numberOfTransitions() != 4 ||
					!scopy.getTransition(1,tp) || tp != &t1 ||
					!scopy.getTransition(2,tp) || tp != &t2 ||
					!scopy.getTransition(3,tp) || tp != &t3 ||
					!scopy.getLabel(0,str) || str != "label" ||
					!scopy.getLabel(3,str) || str != "label3") {
				cout << "Something went wrong 6" << endl;
				nothing = false;
			}
		}

		if (nothing) {
			cout << "All these tests passed" << endl;
		}
	}

	// Test of Autoamton
	if (true) {
		ifstream inFile(FILENAME);
		if (!inFile) {
			cout << "Could not open file " << FILENAME << " for reading!" << endl;
			return 1;
		}

		Automaton aut;
		if (!readFromFile(aut,inFile)) {
			cout << "Failed to read from file!" << endl;
		}

		Automaton copy(aut);
		Automaton copy1(copy);
		cout << copy;

		if (aut != copy) {
			cout << "something wrong with copy!" << endl;
		}
		else {
			cout << "copy worked fine!" << endl;
		}
		if (copy != copy1) {
			cout << "something wrong with copy!" << endl;
		}
		else {
			cout << "copy worked fine!" << endl;
		}

		// Create an automaton with 500 states that is strongly connected
		const int NUMBEROFSTATES=100;
		Automaton hugeAut("huge");
		for (int i=0 ; i<NUMBEROFSTATES ; i++) {
			ostringstream name;
			name << "s" << i;
			State* state=0;
			cout << "adding state " << name.str() << endl;
			hugeAut.addState(name.str(),state);
			for (int j=0 ; j<i ; j++) {
				ostringstream label;
				label << j;
				state->addLabel(label.str());
			}
		}

		for (int i=0 ; i<NUMBEROFSTATES ; i++) {
			for (int j=0 ; j<NUMBEROFSTATES ; j++) {
				ostringstream name1,name2;
				name1 << "s" << i;
				name2 << "s" << j;
				Transition* trans=0;
				cout << "adding transition from " << name1.str()
					   << " to " << name2.str() << endl;
				hugeAut.addTransition(name1.str(),name2.str(),trans);
			}
		}

		cout << hugeAut;

		cout << "Finished printing huge automaton!" << endl;

		Automaton hugeCopy(hugeAut);

		cout << "Finished copying the huge automaton!" << endl;

		if (hugeCopy != hugeAut) {
			cout << "something wrong with copy!" << endl;
		}
		else {
			cout << "copy worked fine!" << endl;
		}

		ofstream outFile("hugeAutomaton.txt");
		outFile << hugeCopy;

		ifstream anotherFile("hugeAutomaton.txt");
		Automaton someAut;
		readFromFile(someAut,anotherFile);

		if (hugeCopy != someAut) {
			cout << "something wrong with copy!" << endl;
		}
		else {
			cout << "copy worked fine!" << endl;
		}
	}

	return 0;
}


bool readFromFile(Automaton& aut, ifstream& inFile)
{
	string buffer="";

	// The first line has the format
	// Automaton(automaton_name):
	getline(inFile,buffer,LEFT_PAREN);
	if (!inFile || buffer != "Automaton") {
		return false;
	}

	getline(inFile,buffer,RIGHT_PAREN);
	string name = buffer;
	// Clear to the end of line (read : then read \n)
	if (!inFile || inFile.get() != COLON || inFile.get() != NEWLINE) {
		return false;
	}

	getline(inFile,buffer);
	if (!inFile || buffer != "States:") {
		return false;
	}
	while (inFile &&
			getLineUntilDelimOrNewline(inFile,buffer,LEFT_PAREN) &&
			buffer != "Transitions:") {
		string statename=buffer;
		State* state=nullptr;
		// Read a state name from the file
		// Allocate a state through the add method
		// Add all the labels of this state through the
		// returned pointer to the state
		if (aut.addState(buffer,state)) {
			// Read the sequence of labels up to the )
			getline(inFile,buffer,RIGHT_PAREN);
			for (int pos=buffer.find(COMMA) ; pos > 0 ; pos = buffer.find(COMMA)) {
				string label = buffer.substr(0,pos);
				state->addLabel(label);
				buffer = buffer.substr(pos+1,buffer.length()-pos-1);
			}
			if (buffer != "") {
				state->addLabel(buffer);
			}
		}
		else {
			return false;
		}
	}
	if (!inFile || buffer != "Transitions:") {
		return false;
	}
	while (inFile && !inFile.eof() && getline(inFile,buffer)) {
		int pos=buffer.find(COMMA);
		if (pos < 0) {
			return false;
		}

		string name1 = buffer.substr(0,pos);
		buffer = buffer.substr(pos+1,buffer.length()-pos-1);
		string name2 = buffer;
		Transition* tempTransPtr=0;
		if (!aut.addTransition(name1,name2,tempTransPtr)) {
			return false;
		}
	}
	if (!inFile.eof()) {
		return false;
	}
	aut.setName(name);
	return true;
}

// This function skips newlines when it starts reading
// Then it reads contents from the ifstream until reaching
// a newline or the delimiter.
bool getLineUntilDelimOrNewline(ifstream& inFile, string& buffer,
		char delimiter)
{
	char readChar=0;
	while (inFile.peek()==NEWLINE) {
		inFile.get(readChar);
	}

	buffer="";
	while (inFile.get(readChar) &&
			readChar != delimiter &&
			readChar != NEWLINE) {
		buffer += readChar;
	}
	return static_cast<bool>(inFile);
}




