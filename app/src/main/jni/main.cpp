#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include <string>
#include <map>
#include <list>
#include <jni.h>
#include <dlfcn.h>
#include <stddef.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/syscall.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include <syscall.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <malloc.h>
#include <regex>
#include <bits/getopt.h>
#include <asm/unistd.h>
#include <unistd.h>
#include <asm/fcntl.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <malloc.h>
#include <regex>
#include <bits/getopt.h>
#include <asm/unistd.h>
#include <unistd.h>
#include <asm/fcntl.h>
#include "limits.h"
#include <string.h>
#include <cerrno>
#include <cstring>
#include <climits>
#include "syscall.h"
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <stdlib.h>
#include <syscall.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <jni.h>
#include <dlfcn.h>
#include <android/log.h>
#include <malloc.h>
#include <regex>
#include <bits/getopt.h>
#include <asm/unistd.h>
#include <unistd.h>
#include <asm/fcntl.h>
#include <fcntl.h>
#include <Log.h>
#include <arpa/inet.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <jni.h>
#include <arch.h>
#include <Log.h>
#include <istream>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netpacket/packet.h>
#include <net/ethernet.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netlink/ifaddrs.h>
#include <bionic_netlink.h>

extern "C" {
__inline__ __attribute__((always_inline))  long raw_syscall(long __number, ...);
}

int listmacaddrs(void) {
    struct ifaddrs *ifap, *ifaptr;

    if (myGetifaddrs(&ifap) == 0) {
        for (ifaptr = ifap; ifaptr != NULL; ifaptr = (ifaptr)->ifa_next) {
            char macp[INET6_ADDRSTRLEN];
            if (ifaptr->ifa_addr != nullptr) {
                if (((ifaptr)->ifa_addr)->sa_family == AF_PACKET) {
                    auto *sockadd = (struct sockaddr_ll *) (ifaptr->ifa_addr);
                    int i;
                    int len = 0;
                    for (i = 0; i < 6; i++) {
                        len += sprintf(macp + len, "%02X%s", sockadd->sll_addr[i],
                                       (i < 5 ? ":" : ""));
                    }
                    //LOGE("%s  %s  ",(ifaptr)->ifa_name,macp)
                    if (strcmp(ifaptr->ifa_name, "wlan0") == 0) {
                        LOGD("%s  %s  ", (ifaptr)->ifa_name, macp)
                        freeifaddrs(ifap);
                        return 1;
                    }
                }
            }
        }
        freeifaddrs(ifap);
        return 0;
    } else {
        return 0;
    }
}

void syscallTest() {
    char buffer[256];
    memset(buffer, 0, 256);
    std::string result;
    long fd = raw_syscall(__NR_openat, dirfd, "/sys/devices/soc0/serial_number", O_RDONLY, O_RDONLY);
    while (read(fd, buffer, 1) != 0) {
        result.append(buffer);
    }
    syscall(__NR_close, fd);
    LOGD("serial_number: = %s", result.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_jnihook_MainActivity_getmac(JNIEnv *env, jclass clazz) {
    LOGD("开始测试获取 pid");

    long fd = raw_syscall(172);
    if (fd < 0) {
        LOGD("获取pid 调用失败");
    } else {
        LOGD("fd := %ld", fd);
        LOGD("获取pid 调用成功");
    }

    LOGD("开始测试openat");
    syscallTest();
    LOGD("完成测试openat");

    LOGD("开始测试获取 mac");
    listmacaddrs();
    LOGD("完成测试获取 mac");
}


