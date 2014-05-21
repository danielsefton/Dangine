Dangine

=======


Setup
-------

1. Clone the repo
2. Download the [Dependencies](https://dl.dropboxusercontent.com/u/31008648/Dependencies.zip) and copy the folder into the root
3. Copy the DLLs from Dependencies/bin/Release and Dependencies/bin/Debug into bin/Release and bin/Debug respectively
4. Open scripts/VC2010/Dangine.sln
5. If you have a different version of Visual Studio, you may need to convert the project
6. Navigate to Project -> Properties -> Debugging -> Working Directory
7. Set it to $(ProjectDir)/../../../bin/$(Configuration)
8. Debug -> Start Debugging

Usage
-------

First we initialise the engine:

```
mRenderSystem = DG_NEW(RenderSystem, mLinearArena)();
mRenderSystem->initialise(pWindowHandle);

// Specify the number of entities to pre-allocate
mWorld = DG_NEW(World, mLinearArena)(mLinearArena, 200);

// Create systems
SystemManager& systemManager = mWorld->getSystemManager();
mCameraSystem = systemManager.addSystem<CameraSystem>();
mCameraSystem->setRenderSystem(mRenderSystem);
mMeshSystem = systemManager.addSystem<MeshSystem>();
mMeshSystem->setRenderSystem(mRenderSystem);
mLightSystem = systemManager.addSystem<LightSystem>();
mLightSystem->setRenderSystem(mRenderSystem);

// Create input
mInput = DG_NEW(Input, mLinearArena)((unsigned long)pWindowHandle);
```

Then we can create a scene. The following code demonstrates how to add a transform and
mesh component to an entity.

```
Transform* trans = DG_NEW(Transform, mLinearArena);
trans->position = vmVector3(0, 0, 0);
Mesh* mesh = DG_NEW(Mesh, mLinearArena);
mesh->file = "MyMesh.x";
mWorld->getEntity(0).addComponent(trans);
mWorld->getEntity(0).addComponent(mesh);
```

Components are allocated with the linear allocator, initial data is filled, and the
components are added to a pre-allocated entity.

We then initialise all the systems:

```
mWorld.getSystemManager().initialiseAll();
```

For manipulating a component with a system, here's an example of how to move the
camera forward:

```
mCameraSystem->moveForward(mWorld->getEntity(0), moveSpeed);
```