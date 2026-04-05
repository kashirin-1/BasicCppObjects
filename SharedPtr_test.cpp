#include "MyAssert.h"
#include "SharedPtr.h"
#include <vector>

int main() {
  int *bair_ptr_1 = new int(64);
  std::vector<SharedPtr<int>> ptrs;
  SharedPtr<int> ptr(new int(67));
  for (int i = 0; i < 1'000'000; i++) {
    ptrs.push_back(ptr);
  }
  ASSERT(ptrs[0].use_count() == ptrs[1].use_count());
  ASSERT(ptrs[0].use_count() == 1'000'001);
  SharedPtr<int> ptr1(new int(67));
  SharedPtr<int> ptr2(ptr1);
  ASSERT(ptr1.use_count() == 2);
  ASSERT(ptr2.use_count() == 2);
  SharedPtr<int> ptr3(std::move(ptr1));
  ASSERT(ptr2.get() == ptr3.get());
  ASSERT(ptr3.use_count() == ptr2.use_count());
  ptr2 = std::move(ptr3);
  ASSERT(ptr2.use_count() == 1);
  ASSERT(*ptr2 == 67);
  return 0;
}
