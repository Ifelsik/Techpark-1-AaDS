// Имеется лог-файл, в котором хранятся пары для N пользователей (Идентификатор пользователя, посещаемость сайта).
// Напишите программу, которая выбирает K пользователей, которые чаще других заходили на сайт,
// и выводит их в порядке возрастания посещаемости.
// Количество заходов и идентификаторы пользователей не повторяются.
// Требования: время работы O(N * logK), где N - кол-во пользователей.
// Ограничение на размер кучи O(K).

#include <assert.h>

#include <iostream>
#include <sstream>

template <typename T>

class PriorityQueue {
private:
    const int BASE_SIZE = 256;

    int array_size;
    int current_position;
    std::pair<int, T> *array;

    bool (*comparator)(const std::pair<int, T> &a, const std::pair<int, T>& b);

    void sift_down(int i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        int largest = i;
        if (left <= current_position && comparator(array[left], array[largest]))
            largest = left;
        if (right <= current_position && comparator(array[right], array[largest]))
            largest = right;

        if (largest == i) {
            return;
        }

        std::swap(array[i], array[largest]);
        sift_down(largest);
    }

    void sift_up(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;

            if (!comparator(array[i], array[parent])) {  // comparator
                return;
            }

            std::swap(array[i], array[parent]);
            i = parent;
        }
    }

    void build_array() {
        for (int i = (current_position - 1) / 2; i >= 0; i--) {
            sift_down(i);
        }
    }

public:
    PriorityQueue(bool (*func_compare)(const std::pair<int, T> &a, const std::pair<int, T>& b))
    : array_size(BASE_SIZE), current_position(-1) {
        comparator = func_compare;
        array = new std::pair<int, T>[BASE_SIZE];
        // if (array == nullptr) {
        //     std::cout << "Allocation error\n";
        //     exit(EXIT_FAILURE);
        // }
    }

    ~PriorityQueue() {
        delete[] array;
    }

    PriorityQueue(const PriorityQueue& other) :
        array_size(other.array_size), current_position(other.current_position) {
        array = new std::pair<int, T>[other.array_size];

        // if (array == nullptr) {
        //     std::cout << "Allocation error\n";
        //     exit(EXIT_FAILURE);
        // }

        for (int i = 0; i <= other.current_position; i++) {
            array++ = other.array++;
        }
    }

    PriorityQueue& operator= (const PriorityQueue& other) {
        array_size = other.array_size;
        current_position = other.current_position;

        array = new std::pair<int, T>[other.array_size];

        // if (array == nullptr) {
        //     std::cout << "Allocation error\n";
        //     exit(EXIT_FAILURE);
        // }

        for (int i = 0; i <= other.current_position; i++) {
            *(array++) = *(other.array++);
        }

        return *this;
    }

    bool is_empty() {
        return (current_position >= 0);
    }

    void push(T element, int priority) {
        if (current_position >= array_size - 2) {
            array_size *= 2;
            std::pair<int, T>* temp = new std::pair<int, T>[array_size];
            for (int i = 0; i <= current_position; i++) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
        }

        array[++current_position] = {priority, element};
        sift_up(current_position);
    }

    T pop() {
        std::swap(array[current_position], array[0]);
        current_position--;
        sift_down(0);
        return array[current_position + 1].second;
    }
};

template <typename T>
bool comparator(const std::pair<int, T> &a,const std::pair<int, T>& b) {
    return a.first > b.first;
}

void run(std::istream &in, std::ostream &out) {
    int n = 0, k = 0;
    in >> n >> k;

    PriorityQueue<int> pq(comparator);
    for (int i = 0; i < n; i++) {
        int id = 0, traffic = 0;
        in >> id >> traffic;
        pq.push(id, traffic);
    }

    int *top = new int[k];
    for (int i = k - 1; i >= 0; i--) {
        top[i] = pq.pop();
    }
    for (int i = 0; i < k; i++) {
        out << top[i] << ' ';
    }
    delete[] top;
    out << std::endl;
}

void test() {
    {
        std::stringstream in;
        std::stringstream out;

        in << "3 3\n";
        in << "100 36\n";
        in << "80 3\n";
        in << "1 5\n";

        run(in, out);
        assert(out.str() == "80 1 100 \n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "5 5\n";
        in << "1 5\n";
        in << "2 3\n";
        in << "3 7\n";
        in << "4 9\n";
        in << "5 1\n";

        run(in, out);
        assert(out.str() == "5 2 1 3 4 \n");
    }
    std::cout << "Tests: OK!" << std::endl;
}

int main() {
    // test();
    run(std::cin, std::cout);
    return 0;
}
