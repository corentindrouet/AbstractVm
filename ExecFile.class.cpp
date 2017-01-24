/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecFile.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:05:56 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/02 12:52:04 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ExecFile.class.hpp"

ExecFile::ExecFile( void ) {
	this->_fileName = "Input";
	return;
}

ExecFile::ExecFile( ExecFile const & copy ) {
	*this = copy;
	return;
}

ExecFile::~ExecFile( void ) {
	for( int i = (this->_instructs.size() - 1); i >= 0; i-- ) {
		delete this->_instructs[i];
		this->_instructs.pop_back();
	}
	return;
}

ExecFile	&ExecFile::operator=( ExecFile const & copy ) {
	this->_stack = copy.getStack();
	this->_fileName = copy.getFileName();
	this->_instructs = copy.getInstructions();
	return *this;
}

AsmOperator	ExecFile::getStack( void ) const {
	return this->_stack;
}

std::string	ExecFile::getFileName( void ) const {
	return this->_fileName;
}

std::vector<Instruction*>	ExecFile::getInstructions( void ) const {
	return this->_instructs;
}

void 	ExecFile::useCin( void ) {
	std::string	tmp;
  int         line = 0;

	tmp = "Input";
  do {
    std::getline(std::cin, tmp);
    line++;
    if (std::cin.eof())
      break;
    if (!std::regex_match(tmp, std::regex("^(\\s*;.*|\\s*$)"))) {
      if (!checkForErrors( tmp ))
        throw FileExceptions(tmp, line);
      this->_instructs.push_back(new Instruction(tmp));
    }

  }	while (tmp != ";;");
  if (std::cin.eof() || !this->_instructs.size() || this->_instructs.back()->getInstruct() != "exit")
      throw FileExceptions(*this);
  this->dispatch();
	return;
}

void 	ExecFile::useFile( std::string fileName ) {
	std::string	tmp;
  int         line = 0;

	this->_file.open(fileName, std::ios::out);
	tmp = "Input";
	while (!this->_file.eof()) {
		std::getline(this->_file, tmp);
    line++;
		if (!std::regex_match(tmp, std::regex("^(\\s*;.*|\\s*$)"))) {
			if (!checkForErrors( tmp ))
				throw FileExceptions(tmp, line);
			this->_instructs.push_back(new Instruction(tmp));
		}
	}
	if (!this->_instructs.size() || this->_instructs.back()->getInstruct() != "exit")
		throw FileExceptions(*this);
  this->dispatch();
  this->_file.close();
  return;
}

bool	ExecFile::checkForErrors( std::string str ) {
	return regex_match(str, std::regex("^\\s*(((push|assert)\\s+((float|double)\\(([+-]{0,1}[\\d.?]+)\\)|(int(8|16|32))\\(([+-]{0,1}[\\d]+)\\)))|(add|pop|dump|sub|mul|div|mod|print|exit))\\s*(;.*|$)"));
}

static bool	needArguments( std::string f ) {
	if (f == "push" || f == "assert")
		return true;
	return false;
}

void	ExecFile::dispatch( void ) {
	std::map<std::string, void (AsmOperator::*)(Instruction const &)> fWithArgs;
	fWithArgs["push"] = &AsmOperator::push;
	fWithArgs["assert"] = &AsmOperator::assert;
	std::map<std::string, void (AsmOperator::*)(void)> f;
	f["pop"] = &AsmOperator::pop;
	f["dump"] = &AsmOperator::dump;
	f["add"] = &AsmOperator::add;
	f["sub"] = &AsmOperator::sub;
	f["mul"] = &AsmOperator::mul;
	f["div"] = &AsmOperator::div;
	f["mod"] = &AsmOperator::mod;
	f["print"] = &AsmOperator::print;
	f["exit"] = &AsmOperator::exit;

  for ( unsigned long i = 0; i < (this->_instructs.size() - 1); i++ ) {
    if (needArguments(this->_instructs[i]->getInstruct()))
      (this->_stack.*fWithArgs[this->_instructs[i]->getInstruct()])(*(this->_instructs[i]));
    else
      (this->_stack.*f[this->_instructs[i]->getInstruct()])();
  }
}

ExecFile::FileExceptions::FileExceptions( void ) {
  this->_isFile = false;
  this->_fileName = "";
  this->_instructSize = -1;
  this->_badInstruct = "";
  this->_line = 0;
  return;
}

ExecFile::FileExceptions::FileExceptions( ExecFile const & file ) {
  this->_isFile = true;
  this->_fileName = file.getFileName();
  this->_instructSize = file.getInstructions().size();
  this->_badInstruct = "";
  this->_line = 0;
  return;
}

ExecFile::FileExceptions::FileExceptions( std::string const badInstruct, int line ) {
  this->_isFile = false;
  this->_fileName = "";
  this->_instructSize = -1;
  this->_badInstruct = badInstruct;
  this->_line = line;
  return;
}

ExecFile::FileExceptions::FileExceptions( ExecFile::FileExceptions const & copy ) {
  *this = copy;
  return;
}

ExecFile::FileExceptions::~FileExceptions( void ) throw() {
  return;
}

ExecFile::FileExceptions  &ExecFile::FileExceptions::operator=( ExecFile::FileExceptions const & ) {
  return *this;
}

const char *ExecFile::FileExceptions::what( void ) const throw() {
  if (this->_isFile) {
    if (!this->_instructSize)
      return (std::string("No instruction found in file: " + this->_fileName + " !").c_str());
    else
      return (std::string("No exit found in file: " + this->_fileName + " !").c_str());
  } else if (this->_badInstruct != "") {
    return (std::string("Bad instruction line: " + std::to_string(this->_line) + " <" + this->_badInstruct + ">").c_str());
  }
  return (std::string("An error occured !").c_str());
}
