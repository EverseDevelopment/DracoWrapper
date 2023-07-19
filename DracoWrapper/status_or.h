#pragma once

#include <vcclr.h>
#include "draco/core/status_or.h"

#using <System.dll>

using namespace System;

namespace dracowrapper {

	generic <typename T>
	public ref class StatusOr {
	public:
		// Allocate the native object on the C++ Heap via a constructor
		StatusOr(T status) : m_Impl(status) {}

		// Deallocate the native object on a destructor
		~StatusOr() { delete m_Impl; }

	protected:
		// Deallocate the native object on the finalizer just in case no destructor
		// is called
		!StatusOr() { delete m_Impl; }

	public:

		T Value() {
			return m_Impl;
		}

	private:
		T m_Impl;
	};
}