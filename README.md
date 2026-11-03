# Icy Towers Game

[Gameplay video](https://www.youtube.com/watch?v=9t0N6fHQx3o)

## Build and run on Windows

Install Visual Studio 2022 with the **Desktop development with C++** workload. From this folder, install the matching SFML 2.6.2 SDKs:

```powershell
powershell -ExecutionPolicy Bypass -File .\setup-sfml.ps1
```

Open `sfml.sln` in Visual Studio, select **Debug | x64** (or **Release | x64**), then build and run with F5. Win32 configurations are supported as well. The build copies SFML DLLs beside the executable, and the debugger starts in this folder so `graphics/`, `fonts/`, and `sounds/` can be found.

The SDK is installed under `.sfml/`, which Git ignores. The script downloads the official Visual C++ 2022 SFML archives and checks their SHA-256 hashes. You can also provide an existing SDK root as the `SFMLRoot` MSBuild property; it must contain `x64/SFML-2.6.2` and/or `Win32/SFML-2.6.2`.
