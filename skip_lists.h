#ifndef SKIP_LISTS_H
#define SKIP_LISTS_H
#include <iostream>
#include <vector>
#include "DynamicArrayNew.h"
#include <random>
template <typename T>
struct Node {
    T key;
    std::vector<Node<T>*> array; //  вектор в котором мы храним указатель на соседние ноды на каждом уровне

    Node(int level, const T& key) : key(key), array(level + 1, nullptr) {}
};

std::mt19937 rng(std::random_device{}());
std::uniform_real_distribution<float> dist(0.0f, 1.0f);


template <typename T>
class SkipList {
private:
    const float P=0.5;
    const int MAX_LEVEL=16;
    int level = 0;
    Node<T>* header = new Node<T>(MAX_LEVEL, T());

    int randomLevel() {
        int lvl=0;
        while (dist(rng) < P && lvl < MAX_LEVEL) {
            lvl++;
        }
        return lvl;
    }


public:

    SkipList()
        : level(0),
          header(new Node<T>(MAX_LEVEL, T()))
    {}
    ~SkipList() {
        Node<T>* cur = header->array[0];
        while (cur) {
            Node<T>* tmp = cur->array[0];
            delete cur;
            cur = tmp;
        }
        delete header;
    }


    void buildFromArray(const DynamicArray<T>& array) {
        for (int i = 0; i < array.GetSize(); ++i) {
            insert(array.Get(i));
        }
    }


    void insert(const T& key) {

        std::vector<Node<T>*> update(MAX_LEVEL + 1, nullptr); // после какого узла мы должны вставить новый элемент.
        Node<T>* current = header;
        for (int i = level; i >= 0; --i) {
            while (current->array[i] && current->array[i]->key < key) {

                current = current->array[i];
            }
            update[i] = current;
        }
        current = current->array[0];
        if (current && current->key == key) {
            return;
        }

        int newLevel = randomLevel();

        if (newLevel > level) { // если у нас еще нет такого уровня по высоте то создаем
            for (int i = level + 1; i <= newLevel; ++i) {
                update[i] = header;
            }
            level = newLevel;
        }
        Node<T>* newNode = new Node<T>(newLevel, key);
        for (int i = 0; i <= newLevel; ++i) {
            newNode->array[i] = update[i]->array[i];
            update[i]->array[i] = newNode;
        }
    }

    bool find(const T& key) const {
        Node<T>* current = header;
        for (int i = level; i >= 0; --i) {
            while (current->array[i] && current->array[i]->key < key) {
                current = current->array[i];
            }
        }
        current = current->array[0];
        return (current && current->key == key);
    }

    void delete_elem(const T& key) {
        Node<T>* current = header;
        std::vector<Node<T>*> update(MAX_LEVEL + 1, nullptr);

        for (int i = level; i >= 0; --i) {
            while (current->array[i] && current->array[i]->key < key) {
                current = current->array[i];
            }
            update[i] = current;
        }
        current = current->array[0];
        if (current && current->key == key) {
            for (int i = 0; i <= level; ++i) {
                if (update[i]->array[i] == current) {
                    update[i]->array[i] = current->array[i];
                }
            }
            while (level > 0 && header->array[level] == nullptr) {
                level--;
            }
            delete current;
        }
    }

    void printLevels() const {
        for (int i = level; i >= 0; --i) {
            std::cout << "Level " << i << ": ";
            Node<T>* current = header->array[i];
            while (current) {
                std::cout << current->key << " ";
                current = current->array[i];
            }
            std::cout << "\n";
        }
    }
};

#endif //SKIP_LISTS_H
