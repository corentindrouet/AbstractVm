/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:27:42 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/02 10:54:20 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ExecFile.class.hpp"

int main( int argc, char **argv )
{
  try {
    if (argc == 1)
      ExecFile::ExecFile().useCin();
    else if (argc == 2)
      ExecFile::ExecFile().useFile(argv[1]);
    else {
      std::cout << "0 or 1 arguments" << std::endl;
      return 1;
    }
  } catch (std::exception & e) {
    std::cout << e.what() << std::endl;
  }
	return 0;
}
