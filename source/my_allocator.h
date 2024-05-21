#pragma once
#include <memory>
#include <stdexcept>
#include <iostream>

struct deleter
{
    void operator()(void* ptr)
    {
        ::operator delete(ptr);
    }
};

/*!
* @brief std::map in the MSVC_19.39 creates 2 AssocioPoolAllocator
*    and requires 2 bloks of a memory when a container is created.
*    If you need 10 elements in the container,  std::map will require
*    12 allocations.
*    AllocatorCounter is common counter for different allocators of the same
*    container.
*/
struct AllocatorCounter
{
    size_t allocated_size_ = 0;
};


////////////////////////////////////////////////////////////////////////////////
// class AssocioPoolAllocator
////////////////////////////////////////////////////////////////////////////////
template <class T, size_t size = 20>
class AssocioPoolAllocator
{
public:
    using value_type = T;

    AssocioPoolAllocator();
    template <class U>
    AssocioPoolAllocator(const AssocioPoolAllocator<U, size>&) noexcept;
    AssocioPoolAllocator& operator=(AssocioPoolAllocator&&) noexcept;
    ~AssocioPoolAllocator() = default;

    template <class U>
    struct rebind {
        using other = AssocioPoolAllocator<U, size>;
    };

    T* allocate(size_t);
    void deallocate(T*, size_t);

    using propagate_on_container_copy_assignment = std::true_type;
    using propagate_on_container_move_assignment = std::true_type;
    using propagate_on_container_swap = std::true_type;

private:
    friend class AssocioPoolAllocator;

    size_t& GetAllocatedSize() const;

    size_t pool_size_;
    const std::shared_ptr<void> pool_;
    const std::shared_ptr<AllocatorCounter> counter_;
};

#include "my_allocator.ipp"

