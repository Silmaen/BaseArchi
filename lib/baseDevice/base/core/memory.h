/**
 * @file memory.h
 * @author argawaen
 * @date 13/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include <cstdint>

/**
 * @brief Namespace for core elements
 */
namespace sys::base::core {

/**
 * @brief Basic Custom implementation of Shared ptr
 * @tparam T The internal data's type
 *
 * @note The copy's maximum number is 255 for memory convenience.
 */
template<typename T>
class SharedPtr {
public:
    /// Destructor
    ~SharedPtr() { cleanup(); }
    /// Default constructor
    SharedPtr() :
        ptr(nullptr), refCount(new uint8_t(0)) {}

    /**
     * @brief Constructor pointer-based
     * @param rawPtr Initial pointer
     * @param ctr Pointer to the counter
     */
    explicit SharedPtr(T* rawPtr, uint8_t* ctr=nullptr) :
        ptr(rawPtr), refCount(ctr) {
        if (refCount==nullptr)
            refCount = new uint8_t(0);
        if (ptr!= nullptr)
            (*refCount)++;
    }

    /**
     * @brief Copy constructor
     * @param obj Pointer to copy
     */
    SharedPtr(const SharedPtr& obj) :
        ptr(obj.ptr), refCount(obj.refCount) {
        if (obj.ptr != nullptr) {
            (*refCount)++;
        }
    }
    /**
     * @brief Copy assignment
     * @param obj Pointer to copy
     * @return This
     */
    SharedPtr& operator=(const SharedPtr& obj) {
        //  self-assignment
        if (&obj == this) return *this;
        ptr      = obj.ptr;     // share the underlying pointer
        refCount = obj.refCount;// share refCount
        if (nullptr != obj.ptr) {
            // if the pointer is not null, increment the refCount
            (*this->refCount)++;
        }
        return *this;
    }

    /**
     * @brief Move constructor
     * @param dyingObj Origin object
     */
    SharedPtr(SharedPtr&& dyingObj) noexcept :
        ptr(dyingObj.ptr), refCount(dyingObj.refCount) {
        dyingObj.ptr = nullptr;
        dyingObj.refCount = nullptr;
    }

    /**
     * @brief Move assignment
     * @param dyingObj Origin object
     * @return This
     */
    SharedPtr& operator=(SharedPtr&& dyingObj) noexcept {
        ptr          = dyingObj.ptr;
        refCount     = dyingObj.refCount;
        dyingObj.ptr = nullptr;
        dyingObj.refCount = nullptr;
        return *this;
    }

    /**
     * @brief Cast to a new pointer type
     * @tparam NewType The destination's type
     * @return Pointer to this object with the right type
     */
    template <typename NewType>
    SharedPtr<NewType> cast() const{
        return SharedPtr<NewType>((NewType*)(ptr), refCount);
    }

    /**
     * @brief Access operator
     * @return Data pointer
     */
    T* operator->() const { return ptr; }
    /**
     * @brief Access operator
     * @return Data reference
     */
    T& operator*() const { return *ptr; }
    /**
     * @brief Get usage count
     * @return usage count
     */
    [[nodiscard]] uint8_t getCount() const { return *refCount; }
    /**
     * @brief Get data pointer
     * @return Data pointer
     */
    T* get() const { return ptr; }

    /**
     * @brief Comparison Operator
     * @param other Other object to compare
     * @return True if data points to the same object
     */
    bool operator==(const SharedPtr& other)const{return other.ptr == ptr;}

    /**
     * @brief Comparison Operator
     * @param other Other object to compare
     * @return True if data points to the same object
     */
    bool operator==(T* other)const{return other == ptr;}
    /**
     * @brief Comparison Operator
     * @param other Other object to compare
     * @return True if data points to another object
     */
    bool operator!=(const SharedPtr& other)const{return other.ptr != ptr;}
    /**
     * @brief Comparison Operator
     * @param other Other object to compare
     * @return True if data points to another object
     */
    bool operator!=(T* other)const{return other != ptr;}
private:
    /// Shared pointer
    T* ptr;
    /// Reference counter
    uint8_t* refCount;

    /**
     * @brief do pointer cleanup
     */
    void cleanup() {
        if (refCount == nullptr) {
            delete ptr;
            return;
        }
        if ((*refCount)>0)
            (*refCount)--;
        if (*refCount == 0) {
            delete ptr;
            delete refCount;
        }
    }
};

}// namespace sys::base::core