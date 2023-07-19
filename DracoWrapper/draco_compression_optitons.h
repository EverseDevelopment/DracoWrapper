#pragma once

#include <vcclr.h>
#include "draco/compression/draco_compression_options.h"

#using <System.dll>

using namespace System;

namespace dracowrapper {

	public ref class SpatialQuantizationOptions {
	public:
		// Allocate the native object on the C++ Heap via a constructor
		explicit SpatialQuantizationOptions(int quantization_bits)
			: m_Impl(new draco::SpatialQuantizationOptions(quantization_bits)) {
		}

		// Deallocate the native object on a destructor
		~SpatialQuantizationOptions() { }

	protected:
		// Deallocate the native object on the finalizer just in case no destructor
		// is called
		!SpatialQuantizationOptions() { }

	public:

		void SetQuantizationBits(int quantization_bits) {
			m_Impl->SetQuantizationBits(quantization_bits);
		}

		SpatialQuantizationOptions^ SetGrid(float spacing) {
			m_Impl = &m_Impl->SetGrid(spacing);
			return this;
		}

		const int quantization_bits() { return m_Impl->quantization_bits(); }
		const float spacing() { return m_Impl->spacing(); }

		draco::SpatialQuantizationOptions* GetRaw() {
			return m_Impl;
		}

	private:
		draco::SpatialQuantizationOptions* m_Impl;
	};

	public ref struct DracoCompressionOptions
	{
		int compression_level = 7;  // compression level [0-10], most=10, least=0.
		SpatialQuantizationOptions quantization_position{ 11 };
		int quantization_bits_normal = 8;
		int quantization_bits_tex_coord = 10;
		int quantization_bits_color = 8;
		int quantization_bits_generic = 8;
		int quantization_bits_tangent = 8;
		int quantization_bits_weight = 8;
		bool find_non_degenerate_texture_quantization = false;
	};
}