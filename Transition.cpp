/*
 * Transition.cpp
 * Created on: 23/10/2017
 * Author: np183
 *         Department of Informatics
 * 	   University of Leicester
 */

#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include"Transition.h"

using std::ostream;
using std::string;

Transition::Transition() 
  : state1_(0), state2_(0)
{
}

Transition::Transition(State* state1, State* state2) 
  : state1_(state1), state2_(state2)
{
}

Transition::~Transition() 
{
}

bool Transition::setState1(State* s) 
{
  if (!s || ""==s->getName()) {
    return false;
  }
  state1_=s;
  return true;
}

bool Transition::setState2(State* s) 
{
  if (!s || ""==s->getName()) {
    return false;
  }
  state2_=s;
  return true;
}

bool Transition::getState1(State*& s)
{
  if (!state1_ || !state2_) {
    return false;
  }
  s=state1_;
  return true;
}

bool Transition::getState1(State*& s) const
{
  if (!state1_ || !state2_) {
    return false;
  }
  s=state1_;
  return true;
}

bool Transition::getState2(State*& s)
{
  if (!state1_ || !state2_) {
    return false;
  }
  s=state2_;
  return true;
}

bool Transition::getState2(State*& s) const
{
  if (!state1_ || !state2_) {
    return false;
  }
  s=state2_;
  return true;
}


void Transition::print(ostream& stream) const 
{
  if (!state1_ || !state2_) { 
    return;
  }
  stream << state1_->getName() << "," << state2_->getName();
}

bool Transition::operator== (const Transition& other) const
{
  if ((state1_ && !other.state1_) ||
      (!state1_ && other.state1_)) {
    return false;
  }
  if (state1_ && state1_->getName() != other.state1_->getName()) {
    return false;
  }
  if ((state2_ && !other.state2_) ||
      (!state2_ && other.state2_)) {
    return false;
  }
  if (state2_ && state2_->getName() != other.state2_->getName()) {
    return false;
  }

  return true;
}
    
ostream& operator<<(ostream& stream, const Transition& trans) 
{
  trans.print(stream);
  return stream;
}


