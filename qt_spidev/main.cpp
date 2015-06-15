#include <QCoreApplication>
#include "spidevm.h"

int main(int argc, char *argv[])
{
  QCoreApplication a(argc, argv);
SpiDev spi;
	spi.start();
	spi.wait();
  return a.exec();
}
