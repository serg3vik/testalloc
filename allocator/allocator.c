
#include <stdint.h>
#include <stdbool.h>

//-----------------------------------------------------------------------------

#define CHUNK_SIZE          (256)
#define POOL_SIZE_CHUNKS    (32)
#define POOL_SIZE           (POOL_SIZE_CHUNKS * CHUNK_SIZE)

//-----------------------------------------------------------------------------

typedef struct {
    uint8_t *data;
    bool     free;
} chunk_t;

//-----------------------------------------------------------------------------

static uint8_t mem_pool[POOL_SIZE];
static chunk_t mem_chunks[POOL_SIZE_CHUNKS];

//=============================================================================
//
//=============================================================================
void init(void) {
    int i;
    for (i = 0; i < POOL_SIZE_CHUNKS; i++) {
        chunk_t *chunk = &mem_chunks[i];
        chunk->data = &mem_pool[i * CHUNK_SIZE];
        chunk->free = true;
    }
}

//=============================================================================
//
//=============================================================================
void *alloc_chunk(void) {
    int i;
    for (i = 0; i < POOL_SIZE_CHUNKS; i++) {
        chunk_t *chunk = &mem_chunks[i];
        if (chunk->free == true) {
            chunk->free = false;
            return (void*)(chunk->data);
        }
    }
    return NULL;
}

//=============================================================================
//
//=============================================================================
void free_chunk(void *ptr) {
    int i;
    for (i = 0; i < POOL_SIZE_CHUNKS; i++) {
        chunk_t *chunk = &mem_chunks[i];
        if (chunk->data == ptr) {
            chunk->free = true;
        }
    }
    return;
}
