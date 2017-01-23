/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOperand.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 09:53:03 by cdrouet           #+#    #+#             */
/*   Updated: 2017/01/23 15:45:33 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPERAND_CLASS_HPP
# define TOPERAND_CLASS_HPP
# include "IOperand.class.hpp"
# include <vector>

enum	eOperandType {
	Int8,
	Int16,
	Int32,
	Float,
	Double
};

template< typename T >
class Operand : IOperand {

	public:
		Operand( void ) {
			return;
		}

		Operand( Operand const & copy ) {
			*this = copy;
			return;
		}

		~Operand<T>( void ) { return; };

		Operand	&operator=( Operand const & otherOperand ) {
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

		IOperand const	*operator+( IOperand const & rhs ) const {
			return new Operand((rhs.getType() > this->_type) ?
					rhs.getType() : this->_type,
					rhs.getValue() + this->_value);
		}

		IOperand const	*operator-( IOperand const & rhs ) const {
			return new Operand((rhs.getType() > this->_type) ?
					rhs.getType() : this->_type,
					rhs.getValue() - this->_value);
		}

		IOperand const	*operator*( IOperand const & rhs ) const {
			return new Operand((rhs.getType() > this->_type) ?
					rhs.getType() : this->_type,
					rhs.getValue() * this->_value);
		}

		IOperand const	*operator/( IOperand const & rhs ) const {
			if (rhs == 0)
				throw std::exception();
			return new Operand((rhs.getType() > this->_type) ?
					rhs.getType() : this->_type,
					rhs.getValue() + this->_value);
		}

		IOperand const	*operator%( IOperand const & rhs ) const {
			if (rhs == 0)
				throw std::exception();
			return new Operand((rhs.getType() > this->_type) ?
					rhs.getType() : this->_type,
					rhs.getValue() + this->_value);
		}

		std::string const	&toString( void ) const {
			return std::to_string(this->_value);
		}

		IOperand const	*createOperand( eOperantType type, std::string const & value ) const {
			vector<IOperand*(*)(std::string &)>	create(5);
			create.push_back(&(this->createInt8));
			create.push_back(&(this->createInt16));
			create.push_back(&(this->createInt32));
			create.push_back(&(this->createFloat));
			create.push_back(&(this->createDouble));
			create[type](value);
		}

	private:
		Operand<T>( eOperandType type, std::string const & value ) :
			_type(type) {
			this->_precision = 0;
			this->_value = dynamic_cast<T>(stod(value, NULL));
			if ( this->_value == NULL )
				throw std::exception();
			return;
		}
		IOperand const * createInt8( std::string const & value ) const {
			return new this->Operand<int8_t>(eOperandType::Int8, value);
		}
		IOperand const * createInt16( std::string const & value ) const {
			return new this->Operand<int16_t>(eOperandType::Int16, value);
		}
		IOperand const * createInt32( std::string const & value ) const {
			return new this->Operand<int32_t>(eOperandType::Int32, value);
		}
		IOperand const * createFloat( std::string const & value ) const {
			return new this->Operand<float>(eOperandType::Float, value);
		}
		IOperand const * createDouble( std::string const & value ) const {
			return new this->Operand<double>(eOperandType::Double, value);
		}
		eOperandType	_type;
		int				_precision;
		T				_value;
};

#endif
