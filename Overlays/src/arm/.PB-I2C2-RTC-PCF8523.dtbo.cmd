cmd_src/arm/PB-I2C2-RTC-PCF8523.dtbo = cpp -Wp,-MD,src/arm/.PB-I2C2-RTC-PCF8523.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.PB-I2C2-RTC-PCF8523.dtbo.dts.tmp src/arm/PB-I2C2-RTC-PCF8523.dts ; dtc -O dtb -o src/arm/PB-I2C2-RTC-PCF8523.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.PB-I2C2-RTC-PCF8523.dtbo.d.dtc.tmp src/arm/.PB-I2C2-RTC-PCF8523.dtbo.dts.tmp ; cat src/arm/.PB-I2C2-RTC-PCF8523.dtbo.d.pre.tmp src/arm/.PB-I2C2-RTC-PCF8523.dtbo.d.dtc.tmp > src/arm/.PB-I2C2-RTC-PCF8523.dtbo.d
PB-I2C2-RTC-PCF8523.o: src/arm/PB-I2C2-RTC-PCF8523.dts \
 include/dt-bindings/board/am335x-bbw-bbb-base.h \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/pinctrl/am33xx.h \
 include/dt-bindings/pinctrl/omap.h
src/arm/PB-I2C2-RTC-PCF8523.dtbo: src/arm/.PB-I2C2-RTC-PCF8523.dtbo.dts.tmp
