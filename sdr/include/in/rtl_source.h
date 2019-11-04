#ifndef IN_RTL_SOURCE_H
#define IN_RTL_SOURCE_H

#include <string>
#include <memory>
#include "rtl-sdr.h"
#include "basic/block.h"
#include "ring_buffer.h"


extern "C" void rtlsdr_callback(unsigned char *buf, uint32_t len, void *ctx);

class rtl_source : public producer<int16_t> {
 private:
  rtlsdr_dev_t * dev;
  uint32_t dev_index;

  void work() override;
  void stop_worker() override;
  void stop() override;

  friend void rtlsdr_callback(unsigned char *buf, uint32_t len, void *ctx);

 public:
  rtl_source(uint32_t dev_index, int freq, int sampling_rate);
  std::string get_type() const override { return "rtl_source"; }
};

#endif  /* IN_RTL_SOURCE_H */
