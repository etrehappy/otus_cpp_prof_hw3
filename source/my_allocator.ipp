////////////////////////////////////////////////////////////////////////////////
// class AssocioPoolAllocator
////////////////////////////////////////////////////////////////////////////////

template <class T, size_t size>
AssocioPoolAllocator<T, size>::AssocioPoolAllocator()
    : pool_size_{size + 2}, //2 blocks of memory requires for stl-container
    pool_{std::shared_ptr<void>{::operator new(pool_size_ * sizeof(T)),deleter()}},
    counter_{std::make_shared<AllocatorCounter>()}
{}

template <class T, size_t size>
template <class U>
AssocioPoolAllocator<T, size>::AssocioPoolAllocator(
    const AssocioPoolAllocator<U, size>& rhs) noexcept
    :pool_{rhs.GetPool()}, pool_size_{rhs.GetPoolSize()}, counter_{rhs.GetCounter()}
{}

template <class T, size_t size>
AssocioPoolAllocator<T, size>&  AssocioPoolAllocator<T, size>::operator=(
    AssocioPoolAllocator<T, size>&& rhs) noexcept
{
    if (&rhs == this)
        return *this;

    pool_ = rhs.pool_;
    pool_size_ = rhs.pool_size_;
    counter_ = rhs.counter_;

    rhs.pool_ = rhs.counter_ = nullptr;
    rhs.pool_size_ = 0;

    return *this;
}

template <class T, size_t size>
T* AssocioPoolAllocator<T, size>::allocate(size_t n)
{
    if (n < 1)
    {
        throw std::invalid_argument("T* allocate requires n >= 1");
    }

    if (GetAllocatedSize() + n > pool_size_)
    {
        throw std::bad_alloc();
    }

    T* ptr = reinterpret_cast<T*>(pool_.get()) + GetAllocatedSize();    
    GetAllocatedSize() += n;
    return ptr;
}

template <class T, size_t size>
void AssocioPoolAllocator<T, size>::deallocate(T* p, size_t n)
{
    GetAllocatedSize() -= n; // deallocate all

    (void)p; // warning C4100: 'p': unreferenced formal parameter
}

template <class T, size_t size>
size_t& AssocioPoolAllocator<T, size>::GetAllocatedSize() const
{
    return counter_->allocated_size_;
}




template <class T, size_t size, class U>
constexpr bool operator== (const AssocioPoolAllocator<T, size>& lhs, 
    const AssocioPoolAllocator<U>& rhs) noexcept
{
    return lhs.pool == rhs.pool_;
}

template <class T, size_t size, class U>
constexpr bool operator!= (const AssocioPoolAllocator<T, size>& lhs, 
    const AssocioPoolAllocator<U>& rhs) noexcept
{
    return !(lhs == rhs);
}

