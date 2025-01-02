cmd_src/arm/PB-SPI1-7SEG-TECHLAB-CAPE.dtbo = cpp -Wp,-MD,src/arm/.PB-SPI1-7SEG-TECHLAB-CAPE.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.PB-SPI1-7SEG-TECHLAB-CAPE.dtbo.dts.tmp src/arm/PB-SPI1-7SEG-TECHLAB-CAPE.dts ; dtc -O dtb -o src/arm/PB-SPI1-7SEG-TECHLAB-CAPE.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.PB-SPI1-7SEG-TECHLAB-CAPE.dtbo.d.dtc.tmp src/arm/.PB-SPI1-7SEG-TECHLAB-CAPE.dtbo.dts.tmp ; cat src/arm/.PB-SPI1-7SEG-TECHLAB-CAPE.dtbo.d.pre.tmp src/arm/.PB-SPI1-7SEG-TECHLAB-CAPE.dtbo.d.dtc.tmp > src/arm/.PB-SPI1-7SEG-TECHLAB-CAPE.dtbo.d
PB-SPI1-7SEG-TECHLAB-CAPE.o: src/arm/PB-SPI1-7SEG-TECHLAB-CAPE.dts \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/pinctrl/am33xx.h \
 include/dt-bindings/pinctrl/omap.h \
 include/dt-bindings/interrupt-controller/irq.h
src/arm/PB-SPI1-7SEG-TECHLAB-CAPE.dtbo: src/arm/.PB-SPI1-7SEG-TECHLAB-CAPE.dtbo.dts.tmp
