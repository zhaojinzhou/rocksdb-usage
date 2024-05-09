#include <iostream>

#include "rocksdb/advanced_cache.h"
#include "rocksdb/cache.h"
struct value{
    value(){}
    value(int v):v(v){}
    ~value() { std::cout << "delete " << v << '\n'; }
    int v;
};
void delete_fn(void* k, rocksdb::MemoryAllocator* allocator) {
    // std::cout << "delete" << (*(int*)k) << "\n";
    delete (value*)k;
}

int main() {
  auto cache = rocksdb::NewLRUCache(500, -1, true);
  rocksdb::Cache::Handle* handle = nullptr;
  const rocksdb::Cache::CacheItemHelper kNoopCacheItemHelper(rocksdb::CacheEntryRole::kMisc, delete_fn);
  for (int i = 0; i < 100; i++) {
    auto v = new value(i);
    rocksdb::Slice key((const char*)v, 4);
    // std::cout <<" input " << *v <<'\n';
   auto res=  cache->Insert(key, v, &kNoopCacheItemHelper, 1, nullptr, rocksdb::Cache::Priority::HIGH);
   if (!res.ok()) {
     std::cout << "error" << res.ToString() << '\n';
   }
    // std::cout << " input" << *v << '\n';
    auto handle = cache->Lookup(key);

    if (handle != nullptr) {
      int* v = (int*)cache->Value(handle);
      std::cout << " output" << *v << '\n';
      cache->Release(handle);
    } else {
      std::cout << " not found\n";
    }
  }

  std::cout << "sadasdad\n";
}