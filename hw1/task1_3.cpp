
// Если в числе содержится только один бит со значением 1, записать в выходной поток OK. Иначе записать FAIL 

#include <iostream>
#include <assert.h>
#include <sstream>
#include <cstdint>

bool hasOnlyOneBit(unsigned int n) {
    bool has_bit_one = false;
    for (int i = 0; i < 32; i++) {
        if (n & 1) {
            if (has_bit_one) {
                return false;
            }
            has_bit_one = true;
        }
        n >>= 1;
    } 
    return has_bit_one;
}

void run(std::istream& in, std::ostream& out) {
    unsigned int n = 0;
    in >> n;
    if (hasOnlyOneBit(n)) {
        out << "OK";
    }
    else {
        out << "FAIL";
    }
    out << std::endl;
}

void tests() {
    {
        std::stringstream in;
        std::stringstream out;
        
        int n = 0b10110;
        in << n;
        run(in, out);
        assert(out.str() == "FAIL\n");
    }
    {
        std::stringstream in;
        std::stringstream out;
        
        int n = 0b1000;
        in << n;
        run(in, out);
        assert(out.str() == "OK\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        int n = 0b0;
        in << n;
        run(in, out);
        assert(out.str() == "FAIL\n");
    }
    {
        std::stringstream in;
        std::stringstream out;
        
        unsigned int n = 0b0001;
        in << n;
        run(in, out);
        assert(out.str() == "OK\n");
    }
     {
        std::stringstream in;
        std::stringstream out;
        
        unsigned int n = 0b1000000000000;
        in << n;
        run(in, out);
        assert(out.str() == "OK\n");
    }
    {
        std::stringstream in;
        std::stringstream out;
        
        unsigned int n = UINT32_MAX;
        in << n;
        run(in, out);
        assert(out.str() == "FAIL\n");
    }
    std::cout << "All tests have been passed" << std::endl;
}

int main() {
    //tests();
    run(std::cin, std::cout);
    return 0;
}
