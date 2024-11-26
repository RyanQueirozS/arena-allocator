#define ARENA_ALLOCATOR_IMPL
#define ARENA_DEBUG
#include "../arena.h"

#define SACI_TEST_IMPLEMENTATION
#include "deps/saci-test/saci-testing.h"

void Test_ArenaInit(void);
void Test_ArenaAlloc();
void Test_ArenaAlignedAllocation();
void Test_ArenaReset(void);
void Test_ArenaDeletion(void);

int main(void) {
    {
        Test_ArenaInit();
        Test_ArenaAlloc();
        Test_ArenaAlignedAllocation();
        Test_ArenaReset();
        Test_ArenaDeletion();
    }
    saci_Test_End();
}

// Test cases
void Test_ArenaInit(void) {
    Arena  arena;
    size_t arenaCapacity = 1024;
    ArenaInit(&arena, arenaCapacity);

    SACI_TEST_ASSERT(arena.capacity == arenaCapacity, "Arena should have correct capacity after initialization.");
    SACI_TEST_ASSERT(arena.offset == 0, "Arena offset should be 0 after initialization.");
    SACI_TEST_ASSERT(arena.data != NULL, "Arena data pointer should not be NULL after initialization.");

    ArenaDelete(&arena);
}

void Test_ArenaAlloc(void) {
    Arena  arena;
    size_t arenaCapacity = 1024;
    ArenaInit(&arena, arenaCapacity);

    void* allocation = ArenaAlloc(&arena, 512);
    SACI_TEST_ASSERT(allocation != NULL, "ArenaAlloc should return a valid pointer.");
    SACI_TEST_ASSERT(arena.offset == 512, "Arena offset should increase by allocation size.");
    SACI_TEST_ASSERT(ArenaRemaining(&arena) == (arenaCapacity - 512), "Arena remaining size should decrease by allocation size.");

    ArenaDelete(&arena);
}

void Test_ArenaAlignedAllocation(void) {
    Arena  arena;
    size_t arenaCapacity = 1024;
    ArenaInit(&arena, arenaCapacity);

    size_t alignment  = 16;
    void*  allocation = ArenaAllocAligned(&arena, 128, alignment);

    SACI_TEST_ASSERT(allocation != NULL, "ArenaAllocAligned should return a valid pointer.");
    SACI_TEST_ASSERT(((size_t)allocation % alignment) == 0, "Allocated pointer should be aligned to the specified alignment.");
    SACI_TEST_ASSERT(arena.offset > 0, "Arena offset should increase after aligned allocation.");
    SACI_TEST_ASSERT(ArenaRemaining(&arena) == (arenaCapacity - arena.offset), "Arena remaining size should decrease by aligned allocation size.");

    ArenaDelete(&arena);
}

void Test_ArenaReset(void) {
    Arena  arena;
    size_t arenaCapacity = 1024;
    ArenaInit(&arena, arenaCapacity);

    ArenaAlloc(&arena, 512);
    SACI_TEST_ASSERT(arena.offset == 512, "Arena offset should increase after allocation.");

    ArenaReset(&arena);
    SACI_TEST_ASSERT(arena.offset == 0, "Arena offset should reset to 0 after ArenaReset.");
    SACI_TEST_ASSERT(ArenaRemaining(&arena) == arenaCapacity, "Arena remaining size should be full capacity after reset.");

    ArenaDelete(&arena);
}

void Test_ArenaDeletion(void) {
    Arena  arena;
    size_t arenaCapacity = 1024;
    ArenaInit(&arena, arenaCapacity);

    ArenaDelete(&arena);
    SACI_TEST_ASSERT(arena.data == NULL, "Arena data pointer should be NULL after ArenaDelete.");
    SACI_TEST_ASSERT(arena.capacity == 0, "Arena capacity should be 0 after ArenaDelete.");
    SACI_TEST_ASSERT(arena.offset == 0, "Arena offset should be 0 after ArenaDelete.");
}
