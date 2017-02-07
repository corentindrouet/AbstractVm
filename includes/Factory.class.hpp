/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 10:34:43 by cdrouet           #+#    #+#             */
/*   Updated: 2017/01/31 12:21:18 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_CLASS_HPP
# define FACTORY_CLASS_HPP

# include "IOperand.class.hpp"

class Factory {
	public:
		Factory( void );
		Factory( Factory const & copy );
		~Factory( void );
		Factory	&operator=( Factory const & other );

		IOperand const	*createOperand( eOperandType type, std::string const & value );
	private:
		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;
		typedef IOperand const*(Factory::*FP[5])(std::string const &) const;
		static FP create;
};

#endif
