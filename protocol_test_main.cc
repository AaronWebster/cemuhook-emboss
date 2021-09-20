#include <arpa/inet.h>
#include <errno.h>
#include <linux/errqueue.h>
#include <linux/ethtool.h>
#include <linux/net_tstamp.h>
#include <linux/netlink.h>
#include <linux/sockios.h>
#include <net/if.h>
#include <netinet/in.h>
#include <poll.h>
#include <resolv.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
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
#include "protocol.emb.h"

ABSL_FLAG(std::string, host, "localhost:26760",
          "Protocol host in the form IP:PORT.");

namespace cemuhook_emboss {
namespace {

int Main() {
  const std::pair<std::string, std::string> ip_and_port =
      absl::StrSplit(absl::GetFlag(FLAGS_host), ':');

  const std::string& ip = ip_and_port.first;
  ABSL_RAW_CHECK(!ip.empty(), "Missing required '--host'");

  int port = -1;
  ABSL_RAW_CHECK(absl::SimpleAtoi(ip_and_port.second, &port), "Missing port");

  std::cout << "Connecting to " << ip << ":" << port << std::endl;

  int fd = socket(AF_INET, SOCK_STREAM | SOCK_CLOEXEC, 0);
  ABSL_RAW_CHECK(fd > 0, strerror(errno));

  sockaddr_in address{};
  address.sin_family = AF_INET;
  ABSL_RAW_CHECK(inet_aton(ip.c_str(), &address.sin_addr) > 0, strerror(errno));
  address.sin_port = htons(port);

  ABSL_RAW_CHECK(
      connect(fd, reinterpret_cast<sockaddr*>(&address), sizeof(address)) >= 0,
      strerror(errno));

  close(fd);

  return EXIT_SUCCESS;
}

}  // namespace

}  // namespace cemuhook_emboss

int main(int argc, char** argv) { return cemuhook_emboss::Main(); }
