#ifndef SPIDEVM_H
#define SPIDEVM_H
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <asm-generic/ioctl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <asm-generic/ioctl.h>

class SpiDev : public QThread
{
  Q_OBJECT
public:
  explicit SpiDev(QObject *parent = 0);
  void run();
  void transfer(int fd, uint8_t const *tx, uint8_t const *rx, size_t len);
signals:

public slots:

private:
  QWaitCondition waitq;
  QMutex mutexq;
};

#endif // SPIDEV_H
