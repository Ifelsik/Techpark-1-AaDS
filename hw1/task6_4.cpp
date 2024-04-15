// Дано множество целых чисел из [0..109] размера n.

// Используя алгоритм поиска k-ой порядковой статистики,
// требуется найти следующие параметры множества:

//     10% перцентиль
//     медиана
//     90% перцентиль

// Требования:

//     К дополнительной памяти: O(n).
//     Среднее время работы: O(n)
//     Должна быть отдельно выделенная функция partition.
//     Рекурсия запрещена.
//     Решение должно поддерживать передачу функции сравнения снаружи.

#include <iostream>
#include <random>

std::mt19937 gen(std::random_device {}());

int getRandom(int start, int end) {
    std::uniform_int_distribution<> dis(start, end);
    return dis(gen);
}

template <typename T>
struct DefaultComparator{
    bool operator() (const T &l, const T &r) {
        return l < r;
    }
};

template <typename T, typename Comparator = DefaultComparator<T>>
int partition(T *arr, int l, int r, Comparator comp = Comparator()) {
    int pivot_index = getRandom(l, r - 1);

    std::swap(arr[pivot_index], arr[r - 1]);
    T& pivot = arr[r - 1];

    int i = r - 2;
    int j = r - 2;

    while (j >= l) {
        if (j >= l && !comp(arr[j], pivot)) {  // arr[j] >= pivot
            std::swap(arr[j], arr[i]);
            i--;
        }
        j--;
    }
    std::swap(arr[i + 1], pivot);
    return i + 1;
}

template <typename T, typename Compartator = DefaultComparator<T>>
int KStat(T *arr, int size, int k, Compartator comp = Compartator()) {
    int l = 0;
    int r = size;

    while (l < r) {  // l <= r may cause segfault
        int m = partition(arr, l, r);
        if (k == m) {
            return arr[k];
        } else if (k < m) {
            r = m;
        } else {  // k > m
            l = m + 1;
        }
    }

}

int main() {
    std::ios_base::sync_with_stdio(false);  // io optimization))
    std::cin.tie(NULL);
    std::cout.tie(NULL);


    int n = 0;
    std::cin >> n;

    int *arr = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> arr[i];
    }

    int percentile_10 = static_cast<int> (0.1 * n);
    int median = n / 2;
    int percentile_90 = static_cast<int> (0.9 * n);

    std::cout << KStat(arr, n, percentile_10) << '\n';
    std::cout << KStat(arr, n, median) << '\n';
    std::cout << KStat(arr, n, percentile_90) << std::endl;

    delete[] arr;
    return 0;
}
