# Grimoire

```text
 ▄█▀▀▀▀▀█  ░█▀▀▀▀█▄   ▀░█▀ ██▄▀▀▀█▄▀▀▀█▄    ▄█▀▀▀█▄  ▀░█▀  ░█▀▀▀▀█▄    ▄░▀▀▀▀█
██ ▄▄ █▄▄  ██ █▄▄ ██   ██   ██    █    ██  ██ █ ▄ ██  ██   ██ █▄▄ ██  ░  ▄▄▄▄▄
░░ ██ ▄▄▄  ░░  ▓█ ░░   ░░   ░░    ░    ░░  ░░ █▓█ ░░  ░░   ░░  ▓█ ░░  ░░  ▓▒░▒
▒▒ █▀  ▒▒  ▒▒ █▀▀ ▒▒   ▒▒   ▒▒ ░  ▒ ░  ▒▒  ▒▒ █▀  ▒▒  ▒▒   ▒▒ █▀▀ ▒▒  ▒▒▀▀ ▒░█
▓▓     ▓▓  ▓▓▄▄▄▄▓▀    ▓▓   ▓▓ ▒  ▓ ▒  ▓▓  ▓▓     ▓▓  ▓▓   ▓▓▄▄▄▄▓▀   ▓▓ █▓▒░█
▄▄     ▄▄  ▄▄ ▄▄▄ ▄    ▄▄   ▄▄ █▄   ▓  ▄▄  ▄▄     ▄▄  ▄▄   ▄▄ ▄▄▄ ▄   ▄▄ ▀▀▀▀▀
▀▓▄▄▄▄▄▓▓ ▄▓▓▄   ▄▓▓▄ ▄▓▓▄ ▄██▄▀▄▄▄██ ▄██▄  ▀█▄▄▄▓▀  ▄▓▓▄ ▄▓▓▄   ▄▓▓▄  ▀▓▄▄▄▄▓
```

Grimoire is an experimental Git-based package manager written in C++.

Instead of relying on a central package registry, Grimoire summons a project
straight from a Git repository, optionally checks out a tag or commit, and
builds CMake, Cargo, or Makefile projects from source.

## Requirements

- CMake 3.20 or newer
- A C++17 compiler
- Git
- Rust and Cargo, when summoning Cargo projects
- Make, when summoning Makefile projects
- [Glow](https://github.com/charmbracelet/glow) (optional), for rendered README files in `scry`

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
4. Detect `CMakeLists.txt`, `Cargo.toml`, or a conventional Makefile.
5. Build CMake projects in Release mode, Cargo projects with `--release`, or
   Makefile projects with `make`.

## Inspect and remove packages

```bash
./build/grimoire scry cargo-spell
./build/grimoire scry cargo-spell --details
./build/grimoire banish cargo-spell
```

`scry` renders a package README with Glow. It falls back to the raw README in
`less` when Glow is unavailable. Use `--details` to show the recorded source,
Git ref, and build output. `banish` removes only that package's Grimoire-managed
directory.

## Current behavior

This is an early prototype. It supports repositories containing a top-level
`CMakeLists.txt`, `Cargo.toml`, `Makefile`, `makefile`, or `GNUmakefile`.
Grimoire stores each package under `~/.grimoire/packages/<name>/`, with its
Git repository in `source/`, CMake output in `build/`, and metadata in
`state.txt`. Cargo and Makefile builds use the output locations chosen by
those projects.

It does not yet install executables, resolve dependencies, or use package
manifests. Future work can add `spell.toml`, an install prefix, and commands
such as `freeze`.

## Safety

Summoning a repository runs its CMake configuration and build commands. Only
summon repositories you trust, especially while this prototype has no sandbox
or signature verification.

## License

See [LICENSE](LICENSE).
