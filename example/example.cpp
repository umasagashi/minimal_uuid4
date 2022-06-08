#include <iostream>

#include "minimal_uuid4.h"

int main() {
    minimal_uuid4::Generator gen;
    for (int i = 0; i < 10; i++) {
        std::cout << gen.uuid4().str() << std::endl;
    }
    return 0;
}
