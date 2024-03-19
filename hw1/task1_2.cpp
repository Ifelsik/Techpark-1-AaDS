
// Вернуть значение бита в числе N по его номеру K.
// Формат входных данных. Число N, номер бита K

#include <assert.h>

#include <iostream>
#include <sstream>
#include <cstdint>

int getBitAt(unsigned int n, unsigned int k) {
    return ((n >> k) & 1);
}

void run(std::istream& in, std::ostream& out) {
    int n = 0, k = 0;
    in >> n >> k;
    out << getBitAt(n, k) << std::endl;
}

void tests() {
    {
        std::stringstream in;
        std::stringstream out;
 
        int n = 0b10110;
        int k = 4;
        in << n << ' ' << k;
        run(in, out);
        assert(out.str() == "1\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        int n = 0b1010;
        int k = 2;
        in << n << ' ' << k;
        run(in, out);
        assert(out.str() == "0\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        int n = 0b111;
        int k = 5;
        in << n << ' ' << k;
        run(in, out);
        assert(out.str() == "0\n");
    }
    {
        std::stringstream in;
        std::stringstream out;
        
        unsigned int n = UINT32_MAX;
        int k = 32;
        in << n << ' ' << k;
        run(in, out);
        assert(out.str() == "1\n");
    }
    std::cout << "All tests have passed" << std::endl;
}

int main() {
    // tests();
    run(std::cin, std::cout);
    return 0;
}
