cmd_src/arm/ACME-revB.dtbo = cpp -Wp,-MD,src/arm/.ACME-revB.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.ACME-revB.dtbo.dts.tmp src/arm/ACME-revB.dts ; dtc -O dtb -o src/arm/ACME-revB.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.ACME-revB.dtbo.d.dtc.tmp src/arm/.ACME-revB.dtbo.dts.tmp ; cat src/arm/.ACME-revB.dtbo.d.pre.tmp src/arm/.ACME-revB.dtbo.d.dtc.tmp > src/arm/.ACME-revB.dtbo.d
ACME-revB.o: src/arm/ACME-revB.dts \
 include/dt-bindings/board/am335x-bbw-bbb-base.h \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/pinctrl/am33xx.h \
 include/dt-bindings/pinctrl/omap.h
src/arm/ACME-revB.dtbo: src/arm/.ACME-revB.dtbo.dts.tmp
