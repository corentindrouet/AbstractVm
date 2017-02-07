/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 15:27:42 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/07 10:06:45 by cdrouet          ###   ########.fr       */
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
      std::cout << "0 or 1 arguments needed" << std::endl;
      std::cout << "0 argument for standard input" << std::endl;
      std::cout << "1 argument for input from a file (should be a valid file)"
        << std::endl;
      return 1;
    }
  } catch (std::exception & e) {
    std::cout << e.what() << std::endl;
    return 1;
  }
	return 0;
}
