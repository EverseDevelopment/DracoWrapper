# Draco C# Wrapper

<p align="center">
<img width="350px"  src="https://s3.amazonaws.com/everse.assets/GithubReadme/draco3d-vert.svg" />
</p>

# Nuget Package
[Nuget Package](https://www.nuget.org/packages/Draco_transcoder)

# About
This a wrapper project to use google's [Draco Compression](https://github.com/google/draco) algorithm with C#

# How to use

```C#
            var decoder = new GltfDecoder();
            var res = decoder.DecodeFromFileToScene(fileToCompress);
            var scene = res.Value();
            DracoCompressionOptions options = new DracoCompressionOptions();
            SceneUtils.SetDracoCompressionOptions(options, scene);
            var encoder = new GltfEncoder();
            encoder.EncodeSceneToFile(scene, fileToCompressTemp);
```

When using the NuGet on .Net Core, an error like this "An attempt was made to load a program with an incorrect format" in that case, you can invoke the DLL directly to make it work

```
public class NonCollectibleAssemblyLoadContext : AssemblyLoadContext
    {
        public NonCollectibleAssemblyLoadContext() : base(isCollectible: false)
        {
        }
    }

var loadContext = new NonCollectibleAssemblyLoadContext();
var assemblyPath = @"C:\location\of\your\dll\DracoWrapper.dll";
Assembly mixedModeAssembly = loadContext.LoadFromAssemblyPath(assemblyPath);

var gltfDecoderType = mixedModeAssembly.GetType("dracowrapper.GltfDecoder");
var gltfDecoderInstance = Activator.CreateInstance(gltfDecoderType);

var decodeFromFileToSceneMethod = gltfDecoderType.GetMethod("DecodeFromFileToScene");
var res = decodeFromFileToSceneMethod.Invoke(gltfDecoderInstance, new object[] { fileToCompress });
var resType = res.GetType();
var valueMethod = resType.GetMethod("Value");
var scene = valueMethod.Invoke(res, null);

var dracoCompressionOptionsType = mixedModeAssembly.GetType("dracowrapper.DracoCompressionOptions");
var dracoCompressionOptionsInstance = Activator.CreateInstance(dracoCompressionOptionsType);

var sceneUtilsType = mixedModeAssembly.GetType("dracowrapper.SceneUtils");
var setDracoCompressionOptionsMethod = sceneUtilsType.GetMethod("SetDracoCompressionOptions");
setDracoCompressionOptionsMethod.Invoke(null, new object[] { dracoCompressionOptionsInstance, scene });

var gltfEncoderType = mixedModeAssembly.GetType("dracowrapper.GltfEncoder");
var gltfEncoderInstance = Activator.CreateInstance(gltfEncoderType);
var encodeSceneToFileMethod = gltfEncoderType.GetMethod("EncodeSceneToFile");
encodeSceneToFileMethod.Invoke(gltfEncoderInstance, new object[] { scene, fileToCompressTemp });

```

## Contributors
This repo is primarily managed by [E-verse](https://www.e-verse.co/) and by [People Like You™](https://github.com/EverseDevelopment/DracoWrapper/pulse).

## Help improve this repo
If you're interested in contributing to this repo, just submit a [pull request](https://github.com/EverseDevelopment/DracoWrapper/pulls) or a [feature request](https://github.com/EverseDevelopment/DracoWrapper/issues).

## About us ##

We are an international mix of AEC professionals, product designers, and software developers. We work together to transform construction requirements into accurate and partnership-driven technological solutions.

<p align="center">
    <a href="https://www.e-verse.com/">
    <img src="https://s3.amazonaws.com/everse.assets/GithubReadme/e-verse_logo_no+slogan.jpg" align="center">
    </a>
</p>
