#include "draco/io/gltf_encoder.h"

#include "scene.h"

#include <vcclr.h>
#include <msclr/marshal_cppstd.h>
#include "draco/io/file_reader_factory.h"
#include "draco/io/file_writer_factory.h"
#include "file_reader.h"
#include "file_writer.h"

#using <System.dll>

using namespace System;

namespace dracowrapper {

	public ref class GltfEncoder {
	public:
		// Allocate the native object on the C++ Heap via a constructor
		GltfEncoder() : m_Impl(new draco::GltfEncoder) {
			draco::FileWriterFactory::RegisterWriter(UD_FileWriter::Open);
		}

		// Deallocate the native object on a destructor
		~GltfEncoder() { delete m_Impl; }

	protected:
		// Deallocate the native object on the finalizer just in case no destructor
		// is called
		!GltfEncoder() { delete m_Impl; }

	public:

		Status^ EncodeSceneToFile(Scene^ scene, String^ filename) {
			std::string str = msclr::interop::marshal_as<std::string>(filename);
			draco::Scene* sc = scene->GetRaw();
			draco::Status status = m_Impl->EncodeFile<draco::Scene>(*sc, str);
			return gcnew Status(&status);
		}

	private:
		draco::GltfEncoder* m_Impl;
	};
}