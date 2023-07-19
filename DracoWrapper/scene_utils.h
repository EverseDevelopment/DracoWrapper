#include "scene.h"

#include <vcclr.h>
#include <msclr/marshal_cppstd.h>
#include "draco_compression_optitons.h"
#include "draco/scene/scene_utils.h"

#using <System.dll>

using namespace System;

namespace dracowrapper {

	public ref class SceneUtils {
	public:
		// Allocate the native object on the C++ Heap via a constructor
		SceneUtils() {
		}

		// Deallocate the native object on a destructor
		~SceneUtils() { }

	protected:
		// Deallocate the native object on the finalizer just in case no destructor
		// is called
		!SceneUtils() { }

	public:
		static void SetDracoCompressionOptions(DracoCompressionOptions^ options, Scene^ scene) {
			draco::DracoCompressionOptions opt;
			opt.compression_level = options->compression_level;
			opt.quantization_position = *(options->quantization_position.GetRaw());
			opt.quantization_bits_normal = options->quantization_bits_normal;
			opt.quantization_bits_tex_coord = options->quantization_bits_tex_coord;
			opt.quantization_bits_color = options->quantization_bits_color;
			opt.quantization_bits_generic = options->quantization_bits_generic;
			opt.quantization_bits_tangent = options->quantization_bits_tangent;
			opt.quantization_bits_weight = options->quantization_bits_weight;
			opt.find_non_degenerate_texture_quantization = options->find_non_degenerate_texture_quantization;

			draco::Scene* sc = scene->GetRaw();

			draco::SceneUtils::SetDracoCompressionOptions(&opt, sc);
		}


	private:

	};
}