/*
 * State.h
 * Created on: 23/10/2017
 * Author: np183
 *         Department of Informatics
 * 	   University of Leicester
 */


#include <string>
#include <iosfwd>

#ifndef STATE
#define STATE 1

#include "Transition.h"

class Transition;

/*
 * A State is an object that has a name and two dynamic arrays
 * of Transitions (through pointers to them) and labels (strings).
 *
 * Your job is to complete the implementation by adding private variables
 * and complete all the functions below.
 *
 * One important issue about the State is that it does not own the
 * Transitions that it stores.
 * That is, the only way to add a Transition to the State is
 * by someone else allocating this Transition and giving it to
 * the State ready made.
 * As you do not allocate the memory for the transitions you are not in
 * charge of deallocating this memory.
 * It would be an error to deallocate this memory.
 *
 * A short comment about string. They will appear in a later lecture
 * but you can use them here.
 * They are a very convenient form for handling strings.
 * They handle all the memory allocation for you and you don't have
 * to worry about it.
 * Copy constructor and operator= are implemented for them etc.
 */

class State {
public:
  // Default constructor.
  // Name is initialized to "".
  // Arrays are initialized as empty.
  State();

  // Creates a state and initializes its name to the string
  // in parameter.
  // Arrays are initialized as empty.
  State(const std::string&);

  // Copy constructor.
  // Copies the labels from the other state.
  // Do *NOT* copy the actual transitions of the other state;
  // copy the same pointer addresses to the new State.
  State(const State&);
  // Move constructor.
  State(State&&);

  // Releases all memory allocated by the class
  ~State();

  // Set the name of the State to the name in parameter
  void setName(const std::string&);
  // Return the name of the STate
  std::string getName() const;

  // Checks that the transition leaves this state
  // If the transition does not start from this state
  // or a transition to the target state already exists 
  // returns false.
  // Otherwise, adds the transition at the end of the array and returns
  // true.
  bool addTransition(Transition*);

  // Searches for a transition leading to a state
  // of the name in parameter.
  // If found sets the pointer reference in parameter
  // to that transition and returns true.
  // Otherwise returns false.
  //
  // There are two versions one working on
  // normal State one working on const State.
  bool getTransition(const std::string&, Transition*&);
  bool getTransition(const std::string&, const Transition*&) const;

  // Return the number of transitions
  int numberOfTransitions() const;

  // Get the i-th transition in the array.
  // If the int parameter is out of bound return false.
  // Otherwise set the pointer reference in parameter to the
  // i-th transition and return true
  //
  // Again, two versions one for State and one for
  // const State.
  bool getTransition(int, Transition*&);
  bool getTransition(int, const Transition*&) const;


  // Add a label to the state if does not exist
  // On successful addition returns true.
  // Add the new transition to the end of the array
  bool addLabel(const std::string&);

  // Return the number of labels
  int numberOfLabels() const;

  // Return the label in the i-th location/
  // If the location is invalid return false.
  // Otherwise set the string to the label and return
  // true
  bool getLabel(int, std::string&) const;

  // Copy and move assignment operators
  //
  // The same comment about Transition pointers:
  // just copy the pointers to Transitions from the other State
  State& operator=(const State&);
  State& operator=(State&&);

  // Check that the state is identical to the state in parameter:
  // 1. Same name
  // 2. Same labels
  // 3. Same transitions: transitions lead to the same states according
  //    to names of target states. Order of transitions matters.
  bool operator==(const State&) const;

  // Output the state to the stream
  // This function is already implemented
  void print(std::ostream &) const;  

  // output the state to the stream
  // This function is already implemented
  friend std::ostream& operator<<(std::ostream&,const State&);

  // Data member variables should be private (except in extreme cases!)
  // DO NOT LEARN FROM THIS!
  // I DO IT TO OBFUSCATE THE IMPLEMENTATION WITH NON-MEMBER FUNCTIONS
  void* pms_[7];
private:
  // Private member functions
  void privateFunction1_(int var=-1);
  void privateFucntion2_();
  void privateFucntion3_();
  void privateFucntion4_();
  void privateFucntion5_(const State&);
};

#endif

