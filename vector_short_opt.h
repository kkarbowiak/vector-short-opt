/*
    Copyright 2018 Krzysztof Karbowiak
*/

#ifndef SHORT_VECTOR_OPT_H__DDK
#define SHORT_VECTOR_OPT_H__DDK

#include <iterator>
#include <vector>
#include <algorithm>
#include <cstddef>


namespace opt
{
    namespace detail
    {
        template<typename T>
        class iterator
        {
            public:
                typedef std::random_access_iterator_tag iterator_category;
                typedef T value_type;
                typedef std::ptrdiff_t difference_type;
                typedef T * pointer;
                typedef T & reference;

            public:
                iterator();
                iterator(iterator const & other);
                explicit iterator(pointer ptr);

                iterator & operator=(iterator const & other);

                reference operator*() const;
                pointer operator->() const;
                reference operator[](difference_type off) const;

                iterator & operator+=(difference_type off);
                iterator & operator-=(difference_type off);

                iterator & operator++();
                iterator & operator--();
                iterator operator++(int) const;
                iterator operator--(int) const;

                bool operator==(iterator const & rhs) const;
                bool operator!=(iterator const & rhs) const;
                bool operator>(iterator const & rhs) const;
                bool operator<(iterator const & rhs) const;
                bool operator>=(iterator const & rhs) const;
                bool operator<=(iterator const & rhs) const;

                template<typename U>
                friend iterator<U> operator+(iterator<U> const & lhs, typename iterator<U>::difference_type rhs);
                template<typename U>
                friend iterator<U> operator+(typename iterator<U>::difference_type lhs, iterator<U> const & rhs);
                template<typename U>
                friend iterator<U> operator-(iterator<U> const & lhs, typename iterator<U>::difference_type rhs);
                template<typename U>
                friend iterator<U> operator-(typename iterator<U>::difference_type lhs, iterator<U> const & rhs);

                template<typename U>
                friend typename iterator<U>::difference_type operator-(iterator<U> const & lhs, iterator<U> const & rhs);

            private:
                T * d_pointer;
        };

        template<typename T>
        class const_iterator
        {
            public:
                typedef std::random_access_iterator_tag iterator_category;
                typedef T value_type;
                typedef std::ptrdiff_t difference_type;
                typedef T const * pointer;
                typedef T const & reference;

            public:
                const_iterator();
                const_iterator(const_iterator const & other);
                const_iterator(iterator<T> const & other);
                explicit const_iterator(pointer ptr);

                const_iterator & operator=(const_iterator const & other);
                const_iterator & operator=(iterator<T> const & other);

                reference operator*() const;
                pointer operator->() const;
                reference operator[](difference_type off) const;

                const_iterator & operator+=(difference_type off);
                const_iterator & operator-=(difference_type off);

                const_iterator & operator++();
                const_iterator & operator--();
                const_iterator operator++(int) const;
                const_iterator operator--(int) const;

                bool operator==(const_iterator const & rhs) const;
                bool operator!=(const_iterator const & rhs) const;
                bool operator>(const_iterator const & rhs) const;
                bool operator<(const_iterator const & rhs) const;
                bool operator>=(const_iterator const & rhs) const;
                bool operator<=(const_iterator const & rhs) const;

                template<typename U>
                friend const_iterator<U> operator+(const_iterator<U> const & lhs, typename const_iterator<U>::difference_type rhs);
                template<typename U>
                friend const_iterator<U> operator+(typename const_iterator<U>::difference_type lhs, const_iterator<U> const & rhs);
                template<typename U>
                friend const_iterator<U> operator-(const_iterator<U> const & lhs, typename const_iterator<U>::difference_type rhs);
                template<typename U>
                friend const_iterator<U> operator-(typename const_iterator<U>::difference_type lhs, const_iterator<U> const & rhs);

                template<typename U>
                friend typename const_iterator<U>::difference_type operator-(const_iterator<U> const & lhs, const_iterator<U> const & rhs);

