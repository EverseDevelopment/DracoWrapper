#pragma once

#include <vcclr.h>
#include "draco/core/status.h"

#using <System.dll>

using namespace System;

namespace dracowrapper {

	public ref class Status {
	public:
		// Allocate the native object on the C++ Heap via a constructor
		Status(draco::Status* status) : m_Impl(status) {}

		// Deallocate the native object on a destructor
		~Status() { delete m_Impl; }

	protected:
		// Deallocate the native object on the finalizer just in case no destructor
		// is called
		!Status() { }

	public:

	private:
		draco::Status* m_Impl;
	};
}