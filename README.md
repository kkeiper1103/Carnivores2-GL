# Carnivores2-GL
Carnivores 2 Reimplementation in OpenGL 3.3

Builds with CMAKE, links to SDL2 and OpenGL. Currently, the build system only thinks of Windows since I haven't had time to make it work on Linux yet. Should be rather straightforward with some if blocks.

Uses Nuklear for GUI, my own code for loading the Carnivores 2 data files, glad for loading OpenGL 3+, and SDL2 for cross platform windowing, glm for math operations and stb_image for a few image loading calls.

/app is meant to house files specific to the implementation of carnivores 2, like Character, CarnivoresApp, Terrain, etc
/core is meant to house utility classes, like Model, Texture, Entity, State, etc

