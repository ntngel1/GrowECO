#ifndef ISENSOR_H_
#define ISENSOR_H_

#include "ISensorReader.h"

class ISensor {
    public:
        float read(void) {
            return _reader -> read();
        }

        void setReader(ISensorReader* reader) {
            this -> _reader = reader;    
        }

        ISensorReader* getReader(void) {
            return _reader;
        }

    protected:
        ISensorReader* _reader;
};

#endif