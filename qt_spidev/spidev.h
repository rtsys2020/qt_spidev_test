#ifndef SPIDEV_H
#define SPIDEV_H
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <QThread>
#include <Qmutex>
#include <QWaitCondition>
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
