#ifndef MESTIERE_MEM_H
#define MESTIERE_MEM_H

#include <Muzzle.h>

#ifndef MS_MALLOC
    #define MS_MALLOC(size) MZ_MALLOC(size)
#endif

#ifndef MS_CALLOC
    #define MS_CALLOC(num, size) MZ_CALLOC(num, size)
#endif

#ifndef MS_FREE
    #define MS_FREE(ptr) MZ_FREE(ptr)
#endif

#ifndef MS_REALLOC
    #define MS_REALLOC(ptr, size) MZ_REALLOC(ptr, size)
#endif

#endif // MESTIERE_MEM_H
