/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.class.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 09:46:03 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/07 11:38:49 by cdrouet          ###   ########.fr       */
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
		Instruction( std::string const line, int nbLine );
		Instruction( Instruction const & copy );
		~Instruction( void );
		Instruction	&operator=( Instruction const & copy );
		std::string	getInstruct( void ) const;
		eOperandType	getType( void ) const;
		std::string	getValue( void ) const;
		std::string	getFullInstruct( void ) const;
		int	        getLine( void ) const;

	private:
		Instruction( void );
    std::string   _fullInstruct;
		std::string		_instruct;
		eOperandType	_type;
		std::string		_value;
    int           _line;
};

#endif
