/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AsmOperator.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 09:03:46 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/02 13:03:33 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASMOPERATOR_CLASS_HPP
# define ASMOPERATOR_CLASS_HPP

# include <iostream>
# include <vector>
# include <string>
# include "instruction.class.hpp"
# include "IOperand.class.hpp"
# include "Factory.class.hpp"

class AsmOperator {

	public:
		AsmOperator( void );
		AsmOperator( AsmOperator const & copy );
		~AsmOperator( void );
		AsmOperator	&operator=( AsmOperator const & copy );
		std::vector<const IOperand*>		getStack( void ) const;
		void	push( Instruction const & value );
		void	pop( void );
		void	dump( void );
		void	assert( Instruction const & value );
		void	add( void );
		void	sub( void );
		void	mul( void );
		void	div( void );
		void	mod( void );
		void	print( void );
		void	exit( void );
    class StackExceptions: public std::exception {
      public:
        StackExceptions( std::string msg );
        StackExceptions( AsmOperator::StackExceptions const & copy );
        ~StackExceptions( void );
        std::string   getMsg( void ) const;
        StackExceptions &operator=( AsmOperator::StackExceptions const & copy );
        virtual const char  *what( void ) const throw();
      private:
        StackExceptions( void );
        std::string   _msg;
    };

	private:
		std::vector<const IOperand*>	_stack;
};

#endif
