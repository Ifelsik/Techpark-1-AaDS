
// Инвертируйте значение бита в числе N по его номеру K.
// Формат входных данных. Число N, номер бита K.
// Формат выходных данных. Число с инвертированным битом в десятичном виде.

#include <iostream>
#include <assert.h>
#include <sstream>
#include <cstdint>

unsigned int invertBitAt(unsigned int n, int k) {
    return (n ^ (1 << k)); 
}

void run(std::istream& in, std::ostream& out) {
    unsigned int n = 0;
    int k = 0;
    in >> n >> k;
    out << invertBitAt(n, k) << std::endl;
}

void tests() {
    {
        std::stringstream in;
        std::stringstream out;
        
        int n = 0b10110;
        int k = 3;
        in << n << ' ' << k;
        run(in, out);
        assert(out.str() == "30\n");
    }
    {
        std::stringstream in;
        std::stringstream out;
        
        int n = 0b10110;
        int k = 2;
        in << n << ' ' << k;
        run(in, out);
        assert(out.str() == "18\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        int n = 0b1;
        int k = 0;
        in << n << ' ' << k;
        run(in, out);
        assert(out.str() == "0\n");
    }
    {
        std::stringstream in;
        std::stringstream out;
        
        unsigned int n = UINT32_MAX;
        int k = 31;
        in << n << ' ' << k;
        run(in, out);
        assert(out.str() == "2147483647\n");
    }
    std::cout << "All tests have been passed" << std::endl;
}

int main() {
    // tests();
    run(std::cin, std::cout);
    return 0;
}
