#include "MyAssert.h"
#include "UniquePtr.h"

int main() {
  UniquePtr<int> ptr1(new int(67));
  UniquePtr<int> ptr2(new int(1337));
  ASSERT(*ptr1.get() == 67);
  ptr1 = std::move(ptr2);
  ASSERT(*ptr1 == 1337);
  UniquePtr<int> ptr3(new int(43));
  ptr1.reset(new int(77));
  ASSERT(*ptr1 == 77);
  ptr1.swap(ptr3);
  ASSERT(*ptr1.get() == 43);
  int *bare_ptr = ptr1.release();
  ASSERT(*bare_ptr == 43);
}
