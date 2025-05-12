# miniRT

This is a simple ray tracer built as part of the 42 school curriculum. It uses the school's graphical library, **minilibx** (MacOS-only version, included in the `mlx` folder). Most of the code is inspired by the book series [Ray Tracing in One Weekend](https://raytracing.github.io/).

---

## Features
- Real-time scene modification
- Support for basic objects: spheres, planes, and cylinders
- Adjustable camera and lighting
- Configurable window size

---

## Getting Started

### Prerequisites
- macOS
- `make` (build tool)

### Installation
Clone the repository:
```bash
git clone https://github.com/mc-localhost/miniRT.git
cd miniRT
```

### Build
Run `make` to compile:
```bash
make
```

### Usage
Run with a map from /rt folder:
```bash
./miniRT rt/new_sphere.rt
```

## How to use
Use keys to modify the scene in real-time (may be slow for bigger resolutions):

| OBJECT | KEY | ACTION |
| --- | --- | --- |
|| `Esc` | Exit |
|*Camera*| `W`, `A` | Move along Z axis |
|| `S`, `D` | Move along X axis |
|| `Q`, `E` | Move along Y axis |
|| `↑`, `←`, `→`, `↓` | Rotate the camera |
|*Object*| `+`, `-` | Choose an object (sphere, plane, cylinder) |
|| `[`, `]` | Change cylinder / sphere diameter |
|| `;`, `'` | Change cylinder height |
|| `I`, `K` | Move along Z axis |
|| `J`, `L` | Move along X axis |
|| `U`, `O` | Move along Y axis |
|| `8`, `2`, `4`, `6` | Rotate the object |
|*Light*| `T`, `G` |  Move along Z axis |
|| `F`, `H` | Move along X axis |
|| `R`, `U` | Move along Y axis |

## Configuration

To change the window size, modify the following lines in `include/minirt.h`:

```c
# define WIDTH 600
# define HEIGHT 300