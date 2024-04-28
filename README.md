# BlockSmith

## Setup
Install Visual Studio with vcpkg.
Go to Visual Studio Installer: "Tools->Get Tools and Features".
Check that **vcpkg package manager** is installed.
Open a Visual Studio terminal.
```
vcpkg integrate install
```

copy the output line that contains your vcpkg buildsystem path:
`CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/2022/Professional/VC/vcpkg/scripts/buildsystems/vcpkg.cmake"`

# Set vcpkg toolchain in the project
Go to "Project->CMake Settings" to generate a CMakePresets file.
Set the CMAKE_TOOLCHAIN_FILE with your vcpkg buildsystem path

```
{
  "version": 2,
  "configurePresets": [
    {
      "name": "default",
      "generator": "Ninja",
      "binaryDir": "${sourceDir}/build",
      "cacheVariables": {
        "CMAKE_TOOLCHAIN_FILE": "enter/your/vcpkg/path"
      }
    }
  ]
}
```

Generate your CMake project. vcpkg will install all the required dependencies.
