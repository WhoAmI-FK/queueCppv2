#include <iostream>

namespace queueV2 {
    template<typename T, class _Alloc = std::allocator<T>>
    class queue {
    public:
        typedef queue<T, _Alloc> _que;
        typedef T _val_type;
        typedef _Alloc _allocator_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef std::size_t size_type;

        queue()
            : _elements(0),_capacity(20),_queue(_Alloc().allocate(20)),_first(0)
        {

        }

        void push(_val_type val) {
            if (_elements == _capacity) {
                extend();
            }
            size_type insertTo = (_first + _elements) % _capacity;
            _Alloc().construct(&_queue[insertTo], val);
            _elements++;
        }
        bool empty() {
            return _elements == 0;
        }
        ~queue() {
            for (size_type i = 0; i < _elements; ++i) {
                _Alloc().destroy(_queue + i);
            }
            _Alloc().deallocate(_queue, _capacity);
        }
        void pop() {
            if (!empty()) {
                _first = (_first + 1) % _capacity;
                _elements--;
            }
            else throw std::runtime_error("Trying to pop empty queue");
        }
        _val_type front() {
            return _queue[_first];
        }
    private:
        size_type _elements, _capacity,_first;
        T* _queue;
        void extend() {
            pointer buff = _Alloc().allocate(_capacity + 20);
            for (size_type i = 0, j = _first; i < _elements; ++i, ++j) {
                size_type copyFrom = j % _capacity;
                _Alloc().construct(&buff[i], *(_queue+copyFrom));
            }
            std::swap(_queue, buff);
            for (size_type i = 0; i < _elements; ++i) {
                _Alloc().destroy((buff + i));
            }
            _Alloc().deallocate(buff, _capacity);
            _capacity += 20;
        }
    };
}

int main()
{
    std::cout << "Hello World!\n";
}
