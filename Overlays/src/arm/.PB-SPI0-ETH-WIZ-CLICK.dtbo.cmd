cmd_src/arm/PB-SPI0-ETH-WIZ-CLICK.dtbo = cpp -Wp,-MD,src/arm/.PB-SPI0-ETH-WIZ-CLICK.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.PB-SPI0-ETH-WIZ-CLICK.dtbo.dts.tmp src/arm/PB-SPI0-ETH-WIZ-CLICK.dts ; dtc -O dtb -o src/arm/PB-SPI0-ETH-WIZ-CLICK.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.PB-SPI0-ETH-WIZ-CLICK.dtbo.d.dtc.tmp src/arm/.PB-SPI0-ETH-WIZ-CLICK.dtbo.dts.tmp ; cat src/arm/.PB-SPI0-ETH-WIZ-CLICK.dtbo.d.pre.tmp src/arm/.PB-SPI0-ETH-WIZ-CLICK.dtbo.d.dtc.tmp > src/arm/.PB-SPI0-ETH-WIZ-CLICK.dtbo.d
PB-SPI0-ETH-WIZ-CLICK.o: src/arm/PB-SPI0-ETH-WIZ-CLICK.dts \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/pinctrl/am33xx.h \
 include/dt-bindings/pinctrl/omap.h \
 include/dt-bindings/interrupt-controller/irq.h
src/arm/PB-SPI0-ETH-WIZ-CLICK.dtbo: src/arm/.PB-SPI0-ETH-WIZ-CLICK.dtbo.dts.tmp
