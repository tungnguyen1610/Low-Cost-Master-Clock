cmd_src/arm/BB-I2C1-RTC-DS3231.dtbo = cpp -Wp,-MD,src/arm/.BB-I2C1-RTC-DS3231.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.BB-I2C1-RTC-DS3231.dtbo.dts.tmp src/arm/BB-I2C1-RTC-DS3231.dts ; dtc -O dtb -o src/arm/BB-I2C1-RTC-DS3231.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.BB-I2C1-RTC-DS3231.dtbo.d.dtc.tmp src/arm/.BB-I2C1-RTC-DS3231.dtbo.dts.tmp ; cat src/arm/.BB-I2C1-RTC-DS3231.dtbo.d.pre.tmp src/arm/.BB-I2C1-RTC-DS3231.dtbo.d.dtc.tmp > src/arm/.BB-I2C1-RTC-DS3231.dtbo.d
BB-I2C1-RTC-DS3231.o: src/arm/BB-I2C1-RTC-DS3231.dts \
 include/dt-bindings/pinctrl/am33xx.h include/dt-bindings/pinctrl/omap.h \
 include/dt-bindings/gpio/gpio.h
src/arm/BB-I2C1-RTC-DS3231.dtbo: src/arm/.BB-I2C1-RTC-DS3231.dtbo.dts.tmp
