/*
 * Transition.h
 * Created on: 23/10/2017
 * Author: np183
 *         Department of Informatics
 * 	   University of Leicester
 */


#include <iosfwd>

#ifndef TRANSITION
#define TRANSITION 1

#include "ModelState.h"

class State;


/*
 * This is a simple class that contains a pair of State pointers.
 * This class is implemented for you.
 */
class Transition {
public:
  // Creates a transition.
  // Both states initialized to null.
  Transition();

  // Creates a transition and initializes the states
  // to the parameters.
  Transition(State*,State*);

  // Clears memory
  ~Transition();

  // If the state in parameter has a valid name
  // sets the source state to it.
  bool setState1(State*);

  // If the state in parameter has a valid name
  // sets the target state to it.
  bool setState2(State*);

  // If the transition is not complete (either source or target
  // is not set) return false.
  // Otherwise, set the parameter to the source state and return true.
  bool getState1(State*&);
  bool getState1(State*&) const;
  // If the transition is not complete (either source or target
  // is not set) return false.
  // Otherwise, set the parameter to the target state and return true.
  bool getState2(State*&);
  bool getState2(State*&) const;

  // Output the names of the two states or nothing if one of them
  // is not set
  void print(std::ostream &) const;

  // Returns true if:
  // The setting of source/target is the same.
  // The names of set source/target are the same
  bool operator==(const Transition&) const;

  // Output the names of the two states or nothing if one of them 
  // is not set
  friend std::ostream& operator<<(std::ostream&,const Transition&);

public:
  State* state1_;
  State* state2_;
};

#endif
