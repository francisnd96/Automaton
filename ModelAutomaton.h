/*
 * Automaton.h
 * Created on: 23/10/2017
 * Author: np183
 *         Department of Informatics
 * 	   University of Leicester
 */

#include<string>
#include<fstream>
#include<iostream>

#ifndef AUTOMATON
#define AUTOMATON 1

#include "ModelState.h"
#include "Transition.h"

class Transition;
class State;

/*
 * An automaton has a name and contains two arrays.
 * One of State-s and one of Transition-s.
 * This is a complete structure that operates the State-s and
 * the Transition-s.
 *
 * All the memory that it allocates should be deallocated when
 * this class is destroyed.
 */

class Automaton { 
public : 
	// Default constructor
	// Initialize the name to ""
	// Initialize the arrays to empty
	Automaton();

	// Name constructor
	// Initialize the name to the name in parameter
	// Initialize arrays to empty
	Automaton(const std::string&);

	// Copy constructor
	// Should create a completely independent copy of the
	// automaton.
	// Copy all the State-s and all the Transition-s.
	// The State-s inside the Automaton should be
	// identical to the origianl State-s (including the Transitions
	// that are inside them, etc).
	//
	// Notice that Transition does not have a deep copy constructor
	// and that the copy constructor of the State does not create
	// copies of the Transitions that are inside it.
	Automaton(const Automaton&);

	// Move constructor
	Automaton(Automaton&&);

	// Release all memeory allocated by this class
	~Automaton();

	// Set the name of this automaton
	void setName(const std::string &);

	// Return the name of the automaton
	std::string getName() const;

	// Try to add a state with this name.
	// If a state of this name exists return false.
	// Otherwise, allocate a new state and add it to the automaton.
	// Update the pointer reference to the newly created state.
	// The state should be added at the end of the array
	bool addState(const std::string&, State*&);

	// If a state of this name does not exist return false.
	// Otherwise update the reference pointer to the state and
	// return true.
	bool getState(const std::string&, State*&);

	// Return the number of states.
	int numberOfStates() const;

	// Access to the State at the given index
	// If a state of this index does not exist return false.
	// Otherwise update the reference pointer to the state and
	// return true
	//
	// One version for a const Automaton and one for an Automaton
	bool getState(int,State*&);
	bool getState(int,const State*&) const;


	// Try to add a new transition between the two states whose
	// names are given.
	// If one of the states does not exist in the automaton return
	// false.
	// If this transition between the two states already exists in
	// the automaton return false.
	// Otherwise, create the new transition, add it to the
	// automaton at the end of the Array, and update the source state.
	// On successful addition return true and update the
	// Transition pointer with the new Transition
	bool addTransition(const std::string&, const std::string&, Transition*&);

	// Search for a transition between these two states.
	// If does not exist return false.
	// If exists, update the pointer reference to it and return
	// true.
	bool getTransition(const std::string&, const std::string&, Transition*&);

	// Return the number of transitions
	int numberOfTransitions() const;

	// Access the transition in the location requested.
	// If the location is invalid return false.
	// Otherwise, update the pointer reference to that transition
	// and return true.
	//
	// One version for a const Automaton and one for an Automaton
	bool getTransition(int, Transition*&);
	bool getTransition(int, const Transition*&) const;

	// Print the entire automaton
	// This method is implemented for you
	void print(std::ostream&) const;

	// Copy and move assignment operator
	Automaton& operator=(const Automaton&);
	Automaton& operator=(Automaton&&);

	// Compare two automata.
	// Two automata are equivalent if:
	// 1. They have the same name
	// 2. They have the same states (order matters)
	// 3. They have the same transitions (order matters)
	bool operator==(const Automaton&) const;
	// The negation of operator==
	bool operator!=(const Automaton&) const;

	// Print the entire automaton
	// This function is implemented for you
	friend std::ostream& operator<<(std::ostream&,const Automaton&);

	// Data member variables should be private (except in extreme cases!)
	// DO NOT LEARN FROM THIS!
	// I DO IT TO OBFUSCATE THE IMPLEMENTATION WITH NON-MEMBER FUNCTIONS
	void* pms_[7];
private:
	void privateFunction1_(int var=-1);
	void privateFunction2_(int var=-1);
	void privateFunction3_();
	void privateFunction4_();
	void privateFunction5_();
	void privateFunction6_();
	void privateFunction7_(const Automaton&);
	void privateFunction8_(State*, const State*);
};

#endif
