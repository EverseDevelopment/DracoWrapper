#pragma once

#include <vcclr.h>
#include "draco/scene/scene.h"

#using <System.dll>

using namespace System;

namespace dracowrapper {

	public ref class Scene {
	public:
		// Allocate the native object on the C++ Heap via a constructor
		Scene() : m_Impl(new draco::Scene) {}
		Scene(draco::Scene* scene) : m_Impl(new draco::Scene) {
			m_Impl->Copy(*scene);
		}

		// Deallocate the native object on a destructor
		~Scene() { delete m_Impl; }

	protected:
		// Deallocate the native object on the finalizer just in case no destructor
		// is called
		!Scene() { delete m_Impl; }

	public:

		draco::Scene* GetRaw() {
			return m_Impl;
		}

	private:
		draco::Scene* m_Impl;
	};
}