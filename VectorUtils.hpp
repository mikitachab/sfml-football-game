#include <iostream>

namespace vecutils {

template<typename VectorType>
void printVector(VectorType v) {
    std::cout << v.x << " " << v.y << std::endl;
}


} // vecutils
