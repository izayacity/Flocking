# Flocking
Flocking written in C++ using SFML. Check out Youtube demo at [https://youtu.be/xtSEIrXISDw](https://youtu.be/xtSEIrXISDw).    
<img src="/1.JPG">  
<img src="/2.JPG">  
### Control:

RMouseBtn:	add boids;
Shift+T:	reduce boids;
Ctrl+S:		add separation;
Shift+S:	reduce separation;
Ctrl+C:		add cohesion;
Shift+C:	reduce cohesion;
Ctrl+A:		add align;
Shift+A:	reduce align;
P:		toggle path

### Note:
Used bin-lattice spacial partition for optimization which can allow 500 boids running at around 90fps if the pathing is turned off;  
Steering force includes separation, cohesion, align and pathing. For pathing I used vehicle's steering force but after adding flocking forces, the steering simulation doesn't look any different from a simple arriving AI. If I didn't do those additional calculation, as well as allocate memory in advance rather than each time dynamically, the performance could be improved further.

# References
[Chapter 6 - Autonomous Agents](http://natureofcode.com/book/chapter-6-autonomous-agents/), in The Nature of Code by Daniel Shiffman. Provides well organized explanations and source code (in Processing, a JAVA-like language) for implementing flocking.
