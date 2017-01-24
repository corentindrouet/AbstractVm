/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecFile.class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 09:24:20 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/02 13:02:00 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECFILE_CLASS_HPP
# define EXECFILE_CLASS_HPP
# include "AsmOperator.class.hpp"
# include <iostream>
# include <fstream>
# include <string>
# include <regex>
# include <vector>
# include <map>
# include "instruction.class.hpp"

class ExecFile {

	public:
		ExecFile( void );
		ExecFile( ExecFile const & copy );
		~ExecFile( void );
		ExecFile	&operator=( ExecFile const & copy );
		void		useCin( void );
		void		useFile( std::string fileName );
		AsmOperator	getStack( void ) const;
		std::string	getFileName( void ) const;
		std::vector<Instruction*>	getInstructions( void ) const;
    class FileExceptions : public std::exception {
      public:
        FileExceptions( void );
        FileExceptions( ExecFile const &file );
        FileExceptions( std::string const badInstruct, int line );
        FileExceptions( ExecFile::FileExceptions const & copy );
        ~FileExceptions( void ) throw();
        FileExceptions  &operator=( ExecFile::FileExceptions const & );
        virtual const char  *what( void ) const throw();
      private:
        bool        _isFile;
        std::string _fileName;
        int         _instructSize;
        std::string _badInstruct;
        int         _line;
    };

	private:
		bool		checkForErrors( std::string str );
		void		dispatch( void );
		AsmOperator	_stack;
		std::string	_fileName;
		std::ifstream	_file;
		std::vector<Instruction*>	_instructs;
};

#endif
