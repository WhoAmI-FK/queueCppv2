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

        explicit queue()
            : _elements(0),_capacity(20),_queue(_Alloc().allocate(20)),_first(0)
        {
            
        }
        explicit queue(const _que& copy)
            :_elements(copy._elements),
            _capacity(copy._capacity+20),
            _queue(_Alloc().allocate(copy._capacity+20)),
            _first(copy._first)
        {
                for (int i = 0; i < copy._elements; ++i) {
                    _Alloc().construct(&_queue[i], *(copy._queue + i));
                }
        }
        _que& operator=(const _que& rhs) {
            if (this == &rhs) {
                throw std::invalid_argument("Self-assignment error");
            }
            else {
                for (size_type i = 0; i < _capacity; ++i) {
                    _Alloc().destroy(_queue + i);
               }
                _Alloc().deallocate(_queue, _capacity);
                _queue = _Alloc().allocate(rhs._capacity);
                for (size_type i = 0; i < rhs._elements; ++i) {
                    _Alloc().construct(&_queue[i], rhs._queue[i]);
                }
                _elements = rhs._elements;
                _capacity = rhs._capacity;
                _first = rhs._first;
            }
            return *this;
        }
        size_type size() const {
            return _elements;
        }
        void push(_val_type val) {
            if (_elements == _capacity) {
                extend();
            }
            size_type insertTo = (_first + _elements) % _capacity;
            _Alloc().construct(&_queue[insertTo], val);
            _elements++;
        }
        bool empty() const{
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
        _val_type& front() {
            return _queue[_first];
        }
        _val_type& back() {
            return  _queue[((_elements - 1) % _capacity)];
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
    try {
        // code
    }
    catch (std::exception e) {
        std::cout << e.what() << std::endl;
    }
    return 0;

}
