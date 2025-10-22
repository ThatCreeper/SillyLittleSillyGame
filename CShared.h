#pragma once

// Simple, single-threaded shared_ptr implementation.
template <class Type>
class CShared
{
public:
	explicit CShared(Type *Pointer);
	CShared(const CShared<Type> &Other);
	~CShared();

	Type &operator*() const;
private:
	Type *mPointer;
	int *mReferences;
};

template<class Type>
inline CShared<Type>::CShared(Type *Pointer)
{
	this->mPointer = Pointer;
	this->mReferences = new int(1);
}

template<class Type>
inline CShared<Type>::CShared(const CShared<Type> &Other)
{
	mPointer = Other.mPointer;
	mReferences = Other.mReferences;
	++*mReferences;
}

template<class Type>
inline CShared<Type>::~CShared()
{
	if (--*mReferences == 0) {
		delete mPointer;
		delete mReferences;
	}
}

template<class Type>
inline Type &CShared<Type>::operator*() const
{
	return *mPointer;
}
