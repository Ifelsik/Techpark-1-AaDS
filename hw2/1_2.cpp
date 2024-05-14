#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>
#include <string>
#include <cassert>

const size_t DEFAULT_SIZE = 8;

enum class Status {REC, NIL, DEL};

struct HashTableNode {
    Status status;
    std::string key;

    HashTableNode()
    : status(Status::NIL), key("") {}

    HashTableNode(const std::string &str)
    : status(Status::REC), key(str) {}
};

class StringHasher {
public:
    explicit StringHasher(size_t prime = 89)
        : prime(prime) {}

    size_t operator() (const std::string &str) {
        size_t hash = 0;
        for (size_t i = 0; i < str.size(); i++) {
            hash = hash * prime + str[i];
        }
        return hash;
    }

private:
    size_t prime;
};


template <typename Hasher>
class HashTable {
public:
    explicit HashTable(size_t seed1, size_t seed2, size_t init_size = DEFAULT_SIZE)
    : table(init_size, HashTableNode()), size(0) {
        hasher1 = Hasher(seed1);
        hasher2 = Hasher(seed2);
    }


    bool add(const std::string &key) {
        if (static_cast<float>(size) / table.size() >= 0.75) {
            resize();
        }

        size_t hash1 = hasher1(key);
        size_t hash2 = 2 * hasher2(key) + 1;
        size_t hash = 0;
        int first_del_pos = -1;  // using int instead of size_t

        for (size_t i = 0; i < table.size(); i++) {
            hash = (hash1 + hash2 * i) % table.size();
            if (table[hash].key == key) {
                return false;
            }
            if (first_del_pos < 0 && table[hash].status == Status::DEL) {
                first_del_pos = hash;
            }
            if (table[hash].status == Status::NIL) {
                break;
            }
        }

        if (first_del_pos >= 0 && (hash > first_del_pos || table[hash].status == Status::REC)) {
            hash = first_del_pos;
        }

        table[hash] = HashTableNode(key);
        size++;

        return true;
    }

    bool has(const std::string &key) {
        size_t hash1 = hasher1(key);
        size_t hash2 = 2 * hasher2(key) + 1;

        for (size_t i = 0; i < table.size(); i++) {
            size_t hash = (hash1 + hash2 * i) % table.size();
            if (table[hash].key == key) {
                return true;
            }
            if (table[hash].status == Status::NIL) {
                return false;
            }
        }

        return false;
    }

    bool del(const std::string &key) {
        size_t hash1 = hasher1(key);
        size_t hash2 = 2 * hasher2(key) + 1;

        for (size_t i = 0; i < table.size(); i++) {
            size_t hash = (hash1 + hash2 * i) % table.size();
            if (table[hash].key == key) {
                table[hash].status = Status::DEL;
                table[hash].key = "";
                size--;
                return true;
            }
            if (table[hash].status == Status::NIL) {
                return false;
            }
        }

        return false;
    }
private:
    void resize() {
        std::vector<HashTableNode> new_table(2 * table.size(), HashTableNode());

        for (HashTableNode &node : table) {
            if (node.status != Status::REC) {
                continue;
            }
            size_t hash1 = hasher1(node.key);
            size_t hash2 = 2 * hasher2(node.key) + 1;
            for (size_t i = 0; i < new_table.size(); i++) {
                size_t hash = (hash1 + hash2 * i) % new_table.size();
                if (new_table[hash].status == Status::NIL) {
                    new_table[hash] = node;
                    break;
                }
            }
        }
        table = new_table;
    }
    std::vector<HashTableNode> table;
    size_t size;
    Hasher hasher1;
    Hasher hasher2;
};

void run(std::istream &in, std::ostream &out) {
    HashTable<StringHasher> set(149, 101);

    char opt = 0;
    while (in >> opt) {
        std::string str;
        in >> str;

        switch (opt) {
        case '+':
            if (set.add(str)) {
                out << "OK\n";
                break;
            }
            out << "FAIL\n";
            break;
        case '?':
            if (set.has(str)) {
                out << "OK\n";
                break;
            }
            out << "FAIL\n";
            break;
        case '-':
            if (set.del(str)) {
                out << "OK\n";
                break;
            }
            out << "FAIL\n";
            break;
        default:
            break;
        }
    }
}

void test() {
    // Тест 1: Добавление пустой строки
    {
        std::stringstream in;
        std::stringstream out;
        std::stringstream expected;

        in << "+ \n";\
        expected << "FAIL\n";

        run(in, out);
        assert(expected.str() == out.str());
    }

    // Тест 2: Добавление строки, превышающей максимальную длину
    {
        std::stringstream in;
        std::stringstream out;
        std::stringstream expected;

        std::string long_string(256, 'a');  // Строка длиной 256 символов
        in << "+ " << long_string << "\n";
        in << "- " << long_string << "\n";
        expected << "OK\n";
        expected << "OK\n";

        run(in, out);
        assert(expected.str() == out.str());
    }

    // Тест 3: Удаление несуществующей строки
    {
        std::stringstream in;
        std::stringstream out;
        std::stringstream expected;

        in << "- non-existent-string\n";
        expected << "FAIL\n";

        run(in, out);
        assert(expected.str() == out.str());
    }

    // Тест 4: Переполнение хеш-таблицы
    {
        std::ifstream in;
        in.open("1_007.input");
        std::ifstream exp;
        exp.open("1_007.a");
        std::stringstream expected;
        expected << exp.rdbuf();
        std::stringstream out;

        run(in, out);

        assert(out.str() == expected.str());

    
    }
    // Тест 5: ???
    {
        std::stringstream in;
        std::stringstream out;
        std::stringstream expected;

        std::string str1 = "abcdefghij";
        std::string str2 = "fgjdfjdfyj";
        for (int i = 0; i < 300; i++) {
            for (int j = 0; j < 24; j++) {
                in << "+ " << str1 << i << str2 << j << "\n";
                expected << "OK\n";
                if (j > 12) {
                    in << "- " << str1 << i << str2 << j << "\n";
                    expected << "OK\n";
                }
            }
        }

        for (int i = 0; i < 300; i++) {
            for (int j = 8; j < 16; j++) {
                if (j <= 12) {
                    in << "? " << str1 << i << str2 << j << "\n";
                    expected << "OK\n";
                } else {
                    in << "? " << str1 << i << str2 << j << "\n";
                    expected << "FAIL\n";
                }
            }
        }

        for (int i = 0; i < 300; i++) {
            for (int j = 8; j < 16; j++) {
                if (j <= 12) {
                    in << "+ " << str1 << i << str2 << j << "\n";
                    expected << "FAIL\n";
                } else {
                    in << "+ " << str1 << i << str2 << j << "\n";
                    expected << "OK\n";
                }
            }
        }

        for (int i = 0; i < 300; i++) {
            for (int j = 0; j < 16; j++) {
                in << "? " << str1 << i << str2 << j << "\n";
                expected << "OK\n";
            }
        }

        run(in, out);
        assert(expected.str() == out.str());
    }
    std::cout << "OK!" << std::endl;
}

int main() {
    // test();
    run(std::cin, std::cout);
    return 0;
}
