# Toon Shading for 3D Models

For this project, I looked at some of the research done by Ken-ichi Anjyo,
Shuhei Wemler, and William Baxter. They created a tool for artists which
allows them to set and tweak parameters for toon shading on objects in 3D
environments. Some of these parameters influence the shape and color of the
highlights on an object as well as the shading. For my own endeavors, I mainly
wanted to just implement some of the properties introduced in their product
to build from the ground up my own implementation of toon shading.

After looking at the paper, I saw how the researchers were developing their
method of toon shading and decided to try something similar with a lot of the
intricacies stripped out.

## Fragment Shader Values

First, I simply tried to limit the number of colors the fragment shader was allowed
to emit. Each color is represented by 3 values for RGB, each one consisting of a float
from 0.0 to 1.0. By multiplying these by some value, taking its floor, and diving it again,
I forced the shader to only create specific values spaced equally apart from each other.
In some parts of the model, it does create an effect where the shades get darker much more
distinctly but it also inntroduces colors that shouldn't be there. The smaller the number
I used to multiply the worse the effect, but if it were too large, barely any effect would
be visible. Look at folders ``pics/frag7``, ``pics/frag10``, and ``pics/frag3``

## Gemotery Shader Values

My next approach was to simply go to the geometry shader and instead of allowing interpolation
of the colors along every triangle of the mesh, I just force the program to choose the color
determined by a single vertex of the triangle. This creates very hard edges in color, but they
appear all over the mesh, and in especially round objects, such as fingers, the colors switch
back and forth very quickly. It doesn't create a smooth, large area for the color there, it bascially
changes for each triangle. Check out ``pics/vert3`` and ``pics/vert10`` to see this.

## Lighting Position Manipulation

I wanted to use a similar technique but this time, I would take the position of a vertex on the mesh,
and I would perform a floor function much like the one in my first attempt so that many nearby vertices
would have their positional parameters change to the same position. That way, every vertex in a
certain cubic area would have the same lighitng properties added to it. From this, I was hoping
I would get closer to my intended effect. I did not. While a lot of the details on the models face
have become obscured and simplified, there are still gradients on different parts of the model
which I thought would be eliminated using this method. Visuals are in ``pics/vf``.

## Luminance

A technique that was brought to my attention was the idea of having something like a pallete of
all the possible colors the model can use to shade and having the shaders choose strictly from those.
I wanted to see if I could do something similar, but limiting the shade of tints for each color,
and then applying them in the right lighting scenarios on the model. Basically, there would be
white, black, and a set of 3 or 4 grays in between, and these would represent the possible
lumincance for each color. So when a specific part of the mesh is going through the shader,
the lighting scenario will determine which white, black or gray will go "on top" of the base color,
hopefully rendering an end effect similar to predetermining 5 ot 6 highlight or shade colors
for each different color seen on the mesh. I represent the pure luminance on all the parts of the
mesh in ``pics/lum``. Then I show the pure diffuse colors, so I know what the luminance values will
be layed on top of. These can be seen in ``pics/diffuse``. By combining these two, I get something
that is admittedly better than the original renderings (in ``pics/normal``), but not quite what
I wanted, especially in terms of getting harder edges between colors.

## Fragment Shader Color and Luminance

So, I had the brilliant idea of combining my luminance method with my earlier fragment color
limitation method, because the luminance was based on the pure diffuse colors I wanted and the
fragment color manipulation method had the hard edges I wanted. A lot of the model is very 
close to what I envisioned for this project, but there are still glaring problems, which you
can see in ``pics/fraglumdif8``. Some of the white and gray colors are way too pronounced,
especially if you look at the hands of the model. And while the red lighting on her head looks
kind of cool, I'm not sure if that's the appropriate color it should be protraying given the
current light parameters. If I had more time to improve on this project, not only would I
focus on figuring those out, but I would so if there's a way to have the abrupt color changes
happen somewhere inside the triangles rather than at the edges. I feel as though this would
be a very difficult problem to solve, which is why I didin't attempt it this time around.

# Acknowledgement 

This bone animation code is based on the skinning project written by
Randall Smith for 2015 Spring Graphics Course.

The PMD parser library is written by
[itsuhane](https://github.com/itsuhane/libmmd), licensed under Boost Software
License.

The author of PMD models is Animasa, you can download the model with the
official editor from his webpage [VPVP](http://www.geocities.jp/higuchuu4/index_e.htm).

[Tweakable light and shade for cartoon animation](http://dl.acm.org/citation.cfm?doid=1124728.1124750)

[Calculating the Perceived Brightness of a Color](http://www.nbdtech.com/Blog/archive/2008/04/27/Calculating-the-Perceived-Brightness-of-a-Color.aspx)
