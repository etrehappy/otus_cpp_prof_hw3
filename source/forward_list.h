#pragma once
#include <memory>
#include <iostream>
#include "my_allocator.h"

template <typename T, class Allocator = std::allocator<T> >
class ForwardList
{
public:
    ForwardList();
    ForwardList(const ForwardList&) = delete; //unused in the project
    ForwardList& operator= (const ForwardList&) = delete; //unused in the project
    ForwardList(ForwardList&&) noexcept; //unused in the project
    ForwardList& operator= (ForwardList&&) noexcept; //unused in the project
    virtual ~ForwardList();

    void emplase_back(T&&);
    size_t size();

    struct iterator;
    iterator begin();
    iterator back();
    iterator end();

    template <typename T_, class Allocator_> //declaration 'T' and 'Allocator' shadows template parameter
    friend std::ostream& operator<<(std::ostream& out, ForwardList<T_, Allocator_>& rhs);

private:
    struct Node;
        
    size_t size_f_list_;
    Node* start_node_;
    Node* last_node_;

public:
    using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;

private:
    //Allocator alloc_; //unused in the project
    NodeAllocator node_alloc_;
};

    
////////////////////////////////////////////////////////////////////////////////
// struct Node
////////////////////////////////////////////////////////////////////////////////
template <typename T, class Allocator>
struct ForwardList<T, Allocator>::Node
{
    Node();
    Node(T);
    ~Node() = default;

    T data_;
    Node* next_;
};

////////////////////////////////////////////////////////////////////////////////
// struct iterator
////////////////////////////////////////////////////////////////////////////////
template <typename T, class Allocator>
struct ForwardList<T, Allocator>::iterator
{
public:
    iterator(Node* p);
    ~iterator() = default;

    T& operator*();
    iterator& operator++();
    bool operator!=(iterator& rhs);

private:
    Node* iterator_ptr_;
};



#include "forward_list.ipp"

