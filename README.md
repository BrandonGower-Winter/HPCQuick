# Dream

A 2D game engine designed for Developers with no artistic skills or abilities.

## Table of Contents:

1. Prerequisites
2. Building & Running Dream
3. Memory Management
4. ToDo

## Prerequisites

* Requires GLFW to be installed. (WILL ADD TO LOCAL BUILD AT SOME POINT)
* Relevant Graphics Drivers
* Currently on tested on linxu Ubuntu 18.X


## 2. Building & Running Dream:

To build:
	
	. Dream.sh build

## 3. Memory Management

Dream requires users to use its memory manager when creating/destroying new objects. You can either use the memory manager directly with MemoryManager.allocate() or indirectly through the ECS [See X]. Dream currently offers 5 Types of Allocators for you to use. You can also create your own Allocator by inheriting Dream::Core::Allocators::Allocator [See 3.0].

If nullptr is ever returned by an allocation, it means that there isn't enough memory left for that specific allocation.

### 3.0 Allocator.cpp:

This is the base Allocator class. Inherit from it if you wish to create a custom allocator.

### 3.1 LinearAllocator.cpp:

This allocator stores memory in a linear fashion. Each allocation follows the previous. The linear allocator does not allow for deallocations, instead clear() must be used to clear the entire block of memory.

### 3.2 ListAllocator.cpp

The ListAllocator uses a linked list to allocate memory. Use allocate() and deallocate() as normal.

### 3.3 PoolAllocator.cpp

The PoolAllocator allows for quick allocations of a given Type T. Use allocate() instead of allocate(size) as the size is already known beforehand.

### 3.4 ProxyAllocator.cpp

Is an allocator that points to another allocator. Used for debugging if multiple systems use a single allocator. The proxy allocator will allow for logging of each systems memory usage.

## 4. ToDo:

* Test Allocators
* Memory Manager
* Entities
* Components
* Systems
