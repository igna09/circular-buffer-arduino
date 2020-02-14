#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <Arduino.h>
#include <BaseClass.h>

#define MAX_SIZE 50

template <class T>
class CircularBuffer : BaseClass {
    private:
        T _messages[MAX_SIZE];
        int _size;
        int _lastItemIndex;
        void _increaseNextItemIndex() {
            BaseClass::_acquireMutex();
            _lastItemIndex++;
            BaseClass::_releaseMutex();
        };

    public:
        CircularBuffer(int size) {
            _lastItemIndex = -1;
            if(size < MAX_SIZE) {
                _size = size;
            } else {
                _size = MAX_SIZE;
            }
        };
        void _init() {}; // this method is not necessary as constructor does not have parameters
        void storeMessage(T message) {
            _increaseNextItemIndex();
            BaseClass::_acquireMutex();
            _messages[_lastItemIndex % _size] = message;
            BaseClass::_releaseMutex();
        };
        T getMessage(int index) {
            if(index >= 0 && index < _size) {
                return _messages[index];
            } else {
                return "";
            }
        };
        int getLastItemIndex() {
            return _lastItemIndex;
        };
        int size() {
            return _size;
        }
};

#endif