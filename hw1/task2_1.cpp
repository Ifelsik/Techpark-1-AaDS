// Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1].
// Для каждого элемента массива B[i] найдите минимальный индекс k минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i].
// Если такого элемента нет, выведите n. n, m ≤ 10000.
// Требования:  Время работы поиска k для каждого элемента B[i]: O(log(k)).
// Внимание! В этой задаче для каждого B[i] сначала нужно определить диапазон для бинарного поиска размером порядка k с помощью экспоненциального поиска, а потом уже в нем делать бинарный поиск.
// Формат входных данных.
// В первой строчке записаны числа n и m. Во второй и третьей массивы A и B соответственно.
#include <iostream>
#include <sstream>
#include <assert.h>


int getIndex(int *array, int size, int value) {
    int left = 0, right = size;

    for (int i = 1; i < size; i *= 2) {
        if (array[i] >= value) {
            left = i / 2;
            right = i;
            break;
        }
    }

    while (left < right) {
        int mid = (right + left) / 2;
        if (array[mid] < value) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

void run(std::istream& in, std::ostream& out) {
    int n = 0, m = 0;
    in >> n >> m;
    
    int *arrayA = new int[n];
    for (int i = 0; i < n; i++) {
        in >> arrayA[i];
    }

    int *arrayB = new int[m];
    for (int i = 0; i < m; i++) {
        in >> arrayB[i];
    }

    for (int i = 0; i < m; i++) {
        out << getIndex(arrayA, n, arrayB[i]) << ' ';
    }
    out << std::endl;

    delete[] arrayA, arrayB;
} 

void test() {
    {
        std::stringstream in;
        std::stringstream out;

        in << "3 1\n";
        in << "1 2 3\n";
        in << "2";
        run(in, out);
        assert(out.str() == "1 \n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "9 1\n";
        in << "1 2 3 4 6 6 7 8 9\n";
        in << "5";
        run(in, out);
        assert(out.str() == "4 \n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "9 3\n";
        in << "3 4 5 7 7 7 8 9 10\n";
        in << "2 7 11\n";
        run(in, out);
        assert(out.str() == "0 3 9 \n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "1 1\n";
        in << "3 \n";
        in << "5 \n";
        run(in, out);
        assert(out.str() == "1 \n");
    }
    std::cout << "All tests have been passed" << std::endl;
}

int main() {
    //test();
    run(std::cin, std::cout);
    return 0;
}
