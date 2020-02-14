#include "BaseClass.h"

BaseClass::BaseClass() {
    _mutex = xSemaphoreCreateMutex();

    _initialized = false;
}

void BaseClass::_acquireMutex() {
    xSemaphoreTake(_mutex, portMAX_DELAY);
}

void BaseClass::_releaseMutex() {
    xSemaphoreGive(_mutex);
}

/*void BaseClass::acquireMutexAndExecute(void (*func)()) {
    _acquireMutex();

    func();

    _releaseMutex();
}*/

void BaseClass::_setInitialized() {
    _initialized = true;
}

bool BaseClass::_isInitialized(){
    return _initialized;
};