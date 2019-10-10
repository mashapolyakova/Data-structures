#pragma once

class Vector {
public:
    Vector() {
        capacity_ = 0;
        size_ = 0;
        data_ = new int[capacity_];
    }
    Vector(size_t size) {
        size_ = size;
        capacity_ = size_;
        data_ = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = 0;
        }
    }
    Vector(std::initializer_list<int> list) {
        capacity_ = list.size();
        data_ = new int[capacity_];
        size_ = list.size();
        size_t i = 0;
        for (int cur : list) {
            data_[i++] = cur;
        }
    }
    Vector(Vector&& rhs) {
        data_ = rhs.data_;
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        rhs.data_ = nullptr;
    }
    Vector(const Vector& rhs) {
        data_ = new int[rhs.size_];
        for (size_t i = 0; i < rhs.size_; ++i) {
            data_[i] = rhs.data_[i];
        }
        capacity_ = rhs.capacity_;
        size_ = rhs.size_;
    }
    void Swap(Vector& rhs) {
        std::swap(data_, rhs.data_);
        std::swap(size_, rhs.size_);
        std::swap(capacity_, rhs.capacity_);
    }
    Vector& operator=(Vector rhs) {
        Swap(rhs);
        return *this;
    }
    ~Vector() {
        delete[] data_;
    }
    int& operator[](size_t index) {
        return data_[index];
    }
    const int operator[](size_t index) const {
        return data_[index];
    }
    const size_t Size() const {
        return size_;
    }
    const int Capacity() const {
        return capacity_;
    }
    void PushBack(int elem) {
        if (size_ < capacity_) {
            data_[size_] = elem;
            ++size_;
            return;
        }
        int capacity = 0;
        if (!capacity_) {
            capacity = 1;
        } else {
            capacity = 2 * capacity_;
        }
        int* tmp = new int[capacity];
        for (size_t i = 0; i < size_; ++i) {
            tmp[i] = data_[i];
        }
        tmp[size_] = elem;
        std::swap(data_, tmp);
        capacity_ = capacity;
        ++size_;
        delete[] tmp;
    }
    int PopBack() {
        --size_;
        int res = data_[size_];
        data_[size_] = 0;
        return res;
    }
    void Clear() {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = 0;
        }
        size_ = 0;
    }
    void Reserve(int capacity) {
        if (capacity <= capacity_) {
            return;
        }
        capacity_ = capacity;
        int* data = new int[capacity_];
        for (size_t i = 0; i < size_; ++i) {
            data[i] = data_[i];
        }
        std::swap(data, data_);
        delete[] data;
    }
    class Iterator : public std::iterator<std::forward_iterator_tag, int> {
    public:
        Iterator() {
        }
        Iterator(int* current) {
            current_ = current;
        }

        Iterator& operator++() {
            ++current_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator cpy(*this);
            ++current_;
            return cpy;
        }
        Iterator& operator--() {
            --current_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator cpy(*this);
            --current_;
            return cpy;
        }
        Iterator& operator+=(int n) {
            while (n > 0) {
                ++current_;
                --n;
            }
            while (n < 0) {
                --current_;
                ++n;
            }
            return *this;
        }
        Iterator& operator-=(int n) {
            while (n > 0) {
                --current_;
                --n;
            }
            while (n < 0) {
                ++current_;
                ++n;
            }
            return *this;
        }
        Iterator operator+(int n) {
            auto tmp = *this;
            return tmp += n;
        }
        Iterator operator-(int n) {
            auto tmp = *this;
            return tmp -= n;
        }
        int operator-(const Iterator rhs) {
            return current_ - rhs.current_;
        }
        bool operator==(const Iterator& rhs) const {
            return current_ == rhs.current_;
        }

        bool operator!=(const Iterator& rhs) const {
            return !(*this == rhs);
        }

        int& operator*() {
            return *current_;
        }

        int* operator->() {
            return current_;
        }

    private:
        int* current_;
    };
    Iterator begin() {  // NOLINT
        return Iterator(data_);
    }

    Iterator end() {  // NOLINT
        return Iterator(data_ + size_);
    }
    Iterator Begin() {
        return Iterator(data_);
    }

    Iterator End() {
        return Iterator(data_ + size_);
    }

private:
    int* data_;
    int capacity_;
    size_t size_;
};
