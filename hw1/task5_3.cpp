// Во всех задачах данного раздела необходимо реализовать и
// использовать сортировку слиянием в виде шаблонной функции.
// Решение должно поддерживать передачу функции сравнения снаружи.
// Общее время работы алгоритма O(n log n).
// 5_3. Закраска прямой 1.
// На числовой прямой окрасили N отрезков.
// Известны координаты левого и правого концов каждого отрезка (Li и Ri).
// Найти длину окрашенной части числовой прямой.
#include <assert.h>

#include <iostream>
#include <sstream>

template <typename T, typename Compare>
void merge(T array[], Compare comparator, int left_size, int right_size) {
    auto* temp = new T[left_size + right_size];
    int temp_position = 0;
    int i = 0, j = 0;
    while (i < left_size && j < right_size) {
        if (comparator(array[left_size + j], array[i])) {
            temp[temp_position++] = array[i++];
        } else {
            temp[temp_position++] = array[left_size + j++];
        }
    }
    if (i == left_size) {
        while (j < right_size) {
            temp[temp_position++] = array[left_size + j++];
        }
    } else {
       while (i < left_size) {
            temp[temp_position++] = array[i++];
        }
    }

    std::copy(temp, temp + (right_size + left_size), array);
    delete[] temp;
}


// max recursion depth <= 14 (when N <= 10 000)
template <typename T, typename Compare>
void mergeSort(T array[], Compare comparator, int size) {
    if (size <= 1) {
        return;
    }
    int left_size = size / 2;
    int right_size = size - left_size;
    mergeSort(array, comparator, left_size);
    mergeSort(array + left_size, comparator, right_size);
    merge(array, comparator, left_size, right_size);
}

// define your own comparator
bool comparator(const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return a.first > b.first;
}

int getLengthOfPaintedPart(std::pair<int, int> array[], int size) {
    mergeSort(array, comparator, size);

    int length = 0;
    int i = 0, j = 0;
    while (i < size) {
        int min_index_of_intersection = j;
        int max_index_of_intersection = j;
        while (i < size && array[i].first < array[j].second) {
            if (array[i].second > array[j].second) {
                max_index_of_intersection = i;
                j = i;
            }
            i++;
        }
        length += (array[max_index_of_intersection].second -
                   array[min_index_of_intersection].first);
        j = i;
    }
    return length;
}

void run(std::istream& in, std::ostream& out) {
    int n = 0;
    in >> n;

    auto* array = new std::pair<int, int>[n];
    for (int i = 0; i < n; i++) {
        in >> array[i].first >> array[i].second;
    }
    out << getLengthOfPaintedPart(array,  n) << std::endl;
    delete[] array;
}

void test() {
    {
        std::stringstream in;
        std::stringstream out;

        in << "4\n";
        in << "5 9\n";
        in << "2 10\n";
        in << "1 12\n";
        in << "6 8\n";

        run(in, out);
        assert(out.str() == "11\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "4\n";
        in << "11 12\n";
        in << "5 7\n";
        in << "1 5\n";
        in << "8 10\n";

        run(in, out);
        assert(out.str() == "9\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "3\n";
        in << "1 12\n";
        in << "6 11\n";
        in << "2 10\n";

        run(in, out);
        assert(out.str() == "11\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "3\n";
        in << "2 5\n";
        in << "1 3\n";
        in << "4 6\n";

        run(in, out);
        assert(out.str() == "5\n");
    }
    std::cout << "Tests: OK!" << std::endl;
}

int main() {
    // test();
    run(std::cin, std::cout);
    return 0;
}
