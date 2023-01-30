using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using dracowrapper;

namespace TestApp
{
    internal class Program
    {
        static void Main(string[] args)
        {
            var decoder = new GltfDecoder();
            var res = decoder.DecodeFromFileToScene(@"E:\\in.glb");
            var scene = res.Value();
            DracoCompressionOptions options = new DracoCompressionOptions();
            SceneUtils.SetDracoCompressionOptions(options, scene);
            var encoder = new GltfEncoder();
            encoder.EncodeSceneToFile(scene, @"E:\\Test.gltf");
        }
    }
}
