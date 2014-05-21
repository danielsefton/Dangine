//------------------------------------------------------------------------------
// Created by Daniel Sefton
// Timing code based on OGRE's implementation
/*
Copyright (c) 2000-2012 Torus Knot Software Ltd

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
*/
//------------------------------------------------------------------------------

#ifndef GAME_H
#define GAME_H

#include "Platform/Prerequisites.h"

#include "Util/Helper/Timer.h"

//------------------------------------------------------------------------------
namespace Dangine {
//------------------------------------------------------------------------------
struct FrameStats
{
	float lastFPS;
	float avgFPS;
	float bestFPS;
	float worstFPS;
	unsigned long bestFrameTime;
	unsigned long worstFrameTime;
	size_t triangleCount;
	size_t batchCount;
};
//------------------------------------------------------------------------------
struct FrameEvent
{
	Real timeSinceLastEvent;
	Real timeSinceLastFrame;
};
//------------------------------------------------------------------------------
/** Indicates the type of event to be considered by calculateEventTime(). */
enum FrameEventTimeType
{
	FETT_ANY = 0, 
	FETT_STARTED = 1, 
	FETT_QUEUED = 2, 
	FETT_ENDED = 3, 
	FETT_COUNT = 4
};
//------------------------------------------------------------------------------
class Game
{
public:
	Game(Config& rConfig);
	~Game();

	bool initialiseClient(void* pHandle);
	bool initialiseServer();
	void shutdown();
	void updateClient();
	void updateServer();

	const FrameStats& getStats() const { return mStats; }
	
private:
	void updateLogic(const Real& elapsed);
	void updateGraphics();
	void updateStats();
	void resetStatistics();

	/// Contains the times of recently fired events
	typedef std::deque<unsigned long> EventTimesQueue;
	EventTimesQueue mEventTimes[FETT_COUNT];

	/**
	 * Internal method for calculating the average time between recently fired events.
	 *
	 * @param now The current time in ms.
	 * @param type The type of event to be considered.
	 */
	Real calculateEventTime(unsigned long now, FrameEventTimeType type);

	/** Update a set of event times (note, progressive, only call once for each type per frame) */
	void populateFrameEvent(FrameEventTimeType type, FrameEvent& evtToUpdate);

	bool mInitialised;
	Input* mInput;
	World* mWorld;
	HeapArea mHeapArea;
	LinearArena mLinearArena;
	System* mCameraSystem;
	System* mMeshSystem;
	System* mLightSystem;
	System* mSoundSystem;
	RenderSystem* mRenderSystem;
	RakClientServer* mRakClientServer;
	SceneManager* mSceneManager;
	PhysXWorld* mPhysXWorld;
	PhysXScene* mPhysXScene;

	FrameStats mStats;
	Timer* mTimer;
	unsigned long mLastSecond;
	unsigned long mLastTime;
	size_t mFrameCount;
	Real mFrameSmoothingTime;
	Config& mConfig;

}; // class Game
//------------------------------------------------------------------------------
} // namespace Dangine
//------------------------------------------------------------------------------

#endif // GAME_H