/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ExecFile.class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdrouet <cdrouet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:05:56 by cdrouet           #+#    #+#             */
/*   Updated: 2017/02/07 09:36:24 by cdrouet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ExecFile.class.hpp"

ExecFile::ExecFile( void ) {
	this->_fileName = "Input";
  this->_error = false;
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
      if (!checkForErrors( tmp, line ))
        this->_error = true;
      else
        this->_instructs.push_back(new Instruction(tmp));
    }

  }	while (tmp != ";;");
  if (std::cin.eof()) {
    this->_errors << std::string(this->_fileName + ": Bad end of file !");
    this->_error = true;
  }
  this->checkEndErrors();
  if (this->_error)
      throw FileExceptions( this->_errors.str() );
  this->dispatch();
	return;
}

void 	ExecFile::useFile( std::string fileName ) {
	std::string	tmp;
  int         line = 0;

	this->_file.open(fileName, std::ios::out);
  if (!this->_file.is_open())
    throw FileExceptions(fileName + ": Can't open this file !");
  tmp = fileName;
  this->_fileName = fileName;
  while (!this->_file.eof()) {
    std::getline(this->_file, tmp);
    line++;
    if (!std::regex_match(tmp, std::regex("^(\\s*;.*|\\s*$)"))) {
      if (!checkForErrors( tmp, line ))
        this->_error = true;
      else
        this->_instructs.push_back(new Instruction(tmp));
    }
  }
  this->checkEndErrors();
  if (this->_error)
    throw FileExceptions( this->_errors.str() );
  this->dispatch();
  this->_file.close();
  return;
}

bool	ExecFile::checkForErrors( std::string str, int line ) {
  if (!regex_match(str, std::regex("^\\s*(((push|assert)\\s+((float|double)"
          "\\(([+-]{0,1}[\\d.?]+)\\)|(int(8|16|32))\\(([+-]{0,1}[\\d]+)\\)))|"
          "(add|pop|dump|sub|mul|div|mod|print|exit))\\s*(;.*|$)"))) {
    if (this->_errors.str().size())
      this->_errors << std::endl;
    this->_errors << std::string(this->_fileName + ": Bad instruction line: " +
        std::to_string(line) + " <" + str + ">");
    return false;
  }
  return true;
}

void  ExecFile::checkEndErrors( void ) {
	if (!this->_instructs.size() && !this->_error) {
    this->_error = true;
    this->_errors << std::string(this->_fileName + ": No instruction found ! ");
  }
  else if (this->_instructs.size() && !std::regex_match(
        this->_instructs.back()->getInstruct(),
        std::regex("^\\s*exit\\s*($|;.*$)"))) {
    if (this->_errors.str().size())
      this->_errors << std::endl;
    this->_error = true;
    this->_errors << std::string(this->_fileName + ": No exit found !");
  }
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

  for ( unsigned long i = 0; i < this->_instructs.size(); i++ ) {
    if (needArguments(this->_instructs[i]->getInstruct()))
      (this->_stack.*fWithArgs[this->_instructs[i]->getInstruct()])(*(this->_instructs[i]));
    else
      (this->_stack.*f[this->_instructs[i]->getInstruct()])();
  }
}

ExecFile::FileExceptions::FileExceptions( std::string const &errors ) : _errors(errors) {
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
  return this->_errors.c_str();
}
