# Array. Simple dynamic vector of pointers.

## Include

    #include "array/pvector.h"

## Macros

**`ZX_ARRAY_PVECTOR_STRUCT(type, prefix)`**

makes struct for array of pointers to elements with type `type`. Name of struct: prefix_array.

For example:

    ZX_ARRAY_PVECTOR_STRUCT(int, integers)

will make struct:

    struct integers_array {
        size_t size;
        size_t capacity;
        int** data;
    };

**`ZX_ARRAY_PVECTOR_HEADER(type, prefix)`**

makes headers of functions for working with structure. `type` and `prefix` should be equal to type and prefix of `ZX_ARRAY_PVECTOR_STRUCT` parameters.

For example:

    ZX_ARRAY_PVECTOR_HEADER(int, integers)

will make headers:

    _Bool
    integers_init_with(struct integers_array *array, size_t start_capacity);
    
    _Bool
    integers_init(struct integers_array *array);
    
    _Bool
    integers_free(struct integers_array *array);
    
    _Bool
    integers_realloc_array(struct integers_array *array);
    
    _Bool
    integers_push(struct integers_array *array, int* value);
    
    int*
    integers_pop(struct integers_array *array, int* value);
    
    _Bool
    integers_popd(struct integers_array *array, int* value);
    
    int*
    integers_get(struct integers_array *array, size_t index);
    
    _Bool
    integers_set(struct integers_array *array, size_t index, int* value);
    
    int*
    integers_change_to(struct integers_array *array, size_t index, int* new_value);
    
    _Bool
    integers_swap(struct integers_array *array, size_t index1, size_t index2);
    
    _Bool
    integers_insert(struct integers_array *array, size_t index, int* value);
    
    int*
    integers_tear(struct integers_array *array, size_t index);
    
    _Bool
    integers_delete(struct integers_array *array, size_t index);

**`ZX_ARRAY_PVECTOR_BODY_FREE(type, prefix, min, before_free_func)`** 

makes body of functions for working with dynamic array of type `type`.
`type` should be equal to type and prefix of `ZX_ARRAY_PVECTOR_STRUCT` parameters.
`prefix` should be equal to type and prefix of `ZX_ARRAY_PVECTOR_STRUCT` parameters.
`min` parameter - means minimal capacity of array. 
`before_free_function` - pointer to function of type `_Bool func(type* value)` witch calls before deleting element of function. Function returns 1 (true) if clearing before deleting is finished successfully.

**`ZX_ARRAY_PVECTOR_BODY(type, prefix, min)`**

the same than `ZX_ARRAY_PVECTOR_BODY_FREE` but `before_free_function` is empty function witch always returns 1 (true).

## Functions

**`_Bool <prefix>_init_with(struct <prefix>_array *array, size_t start_capacity)`**

`<prefix>` depends on prefix macros parameter. Initialize array with size of start capacity equals to start_capacity. Returns 1 (true) when finished successfully.

**`_Bool <prefix>_init(struct <prefix>_array *array)`**

`<prefix>` depends on prefix macros parameter. Initialize array with size of start capacity equals to `min` parameter of macros. Returns 1 (true) when finished successfully.

**`_Bool <prefix>_free(struct <prefix>_array *array)`**

`<prefix>` depends on prefix macros parameter. Free all elements of array and array itself. Returns 1 (true) when finished successfully. If you create array dinamically don't forget to free it:

    struct integers_array* arr = malloc(size_of(struct integers_array));
    integers_init(arr)
    
    <...>
    
    integers_free(arr);
    free(arr);

**`_Bool <prefix>_realloc_array(struct <prefix>_array *array)`**

`<prefix>` depends on prefix macros parameter. Realloc array to possible minimum capacity from series min, min\*2, min\*4, min\*8, min\*16... Where `min` is parameter of macros.

**`_Bool <prefix>_push(struct <prefix>_array *array, <type>* value);`**
`<prefix>` and `<type>` depend on prefix macros parameter. Add element at the end of array.

**`<type>* <prefix>_pop(struct <prefix>_array *array, <type>* value);`**
`<prefix>` and `<type>` depend on prefix macros parameter. Tear element from the end of array and returns it.

**`_Bool <prefix>_popd(struct <prefix>_array *array, <type>* value);`**
`<prefix>` and `<type>` depend on prefix macros parameter. Delete element from the end of array.

**`<type>* <prefix>_get(struct <prefix>_array *array, size_t index);`**
`<prefix>` and `<type>` depend on prefix macros parameter. Return point to element from index position. If index position is incorrect, return NULL.

**`_Bool <prefix>_set(struct <prefix>_array *array, size_t index, <type>* value);`**
`<prefix>` and `<type>` depend on prefix macros parameter. Replace to element from index position, deleting old value. Return true if function finished success.

**`<type>* <prefix>_change_to(struct <prefix>_array *array, size_t index, <type>* new_value);`**
`<prefix>` and `<type>` depend on prefix macros parameter. Replace to element from index position. Returns old value if function finished success or NULL in another case.

**`_Bool <prefix>_swap(struct <prefix>_array *array, size_t index1, size_t index2);`**
`<prefix>` and `<type>` depend on prefix macros parameter. Swap two elements in array. Return true if function finished success.

**`_Bool <prefix>_insert(struct <prefix>_array *array, size_t index, <type>* value);`**
`<prefix>` and `<type>` depend on prefix macros parameter. Insert element in array. Return true if function finished success.

**`<type>* <prefix>_tear(struct <prefix>_array *array, size_t index);`**
`<prefix>` and `<type>` depend on prefix macros parameter. Tear element from the index position of array and returns it. Return true if function finished success.

**`_Bool <prefix>_delete(struct <prefix>_array *array, size_t index);`**
`<prefix>` and `<type>` depend on prefix macros parameter. Delete  element from the index position of array and returns it. Return true if function finished success.
