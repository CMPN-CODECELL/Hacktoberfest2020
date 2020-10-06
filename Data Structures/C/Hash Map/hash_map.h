#ifndef HASHMAP_H
#define HASHMAP_H

typedef union NodeInfo {
    int intValue;
    char *stringValue;
    double realValue;
    void *pointerValue;
} NodeInfo;

typedef char* HashmapKey;

typedef NodeInfo HashmapValue;

typedef struct HashMapEntry {
    HashmapKey key;
    HashmapValue value;
    struct HashMapEntry *next;
    unsigned int hash;
} HashMapEntry;

typedef struct HashMap {
    int size;
    HashMapEntry **table;
} HashMap;

HashMap hashmap_create(int size);

unsigned int hashmap_hashCode(HashmapKey key);

void hashmap_put(HashMap map, HashmapKey key, HashmapValue value);

HashmapValue hashmap_get(HashMap map, HashmapKey key, HashmapValue defaultValue);

HashmapValue hashmap_forceGet(HashMap map, HashmapKey key);

int hashmap_isEmpty(HashMap map);

int hashmap_containsKey(HashMap map, HashmapKey key);

int hashmap_size(HashMap map);

HashMapEntry hashmap_remove(HashMap map, HashmapKey key);

void hashmap_clear(HashMap map);

void hashmap_removeMap(HashMap *map);

HashMapEntry* hashmap_entryArr(HashMap map);

#endif //HASHMAP_H