cmd_src/arm/BB-mBC1-ETH-CLICK.dtbo = cpp -Wp,-MD,src/arm/.BB-mBC1-ETH-CLICK.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.BB-mBC1-ETH-CLICK.dtbo.dts.tmp src/arm/BB-mBC1-ETH-CLICK.dts ; dtc -O dtb -o src/arm/BB-mBC1-ETH-CLICK.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.BB-mBC1-ETH-CLICK.dtbo.d.dtc.tmp src/arm/.BB-mBC1-ETH-CLICK.dtbo.dts.tmp ; cat src/arm/.BB-mBC1-ETH-CLICK.dtbo.d.pre.tmp src/arm/.BB-mBC1-ETH-CLICK.dtbo.d.dtc.tmp > src/arm/.BB-mBC1-ETH-CLICK.dtbo.d
BB-mBC1-ETH-CLICK.o: src/arm/BB-mBC1-ETH-CLICK.dts \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/pinctrl/am33xx.h \
 include/dt-bindings/pinctrl/omap.h \
 include/dt-bindings/interrupt-controller/irq.h
src/arm/BB-mBC1-ETH-CLICK.dtbo: src/arm/.BB-mBC1-ETH-CLICK.dtbo.dts.tmp