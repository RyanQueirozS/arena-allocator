#define ARENA_ALLOCATOR_IMPL
#define ARENA_DEBUG
#include "../arena.h"

#define SACI_TEST_IMPLEMENTATION
#include "deps/saci-test/saci-testing.h"

static void TestArenaInit(void);

int main(void) {
    {
        TestArenaInit();
    }
    saci_Test_End();
}

static void TestArenaInit(void) {
    {
        Arena  arena;
        size_t arenaCapacity = 1024;
        ArenaInit(&arena, arenaCapacity);
        SACI_TEST_ASSERT((ArenaRemaining(&arena) == arenaCapacity),
                         "Should have correct arena capacity when initialized");
    }
}
