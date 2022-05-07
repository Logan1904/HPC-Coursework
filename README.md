# 2D Reaction-Diffusion Simulation

## Description
This repository is the implementation of a parallel numerical code to solve a 2D system of partial differential equations, describing a variant of the Barkley Model. This system is a partially chaotic system, evolving to very different states for a small perturbation in the initial conditions.

<img src="https://latex.codecogs.com/svg.image?\frac{\partial&space;u}{\partial&space;t}&space;-\mu_1&space;\nabla^2&space;u&space;=&space;\varepsilon&space;u(1-u)(u-\frac{v&plus;b}{a})" title="https://latex.codecogs.com/svg.image?\frac{\partial u}{\partial t} -\mu_1 \nabla^2 u = \varepsilon u(1-u)(u-\frac{v+b}{a})" />


<img src="https://latex.codecogs.com/svg.image?\frac{\partial&space;u}{\partial&space;t}&space;-\mu_2&space;\nabla^2&space;v&space;=&space;u^3&space;-&space;v" title="https://latex.codecogs.com/svg.image?\frac{\partial u}{\partial t} -\mu_2 \nabla^2 v = u^3 - v" />

The initial conditions are given by:

<img src="https://latex.codecogs.com/svg.image?u(x,y)&space;=&space;&space;&space;&space;&space;\begin{cases}&space;&space;&space;&space;&space;&space;1&space;&&space;\text{if&space;}&space;y&space;>&space;\frac{L_y}{2}\\0&space;&&space;\text{otherwise}\end{cases}&space;&space;" />

<img src="https://latex.codecogs.com/svg.image?v(x,y)&space;=&space;&space;&space;&space;&space;\begin{cases}&space;&space;&space;&space;&space;&space;\frac{a}{2}&space;&&space;\text{if&space;}&space;x&space;<&space;\frac{L_x}{2}\\0&space;&&space;\text{otherwise}\end{cases}&space;&space;" title="https://latex.codecogs.com/svg.image?v(x,y) = \begin{cases} \frac{a}{2} & \text{if } x < \frac{L_x}{2}\\0 & \text{otherwise}\end{cases} " />

The time-step for the evolution of the system is set at <img src="https://latex.codecogs.com/svg.image?\Delta&space;t&space;=&space;0.001&space;" title="https://latex.codecogs.com/svg.image?\Delta t = 0.001 " />

The mesh discretisation is set at  <img src="https://latex.codecogs.com/svg.image?dx&space;=&space;dy&space;=&space;1" title="https://latex.codecogs.com/svg.image?dx = dy = 1" />
