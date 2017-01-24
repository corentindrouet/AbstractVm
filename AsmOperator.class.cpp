/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AsmOperator.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 12:35:05 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/02 13:34:39 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AsmOperator.class.hpp"

AsmOperator::AsmOperator( void ) {
  return;
}

AsmOperator::AsmOperator( AsmOperator const & copy ) {
  *this = copy;
  return;
}

AsmOperator::~AsmOperator( void ) {
  for( int i = (this->_stack.size() - 1); i >= 0; i-- ) {
    delete this->_stack[i];
    this->_stack.pop_back();
  }
  return;
}

AsmOperator	&AsmOperator::operator=( AsmOperator const & copy ) {
  for( int i = (this->_stack.size() - 1); i >= 0; i-- ) {
    delete this->_stack[i];
    this->_stack.pop_back();
  }
  this->_stack = copy.getStack();
  return *this;
}

std::vector<const IOperand*>		AsmOperator::getStack( void ) const {
  return this->_stack;
}

void	AsmOperator::push( Instruction const & value ) {
  try {
    this->_stack.push_back(Factory::Factory().createOperand(value.getType(), value.getValue()));
  } catch ( std::exception & e ) {
    std::cout << e.what() << std::endl;
  }
}

void	AsmOperator::pop( void ) {
  if (this->_stack.size() == 0)
    throw StackExceptions("Error: pop on empty stack !");
  delete this->_stack[this->_stack.size() - 1];
  this->_stack.pop_back();
}

void	AsmOperator::dump( void ) {
  for ( int i = (this->_stack.size() - 1); i >= 0; i-- ) {
    std::cout << i << " " << this->_stack[i]->toString() << std::endl;
  }
}

void	AsmOperator::assert( Instruction const & value ) {
  const IOperand *tmp = Factory::Factory().createOperand(value.getType(), value.getValue());

  if (this->_stack.size() < 1)
    throw StackExceptions("Error: assert on empty stack !");
  if (stod(this->_stack.back()->toString()) != stod(tmp->toString()))
    throw StackExceptions("Error: assert between " + this->_stack.back()->toString() + " and " + tmp->toString() + " is false !");
  return;
}

void	AsmOperator::add( void ) {
  const IOperand *tmp;

  if (this->_stack.size() < 2)
    throw StackExceptions("Error operator add: less than 2 values in the stack");
  tmp = *(this->_stack[this->_stack.size() - 2]) +
    *(this->_stack[this->_stack.size() - 1]);
  delete this->_stack[this->_stack.size() - 1];
  delete this->_stack[this->_stack.size() - 2];
  this->_stack.pop_back();
  this->_stack.pop_back();
  this->_stack.push_back(tmp);
}

void	AsmOperator::sub( void ) {
  const IOperand *tmp;

  if (this->_stack.size() < 2)
    throw StackExceptions("Error operator sub: less than 2 values in the stack");
  tmp = *(this->_stack[this->_stack.size() - 2]) -
    *(this->_stack[this->_stack.size() - 1]);
  delete this->_stack[this->_stack.size() - 2];
  delete this->_stack[this->_stack.size() - 1];
  this->_stack.pop_back();
  this->_stack.pop_back();
  this->_stack.push_back(tmp);
}

void	AsmOperator::mul( void ) {
  const IOperand *tmp = NULL;

  if (this->_stack.size() < 2)
    throw StackExceptions("Error operator mul: less than 2 values in the stack");
  tmp = *(this->_stack[this->_stack.size() - 2]) *
    *(this->_stack[this->_stack.size() - 1]);
  delete this->_stack[this->_stack.size() - 2];
  delete this->_stack[this->_stack.size() - 1];
  this->_stack.pop_back();
  this->_stack.pop_back();
  this->_stack.push_back(tmp);
}

void	AsmOperator::div( void ) {
  const IOperand *tmp = NULL;

  if (this->_stack.size() < 2)
    throw StackExceptions("Error operator div: less than 2 values in the stack");
  tmp = *(this->_stack[this->_stack.size() - 2]) /
    *(this->_stack[this->_stack.size() - 1]);
  delete this->_stack[this->_stack.size() - 2];
  delete this->_stack[this->_stack.size() - 1];
  this->_stack.pop_back();
  this->_stack.pop_back();
  this->_stack.push_back(tmp);
}

void	AsmOperator::mod( void ) {
  const IOperand *tmp;

  if (this->_stack.size() < 2)
    throw StackExceptions("Error operator mod: less than 2 values in the stack");
  tmp = *(this->_stack[this->_stack.size() - 2]) %
    *(this->_stack[this->_stack.size() - 1]);
  delete this->_stack[this->_stack.size() - 2];
  delete this->_stack[this->_stack.size() - 1];
  this->_stack.pop_back();
  this->_stack.pop_back();
  this->_stack.push_back(tmp);
}

void	AsmOperator::print( void ) {
  if (this->_stack.size() < 1)
    throw StackExceptions("Error: print on empty stack");
  if (this->_stack.back()->getType() != Int8)
    throw StackExceptions("The last stack value isnot an Int8");
  if (!std::isprint(std::stoi(this->_stack.back()->toString())))
    throw StackExceptions("Character not printable");
  std::cout << static_cast<char>(std::stoi(this->_stack.back()->toString())) << std::endl;
}

void	AsmOperator::exit( void ) {
  for ( int i = (this->_stack.size() - 1); i >= 0; i--) {
    delete this->_stack[i];
    this->_stack.pop_back();
  }
}

AsmOperator::StackExceptions::StackExceptions( void ) {
  return;
}

AsmOperator::StackExceptions::StackExceptions( AsmOperator::StackExceptions const & copy ) {
  *this = copy;
  return;
}

AsmOperator::StackExceptions::StackExceptions( std::string msg ) : _msg(msg) {
  return;
}

AsmOperator::StackExceptions::~StackExceptions( void ) {
  return;
}

std::string   AsmOperator::StackExceptions::getMsg( void ) const {
  return this->_msg;
}

AsmOperator::StackExceptions  &AsmOperator::StackExceptions::operator=( AsmOperator::StackExceptions const & copy ) {
  this->_msg = copy.getMsg();
  return *this;
}

const char  *AsmOperator::StackExceptions::what( void ) const throw() {
  return this->_msg.c_str();
}
