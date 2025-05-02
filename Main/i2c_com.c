#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <iomanip>
#include <fcntl.h>
#include <sys/mman.h>
#include "i2c_com.h"
#include <unistd.h>
void setupDAConverter(int *file, int adapter_nr) {
    char filename[20];
    snprintf(filename, sizeof(filename), "/dev/i2c-%d", adapter_nr);

    *file = open(filename, O_RDWR);
    if (*file < 0) {
        perror("Failed to open the I2C bus");
        exit(EXIT_FAILURE);
    }

    if (ioctl(*file, I2C_SLAVE, AD569X_ADDR) < 0) {
        perror("Failed to acquire bus access or talk to slave");
        exit(EXIT_FAILURE);
    }
}

void write_DAC(int &fd,uint16_t value) {
    uint8_t buff[3];
    buff[0] = COM_BYTE;
    buff[1] = (value >> 8) & 0xFF;
    buff[2] = value & 0xFF;
    if (write(fd, buff, 3) != 3) {
        perror("Failed to write to the I2C bus");
        exit(1);
    }

//    close(fd);  // Always close file descriptors
}
// Digital temperature sensor 
void readTemperature(int fd,uint8_t *buff)
{
//    int fd;
//    setupTempSensor(fd,2);
    uint8_t reg = 0x05; // internal temperature register address
    // send read command to the bus, wait for the ACK
    if (write(fd, &reg, 1) != 1) {
        perror("Failed to write register address");
        exit(1);
    }
    // read from the pointer of temp register
    if(read(fd,buff,2) != 2)
    {
        perror("Failed to read from the i2c bus");
        exit(1);
    }
    return;
}
float convert_temp(uint8_t *buff)
{
    float temp;
    uint8_t UpperByte = buff[0];
    uint8_t LowerByte = buff[1];
    if ((UpperByte & 0x80) == 0x80){ // Ta> T crit
    }
    if ((UpperByte & 0x40) == 0x40) // Ta  > T upper
    {
    }
    if ((UpperByte & 0x20) == 0x20) // Ta  < T lower
    {
    }
    UpperByte = UpperByte & 0x1F; // clear the flags
    if ((UpperByte & 0x10) == 0x10) // Ta  < 0 C
    {
        UpperByte = UpperByte & 0x0F; // clear the sign bit
        temp= 256 - ((UpperByte << 4) + (LowerByte /16.0)); // convert to C
    }
    else  // Ta > 0 C
    {
        UpperByte = UpperByte & 0x0F; // clear the sign bit
        temp = (UpperByte *16) + (LowerByte /16.0); // convert to C
    }
    return temp;
}
void setupTempSensor(int *file, int adapter_nr)
{
    char filename[20];
    snprintf(filename, sizeof(filename), "/dev/i2c-%d", adapter_nr);

    *file = open(filename, O_RDWR);
    if (*file < 0) {
    perror("Failed to open the I2C bus");
        exit(EXIT_FAILURE);
        return;
    }
    if (ioctl(*file, I2C_SLAVE, MCP9808_ADDR) < 0) {
        perror("Failed to acquire bus access or talk to slave");
        exit(EXIT_FAILURE);
        return;
    }
    return;
}
