#ifndef CEMUHOOK_EMBOSS_CRC32_H_
#define CEMUHOOK_EMBOSS_CRC32_H_

#include <memory>
#include <vector>

namespace cemuhook_emboss {

class Crc32Engine {
 public:
  virtual ~Crc32Engine() = default;
  static std::unique_ptr<Crc32Engine> New();

  virtual uint32_t Foo(const std::vector<uint8_t>& bytes) = 0;
};

}  // namespace cemuhook_emboss

#endif  // CEMUHOOK_EMBOSS_CRC32_H_
