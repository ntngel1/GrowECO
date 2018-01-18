#ifndef ISENSOR_READER_H_
#define ISENSOR_READER_H_

class ISensorReader {
    public:
        virtual float read(void) = 0;
};

class NotRealizedReader : public ISensorReader {
    public:
        NotRealizedReader(void) {}

        float read(void) {
            return 0;
        }
};

#endif