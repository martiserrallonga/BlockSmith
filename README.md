# BlockSmith

## Init submodules
`git submodule update --init --recursive`



## VS Code setup
- Copy and paste config/.vscode in the root of your project

### Install Recomended extensions
- Check .vscode/extensions.json

### Install Ninja throw Chocolatey
- Open PowerShell (Administrator) (Shortcut: Win + X)

`choco install ninja`



## Visual Studio setup
Open the generated solution (.sln) file
BlockSmith -> Set as Startup Project

### Generate project
`cmake -G "Visual Studio 16 2019" -B ./build`

`cmake -G "Visual Studio 17 2022" -B ./build`
