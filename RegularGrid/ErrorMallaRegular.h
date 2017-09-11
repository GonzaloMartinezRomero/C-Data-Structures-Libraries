/* 
 * File:   ErrorMallaRegular.h
 * Author: Drebin
 *
 * Created on 14 de diciembre de 2015, 13:18
 */

#ifndef ERRORMALLAREGULAR_H
#define	ERRORMALLAREGULAR_H

 
#include <stdexcept>
using namespace std;

class ErrorMallaRegular:public logic_error{
public:
    ErrorMallaRegular(const string &msg):logic_error(msg){};
    virtual ~ErrorMallaRegular() throw(){};
};

#endif	/* ERRORMALLAREGULAR_H */

