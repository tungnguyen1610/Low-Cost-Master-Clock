cmd_src/arm/BBORG_DISPLAY18-00A2.dtbo = cpp -Wp,-MD,src/arm/.BBORG_DISPLAY18-00A2.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.BBORG_DISPLAY18-00A2.dtbo.dts.tmp src/arm/BBORG_DISPLAY18-00A2.dts ; dtc -O dtb -o src/arm/BBORG_DISPLAY18-00A2.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.BBORG_DISPLAY18-00A2.dtbo.d.dtc.tmp src/arm/.BBORG_DISPLAY18-00A2.dtbo.dts.tmp ; cat src/arm/.BBORG_DISPLAY18-00A2.dtbo.d.pre.tmp src/arm/.BBORG_DISPLAY18-00A2.dtbo.d.dtc.tmp > src/arm/.BBORG_DISPLAY18-00A2.dtbo.d
BBORG_DISPLAY18-00A2.o: src/arm/BBORG_DISPLAY18-00A2.dts \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/pinctrl/am33xx.h \
 include/dt-bindings/pinctrl/omap.h \
 include/dt-bindings/board/am335x-bbw-bbb-base.h
src/arm/BBORG_DISPLAY18-00A2.dtbo: src/arm/.BBORG_DISPLAY18-00A2.dtbo.dts.tmp