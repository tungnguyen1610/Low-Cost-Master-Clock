cmd_src/arm/PB-I2C2-ACCEL-TECHLAB-CAPE.dtbo = cpp -Wp,-MD,src/arm/.PB-I2C2-ACCEL-TECHLAB-CAPE.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.PB-I2C2-ACCEL-TECHLAB-CAPE.dtbo.dts.tmp src/arm/PB-I2C2-ACCEL-TECHLAB-CAPE.dts ; dtc -O dtb -o src/arm/PB-I2C2-ACCEL-TECHLAB-CAPE.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.PB-I2C2-ACCEL-TECHLAB-CAPE.dtbo.d.dtc.tmp src/arm/.PB-I2C2-ACCEL-TECHLAB-CAPE.dtbo.dts.tmp ; cat src/arm/.PB-I2C2-ACCEL-TECHLAB-CAPE.dtbo.d.pre.tmp src/arm/.PB-I2C2-ACCEL-TECHLAB-CAPE.dtbo.d.dtc.tmp > src/arm/.PB-I2C2-ACCEL-TECHLAB-CAPE.dtbo.d
PB-I2C2-ACCEL-TECHLAB-CAPE.o: src/arm/PB-I2C2-ACCEL-TECHLAB-CAPE.dts \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/pinctrl/am33xx.h \
 include/dt-bindings/pinctrl/omap.h \
 include/dt-bindings/interrupt-controller/irq.h
src/arm/PB-I2C2-ACCEL-TECHLAB-CAPE.dtbo: src/arm/.PB-I2C2-ACCEL-TECHLAB-CAPE.dtbo.dts.tmp
