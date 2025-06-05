# Fabry-Perot Etalon Simulation
This project aims to simulate the physics of a Fabry-Perot etalon with a strong focus on physical accuracy and ray-based modeling.

> **Note: At this stage, only the core lens simulation module is complete. The etalon modeling is planned for future updates.**
## Overview
- **Project Goal:** Accurately simulate the interference effects in a Fabry-Perot etalon using precise and modified ray-tracing methods and render it on a screen outputted through a **.ppm** image file.

- **Current Status:** 
  - Lens simulation is fully implemented using physically accurate ray tracing (Snell's Law), not relying on thin-lens or paraxial approximations.
  - All calculations are performed with double-precision for maximum accuracy.

## Features (as of now)
- High-Precision Lens Simulation:

  - Arbitrary spherical lenses supported.

  - Full Snell’s Law calculation at each interface.
  - Path length is also calculated.

- Configurable Parameters:

  - Radii of curvature, thickness, refractive indices, aperature, location of lens incoming ray geometry are all customizable.

## Roadmap
 - ☑️ Physically accurate lens simulation (done)

 - ⬜ Fabry-Perot etalon cavity simulation (upcoming)

 - ⬜ Visualization/plotting of ray paths and transmission spectra

## Usage
Clone the repo and run the MSVS solution.
> No external libraries requried.
> Make config files will be provided at the end of the project.

## Why This Project?
- While studying Applied Optics course in my Academia, my professor showed a computer simulated result of Fabry-Perot etalon. I have always had interest in simulating and modelling physical structures. They always teach me something deeper and completely new about that concept. It is always fun to get new insights you never knew.
- Most online etalon/lens simulators use major approximations (thin lens, paraxial, matrix optics) or even just simple closed form formulas taught in theory. This project is focused on true physical simulation—meaning the results are not table-based or simplified, but derived from fundamental laws at every step.