            private:
                T const * d_pointer;
        };
    }
}

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
            typedef detail::iterator<T> iterator;
            typedef detail::const_iterator<T> const_iterator;
            typedef std::reverse_iterator<iterator> reverse_iterator;
            typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

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

            reverse_iterator rbegin();
            const_reverse_iterator rbegin() const;
            reverse_iterator rend();
            const_reverse_iterator rend() const;

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

            void clear();

            bool empty() const;
            size_type size() const;
            size_type capacity() const;
            size_type max_size() const;

            allocator_type get_allocator() const;

        private:
            pointer get_ptr(size_type index);
            const_pointer get_ptr(size_type index) const;

            reference get_ref(size_type index);
            const_reference get_ref(size_type index) const;

            void construct(size_type index, value_type const & val);
            void destroy(size_type index);

            void move_array_to_vector();

            void destroy_array();

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
    : d_size(0)
    , d_array_used(true)
    , d_vector(alloc)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline vector_short_opt<T, N>::vector_short_opt(size_type n, value_type const & val, allocator_type const & alloc)
    : d_size(0)
    , d_array_used(n < N)
    , d_vector(alloc)
{
    if (d_array_used)
    {
        try
        {
            while (d_size < n)
            {
                construct(d_size, val);

                ++d_size;
            }
        }
        catch (...)
        {
            destroy_array();

            throw;
        }
    }
    else
    {
        d_vector = std::vector<T>(n, val, alloc);
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
template <class InputIterator>
inline vector_short_opt<T, N>::vector_short_opt(InputIterator first, InputIterator last, allocator_type const & alloc)
    : d_size(0)
    , d_array_used(true)
    , d_vector(alloc)
{
    try
    {
        for (InputIterator i = first; i != last; ++i)
        {
            push_back(*i);
        }
    }
    catch (...)
    {
        destroy_array();

        throw;
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline vector_short_opt<T, N>::vector_short_opt(vector_short_opt const & other)
    : d_size(0)
    , d_array_used(other.d_array_used)
    , d_vector(other.d_vector)
{
    if (d_array_used)
    {
        try
        {
            while (d_size < other.d_size)
            {
                construct(d_size, *other.get_ptr(d_size));

                ++d_size;
            }
        }
        catch (...)
        {
            destroy_array();

            throw;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline vector_short_opt<T, N>::~vector_short_opt()
{
    if (d_array_used)
    {
        destroy_array();
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline vector_short_opt<T, N> & vector_short_opt<T, N>::operator=(vector_short_opt const & other)
{
    assign(other.begin(), other.end()); // TODO: replace with proper assignment operation

    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::iterator vector_short_opt<T, N>::begin()
{
    pointer ptr = d_array_used
        ? get_ptr(0)
        : d_vector.empty()
            ? NULL
            : &d_vector[0];

    return iterator(ptr);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_iterator vector_short_opt<T, N>::begin() const
{
    const_pointer ptr = d_array_used
        ? get_ptr(0)
        : d_vector.empty()
            ? NULL
            : &d_vector[0];

    return const_iterator(ptr);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::iterator vector_short_opt<T, N>::end()
{
    pointer ptr = d_array_used
        ? get_ptr(d_size)
        : d_vector.empty()
            ? NULL
            : &d_vector[0] + d_vector.size();

    return iterator(ptr);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_iterator vector_short_opt<T, N>::end() const
{
    const_pointer ptr = d_array_used
        ? get_ptr(d_size)
        : d_vector.empty()
            ? NULL
            : &d_vector[0] + d_vector.size();

    return const_iterator(ptr);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::reverse_iterator vector_short_opt<T, N>::rbegin()
{
    return reverse_iterator(end());
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_reverse_iterator vector_short_opt<T, N>::rbegin() const
{
    return const_reverse_iterator(end());
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::reverse_iterator vector_short_opt<T, N>::rend()
{
    return reverse_iterator(begin());
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_reverse_iterator vector_short_opt<T, N>::rend() const
{
    return const_reverse_iterator(begin());
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::resize(size_type n, value_type val)
{
    if (d_array_used)
    {
        if (n <= N)
        {
            if (n < d_size)
            {
                for (size_type i = n; i < d_size; ++i)
                {
                    destroy(i);
                }

                d_size = n;
            }
            else if (n == d_size)
            {
                // do nothing
            }
            else
            {
                for (; d_size != n; ++d_size)
                {
                    construct(d_size, val);
                }
            }
        }
        else
        {
            d_array_used = false;

            d_vector.reserve(n);

            move_array_to_vector();

            d_vector.resize(n, val);
        }
    }
    else
    {
        d_vector.resize(n, val);
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::reserve(size_type n)
{
    if (d_array_used)
    {
        if (n <= N)
        {
            // do nothing
        }
        else
        {
            d_array_used = false;

            d_vector.reserve(n);

            move_array_to_vector();
        }
    }
    else
    {
        d_vector.reserve(n);
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::reference vector_short_opt<T, N>::operator[](size_type n)
{
    if (d_array_used)
    {
        return *get_ptr(n);
    }
    else
    {
        return d_vector[n];
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_reference vector_short_opt<T, N>::operator[](size_type n) const
{
    if (d_array_used)
    {
        return *get_ptr(n);
    }
    else
    {
        return d_vector[n];
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::reference vector_short_opt<T, N>::at(size_type n)
{
    if (d_array_used)
    {
        if (n < d_size)
        {
            return *get_ptr(n);
        }
        else
        {
            throw std::out_of_range("");
        }
    }
    else
    {
        return d_vector.at(n);
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_reference vector_short_opt<T, N>::at(size_type n) const
{
    if (d_array_used)
    {
        if (n < d_size)
        {
            return *get_ptr(n);
        }
        else
        {
            throw std::out_of_range("");
        }
    }
    else
    {
        return d_vector.at(n);
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::reference vector_short_opt<T, N>::front()
{
    return d_array_used
        ? *get_ptr(0)
        : d_vector.front();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_reference vector_short_opt<T, N>::front()  const
{
    return d_array_used
        ? *get_ptr(0)
        : d_vector.front();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::reference vector_short_opt<T, N>::back()
{
    return d_array_used
        ? *get_ptr(d_size - 1)
        : d_vector.front();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_reference vector_short_opt<T, N>::back() const
{
    return d_array_used
        ? *get_ptr(d_size - 1)
        : d_vector.front();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
template <class InputIterator>
inline void vector_short_opt<T, N>::assign(InputIterator first, InputIterator last)
{
    clear();

    for (InputIterator i = first; i != last; ++i)
    {
        push_back(*i);
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::assign(size_type n, value_type const & val)
{
    if (d_array_used)
    {
        destroy_array();
    }

    if (n <= N)
    {
        d_array_used = true;

        for (d_size = 0; d_size < n; ++d_size)
        {
            construct(d_size, val);
        }
    }
    else
    {
        d_array_used = false;
        d_vector.assign(n, val);
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::push_back(value_type const & val)
{
    if (d_array_used)
    {
        if (d_size < N)
        {
            construct(d_size, val);

            ++d_size;
        }
        else
        {
            d_vector.reserve(N + 1);

            move_array_to_vector();

            d_vector.push_back(val);

            d_array_used = false;
        }
    }
    else
    {
        d_vector.push_back(val);
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::pop_back()
{
    if (d_array_used)
    {
        destroy(--d_size);
    }
    else
    {
        d_vector.pop_back();
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::iterator vector_short_opt<T, N>::insert(iterator position, value_type const & val)
{
    iterator result;

    if (d_array_used)
    {
        if (d_size < N)
        {
            if (position == end())
            {
                construct(d_size++, val);

                result = position;
            }
            else
            {
                construct(d_size, *get_ptr(d_size - 1));
                std::copy_backward(position, iterator(get_ptr(d_size - 1)), iterator(get_ptr(d_size)));
                ++d_size;
                *position = val;
                result = position;
            }
        }
        else
        {
            d_vector.reserve(N + 1);

            move_array_to_vector();

            result = iterator(&*d_vector.insert(d_vector.begin() + (position - iterator(get_ptr(0))), val));

            d_array_used = false;
        }
    }
    else
    {
        result = iterator(&*d_vector.insert(d_vector.begin() + std::distance(begin(), position), val));
    }

    return result;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::insert(iterator position, size_type n, value_type const & val)
{
    if (d_array_used)
    {
        if (d_size + n <= N)
        {
            while (n-- > 0)
            {
                position = insert(position, val);
                ++position;
            }
        }
        else
        {
            d_vector.reserve(d_size + n);

            move_array_to_vector();

            d_vector.insert(d_vector.begin() + (position - iterator(get_ptr(0))), n, val);

            d_array_used = false;
        }
    }
    else
    {
        d_vector.insert(d_vector.begin() + std::distance(begin(), position), n, val);
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
template <class InputIterator>
inline void vector_short_opt<T, N>::insert(iterator position, InputIterator first, InputIterator last)
{
    if (d_array_used)
    {
        while (first != last)
        {
            position = insert(position, *first);
            ++position;
        }
    }
    else
    {
        d_vector.insert(d_vector.begin() + std::distance(begin(), position), first, last);
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::iterator vector_short_opt<T, N>::erase(iterator position)
{
    if (d_array_used)
    {
        std::copy_backward(position + 1, end(), position);

        destroy(d_size--);

        return position;
    }
    else
    {
        typename std::vector<T>::iterator i = d_vector.erase(d_vector.begin() + std::distance(begin(), position));

        return i != d_vector.end()
            ? iterator(&*i)
            : end();
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::iterator vector_short_opt<T, N>::erase(iterator first, iterator last)
{
    if (d_array_used)
    {
        iterator i = first;
        while (i != last)
        {
            erase(i);
        }

        return first;
    }
    else
    {
        typename std::vector<T>::iterator i = d_vector.erase(d_vector.begin() + std::distance(begin(), first), d_vector.begin() + std::distance(begin(), last));

        return i != d_vector.end()
            ? iterator(&*i)
            : end();
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::clear()
{
    if (d_array_used)
    {
        destroy_array();

        d_size = 0;
    }
    else
    {
        d_vector.clear();
    }
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline bool vector_short_opt<T, N>::empty() const
{
    return d_array_used
        ? d_size == 0
        : d_vector.empty();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::size_type vector_short_opt<T, N>::size() const
{
    return d_array_used
        ? d_size
        : d_vector.size();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::size_type vector_short_opt<T, N>::capacity() const
{
    return d_array_used
        ? N
        : d_vector.capacity();
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
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::reference vector_short_opt<T, N>::get_ref(size_type index)
{
    return *get_ptr(index);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline typename vector_short_opt<T, N>::const_reference vector_short_opt<T, N>::get_ref(size_type index) const
{
    return *get_ptr(index);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::construct(size_type index, value_type const & val)
{
    (void) new(get_ptr(index)) T(val);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::destroy(size_type index)
{
    get_ptr(index)->~T();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::move_array_to_vector()
{
    d_vector.assign(get_ptr(0), get_ptr(d_size));

    destroy_array();
}
////////////////////////////////////////////////////////////////////////////////
template<typename T, std::size_t N>
inline void vector_short_opt<T, N>::destroy_array()
{
    for (size_type i = 0; i < d_size; ++i)
    {
        destroy(i);
    }
}
////////////////////////////////////////////////////////////////////////////////
}

namespace opt
{
namespace detail
{
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T>::iterator()
    : d_pointer(NULL)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T>::iterator(iterator const & other)
    : d_pointer(other.d_pointer)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T>::iterator(pointer ptr)
    : d_pointer(ptr)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T> & iterator<T>::operator=(iterator const & other)
{
    d_pointer = other.d_pointer;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename iterator<T>::reference iterator<T>::operator*() const
{
    return *d_pointer;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename iterator<T>::pointer iterator<T>::operator->() const
{
    return d_pointer;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename iterator<T>::reference iterator<T>::operator[](difference_type off) const
{
    return d_pointer[off];
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T> & iterator<T>::operator+=(difference_type off)
{
    d_pointer += off;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T> & iterator<T>::operator-=(difference_type off)
{
    d_pointer -= off;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T> & iterator<T>::operator++()
{
    ++d_pointer;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T> & iterator<T>::operator--()
{
    --d_pointer;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T> iterator<T>::operator++(int) const
{
    iterator tmp(*this);

    ++d_pointer;

    return tmp;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T> iterator<T>::operator--(int) const
{
    iterator tmp(*this);

    --d_pointer;

    return tmp;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool iterator<T>::operator==(iterator const & rhs) const
{
    return (d_pointer == rhs.d_pointer);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool iterator<T>::operator!=(iterator const & rhs) const
{
    return !(*this == rhs);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool iterator<T>::operator>(iterator const & rhs) const
{
    return (d_pointer > rhs.d_pointer);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool iterator<T>::operator<(iterator const & rhs) const
{
    return (d_pointer < rhs.d_pointer);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool iterator<T>::operator>=(iterator const & rhs) const
{
    return !(*this < rhs);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool iterator<T>::operator<=(iterator const & rhs) const
{
    return !(*this > rhs);
}
////////////////////////////////////////////////////////////////////////////////
}
}

namespace opt
{
namespace detail
{
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T> operator+(iterator<T> const & lhs, typename iterator<T>::difference_type rhs)
{
    return iterator<T>(lhs.d_pointer + rhs);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T> operator+(typename iterator<T>::difference_type lhs, iterator<T> const & rhs)
{
    return iterator<T>(lhs + rhs.d_pointer);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T> operator-(iterator<T> const & lhs, typename iterator<T>::difference_type rhs)
{
    return iterator<T>(lhs.d_pointer - rhs);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline iterator<T> operator-(typename iterator<T>::difference_type lhs, iterator<T> const & rhs)
{
    return iterator<T>(lhs - rhs.d_pointer);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename iterator<T>::difference_type operator-(iterator<T> const & lhs, iterator<T> const & rhs)
{
    return (lhs.d_pointer - rhs.d_pointer);
}
////////////////////////////////////////////////////////////////////////////////
}
}

namespace opt
{
namespace detail
{
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T>::const_iterator()
    : d_pointer(NULL)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T>::const_iterator(const_iterator const & other)
    : d_pointer(other.d_pointer)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T>::const_iterator(iterator<T> const & other)
    : d_pointer(other.d_pointer)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T>::const_iterator(pointer ptr)
    : d_pointer(ptr)
{
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T> & const_iterator<T>::operator=(const_iterator const & other)
{
    d_pointer = other.d_pointer;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T> & const_iterator<T>::operator=(iterator<T> const & other)
{
    d_pointer = other.d_pointer;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename const_iterator<T>::reference const_iterator<T>::operator*() const
{
    return *d_pointer;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename const_iterator<T>::pointer const_iterator<T>::operator->() const
{
    return d_pointer;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename const_iterator<T>::reference const_iterator<T>::operator[](difference_type off) const
{
    return d_pointer[off];
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T> & const_iterator<T>::operator+=(difference_type off)
{
    d_pointer += off;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T> & const_iterator<T>::operator-=(difference_type off)
{
    d_pointer -= off;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T> & const_iterator<T>::operator++()
{
    ++d_pointer;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T> & const_iterator<T>::operator--()
{
    --d_pointer;

    return *this;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T> const_iterator<T>::operator++(int) const
{
    const_iterator tmp(*this);

    ++d_pointer;

    return tmp;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T> const_iterator<T>::operator--(int) const
{
    const_iterator tmp(*this);

    --d_pointer;

    return tmp;
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool const_iterator<T>::operator==(const_iterator const & rhs) const
{
    return (d_pointer == rhs.d_pointer);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool const_iterator<T>::operator!=(const_iterator const & rhs) const
{
    return !(*this == rhs);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool const_iterator<T>::operator>(const_iterator const & rhs) const
{
    return (d_pointer > rhs.d_pointer);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool const_iterator<T>::operator<(const_iterator const & rhs) const
{
    return (d_pointer < rhs.d_pointer);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool const_iterator<T>::operator>=(const_iterator const & rhs) const
{
    return !(*this < rhs);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline bool const_iterator<T>::operator<=(const_iterator const & rhs) const
{
    return !(*this > rhs);
}
////////////////////////////////////////////////////////////////////////////////
}
}

namespace opt
{
namespace detail
{
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T> operator+(const_iterator<T> const & lhs, typename const_iterator<T>::difference_type rhs)
{
    return const_iterator<T>(lhs.d_pointer + rhs);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T> operator+(typename const_iterator<T>::difference_type lhs, const_iterator<T> const & rhs)
{
    return const_iterator<T>(lhs + rhs.d_pointer);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T> operator-(const_iterator<T> const & lhs, typename const_iterator<T>::difference_type rhs)
{
    return const_iterator<T>(lhs.d_pointer - rhs);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline const_iterator<T> operator-(typename const_iterator<T>::difference_type lhs, const_iterator<T> const & rhs)
{
    return const_iterator<T>(lhs - rhs.d_pointer);
}
////////////////////////////////////////////////////////////////////////////////
template<typename T>
inline typename const_iterator<T>::difference_type operator-(const_iterator<T> const & lhs, const_iterator<T> const & rhs)
{
    return (lhs.d_pointer - rhs.d_pointer);
}
////////////////////////////////////////////////////////////////////////////////
}
}

#endif /* SHORT_VECTOR_OPT_H__DDK */
