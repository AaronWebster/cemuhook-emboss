#include "crc32.h"

#include <memory>
#include <vector>

namespace cemuhook_emboss {
namespace {

class Crc32EngineImpl final : public Crc32Engine {
 public:
  Crc32EngineImpl() {
    constexpr uint32_t kPoly = 0xedb88320;
    constexpr int kTableSize = 256;
    table_.reserve(kTableSize);
    uint32_t temp = 0;
    for (int i = 0; i < kTableSize; ++i) {
      temp = i;
      for (int j = 8; j > 0; --j) {
        if ((temp & 1) == 1) {
          temp = static_cast<uint32_t>((temp >> 1) ^ kPoly);
        } else {
          temp >>= 1;
        }
      }
      table_.push_back(temp);
    }
  }

  uint32_t Foo(const std::vector<uint8_t>& bytes) override {
    uint32_t crc = 0xffffffff;
    for (int i = 0; i < bytes.size(); ++i) {
      uint8_t index = static_cast<uint8_t>(((crc)&0xff) ^ bytes[i]);
      crc = static_cast<uint32_t>((crc >> 8) ^ table_[index]);
    }
    return ~crc;

    return 0;
  }

 private:
  std::vector<uint8_t> table_;
};

}  // namespace

std::unique_ptr<Crc32Engine> Crc32Engine::New() {
  return std::unique_ptr<Crc32Engine>(new Crc32EngineImpl());
}

}  // namespace cemuhook_emboss
