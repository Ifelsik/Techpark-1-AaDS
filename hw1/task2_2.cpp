// Дан массив целых чисел А[0..n-1].
// Известно, что на интервале [0, m] значения массива строго возрастают,
// а на интервале [m, n-1] строго убывают.
// Найти m за O(log m).
#include <assert.h>

#include <iostream>
#include <sstream>

int getExtremumIndex(int array[], int size) {
    int left = 0, right = size - 1;

    // O(log(m))
    for (int i = 1; i < size; i *= 2) { 
        if (array[i / 2] > array[i]) {
            left = i / 2;
            right = i;
            break;
        }
    }

    // founded range: 2^h - 2^(h-1)
	// where h <= log(m) + 1
	// so range length is m
    while (left < right) {
        int mid = (left + right) / 2;
        if ((mid > 0 && mid < size - 1) 
            && array[mid - 1] < array[mid] && array[mid] < array[mid + 1]) {
            left = mid + 1;
        }
        else {
            right = mid;
        }
    }

    return left;
}

void run(std::istream& in, std::ostream& out) {
    int n = 0;
    in >> n;

    int* array = new int[n];

    for (int i = 0; i < n; i++) {
        in >> array[i];
    }
    out << getExtremumIndex(array, n) << std::endl;

    delete[] array;
}

void test() {
    {
        std::stringstream in;
        std::stringstream out;

        in << "10\n";
        in << "1 2 3 4 5 6 7 6 5 4\n";

        run(in, out);
        assert(out.str() == "6\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "2\n";
        in << "1 2\n";
        run(in, out);
        assert(out.str() == "1\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "2\n";
        in << "2 1\n";
        run(in, out);
        assert(out.str() == "0\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "3\n";
        in << "1 2 3\n";
        run(in, out);
        assert(out.str() == "2\n");
    }
    std::cout << "Tests: OK" << std::endl;
}

int main() {
    test();
    //run(std::cin, std::cout);
    return 0;
}