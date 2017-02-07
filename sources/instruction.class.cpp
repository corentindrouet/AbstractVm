/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.class.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 09:51:31 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/07 11:43:06 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "instruction.class.hpp"
#include <iostream>

Instruction::Instruction( void ) : _instruct(NULL), _type(Int8), _value(NULL) {
	return;
}

Instruction::Instruction( std::string const line, int nbLine ) : _instruct(""), _type(Int8), _value("") {
	char	*cline = new char[line.length() + 1];
	strcpy(cline, line.c_str());
	char	*tmp = NULL;

  this->_fullInstruct = line;
  this->_line = nbLine;
	tmp = std::strtok(cline, " ()");
	if (tmp)
		this->_instruct = tmp;
	tmp = std::strtok(NULL, " ()");
	if (tmp) {
		if (strcmp(tmp, "int8") == 0)
			this->_type = Int8;
		else if (strcmp(tmp,"int16") == 0)
			this->_type = Int16;
		else if (strcmp(tmp, "int32") == 0)
			this->_type = Int32;
		else if (strcmp(tmp, "float") == 0)
			this->_type = Float;
		else if (strcmp(tmp, "double") == 0)
			this->_type = Double;
		tmp = std::strtok(NULL, " ()");
		if (tmp)
			this->_value = tmp;
	}
	delete [] cline;
	return;
}

Instruction::Instruction( Instruction const & copy ) {
	*this = copy;
	return;
}

Instruction::~Instruction( void ) {
	return;
}

Instruction	&Instruction::operator=( Instruction const & copy ) {
	this->_instruct = copy.getInstruct();
	this->_type = copy.getType();
	this->_value = copy.getValue();
	return *this;
}

std::string	Instruction::getInstruct( void ) const {
	return this->_instruct;
}

eOperandType	Instruction::getType( void ) const {
	return this->_type;
}

std::string	Instruction::getValue( void ) const {
	return this->_value;
}

std::string	Instruction::getFullInstruct( void ) const {
	return this->_fullInstruct;
}

int	Instruction::getLine( void ) const {
	return this->_line;
}
