# Grimoire

Grimoire is an experimental Git-based package manager written in C++.

Instead of relying on a central package registry, Grimoire summons a project
straight from a Git repository, optionally checks out a tag or commit, and
builds CMake projects from source.

## Requirements

- CMake 3.20 or newer
- A C++17 compiler
- Git

## Build

```bash
cmake -S . -B build
cmake --build build
```

This creates the `grimoire` executable in `build/`.

## Summon a project

```bash
./build/grimoire summon https://github.com/jarro2783/cxxopts.git
```

To summon a specific branch, tag, or commit:

```bash
./build/grimoire summon https://github.com/fmtlib/fmt.git 11.2.0
```

Grimoire will:

1. Clone the repository if it has not been summoned before.
2. Fetch updates when a local clone already exists.
3. Check out the requested Git ref, when one is supplied.
4. Configure the project with CMake in Release mode.
5. Build the project using the available CPU cores.

## Current behavior

This is an early prototype. It supports repositories containing a top-level
`CMakeLists.txt` and currently stores cloned source directories in
`~/sources/<package>` and builds in `~/build/<package>`.

It does not yet install executables, resolve dependencies, track installed
packages, or remove packages. A future version will use a managed
`~/.grimoire` directory, a `spell.toml` manifest, and commands such as
`banish`, `scry`, and `freeze`.

## Safety

Summoning a repository runs its CMake configuration and build commands. Only
summon repositories you trust, especially while this prototype has no sandbox
or signature verification.

## License

See [LICENSE](LICENSE).
