cmd_src/arm/PB-MCP2515-SPI1.dtbo = cpp -Wp,-MD,src/arm/.PB-MCP2515-SPI1.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.PB-MCP2515-SPI1.dtbo.dts.tmp src/arm/PB-MCP2515-SPI1.dts ; dtc -O dtb -o src/arm/PB-MCP2515-SPI1.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.PB-MCP2515-SPI1.dtbo.d.dtc.tmp src/arm/.PB-MCP2515-SPI1.dtbo.dts.tmp ; cat src/arm/.PB-MCP2515-SPI1.dtbo.d.pre.tmp src/arm/.PB-MCP2515-SPI1.dtbo.d.dtc.tmp > src/arm/.PB-MCP2515-SPI1.dtbo.d
PB-MCP2515-SPI1.o: src/arm/PB-MCP2515-SPI1.dts \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/pinctrl/am33xx.h \
 include/dt-bindings/pinctrl/omap.h \
 include/dt-bindings/interrupt-controller/irq.h
src/arm/PB-MCP2515-SPI1.dtbo: src/arm/.PB-MCP2515-SPI1.dtbo.dts.tmp
