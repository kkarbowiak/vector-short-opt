#ifndef SHORT_VECTOR_OPT_H__DDK
#define SHORT_VECTOR_OPT_H__DDK

#include <vector>
#include <cstddef>


namespace opt
{
    template<typename T, std::size_t N>
    class vector_short_opt
    {
        public:
            typedef T value_type;
            typedef typename std::vector<T>::allocator_type allocator_type;
            typedef T & reference;
            typedef T * pointer;
            typedef T const & const_reference;
            typedef T const * const_pointer;
            typedef T * iterator;
            typedef T const * const_iterator;

            typedef std::ptrdiff_t difference_type;
            typedef std::size_t size_type;

        public:
            explicit vector_short_opt(allocator_type const & alloc = allocator_type());
            explicit vector_short_opt(size_type n, value_type const & val = value_type(), allocator_type const & alloc = allocator_type());
            template <class InputIterator>
            vector_short_opt(InputIterator first, InputIterator last, allocator_type const & alloc = allocator_type());
            vector_short_opt(vector_short_opt const & other);

            ~vector_short_opt();

            vector_short_opt & operator=(vector_short_opt const & other);

            iterator begin();
            const_iterator begin() const;
            iterator end();
            const_iterator end() const;

            void resize(size_type n, value_type val = value_type());

            void reserve(size_type n);

            reference operator[] (size_type n);
            const_reference operator[] (size_type n) const;

            reference at(size_type n);
            const_reference at(size_type n) const;

            reference front();
            const_reference front() const;
            reference back();
            const_reference back() const;

            template <class InputIterator>
            void assign(InputIterator first, InputIterator last);
            void assign(size_type n, value_type const & val);

            void push_back(value_type const & val);
            void pop_back();

            iterator insert(iterator position, value_type const & val);
            void insert(iterator position, size_type n, value_type const & val);
            template <class InputIterator>
            void insert(iterator position, InputIterator first, InputIterator last);

            iterator erase(iterator position);
            iterator erase(iterator first, iterator last);

            void swap(vector_short_opt & other);

            void clear();

            bool empty() const;
            size_type size() const;
            size_type capacity() const;
            size_type max_size() const;

            allocator_type get_allocator() const;

        private:
            pointer get_ptr(size_type index);
            const_pointer get_ptr(size_type index) const;

        private:
            char d_array[N * sizeof(T)];
            size_type d_size;
            bool d_array_used;
            std::vector<T> d_vector;
    };
}


namespace opt
{
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline vector_short_opt<T, N>::vector_short_opt(allocator_type const & alloc)
    : d_vector(alloc)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline vector_short_opt<T, N>::vector_short_opt(size_type n, value_type const & val, allocator_type const & alloc)
    : d_vector(n, val, alloc)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
template <class InputIterator>
inline vector_short_opt<T, N>::vector_short_opt(InputIterator first, InputIterator last, allocator_type const & alloc)
    : d_vector(first, last, alloc)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline vector_short_opt<T, N>::vector_short_opt(vector_short_opt const & other)
    : d_vector(other.d_vector)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline vector_short_opt<T, N>::~vector_short_opt()
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline vector_short_opt<T, N> & vector_short_opt<T, N>::operator=(vector_short_opt const & other)
{
    d_vector = other.d_vector;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::iterator vector_short_opt<T, N>::begin()
{
    return d_vector.empty()
        ? NULL
        : &d_vector[0];
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_iterator vector_short_opt<T, N>::begin() const
{
    return d_vector.empty()
        ? NULL
        : &d_vector[0];
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::iterator vector_short_opt<T, N>::end()
{
    return d_vector.empty()
        ? NULL
        : &d_vector[0] + d_vector.size();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_iterator vector_short_opt<T, N>::end() const
{
    return d_vector.empty()
        ? NULL
        : &d_vector[0] + d_vector.size();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::resize(size_type n, value_type val)
{
    d_vector.resize(n, val);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::reserve(size_type n)
{
    d_vector.reserve(n);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::reference vector_short_opt<T, N>::operator[](size_type n)
{
    return d_vector[n];
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_reference vector_short_opt<T, N>::operator[](size_type n) const
{
    return d_vector[n];
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::reference vector_short_opt<T, N>::at(size_type n)
{
    return d_vector.at(n);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_reference vector_short_opt<T, N>::at(size_type n) const
{
    return d_vector.at(n);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::reference vector_short_opt<T, N>::front()
{
    return d_vector.front();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_reference vector_short_opt<T, N>::front()  const
{
    return d_vector.front();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::reference vector_short_opt<T, N>::back()
{
    return d_vector.back();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_reference vector_short_opt<T, N>::back() const
{
    return d_vector.back();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
template <class InputIterator>
inline void vector_short_opt<T, N>::assign(InputIterator first, InputIterator last)
{
    d_vector.assign(first, last);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::assign(size_type n, value_type const & val)
{
    d_vector.assign(n, val);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::push_back(value_type const & val)
{
    d_vector.push_back(val);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::pop_back()
{
    d_vector.pop_back();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::iterator vector_short_opt<T, N>::insert(iterator position, value_type const & val)
{
    return &*d_vector.insert(d_vector.begin() + std::distance(begin(), position), val);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::insert(iterator position, size_type n, value_type const & val)
{
    d_vector.insert(d_vector.begin() + std::distance(begin(), position), n, val);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
template <class InputIterator>
inline void vector_short_opt<T, N>::insert(iterator position, InputIterator first, InputIterator last)
{
    d_vector.insert(d_vector.begin() + std::distance(begin(), position), first, last);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::iterator vector_short_opt<T, N>::erase(iterator position)
{
    std::vector<T>::iterator i = d_vector.erase(d_vector.begin() + std::distance(begin(), position));

    return i  != d_vector.end()
        ? &*i
        : end();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::iterator vector_short_opt<T, N>::erase(iterator first, iterator last)
{
    std::vector<T>::iterator i = d_vector.erase(d_vector.begin() + std::distance(begin(), first), d_vector.begin() + std::distance(begin(), last));

    return i != d_vector.end()
        ? &*i
        : end();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::swap(vector_short_opt & other)
{
    std::swap(d_vector, other.d_vector);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::clear()
{
    d_vector.clear();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline bool vector_short_opt<T, N>::empty() const
{
    return d_vector.empty();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::size_type vector_short_opt<T, N>::size() const
{
    return d_vector.size();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::size_type vector_short_opt<T, N>::capacity() const
{
    return d_vector.capacity();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::size_type vector_short_opt<T, N>::max_size() const
{
    return d_vector.max_size();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::allocator_type vector_short_opt<T, N>::get_allocator() const
{
    return d_vector.get_allocator();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::pointer vector_short_opt<T, N>::get_ptr(size_type index)
{
    pointer p = reinterpret_cast<pointer>(d_array);

    return (p + index);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_pointer vector_short_opt<T, N>::get_ptr(size_type index) const
{
    const_pointer p = reinterpret_cast<const_pointer>(d_array);

    return (p + index);
}
////////////////////////////////////////////////////////////////////////////////
}

#endif /* SHORT_VECTOR_OPT_H__DDK */
