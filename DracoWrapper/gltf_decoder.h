#include "draco/io/gltf_decoder.h"

#include "status_or.h"
#include "mesh.h"
#include "scene.h"

#include <vcclr.h>
#include "draco/mesh/mesh.h"
#include <msclr/marshal_cppstd.h>
#include "draco/io/file_reader_factory.h"
#include "file_reader.h"

#using <System.dll>

using namespace System;

namespace dracowrapper {

	public ref class GltfDecoder {
	public:
		// Allocate the native object on the C++ Heap via a constructor
		GltfDecoder() : m_Impl(new draco::GltfDecoder) {
			draco::FileReaderFactory::RegisterReader(UD_FileReader::Open);
		}

		// Deallocate the native object on a destructor
		~GltfDecoder() { delete m_Impl; }

	protected:
		// Deallocate the native object on the finalizer just in case no destructor
		// is called
		!GltfDecoder() { delete m_Impl; }

	public:

		StatusOr<Mesh^>^ DecodeFromFile(String^ file_name) {
			std::string str = msclr::interop::marshal_as<std::string>(file_name);
			draco::StatusOr<std::unique_ptr<draco::Mesh>> status = m_Impl->DecodeFromFile(str);
			return gcnew StatusOr<Mesh^>(gcnew Mesh(status.value().get()));
		}

		StatusOr<Scene^>^ DecodeFromFileToScene(String^ file_name) {
			std::string str = msclr::interop::marshal_as<std::string>(file_name);
			draco::StatusOr<std::unique_ptr<draco::Scene>> status = m_Impl->DecodeFromFileToScene(str);
			return gcnew StatusOr<Scene^>(gcnew Scene(status.value().get()));
		}

	private:
		draco::GltfDecoder* m_Impl;
	};
}