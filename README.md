# physx-c

physx-c is a handcrafted C wrapper over the [PhysX 4.1](https://github.com/NVIDIAGameWorks/PhysX/tree/4.1) SDK.

## Wrapping Philosophy

physx-c aims to faithfully reproduce PhysX by matching terminology for classes/structs, functions, variables, and even function arguments.

physx-c is *not* a higher level abstraction over PhysX nor does it try to simplify or improve any choices made by PhysX.
Instead the aim is expose the SDK through a C API with minimal overhead, in a way that enables people familiar with
PhysX to get started without having to learn anything new, and to enable newcomers to use existing PhysX resources.

With that being said, a few 'utility' functions like `NewCPxSomeClass` are provided, but their usage is completely optional.

### Naming

PhysX uses the naming scheme `PxSomeName`. physx-c simply prefixes a 'C' to make the equivalent C struct `CPxSomeName`.

For example, PhysX classes are usually in the format `PxSomeClass`. physx-c wraps these using C structs in the format `CPxSomeClass` with the
C struct usually holding a `void*` to the C++ class. This general rule is only broken in cases where the C++ equivalent is a simple
value type, like vectors or quaternions. In these cases the C struct holds the actual data (e.g. x,y,z fields) and is converted into
the proper C++ class by physx-c transparently where needed. This helps avoid unnecessary heap allocations.

Similarly, PhysX macros and typedefs can have physx-c parallels, like `PxU32` being matched by `CPxU32`.

### Class Members

Member functions of classes (aka methods) are wrapped in the format `CPxSomeClass_funcName`, where 'funcName' matches the name
used by PhysX. A pointer to the `CPxSomeClass` struct is always taken as the first argument, with the rest of the arguments matching PhysX.

Member variables are accessed through getters and setters (where available) in the format `CPxSomeClass_get_myVar`/`CPxSomeClass_set_myVar`.
Similar to methods, a pointer to the `CPxSomeClass` struct is always taken as the first argument.

### Allocations

physx-c uses `physx::PxDefaultAllocator` for *all* allocations through the `CPxAlloc`/`CPxDealloc` macros defined in `PxDefaultAllocator.h`. If you would like to use a custom allocator then you can change the header to add your own implementation.

## Usage

By default, physx-c builds into a single `physx-c.dll` file which then loads the needed PhysX DLLs at startup.

To use it simply add the `include` folder to your includes and make sure `physx-c.dll` and the normal PhysX DLLs (e.g. `PhysX_64.dll`) are
in the same folder (usually in the same folder as your executable).

You can get some prebuilt PhysX DLLs from the [PhysX](https://github.com/NVIDIAGameWorks/PhysX/tree/4.1) repo, or you can build the source from the original PhysX repo, or from the releases on this [repo](https://github.com/bloeys/physx-builder).

To see a real-world usage of physx-c, you can checkout [physx-go](https://github.com/bloeys/physx-go) for an example of how to use physx-c
to provide a PhysX wrapper for a different programming language (Go in this case).

## Features

The absolute core features of PhysX have all been wrapped, which includes scenes, collision shapes, raycasts, rigid bodies, visual debugger, and simulations, among others.

Some of the things that have not been wrapped include:

- Joints (planned)
- Articulations
- Vehicles
- Character controller
- Serialization
- Simulation Statistics

PRs are welcome!
