# 3D-Render-Engine

This is a simple CPU raytracer that renders a scene with a few objects using Phong or Cook-Torrance shading.

# Dependencies 

The code depends on the following libraries:

- GLM (OpenGL Mathematics)
- OpenMP
- libjpeg

# Usage

The program must be launched with three arguments: the width and height of the output image, and the name of the output file. For example:
```
./ISICG_ISIR_RT_2020.exe 800 600 output.jpg
```

# Scene description

The scene currently contains the following objects :
- A plane with a green checkboard procedural texture
- A 3D object with a triangle mesh to represent a Bunny with Cook-Torrance material
- Four metaballs with a Phong material
- A sphere light
- A transparent sphere
- A miror sphere

The result is :
![image](https://user-images.githubusercontent.com/66914830/228835652-c1572e22-45ea-4f1c-a8af-9c5520d05ca2.png)

# Other results
You can tweak the parameters to your need. For example you could :
- Change the roughness of the Cook-Torrance materials :
![imageCookTorrance](https://user-images.githubusercontent.com/66914830/228836295-d67de1a8-6c65-411d-9881-8647f04fa573.jpg)

- Change the refractive index of the transparent materials : 
![imageRefraction](https://user-images.githubusercontent.com/66914830/228836522-499e7a8d-4a77-4d3c-84d2-2360c853204a.jpg)

- Change how much a miror object is reflective :
![imageReflexionn](https://user-images.githubusercontent.com/66914830/228836757-bb51560e-ea47-4c6a-972a-b7203fb7b4ff.jpg)
