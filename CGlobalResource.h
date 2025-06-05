#pragma once

template <class T>
class CGlobalResource
{
public:
	CGlobalResource() {
		T::Open();
	}
	~CGlobalResource() {
		T::Close();
	}
};

