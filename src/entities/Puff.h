#pragma once

#include <Arduboy2.h>
#include "../utils/Constants.h"



struct Puff {

    private:

        PuffMode mode;
        uint8_t counter;
        uint8_t index;

    public:

        PuffMode getPuffMode()              { return this->mode; }
        uint8_t getCounter()                { return this->counter; }
        uint8_t getIndex()                  { return this->index; }

        void setPuffMode(PuffMode val)      { this->mode = val; }
        void setCounter(uint8_t val)        { this->counter = val; }
        void setIndex(uint8_t val)          { this->index = val; }

        void init(PuffMode mode, uint8_t index) {
        
            this->counter = 1;
            this->mode = mode;
            this->index = index;

        }

};