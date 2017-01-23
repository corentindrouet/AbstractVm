/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:27:42 by cdrouet           #+#    #+#             */
/*   Updated: 2017/01/23 15:33:06 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TOperand.class.hpp"

int main( void )
{
	IOperand	*op;

	op = Operand<int8_t>::Operand().createOperand(Int8, "56");
	std::cout << op->toString() << std::endl;
	return 0;
}
