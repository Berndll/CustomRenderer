#include "../include/Vector.hpp"

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> v) {
    sizeCheck();
    for (int i = 0; i < size(); ++i)
        _vec.at(i) = v.at(i);
}

template<typename T>
Vector<T>& Vector<T>::operator=(std::initializer_list<T> v) {
    _vec.assign(v.begin(), v.end());
}
