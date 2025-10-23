#pragma once

// Simple, single-threaded shared_ptr implementation.
template <class Type>
class CShared
{
public:
	// Creates an invalid state. Be careful!
	explicit CShared();
	explicit CShared(Type *Pointer);
	CShared(const CShared<Type> &Other);
	~CShared();

	Type &operator*() const;
	Type *operator->() const;

	CShared<Type> &operator =(const CShared &Other);
private:
	Type *mPointer;
	int *mReferences;
};

template<class Type>
inline CShared<Type>::CShared()
{
	this->mPointer = nullptr;
	this->mReferences = nullptr;
}

template<class Type>
inline CShared<Type>::CShared(Type *Pointer)
{
	this->mPointer = Pointer;
	this->mReferences = new int(1);
}

template<class Type>
inline CShared<Type>::CShared(const CShared<Type> &Other)
{
	*this = Other;
}

template<class Type>
inline CShared<Type>::~CShared()
{
	if (!mReferences) return;
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

template<class Type>
inline Type *CShared<Type>::operator->() const
{
	return mPointer;
}

template<class Type>
inline CShared<Type> &CShared<Type>::operator=(const CShared &Other)
{
	mPointer = Other.mPointer;
	mReferences = Other.mReferences;
	++*mReferences;
	return *this;
}
