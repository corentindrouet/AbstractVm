/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOperand.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 09:53:03 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/02 13:36:33 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPERAND_CLASS_HPP
# define TOPERAND_CLASS_HPP

# include "IOperand.class.hpp"
# include <vector>
# include <string>
# include <math.h>
# include <limits.h>
# include "Factory.class.hpp"

template< typename T >
class Operand : public IOperand {

	public:
		Operand<T>( void ) {
			return;
		}

		Operand<T>( eOperandType type, std::string const & value ) :
			_type(type) {
			this->_precision = 0;
			this->_stringRep = std::to_string(static_cast<T>(stod(value, NULL)));
			if (static_cast<double>(stod(value, NULL)) > std::numeric_limits<T>::max())
				throw OverflowException();
			else if (static_cast<double>(stod(value, NULL)) < std::numeric_limits<T>::lowest())
				throw UnderflowException();
			this->_value = static_cast<T>(stod(value, NULL));
			return;
		}

		Operand<T>( Operand const & copy ) {
			*this = copy;
			return;
		}

		~Operand<T>( void ) { return; }

		Operand<T>	&operator=( Operand const & otherOperand ) {
			this->_type = otherOperand.getType();
			this->_precision = otherOperand.getPrecision();
			this->_value = static_cast<T>(otherOperand.getValue());
			return;
		}

		int	getPrecision( void ) const {
			return this->_precision;
		}

		eOperandType	getType( void ) const {
			return this->_type;
		}

		T				getValue( void ) const {
			return this->_value;
		}

		const IOperand	*operator+( IOperand const & rhs ) const {
			return Factory::Factory().createOperand((rhs.getType() > this->_type) ?
					rhs.getType() : this->_type,
					std::to_string(static_cast<double>(stod(rhs.toString(), NULL)) + this->_value));
		}

		IOperand const	*operator-( IOperand const & rhs ) const {
			return Factory::Factory().createOperand((rhs.getType() > this->_type) ?
					rhs.getType() : this->_type,
					std::to_string(this->_value - static_cast<double>(stod(rhs.toString(), NULL))));
		}

		IOperand const	*operator*( IOperand const & rhs ) const {
			return Factory::Factory().createOperand((rhs.getType() > this->_type) ?
					rhs.getType() : this->_type,
					std::to_string(static_cast<double>(stod(rhs.toString(), NULL)) * this->_value));
		}

		IOperand const	*operator/( IOperand const & rhs ) const {
			if (static_cast<T>(stod(rhs.toString(), NULL)) == 0)
				throw DivideZeroException();
			return Factory::Factory().createOperand((rhs.getType() > this->_type) ?
					rhs.getType() : this->_type,
					std::to_string(this->_value / static_cast<double>(stod(rhs.toString(), NULL))));
		}

		IOperand const	*operator%( IOperand const & rhs ) const {
			if (static_cast<T>(stod(rhs.toString(), NULL)) == 0)
				throw DivideZeroException();
			return Factory::Factory().createOperand((rhs.getType() > this->_type) ?
					rhs.getType() : this->_type,
					std::to_string(fmod(static_cast<double>(this->_value), stod(rhs.toString(), NULL))));
		}

		std::string const	&toString( void ) const {
			return this->_stringRep;
		}

		class OverflowException : public std::exception {

			public:
				OverflowException( void ) { return; }
				OverflowException( OverflowException const & copy ) {
					*this = copy;
					return;
				}
				~OverflowException( void ) throw() { return; }
				OverflowException	&operator=( OverflowException const & ) {
					return *this;
				}
				virtual const char *what() const throw() {
					return ("Value overflow");
				}
		};

		class UnderflowException : public std::exception {

			public:
				UnderflowException( void ) { return; }
				UnderflowException( UnderflowException const & copy ) {
					*this = copy;
					return;
				}
				~UnderflowException( void ) throw() { return; }
				UnderflowException	&operator=( UnderflowException const & ) {
					return *this;
				}
				virtual const char *what() const throw() {
					return ("Value underflow");
				}
		};

		class DivideZeroException : public std::exception {

			public:
				DivideZeroException( void ) { return; }
				DivideZeroException( DivideZeroException const & copy ) {
					*this = copy;
					return;
				}
				~DivideZeroException( void ) throw() { return; }
				DivideZeroException	&operator=( DivideZeroException const & ) {
					return *this;
				}
				virtual const char *what() const throw() {
					return ("Divide by 0");
				}
		};

	private:
		eOperandType		_type;
		int					_precision;
		T					_value;
		std::string			_stringRep;
};
#endif
