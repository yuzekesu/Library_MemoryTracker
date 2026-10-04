#pragma once
#include "IMemory.h"
#include "Memory.h"
#include <Windows.h>
#include <atomic>
#include <chrono>
#include <mutex>
#include <thread>
#include <vector>

namespace Debug {
	/// <summary>
	/// Class that creates a terminal and updates the monitored memory in a certain interval.
	/// </summary>
	class MemoryTracker {
	public:
		template <typename ...Memory_T>
		MemoryTracker(unsigned int interval_milli, const Memory_T& ...Memories);
		~MemoryTracker();
		template <typename ...Memory_T>
		void Add(const Memory_T& ...Memories);
		void Stop();
	private:
		void Update();
	private:
		std::atomic_bool m_running = true;
		std::chrono::duration<unsigned int, std::milli> m_interval_milli;
		std::mutex m_queue_mutex;
		std::vector<std::unique_ptr<IMemory>> m_queue;
		std::thread m_thread;
		FILE* m_new_output = nullptr;
	};

	//********************************************************************************************
	//********************************************************************************************
	//********************************************************************************************
	// Template Implementation
	//********************************************************************************************
	//********************************************************************************************
	//********************************************************************************************

/// <summary>
/// Constructor of MemoryTracker. It creates a terminal in a thread and updates the monitored memory in a certain interval. 
/// </summary>
	template<typename ...Memory_T>
	inline MemoryTracker::MemoryTracker(unsigned int interval_milli, const Memory_T& ...Memories) {
		(m_queue.push_back(std::make_unique<Memory_T>(Memories)), ...);
		m_interval_milli = std::chrono::duration<unsigned int, std::milli>(interval_milli);
		if (GetConsoleWindow() == NULL) {
			AllocConsole();
			freopen_s(&m_new_output, "CONOUT$", "w", stdout);
		}
		m_thread = std::thread(&MemoryTracker::Update, this);
	}

	template<typename ...Memory_T>
	inline void MemoryTracker::Add(const Memory_T & ...Memories) {
		std::lock_guard<std::mutex> lock(m_queue_mutex);
		(m_queue.push_back(std::make_unique<Memory_T>(Memories)), ...);
	}
}