/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 11:10:41 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/06 09:09:26 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Factory.class.hpp"
# include "TOperand.class.hpp"

Factory::FP Factory::create = {
	&Factory::createInt8,
	&Factory::createInt16,
	&Factory::createInt32,
	&Factory::createFloat,
	&Factory::createDouble
};

Factory::Factory( void ) {
	return;
}

Factory::Factory( Factory const & copy ) {
	*this = copy;
	return;
}

Factory::~Factory( void ) {
	return;
}

Factory	&Factory::operator=( Factory const & ) {
	return *this;
}

IOperand const	*Factory::createOperand( eOperandType type, std::string const & value ) {
	return (this->*create[type])(value);
}

IOperand const * Factory::createInt8( std::string const & value ) const {
	return new Operand<int8_t>(Int8, value);
}

IOperand const * Factory::createInt16( std::string const & value ) const {
	return new Operand<int16_t>(Int16, value);
}

IOperand const * Factory::createInt32( std::string const & value ) const {
	return new Operand<int32_t>(Int32, value);
}

IOperand const * Factory::createFloat( std::string const & value ) const {
	return new Operand<float>(Float, value);
}

IOperand const * Factory::createDouble( std::string const & value ) const {
	return new Operand<double>(Double, value);
}
