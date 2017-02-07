/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOperand.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 09:53:03 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/07 08:51:34 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPERAND_CLASS_HPP
# define TOPERAND_CLASS_HPP

# include "IOperand.class.hpp"
# include <vector>
# include <string>
# include <cmath>
# include <limits.h>
# include <stdexcept>
# include "Factory.class.hpp"

template< typename T >
class Operand : public IOperand {

	public:
		Operand<T>( void ) {
			return;
		}

		Operand<T>( eOperandType type, std::string const & value ) :
			_type(type) {
			this->_precision = type;
			this->_stringRep = std::to_string(static_cast<T>(stod(value, NULL)));
			if (static_cast<double>(stod(value, NULL)) > std::numeric_limits<T>::max())
        throw std::overflow_error("Value overflow");
			else if (static_cast<double>(stod(value, NULL)) < std::numeric_limits<T>::lowest())
        throw std::underflow_error("Value underflow");
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
			return Factory::Factory().createOperand((rhs.getPrecision() > this->_precision) ?
					rhs.getType() : this->_type,
					std::to_string(static_cast<double>(stod(rhs.toString(), NULL)) + this->_value));
		}

		IOperand const	*operator-( IOperand const & rhs ) const {
			return Factory::Factory().createOperand((rhs.getPrecision() > this->_precision) ?
					rhs.getType() : this->_type,
					std::to_string(this->_value - static_cast<double>(stod(rhs.toString(), NULL))));
		}

		IOperand const	*operator*( IOperand const & rhs ) const {
			return Factory::Factory().createOperand((rhs.getPrecision() > this->_precision) ?
					rhs.getType() : this->_type,
					std::to_string(static_cast<double>(stod(rhs.toString(), NULL)) * this->_value));
		}

		IOperand const	*operator/( IOperand const & rhs ) const {
			if (static_cast<T>(stod(rhs.toString(), NULL)) == 0)
				throw std::domain_error("Divide by 0");
			return Factory::Factory().createOperand((rhs.getPrecision() > this->_precision) ?
					rhs.getType() : this->_type,
					std::to_string(this->_value / static_cast<double>(stod(rhs.toString(), NULL))));
		}

		IOperand const	*operator%( IOperand const & rhs ) const {
			if (static_cast<T>(stod(rhs.toString(), NULL)) == 0)
				throw std::domain_error("Divide by 0");
			return Factory::Factory().createOperand((rhs.getPrecision() > this->_precision) ?
					rhs.getType() : this->_type,
					std::to_string(fmod(static_cast<double>(this->_value), stod(rhs.toString(), NULL))));
		}

		std::string const	&toString( void ) const {
			return this->_stringRep;
		}

	private:
		eOperandType		_type;
		int					_precision;
		T					_value;
		std::string			_stringRep;
};
#endif
