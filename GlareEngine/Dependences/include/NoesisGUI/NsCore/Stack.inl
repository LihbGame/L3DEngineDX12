////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace eastl
{

////////////////////////////////////////////////////////////////////////////////////////////////////
// stack
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, typename Allocator>
inline stack<T, Allocator>::stack() :
    mContainer()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, typename Allocator>
inline stack<T, Allocator>::stack(const this_type& other) :
    mContainer(other.mContainer)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, typename Allocator>
inline typename stack<T, Allocator>::this_type& 
stack<T, Allocator>::operator=(const this_type& other)
{
    mContainer = other.mContainer;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, typename Allocator>
inline void stack<T, Allocator>::push(const value_type& value)
{
    mContainer.push_back(value);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, typename Allocator>
inline void stack<T, Allocator>::pop()
{
    mContainer.pop_back();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, typename Allocator>
inline typename stack<T, Allocator>::reference 
stack<T, Allocator>::top()
{
    return const_cast<reference>(static_cast<const this_type*>(this)->top());
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, typename Allocator>
inline typename stack<T, Allocator>::const_reference 
stack<T, Allocator>::top() const
{
    return mContainer.back();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, typename Allocator>
inline bool stack<T, Allocator>::empty() const
{
    return mContainer.empty();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, typename Allocator>
inline typename stack<T, Allocator>::size_type 
stack<T, Allocator>::size() const
{
    return mContainer.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, typename Allocator>
inline typename stack<T, Allocator>::container_type& 
stack<T, Allocator>::get_container()
{
    return mContainer;
}

}

////////////////////////////////////////////////////////////////////////////////////////////////////
// NsStack
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, typename Allocator>
inline NsStack<T, Allocator>::NsStack() :
    BaseType()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, typename Allocator>
inline NsStack<T, Allocator>::NsStack(const ThisType& other) :
    BaseType(other)
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////
template<class T, typename Allocator>
inline typename NsStack<T, Allocator>::ThisType& 
NsStack<T, Allocator>::operator=(const ThisType& other)
{
    return static_cast<ThisType&>(BaseType::operator=(other));
}
