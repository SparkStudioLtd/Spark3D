#include "pch.h"

class Obj {
public:
	std::any m_Handle;
	template<typename T> T get() {
		return std::any_cast<T>(this->m_Handle);
	};
	template<typename T> void set(T clazz) {
		this->m_Handle = clazz;
	}
};