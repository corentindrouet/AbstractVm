/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 09:46:03 by cdrouet           #+#    #+#             */
/*   Updated: 2017/01/31 10:32:23 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTION_CLASS_HPP
# define INSTRUCTION_CLASS_HPP
# include <string>
# include <vector>
# include <cstring>
# include "Abstract.hpp"

class Instruction {

	public:
		Instruction( std::string const line );
		Instruction( Instruction const & copy );
		~Instruction( void );
		Instruction	&operator=( Instruction const & copy );
		std::string	getInstruct( void ) const;
		eOperandType	getType( void ) const;
		std::string	getValue( void ) const;

	private:
		Instruction( void );
		std::string		_instruct;
		eOperandType	_type;
		std::string		_value;
};

#endif
