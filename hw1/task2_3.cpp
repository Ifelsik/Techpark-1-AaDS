// Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
// A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение.
// Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в массиве A.
// В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска элемента B[i-1]. n, k ≤ 10000. 

#include <assert.h>

#include <iostream>
#include <sstream>

int getIndex(int array[], int size, int start_position, int value) {
    int left = start_position;
    int right = size - 1;

    for (int i = 1; i < size; i *= 2) {
        if (array[i] > value) {
            left = i / 2;
            right = i;
            break;
        }
    }

    while (left < right) {
        int mid = (left + right) / 2;
        if (array[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return (left == size) || (array[left] != value) ? -1 : left;
}

void run(std::istream& in, std::ostream& out) {
    int n = 0, m = 0;

    in >> n >> m;

    int *arrayA = new int[n];
    int *arrayB = new int[m];

    for (int i = 0; i < n; i++) {
        in >> arrayA[i];
    }

    int position = 0;
    for (int i = 0; i < m; i++) {
        in >> arrayB[i];
        int prev = position;
        position = getIndex(arrayA, n, position, arrayB[i]);
        if (position != -1) {
            out << arrayA[position] << ' ';
        } else {
            position = prev;
        }
    }
    out << std::endl;

    delete[] arrayA, arrayB;
}

void test() {
    {
        std::stringstream in;
        std::stringstream out;

        in << "5\n";
        in << "3\n";
        in << "1 2 3 4 5\n";
        in << "1 3 5\n";

        run(in, out);
        assert(out.str() == "1 3 5 \n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "5\n";
        in << "3\n";
        in << "1 2 3 5 6\n";
        in << "0 4 7\n";

        run(in, out);
        assert(out.str() == "\n");
    }
    std::cout << "Tests: OK" << std::endl;
}

int main() {
    // test();
    run(std::cin, std::cout);
    return 0;
}
