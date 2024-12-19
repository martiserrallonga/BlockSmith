# BlockSmith

## Visual Studio setup

### 1. Install Visual Studio with vcpkg.
Go to Visual Studio Installer: **Tools->Get Tools and Features**.
Check that "vcpkg package manager" is installed.

### 2. vcpkg setup
Open a Visual Studio terminal.
```
vcpkg integrate install
```

Copy the output line that contains your vcpkg buildsystem path:
```
CMake projects should use: "-DCMAKE_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/2022/Professional/VC/vcpkg/scripts/buildsystems/vcpkg.cmake"
```

Set vcpkg toolchain in the project:
Go to **Project->CMake Settings** and set the CMake Toolchain File with your vcpkg buildsystem path.

### 3. Generate the CMake project
Go to **Project->Delete Cache and Reconfigure** to force CMake generation.
All the required dependencies should be installed by vcpkg.