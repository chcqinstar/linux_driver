#include <fcntl.h>
#include <linux/string.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
// ledtest /dev/100ask_led on; ledtest /dev/100ask_led off

int main(int argc, char **argv) {
  int fd;
  char status;
  if (argc != 3) {
    printf("Usage :%s <dev> <on|off>\n", argv[0]);
    printf("eg: %s /dev/100ask_led on\n", argv[0]);
  }

  // open
  fd = open(argv[1], O_RDWR);
  if (fd < 0) {
    printf("err：open failed\n");
    return -1;
  }

  // write
  if (strcmp(argv[2], "on") == 0) {
    status = 1;
    write(fd, &status, 1);
  } else if (strcmp(argv[2], "off") == 0) {
    status = 0;
    write(fd, &status, 1);
  } else {
    printf("err:wrong parameter,please enter on|off\n");
  }

  return 0;
}