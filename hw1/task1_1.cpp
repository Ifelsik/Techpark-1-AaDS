
//  Подсчитать кол-во единичных бит в входном числе , стоящих на четных позициях. Позиции битов нумеруются с 0.
// in   25
// out  2


#include <assert.h>
#include <iostream>
#include <sstream>

int numberOfEvenBits(unsigned int n) {
    int count = 0;
    while (n > 0) {
        count += (n & 1);
        n >>= 2;
    }
    return count;
}

void run(std::istream& in, std::ostream& out) {
    int n = 0;
    in >> n;
    out << numberOfEvenBits(n) << std::endl;
}

void tests() {
    {
        std::stringstream in;
        std::stringstream out;

        in << "3\n";
        run(in, out);
        assert(out.str() == "1\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        int val = 0b1010;
        in << val;
        run(in, out);
        assert(out.str() == "0\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        int val = 0b0;
        in << val;
        run(in, out);
        assert(out.str() == "0\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        int val = 0b10110;
        in << val;
        run(in, out);
        assert(out.str() == "2\n");
    }
    {
        std::stringstream in;
        std::stringstream out;
        
        unsigned int val = UINT32_MAX;
        in << val;
        run(in, out);
        assert(out.str() == "16\n");
    }
    std::cout << "All tests have passed" << std::endl;
}

int main() {
    tests();
    run(std::cin, std::cout);
    return 0;
}
