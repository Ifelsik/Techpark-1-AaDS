// Реализовать очередь с помощью двух стеков.
// Требования: Очередь должна быть реализована в виде класса. Стек тоже должен быть реализован в виде класса.
#include <assert.h>

#include <iostream>
#include <sstream>

class Stack {
public:
    Stack() : buffer_size(BASE_SIZE), top(-1)
        {
            buffer = new int[buffer_size];
        }


    Stack(int _buffer_size) : buffer_size(_buffer_size), top(-1)
    {
        buffer = new int[buffer_size]; 
    }

    ~Stack() {
        delete[] buffer;
    }

    Stack(const Stack& other) : buffer_size(other.buffer_size), top(other.top) {
        buffer = new int[buffer_size];
        for (int i = 0; i <= top; i++) {
            buffer[i] = other.buffer[i];
        }
    }

    Stack& operator = (const Stack& other) {
        this->buffer_size = other.buffer_size;
        this->top = other.top;
        buffer = new int[buffer_size];
        for (int i = 0; i <= top; i++) {
            buffer[i] = other.buffer[i];
        }
        return *this;
    }

    bool is_empty() {
        if (top == -1) {
            return true;
        }
        return false;
    }

    void push(int element) {
        if (top >= buffer_size - 1) {
            buffer_size *= 2;

            int *temp = new int[buffer_size];
            for (int i = 0; i <= top; i++) {
                temp[i] = buffer[i];
            }

            delete[] buffer;
            buffer = temp;
        }

        buffer[++top] = element;
    }

    int pop() {
        return buffer[top--];
    }

private:
    const int BASE_SIZE = 256;

    int buffer_size;
    int top;
    int *buffer;
};


class Queue {
public:
    Queue() : left(Stack()), right(Stack()) {}

    bool is_empty() {
        return left.is_empty() && right.is_empty();
    }

    void push(int element) {
        left.push(element);
    };

    int pop() {
        if (is_empty()) { 
            return -1;
        }

        if (right.is_empty()) {
            while (!left.is_empty()) {
                right.push(left.pop());
            }
        }
        return right.pop();
    }

private:
    Stack left;
    Stack right;
};

void run(std::istream& in, std::ostream& out) {
    int n = 0;
    in >> n;

    Queue queue = Queue();
    int command = 0, value = 0;
    bool as_expected = true;

    while (n--) {
        in >> command >> value;
        switch (command)
        {
        case 2: // pop front
            as_expected = (queue.pop() == value);
            break;
        
        case 3: // push back
            queue.push(value);
            break;

        default:
            break;
        }
    }

    if (as_expected)
        out << "YES" << std::endl;
    else
        out << "NO" << std::endl;
}

void test() {
    {
        std::stringstream in;
        std::stringstream out;

        in << "3\n";
        in << "3 44\n";
        in << "3 50\n";
        in << "2 44\n";

        run(in, out);
        assert(out.str() == "YES\n");
    }
    {
        std::stringstream in;
        std::stringstream out;

        in << "2\n";   
        in << "2 -1\n";
        in << "3 10\n";

        run(in, out);
        assert(out.str() == "YES\n");
    }
        {
        std::stringstream in;
        std::stringstream out;

        in << "2\n";   
        in << "3 44\n";
        in << "2 66\n";

        run(in, out);
        assert(out.str() == "NO\n");
    }
    std::cout << "Test: OK" << std::endl;
}

int main() {
    //test();
    run(std::cin, std::cout);
    return 0;
}
