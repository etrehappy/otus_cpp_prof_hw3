////////////////////////////////////////////////////////////////////////////////
// class ForwardList
////////////////////////////////////////////////////////////////////////////////
template<typename T, class Allocator>
ForwardList<T, Allocator>::ForwardList()
    :size_f_list_{0}, start_node_{nullptr}, last_node_{nullptr}, node_alloc_{}
{
}

template<typename T, class Allocator>
ForwardList<T, Allocator>::ForwardList(ForwardList&& rhs) noexcept
{
    *this = std::move(rhs);
}

template<typename T, class Allocator>
ForwardList<T, Allocator>& ForwardList<T, Allocator>::operator=(ForwardList&& rhs) noexcept
{
    if (&rhs == this)
        return *this;

    start_node_ = rhs.start_node_;
    last_node_ = rhs.last_node_;
    size_f_list_ = rhs.size_f_list_;
    node_alloc_ = std::move(rhs.node_alloc_);

    rhs.start_node_ = rhs.last_node_ = nullptr;
    rhs.size_f_list_ = 0;

    return *this;
}

template<typename T, class Allocator>
ForwardList<T, Allocator>::~ForwardList()
{
    std::allocator_traits<NodeAllocator>::deallocate(node_alloc_, start_node_,
        size_f_list_);
}

template<typename T, class Allocator>
void ForwardList<T, Allocator>::emplase_back(T&& value)
{
    ++size_f_list_;

    Node* new_node = std::allocator_traits<NodeAllocator>::allocate(node_alloc_, 1);

    new_node->data_ = std::move(value);
    new_node->next_ = nullptr;

    if (size_f_list_ == 1)
        start_node_ = new_node;
    else
        last_node_->next_ = new_node;

    last_node_ = new_node;
}

template<typename T, class Allocator>
size_t ForwardList<T, Allocator>::size()
{
    return size_f_list_;
}


template<typename T, class Allocator>
typename ForwardList<T, Allocator>::iterator ForwardList<T, Allocator>::begin()
{
    return iterator(start_node_);
}

template<typename T, class Allocator>
typename ForwardList<T, Allocator>::iterator ForwardList<T, Allocator>::back()
{
    return iterator(last_node_);
}

template<typename T, class Allocator>
typename ForwardList<T, Allocator>::iterator ForwardList<T, Allocator>::end()
{
    return iterator(last_node_->next_);
}

template<typename T, class Allocator>
std::ostream& operator<<(std::ostream& out, ForwardList<T, Allocator>& rhs)
{
    if (rhs.size() == 0) { return out; }

    auto last = rhs.back();

    for (auto it = rhs.begin(); it != last; ++it)
    {
        out << *it << ", ";
    }

    out << *last;

    return out;
}


////////////////////////////////////////////////////////////////////////////////
// struct Node
////////////////////////////////////////////////////////////////////////////////
template <typename T, class Allocator>
ForwardList<T, Allocator>::Node::Node()
    :data_{}, next_{nullptr}
{
}

template <typename T, class Allocator>
ForwardList<T, Allocator>::Node::Node(T value)
    : data_{value}, next_{nullptr}
{
}


////////////////////////////////////////////////////////////////////////////////
// struct iterator
////////////////////////////////////////////////////////////////////////////////

template<typename T, class Allocator>
ForwardList<T, Allocator>::iterator::iterator(Node* p)
    :iterator_ptr_{p}
{
}

template<typename T, class Allocator>
T& ForwardList<T, Allocator>::iterator::operator*()
{
    return iterator_ptr_->data_;
}

template<typename T, class Allocator>
typename ForwardList<T, Allocator>::iterator& ForwardList<T, Allocator>::iterator::operator++()
{
    iterator_ptr_ = iterator_ptr_->next_;
    return *this;
}

template<typename T, class Allocator>
bool ForwardList<T, Allocator>::iterator::operator!=(iterator& rhs)
{
    return iterator_ptr_ != rhs.iterator_ptr_;
}

