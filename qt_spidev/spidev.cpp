#include "spidevm.h"
#include <QCoreApplication>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
static const char *device = "/dev/spidev1.0";
static uint32_t mode;
static uint8_t bits = 8;
static uint32_t speed = 500000;
static uint16_t delay;
static int verbose;

uint8_t default_tx[] = {
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0x40, 0x00, 0x00, 0x00, 0x00, 0x95,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
	0xF0, 0x0D,
};

uint8_t default_rx[ARRAY_SIZE(default_tx)] = {0, };
char *input_tx;


SpiDev::SpiDev(QObject *parent) :
  QThread(parent)
{

}


void SpiDev::run()
{
  int ret = 0;
  int fd;
  uint8_t *tx;
  uint8_t *rx;
  int size;

  fd = open(device, O_RDWR);
  if (fd < 0)
          printf("can't open device\n");

  /*
   * spi mode
   */


  /*
   * bits per word
   */
  ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
  if (ret == -1)
          printf("can't set bits per word\n");

  ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
  if (ret == -1)
          printf("can't get bits per word\n");

  /*
   * max speed hz
   */
  ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
  if (ret == -1)
          printf("can't set max speed hz\n");

  ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
  if (ret == -1)
          printf("can't get max speed hz\n");

  printf("spi mode: 0x%x\n", mode);
  printf("bits per word: %d\n", bits);
  printf("max speed: %d Hz (%d KHz)\n", speed, speed/1000);


  while(1)
    {
        mutexq.lock();
        waitq.wait(&mutexq,1000);
        transfer(fd, default_tx, default_rx, sizeof(default_tx));
        mutexq.unlock();
        break;
    }
        close(fd);
}


void SpiDev::transfer(int fd, uint8_t const *tx, uint8_t const *rx, size_t len)
{
	int ret;

	struct spi_ioc_transfer tr ={
		tr.tx_buf = (unsigned long)tx,
		tr.rx_buf = (unsigned long)rx,
		tr.len = len,
		tr.delay_usecs = delay
		//.speed_hz = 0,//speed,
		//.bits_per_word = bits,
};

	ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);

	if (ret < 1)
		printf("can't send spi message\n");

}


