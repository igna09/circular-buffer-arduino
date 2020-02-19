#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <Arduino.h>

#include <BaseClass.h>

#include <LinkedList.h>

template <class T>
class CircularBuffer : BaseClass {
    private:
        MyLinkedList::LinkedList<T> _elements;
        int _maxSize;
        int _lastItemIndex;
        void _increaseNextItemIndex() {
            BaseClass::_acquireMutex();
            _lastItemIndex++;
            BaseClass::_releaseMutex();
        };

    public:
        CircularBuffer(int size) {
            _lastItemIndex = -1;
            _maxSize = size;
            _elements = MyLinkedList::LinkedList<T>();
            for(int i = 0; i < _maxSize; i++) {
                _elements.add(T());
            }
        };
        void _init() {}; // this method is not necessary because is not a singleton
        void storeElement(T element) {
            _increaseNextItemIndex();
            BaseClass::_acquireMutex();
            _elements.add(_lastItemIndex % _maxSize, element);
            BaseClass::_releaseMutex();
        };
        T getElement(int index) {
            return _elements.get(index);
        };
        bool setElement(T element, int index) {
            return _elements.set(index, element);
        };
        int getLastItemIndex() {
            return _lastItemIndex;
        };
        int size() {
            return _maxSize;
        };
        void setSize(int size) {
            BaseClass::_acquireMutex();
            if(size < _maxSize) {
                for(int i = 0; i < (_maxSize - size); i++) {
                    _elements.pop();
                }
            } else if(size > _maxSize) {
                for(int i = 0; i < (size - _maxSize); i++) {
                    _elements.add(T());
                }
            }
            //_elements._size = size;
            _maxSize = size;
            BaseClass::_releaseMutex();
        };
        void removeFirst() {
            BaseClass::_acquireMutex();
            _elements.shift();
            BaseClass::_releaseMutex();
        }
        void removeLast() {
            BaseClass::_acquireMutex();
            _elements.pop();
            BaseClass::_releaseMutex();
        }
};

#endif