#include <YSI\y_malloc>

#define Dynamic:%1; Alloc:%1 = calloc(2);

#define add_slot.%0(); DYNAMIC_ARRAYS_add_slot(%0);

#define pop_slot.%0(); DYNAMIC_ARRAYS_pop_slot(%0);

#define set.%0(%1,%2); DYNAMIC_ARRAYS_set(%0, %1, %2);
        
#define get.%0(%1); DYNAMIC_ARRAYS_get(%0, %1);


stock DYNAMIC_ARRAYS_add_slot(Alloc:mem)
    return realloc(mem, 1);

stock DYNAMIC_ARRAYS_set(Alloc:mem, index, value)
    return mset(mem, index, value);

stock DYNAMIC_ARRAYS_get(Alloc:mem, index)
    return mget(mem, index);

stock DYNAMIC_ARRAYS_pop_slot(Alloc:mem)
    return unalloc(mem, 1);


stock realloc(Alloc:mem, size)
{
    new old = Malloc_SlotSize(mem);
    new Alloc:save = malloc(old);
    
    for(new i = 0; i <= old; ++i)
        mset(save, i, mget(mem, i));

    free(mem);

    mem = calloc(size+old);
    for(new i = 0; i <= old; ++i)
        mset(save, i, mget(save, i));

    free(save);
    return 1;
}

stock unalloc(Alloc:mem, size)
{
    new old = Malloc_SlotSize(mem);
    new Alloc:save = malloc(old-size);
    
    for(new i = 1; i <= old-size; ++i)
        mset(save, i, mget(mem, i));

    free(mem);

    mem = calloc(old-size);
    for(new i = 1; i <= old-size; ++i)
        mset(save, i, mget(save, i));

    free(save);
    return 1;
}