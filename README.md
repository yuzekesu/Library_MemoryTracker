# Description
A Windows-only library to recreate the live-expression experience. Let the user to observe the code in runtime without pausing the program.

# How to Use
The minimum requirement is to make sure the `<Windows.h>` is reachable as a header. 
Afterwards:
1. Include the `MemoryTracker.h`.
2. Create `Memory` type variables with the variable you want to observe.
3. Create `MemoryTracker` type variable with the interval and the `Memory`:s as argument to start the monitoring.
4. A cmd window will pop up with the variables you specified earlier.
5. Enjoy.

# Remark
Implement `operator std::string() const;` if you want your own class "trackable". `explicit` version works well too.

# Demo
![demo](./image/demo.png) 

<img width="1228" height="292" alt="image" src="https://github.com/user-attachments/assets/f4563c2f-6ea8-428f-9bb7-39f04170c8f5" />


