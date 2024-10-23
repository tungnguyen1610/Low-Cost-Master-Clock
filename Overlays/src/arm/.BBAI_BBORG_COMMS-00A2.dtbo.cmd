cmd_src/arm/BBAI_BBORG_COMMS-00A2.dtbo = cpp -Wp,-MD,src/arm/.BBAI_BBORG_COMMS-00A2.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.BBAI_BBORG_COMMS-00A2.dtbo.dts.tmp src/arm/BBAI_BBORG_COMMS-00A2.dts ; dtc -O dtb -o src/arm/BBAI_BBORG_COMMS-00A2.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.BBAI_BBORG_COMMS-00A2.dtbo.d.dtc.tmp src/arm/.BBAI_BBORG_COMMS-00A2.dtbo.dts.tmp ; cat src/arm/.BBAI_BBORG_COMMS-00A2.dtbo.d.pre.tmp src/arm/.BBAI_BBORG_COMMS-00A2.dtbo.d.dtc.tmp > src/arm/.BBAI_BBORG_COMMS-00A2.dtbo.d
BBAI_BBORG_COMMS-00A2.o: src/arm/BBAI_BBORG_COMMS-00A2.dts \
 include/dt-bindings/interrupt-controller/irq.h \
 include/dt-bindings/pinctrl/dra.h include/dt-bindings/gpio/gpio.h
src/arm/BBAI_BBORG_COMMS-00A2.dtbo: src/arm/.BBAI_BBORG_COMMS-00A2.dtbo.dts.tmp
