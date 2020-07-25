#include <iostream>
#include "dlist.h"
#include <sstream>

using namespace std;

class LRUCache {
private:
    int mem_size; // size of memory
    int *memory;
    struct block {
        int address; // its address in memory
        int data;
    };
    Dlist<block> cache;
    int cur_cache_size; // current length of `cache`
    int max_cache_size; // maximum length of `cache`
    static bool compare(const block *a, const block *b);
    // EFFECTS: returns true if two blocks have the same address

    bool hit_read(int address, block *new_block) {
        Dlist<block> new_cache;
        block *medium;
        bool hit_result = false;
        while (!cache.isEmpty()) {
            medium = cache.removeFront();
            if (medium->address == address) {
                new_block->data = medium->data;
                hit_result = true;
            } else {
                new_cache.insertBack(medium);
            }
        }
        cache = new_cache;
        return hit_result;
    }
    // EFFECTS: return whether hit and modifies cache as well

    bool hit_write(int address, block *new_block) {
        Dlist<block> new_cache;
        block *medium;
        bool hit_result = false;
        while (!cache.isEmpty()) {
            medium = cache.removeFront();
            if (medium->address == address) {
                hit_result = true;
            } else {
                new_cache.insertBack(medium);
            }
        }
        cache = new_cache;
        return hit_result;
    }
    // EFFECTS: return whether hit and modifies cache as well
public:
    LRUCache(int cache_size, int memory_size); // constructor
    // Initialize `cur_cache_size`, `max_cache_size`, `memory`
    // Initialize all elements in `memory` to 0
    ~LRUCache(); // destructor
    int read(int address);

    // EFFECTS: returns data corresponding to address,
    // 0 <= address < mem_size;
    // if address is out of bound, throws an exception
    //
    // if hit,
    // removes this block and insert it to the front;
    // returns `data`;
    // if miss,
    // if `cur_cache_size` equals to `max_cache_size`,
    // removes the last (least recently used) block
    // in the `cache`;
    // writes data in the last block
    // to the corresponding address in `memory`;
    // if `cur_cache_size` < `max_cache_size`,
    // increment `cur_cache_size` by 1;
    // reads `data` of `address` from `memory`,
    // inserts the block with `address` and `data`
    // to the front of `cache`;
    // returns `data`
    void write(int address, int data);

    // EFFECTS: writes data to address, 0 <= address < mem_size
    // if address is out of bound, throws an exception
    //
    // if hit,
    // removes this block from list,
    // writes `data` to this block,
    // and inserts this block to the front;
    // if miss,
    // if `cur_cache_size` equals to `max_cache_size`,
    // removes the last (least recently used) block
    // in the `cache`;
    // writes data in the last block
    // to the corresponding address in `memory`;
    // if `cur_cache_size` < `max_cache_size`,
    // increment `cur_cache_size` by 1;
    // inserts the block with `address` and `data`
    // to the front of `cache`
    void printCache();

    // EFFECTS: prints the cache in given format
    void printMem();
    // EFFECTS: prints the memory in given format
};

LRUCache::LRUCache(int cache_size, int memory_size) : mem_size(memory_size), cur_cache_size(0),
                                                      max_cache_size(cache_size) {
    memory = new int[memory_size];
    int i = 0;
    for (i = 0; i < memory_size; i++) {
        memory[i] = 0;
    }
}

LRUCache::~LRUCache() {
    delete[] memory;
}

bool LRUCache::compare(const block *a, const block *b) {
    return a->address == b->address;
}

int LRUCache::read(int address) {
    block *current_block = new block;
    current_block->address = address;
    current_block->data = memory[address];
    if (!hit_read(address, current_block)) {
        if (cur_cache_size == max_cache_size) {
            block *medium = cache.removeBack();
            memory[medium->address] = medium->data;
        } else {
            cur_cache_size++;
        }
    }
    cache.insertFront(current_block);
    return current_block->data;
}

void LRUCache::write(int address, int data) {
    block *current_block = new block;
    current_block->address = address;
    current_block->data = data;
    if (!hit_write(address, current_block)) {
        if (cur_cache_size == max_cache_size) {
            block *medium = cache.removeBack();
            memory[medium->address] = medium->data;
        } else {
            cur_cache_size++;
        }
    }
    cache.insertFront(current_block);
}

void LRUCache::printCache() {
    block *medium;
    Dlist<block> new_cache;
    while (!cache.isEmpty()) {
        medium = cache.removeFront();
        cout << medium->address << " " << medium->data << endl;
        new_cache.insertBack(medium);
    }
    cache = new_cache;
}

void LRUCache::printMem() {
    int i;
    for (i = 0; i < mem_size; i++) {
        cout << memory[i] << " ";
    }
    cout << endl;
}

int main() {
    int cache_size, mem_size;
    string medium, medium2, empty_check;
    int address, data;
    cin >> cache_size;
    cin >> mem_size;
    //cout<<cache_size<<" "<<mem_size<<endl;
    getline(cin, medium2);
    LRUCache LRU(cache_size, mem_size);
    stringstream medium_string_stream;
    //TODO: EXCEPTION if medium= READ READ
    while (getline(cin, medium)) {
        medium_string_stream.clear();
        medium_string_stream.str(medium);
        medium_string_stream >> medium2;
        if (medium2 == "READ") {
            if (!(medium_string_stream >> address)) {
                cout << "ERROR: Not enough operands" << endl;
            } else {
                if (medium_string_stream >> empty_check) {
                    cout << "ERROR: Too many operands" << endl;
                } else {
                    if (address >= 0 && address < mem_size) {
                        // cout<<"read: "<<medium2<<" "<<address<<endl;
                        cout << LRU.read(address) << endl;
                    } else {
                        cout << "ERROR: Address out of bound" << endl;
                    }
                }
            }
        } else if (medium2 == "WRITE") {
            if (!(medium_string_stream >> address)) {
                cout << "ERROR: Not enough operands" << endl;
            } else {
                if (!(medium_string_stream >> data)) {
                    cout << "ERROR: Not enough operands" << endl;
                } else {
                    if (medium_string_stream >> empty_check) {
                        cout << "ERROR: Too many operands" << endl;
                    } else {
                        if (address >= 0 && address < mem_size) {
                            LRU.write(address, data);
                        } else {
                            cout << "ERROR: Address out of bound" << endl;
                        }
                    }
                }
            }

        } else if (medium2 == "PRINTCACHE") {
            if (medium_string_stream >> empty_check) {
                cout << "ERROR: Too many operands" << endl;
            } else {
                LRU.printCache();
            }
        } else if (medium2 == "PRINTMEM") {
            if (medium_string_stream >> empty_check) {
                cout << "ERROR: Too many operands" << endl;
            } else {
                LRU.printMem();
            }
        } else if (medium2 == "EXIT") {
            break;
        } else {
            cout << "ERROR: Unknown instruction" << endl;
        }
    }

    return 0;
}
