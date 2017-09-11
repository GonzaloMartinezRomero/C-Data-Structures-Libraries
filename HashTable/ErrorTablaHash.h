/* 
 * File:   ErrorTablaHash.h
 * Author: Drebin
 *
 * Created on 27 de noviembre de 2015, 11:54
 */

#ifndef ERRORTABLAHASH_H
#define	ERRORTABLAHASH_H
#include <stdexcept>
using namespace std;

class ErrorTablaHash:public logic_error{
public:
    ErrorTablaHash(const string &msg):logic_error(msg){};
    virtual ~ErrorTablaHash() throw(){};
};



#endif	/* ERRORTABLAHASH_H */

