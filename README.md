
## 3D - Renderer from Scratch
A from-scratch 3D renderer written in C using SDL2. This project implements a basic software rendering pipeline including camera movement, matrix transformations, OBJ loading, and rasterization concepts without using a GPU API (OpenGL/Vulkan).


## Features
- Software-based 3D rendering (CPU rasterizer)
- OBJ model loading
- Perspective projection matrix
- Camera system with yaw/pitch control (FPS-style)
- WASD movement + mouse look
- Basic scene system with multiple objects
- Custom math library (vectors, matrices)


## Project Structure

```text
.
├── assets
│   ├── cube.obj
│   ├── icosaedron.obj
│   ├── octaedron.obj
│   └── sphere.obj
├── bin
│   └── main
├── build
│   ├── camera.o
│   ├── main.o
│   ├── math.o
│   ├── math_utils.o
│   ├── object.o
│   ├── obj_loader.o
│   ├── renderer.o
│   └── scene.o
├── include
│   ├── camera.h
│   ├── config.h
│   ├── math_utils.h
│   ├── object.h
│   ├── obj_loader.h
│   ├── renderer.h
│   └── scene.h
├── Makefile
└── src
    ├── camera.c
    ├── main.c
    ├── math_utils.c
    ├── object.c
    ├── obj_loader.c
    ├── renderer.c
    └── scene.c
```


## Build 
### Requirements 
- gcc
- SDL2 

### Compile 
```bash
$ make
```
### Run
```bash
$ cd /bin
$ ./main
```

