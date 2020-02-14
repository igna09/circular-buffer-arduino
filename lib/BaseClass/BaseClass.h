#ifndef __BASE_CLASS_H__
#define __BASE_CLASS_H__

#include <Arduino.h>

class BaseClass {
    private:
        SemaphoreHandle_t _mutex;
        bool _initialized;
        /*void _acquireMutex();
        void _releaseMutex();*/

    protected:
        BaseClass();
        void _acquireMutex();
        void _releaseMutex();
        virtual void _init() = 0;
        void _setInitialized();
        bool _isInitialized();
        //void acquireMutexAndExecute(void (*func)());
        
};

#endif