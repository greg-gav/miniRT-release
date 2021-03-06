# miniRT
Minimal implementation of raytracing using C and mlx for window management  

![spheres rt mix](samples/spheres_mix.png)

## Usage
```
./miniRT [scene file .rt]
```

## Run
```
git clone git@github.com:greg-gav/miniRT-release.git
cd miniRT-release && make 
./miniRT scenes/sphere.rt
```


## Features :
* Objects : ``sphere`` ``plane`` ``cylinder`` ``cone``
* General : ``camera`` ``scene file`` ``Phong reflection`` ``checkerboard`` 
* Extra : ``multiple lights`` ``colored lights`` ``materials`` ``transparency``


## Information
Some scene files provided for reference in scenes/ directory  

## More Examples

### Mixing colors 
![color rt mix](samples/color_mix.png)

### Sample materials 
![materials rt mix](samples/materials.png)

### Hard shadows 
![shadows rt mix](samples/shadows.png)

### Basic shapes 
![simple rt mix](samples/simple_mix.png)

### Columns scene 
![columns rt mix](samples/columns.png)

### Some reflections 
![reflections rt mix](samples/some_reflections.png)

### Some transparency 
![transparent rt mix](samples/transparent_sphere.png)
