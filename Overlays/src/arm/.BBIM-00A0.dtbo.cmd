cmd_src/arm/BBIM-00A0.dtbo = cpp -Wp,-MD,src/arm/.BBIM-00A0.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.BBIM-00A0.dtbo.dts.tmp src/arm/BBIM-00A0.dts ; dtc -O dtb -o src/arm/BBIM-00A0.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.BBIM-00A0.dtbo.d.dtc.tmp src/arm/.BBIM-00A0.dtbo.dts.tmp ; cat src/arm/.BBIM-00A0.dtbo.d.pre.tmp src/arm/.BBIM-00A0.dtbo.d.dtc.tmp > src/arm/.BBIM-00A0.dtbo.d
BBIM-00A0.o: src/arm/BBIM-00A0.dts \
 include/dt-bindings/board/am335x-bbw-bbb-base.h \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/pinctrl/am33xx.h \
 include/dt-bindings/pinctrl/omap.h
src/arm/BBIM-00A0.dtbo: src/arm/.BBIM-00A0.dtbo.dts.tmp
