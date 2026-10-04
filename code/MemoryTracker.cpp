#include "MemoryTracker.h"
#include <Windows.h>
#include <iostream>
#include <mutex>
#include <thread>

Debug::MemoryTracker::~MemoryTracker() {
	Stop();
}

void Debug::MemoryTracker::Stop() {
	if (m_thread.joinable()) {
		m_running = false;
		m_thread.join();
		if (m_new_output != nullptr) {
			fclose(m_new_output);
			FreeConsole();
		}
	}
}

/// <summary>
/// The multithreading part.
/// </summary>
void Debug::MemoryTracker::Update() {
	while (m_running) {
		std::lock_guard<std::mutex> lock(m_queue_mutex);
		system("cls");
		for (std::unique_ptr<IMemory>& p_memory : m_queue) {
			std::cout << p_memory->What();
		}
		std::this_thread::sleep_for(m_interval_milli);
	}
}
