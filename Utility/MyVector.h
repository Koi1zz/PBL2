#ifndef MYVECTOR_H
#define MYVECTOR_H

template <typename T>
class MyVector {
private:
    // Cau truc mot node trong danh sach lien ket
    struct Node {
        T data;        // Du lieu cua node
        Node* next;    // Con tro toi node tiep theo

        // Khoi tao node
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;        // Con tro toi node dau
    Node* tail;        // Con tro toi node cuoi (de them nhanh)
    int length;        // So luong node

public:
    // Khoi tao danh sach rong
    MyVector() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    // Huy - giai phong tat ca node
    ~MyVector() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Copy constructor
    MyVector(const MyVector& other) {
        head = nullptr;
        tail = nullptr;
        length = 0;

        // Sao chep tung node
        Node* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    // Toan tu gan
    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            // Xoa du lieu cu
            Node* current = head;
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }

            // Reset
            head = nullptr;
            tail = nullptr;
            length = 0;

            // Copy moi
            current = other.head;
            while (current != nullptr) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Them phan tu vao cuoi danh sach
    void push_back(const T& value) {
        Node* nodeNew = new Node(value);

        // Neu danh sach rong
        if (head == nullptr) {
            head = nodeNew;
            tail = nodeNew;
        }
        // Neu da co phan tu
        else {
            tail->next = nodeNew;
            tail = nodeNew;
        }

        length++;
    }

    // Lay so phan tu
    int size() const {
        return length;
    }

    // Kiem tra rong
    bool empty() const {
        return (length == 0);
    }

    // Truy cap phan tu thu index (khong hieu qua nhu mang)
    T& operator[](int index) {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](int index) const {
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    // Xoa phan tu theo dieu kien
    template<typename Condition>
    void removeIf(Condition condition) {
        // Xu ly cac node dau neu thoa dieu kien xoa
        while (head != nullptr && condition(head->data)) {
            Node* temp = head;
            head = head->next;
            delete temp;
            length--;
        }

        // Neu da xoa het
        if (head == nullptr) {
            tail = nullptr;
            return;
        }

        // Xu ly cac node con lai
        Node* current = head;
        while (current->next != nullptr) {
            if (condition(current->next->data)) {
                // Xoa node tiep theo
                Node* temp = current->next;
                current->next = temp->next;

                // Neu xoa node cuoi
                if (temp == tail) {
                    tail = current;
                }

                delete temp;
                length--;
            } else {
                current = current->next;
            }
        }
    }

    // Xoa tat ca
    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    // Iterator de duyet (don gian)
    class Iterator {
    private:
        Node* currentNode;

    public:
        Iterator(Node* node) : currentNode(node) {}

        // Toan tu ++
        Iterator& operator++() {
            if (currentNode != nullptr) {
                currentNode = currentNode->next;
            }
            return *this;
        }

        // Toan tu *
        T& operator*() {
            return currentNode->data;
        }

        // Toan tu !=
        bool operator!=(const Iterator& other) const {
            return currentNode != other.currentNode;
        }
    };

    // Tra ve iterator dau
    Iterator begin() {
        return Iterator(head);
    }

    // Tra ve iterator cuoi
    Iterator end() {
        return Iterator(nullptr);
    }
};

#endif