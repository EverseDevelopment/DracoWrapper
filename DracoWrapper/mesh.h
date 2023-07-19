#pragma once

#include <vcclr.h>
#include "draco/mesh/mesh.h"

#using <System.dll>

using namespace System;

namespace dracowrapper {

	public ref class Mesh {
	public:
		// Allocate the native object on the C++ Heap via a constructor
		Mesh() : m_Impl(new draco::Mesh) {}
		Mesh(draco::Mesh* mesh) : m_Impl(mesh) {}

		// Deallocate the native object on a destructor
		~Mesh() { delete m_Impl; }

	protected:
		// Deallocate the native object on the finalizer just in case no destructor
		// is called
		!Mesh() { delete m_Impl; }

	public:

	private:
		draco::Mesh* m_Impl;
	};
}