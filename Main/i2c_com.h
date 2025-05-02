#ifndef i2c_com_h
#define i2c_com_h
#define AD569X_ADDR 0x4c       // Replace with your actual I2C address
#define COM_BYTE    0x30       // Command: Write and update DAC
// MCP9808 (temp sensor)
#define MCP9808_ADDR 0x1f
// digital temperature sensor
#define TEMP_REG 0x05

#ifdef __cplusplus
extern "C" {
#endif
void setupDAConverter(int *file, int adapter_nr);
void write_DAC(int &fd,uint16_t value);
void readTemperature(int fd,uint8_t *buff);
float convert_temp(uint8_t *buff);
void setupTempSensor(int *file, int adapter_nr);
#ifdef __cplusplus
}
#endif
#endif
