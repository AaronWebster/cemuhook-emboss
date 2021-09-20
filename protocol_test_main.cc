#include <arpa/inet.h>
#include <errno.h>
#include <linux/errqueue.h>
#include <linux/ethtool.h>
#include <linux/ip.h>
#include <linux/net_tstamp.h>
#include <linux/netlink.h>
#include <linux/sockios.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <poll.h>
#include <resolv.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/uio.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/numbers.h"
#include "absl/strings/str_cat.h"
#include "absl/strings/str_format.h"
#include "absl/strings/str_split.h"
#include "glog/logging.h"
#include "protocol.emb.h"

ABSL_FLAG(std::string, ip, "127.0.0.1", "Protocol host IPv4 address.");
ABSL_FLAG(uint16_t, port, 26760, "Protocol host port.");

namespace cemuhook_emboss {
namespace {

int Main() {
  const std::string ip = absl::GetFlag(FLAGS_ip);
  CHECK(!ip.empty()) << "Missing required '--ip'";

  const uint16_t port = absl::GetFlag(FLAGS_port);
  CHECK_GT(port, 0) << "Missing required '--port'";

  int fd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
  PCHECK(fd > 0) << "Could not open socket.";

  sockaddr_in address{};
  address.sin_family = AF_INET;
  PCHECK(inet_aton(ip.c_str(), &address.sin_addr) > 0);
  address.sin_port = htons(port);

  PCHECK(bind(fd, reinterpret_cast<const sockaddr*>(&address),
              sizeof(address)) != -1)
      << "Could not bind socket.";

  close(fd);
  return EXIT_SUCCESS;
}

}  // namespace
}  // namespace cemuhook_emboss

int main(int argc, char** argv) { return cemuhook_emboss::Main(); }
