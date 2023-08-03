#ifndef SHARED_PTR_SHAREDPTR_H
#define SHARED_PTR_SHAREDPTR_H

#include <iostream>
#include <atomic>

template<typename T>
class [[maybe_unused]] SharedPtr {
private:
    T *ptr_;
    std::atomic_uint cnt_;
public:
    // Constructor
    explicit SharedPtr(T * = nullptr);

    // Copy
    SharedPtr(SharedPtr &);

    // Copy const
    SharedPtr(const SharedPtr &);

    // Destructor
    ~SharedPtr() = default;

    // Overloading =
    SharedPtr &operator=(SharedPtr<T>);

    // Overloading = const
    SharedPtr &operator=(const SharedPtr<T> &);

    // Overloading bool
    explicit operator bool() const;

    // Overloading *
    T &operator*() const;

    // Overloading ->
    T *operator->() const;

    // Method get()
    [[maybe_unused]] T *get();

    // Method reset()
    [[maybe_unused]] void reset();

    // Method reset(T* ptr)
    [[maybe_unused]] void reset(T *);

    // Method swap
    [[maybe_unused]] void swap(SharedPtr &);

    // Method use_count
    [[maybe_unused]] [[nodiscard]] size_t use_count() const;
};

#define qwerty template <class T> [[maybe_unused]]

// Constructor
qwerty SharedPtr<T>::SharedPtr(T *ptr) : ptr_(ptr), cnt_(1) {}

// Copy
qwerty SharedPtr<T>::SharedPtr(SharedPtr &obj) {
    ptr_ = obj.ptr_;
    cnt_ = cnt_ + obj.cnt_;
    obj.cnt_ = cnt_;
}

// Copy const
qwerty SharedPtr<T>::SharedPtr(const SharedPtr &obj) {
    ptr_ = obj.ptr_;
    cnt_ = cnt_ + obj.cnt_;
    obj.cnt_ = cnt_;
}

// Overloading =
qwerty SharedPtr<T> &SharedPtr<T>::operator=(SharedPtr<T> obj) {
    ptr_ = obj.ptr_;
    cnt_ = cnt_ + obj.cnt_;
    obj.cnt_ = cnt_;
    return *this;
}

// Overloading = const
qwerty SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &obj) {
    if (this == obj) {
        return *this;
    }
    ptr_ = obj.ptr_;
    cnt_ = cnt_ + obj.cnt_;
    obj.cnt_ = cnt_;
    return *this;
}

// Overloading bool
qwerty SharedPtr<T>::operator bool() const {
    return ptr_ != nullptr;
}

// Overloading *
qwerty T &SharedPtr<T>::operator*() const {
    return *ptr_;
}

// Overloading ->
qwerty T *SharedPtr<T>::operator->() const {
    return ptr_;
}

// Method get()
qwerty T *SharedPtr<T>::get() {
    return ptr_;
}

// Method reset()
qwerty void SharedPtr<T>::reset() {
    ptr_ = nullptr;
    cnt_ = 0;
    ~SharedPtr();
}

// Method reset(T* ptr)
qwerty void SharedPtr<T>::reset(T *ptr) {
    ptr_ = ptr;
    cnt_ = 1;
}

// Method swap
qwerty void SharedPtr<T>::swap(SharedPtr &obj) {
    T *ptr1_ = ptr_;
    unsigned int cnt1_ = cnt_;
    ptr_ = obj.ptr_;
    cnt_ = obj.cnt_;
    obj.ptr_ = ptr1_;
    obj.cnt_ = cnt1_;
}

// Method use_count
qwerty size_t SharedPtr<T>::use_count() const {
    return cnt_;
}

#endif //SHARED_PTR_SHAREDPTR_H
