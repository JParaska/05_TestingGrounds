# 05_TestingGrounds
A Hunger Games inspired FPS with large outdoor terrains, advanced AI, basic networking, pickups, skeletal meshes, checkpoints &amp; more.

This project was created following [Unreal Engine Developer Course | Udemy](https://www.udemy.com/unrealcourse/).

## Game Development Document

1. Concept
* Player is a contestant in an entertainment game
* Survive as many testing grounds as possible
* Try to reach the end (if there is any)
* Use force or stealth
2. Rules
* Try to pass testing ground undetected
* If detected, clear the area
* You're scored on how many areas you pass
3. Requirements
* Testing grounds scenery
* Props and textures
* A rigged character
* Gun and projectile
4. Challenges
* Procedural generation of grounds
* AI

## Lecture list (Commit)

1. Testing Grounds Introduction
1. Testing Grounds GDD (Initial Commit)
1. Using Git LFS (Enabled Git LFS and added FPS content)
1. Marketing &amp; Markdown (Create README.md)
1. Using `git clean` to revert project (TG05 Using git clean to revert project)
1. First person character overview (TG06 First person character overview, adjusting arena)
1. The third person character (TG07 Adding third person character and navmesh)
1. Introducing AI behaviour trees (TG08 Introducing AI behaviour trees)
1. Introducing AI blackboard data (TG09 Introducing AI blackboard data)
1. Target points and patrol routes (TG10 Target points and patrol routes)
1. Using any actor for waypoint (TG11 Using any actor for waypoint)
1. Options for grouping actors
1. Blueprint Behaviour tree tasks
1. Modular arithmetic & cycles (TG14 Patroling using behavior tree task and multiple target points)
1. Performance profiling 101
1. C++ AIBehavior tree tasks
1. Reading blackboard data in C++
1. The consequences of inheritance
1. Converting blueprint to C++ (TG19 Converting patrolling to C++)
1. Composition over inheritance (TG20 Creating patrol route component)
1. Talking head: What we've covered so far
1. How to delete a C++ class (TG22 Deleting Patrolling Guard class, clean-up)
1. Instanced materials (TG23 Creating instanced materials)
1. Introducing AI perception
1. OnTargetPerceptionUpdated event (TG25 Simple AI perception sight)
1. AI hearing perception in Unreal (TG26 Simple AI perception hearing)
1. The animation starter pack (TG27 Adding animation starter pack)
1. Changing a character's animation (TG28 Changing a character's animation)
1. Customising a character blueprint (TG29 Customising a character blueprint)
1. Sub behaviour trees (TG30 Sub behaviour trees)
1. Talking head - Introducing Sam
1. Talking head - Refactoring superpowers
1. Simplifying our project (TG33 Refactoring content structure)
1. Renaming & moving CPP (TG34 Renaming & moving CPP, deleting old content files)
1. Solution: Renaming & moving CPP (TG35 Refactoring source folder structure)
1. Holding a gun with skeletal sockets (TG36 Added gun mesh to third person character, removing trash folder)
1. Understanding animation blueprints
1. Creating Animation state machines
1. Movement blend spaces (TG39 Introduciton to animations)
1. Offset animations (TG40 Creating aditive aim offset animations)
1. Aiming blend spaces offsets (TG41 Aiming blend spaces offsets)
1. Rotating with SetFocalPoint() (TG42 Rotating with SetFocalPoint())
1. Character movement vs. rotation
1. Control rotation for aim (TG44 Control rotation for aim)
1. Behavior tree decorators (TG45 Behavior tree decorators)
1. Behaviour tree services
1. Tweaking AI behaviour
1. Debugung AI behaviour (TG48 Adding "suspicious" behaviour)
1. Refactoring to a Gun actor
1. Attaching actors to components (TG50 Moving Fire logic to gun)
1. Configuring the gun (TG51 Configuring the gun)
1. Moving files from LFS to Git (Moved all assets into Static sub-folder; TG52 Updated .gitattributes to track only Static sub-folder)
1. To LFS or Not to LFS? (TG53 Moved some assets into non LFS folder)
1. Child actor components (TG54 Giving new gun to 3rd person character)
1. Introduction to Inverse kinematics
1. Inverse kinematics with animations (TG55 IK for hands on gun)
1. Compare blueprints with diffs
1. Boolean blending for aim states (TG57 Boolean blending for aim states)
1. Adding firing animations (TG58 Adding firing animations additive)
1. Animation notify events (TG59 Fire anim notify)