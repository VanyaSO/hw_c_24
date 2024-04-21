#ifndef ARRAY_H
#define ARRAY_H

template<typename T>
class Array {
    T* _arr;
    // размер массива на сколько выделили память
    int _size;
    int _grow;
    // реальное количество елементов  в массиве
    int _elements;

public:
    Array();
    Array(T* arr, int size);
    Array(const Array<T>&);
    ~Array();

    int getSize() const;
    int getElements() const;
    void setSize(int, int);
    int getUpperBound() const;
    bool isEmpty() const;
    void freeExtra();
    void removeAll();
    T& getAt(int) const;
    T& operator[](int) const;
    void setAt(const T&, int);
    void add(const T&);
    void show();
    void append(const Array<T>&);
    Array<T>& operator=(const Array<T>&);
    T* getData();
    void insertAt(const T&, int);
    void insertAt(const T*, int, int);
    void removeAt(int);
};

template<typename T>
void Array<T>::removeAt(int index) {
    if (index > _elements-1 || index < 0)
    {
        return;
    }

    for (int i = 0, j = 0; i < _size; ++i) {
        if (i == index)
            ++j;

        _arr[i] = _arr[i + j];
    }
}


template<typename T>
Array<T>::Array():
        _arr{nullptr},
        _size{0},
        _grow{0},
        _elements{0}
{
}

template<typename T>
Array<T>::Array(T* arr, int size) {
    if(size > 0 && arr != nullptr)
    {
        _size = size;
        _grow = 0;
        _elements = 0;

        _arr = new T[_size];
        for (int i = 0; i < _size; ++i) {
            _arr[i] = arr[i];
            _elements+=1;
        }
    }
    else
    {
        _arr = nullptr;
        _size = 0;
        _grow = 0;
        _elements = 0;
    }
}

template<typename T>
Array<T>::Array(const Array<T>& obj) {
    _size = obj._size;
    _grow = obj._grow;
    _elements = obj._elements;
    _arr = new T[_size];
    for (int i = 0; i < _size; ++i) {
        _arr[i] = obj._arr[i];
    }
}

template<typename T>
Array<T>::~Array() {
    if(_arr != nullptr)
    {
        delete[] _arr;
    }
}

template<typename T>
int Array<T>::getSize() const {
    return _size;
}

template<typename T>
int Array<T>::getElements() const {
    return _elements;
}

template<typename T>
void Array<T>::setSize(int size, int grow) {

    if (size < _elements)
    {
        _elements = size;
    }

    T* newArr = new T[size];
    for (int i = 0; i < _elements; ++i) {
        newArr[i] = _arr[i];
    }
    delete[] _arr;
    _arr = newArr;
    _size = size;
    _grow = grow;
}

template<typename T>
int Array<T>::getUpperBound() const {
    return _elements - 1;
}

template<typename T>
bool Array<T>::isEmpty() const {
    return _elements == 0;
}

template<typename T>
void Array<T>::show() {
    for (int i = 0; i < _size; ++i) {
        cout << _arr[i] << " ";
    }
    cout << endl;
}

template<typename T>
void Array<T>::freeExtra() {
    _size = _elements;
    T* newArr = new T[_size];

    for (int i = 0; i < _elements; ++i) {
        newArr[i] = _arr[i];
    }
}

template<typename T>
void Array<T>::removeAll() {
    _size = 0;
    _elements = 0;
    delete[] _arr;
    _arr = nullptr;
}

template<typename T>
T& Array<T>::getAt(int index) const {
    return _arr[index];
}

template<typename T>
T& Array<T>::operator[](int index) const {
    return _arr[index];
}

template<typename T>
void Array<T>::setAt(const T& obj, int index) {
    if (index < _size && index >= 0)
    {
        _arr[index] = obj;
    }
}

template<typename T>
void Array<T>::add(const T& obj) {
    if (_elements == _size) {
        setSize(_size+_grow, _grow);
    }
    _arr[_elements++] = obj;
}

template<typename T>
void Array<T>::append(const Array<T>& obj)
{
    int newSize = _elements + obj.getElements();
    int elements = 0;
    T* newArr = new T[newSize];

    int k = 0;
    for (int i = 0; i < _elements; ++i) {
        newArr[k++] = _arr[i];
        elements++;
    }
    for (int i = 0; i < obj.getElements(); ++i) {
        newArr[k++] = obj[i];
        elements++;
    }

    _size = newSize;
    _elements = elements;
    _grow = _grow > obj._grow ? _grow : obj._grow;
    delete _arr;
    _arr = newArr;
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& obj) {
    _size = obj._size;
    _grow = obj._grow;
    _elements = obj._elements;
    _arr = new T[_size];

    for (int i = 0; i < _size; ++i) {
        _arr[i] = obj._arr[i];
    }

    return *this;
}

template<typename T>
T* Array<T>::getData() {
    return _arr;
}

template<typename T>
void Array<T>::insertAt(const T& obj, int index) {
    if (index > _elements-1 || index < 0)
    {
        return;
    }

    if (_elements == _size) {
        setSize(_size+_grow, _grow);
    }

    T* newArr = new int[_elements+1];
    for (int i = 0, j = 0; i < _elements+1; ++i, j++) {
        if (j == index)
        {
            newArr[j] = obj;
            --i;
        }
        else
        {
            newArr[j] = _arr[i];
        }
    }
    _elements++;

    delete[] _arr;
    _arr = newArr;
}

template<typename T>
void Array<T>::insertAt(const T* arr, int sizeArr, int index) {
    if (index > _elements-1 || index < 0)
    {
        return;
    }

    if ((_elements + sizeArr) > _size)
    {
        setSize((_size+sizeArr) + _grow, _grow);
    }

    T* newArr = new int[_size];
    for (int i = 0, j = 0; i < _size; ++i, ++j)
    {
        if (j == index)
        {
            for (int k = 0; k < sizeArr; ++k) {
                newArr[j] = arr[k];
                ++j;
            }
        }
        newArr[j] = _arr[i];
    }

    delete[] _arr;
    _arr = newArr;
}




#endif
