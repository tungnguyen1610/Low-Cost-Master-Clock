cmd_src/arm/cape-CBB-Serial-r01.dtbo = cpp -Wp,-MD,src/arm/.cape-CBB-Serial-r01.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.cape-CBB-Serial-r01.dtbo.dts.tmp src/arm/cape-CBB-Serial-r01.dts ; dtc -O dtb -o src/arm/cape-CBB-Serial-r01.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.cape-CBB-Serial-r01.dtbo.d.dtc.tmp src/arm/.cape-CBB-Serial-r01.dtbo.dts.tmp ; cat src/arm/.cape-CBB-Serial-r01.dtbo.d.pre.tmp src/arm/.cape-CBB-Serial-r01.dtbo.d.dtc.tmp > src/arm/.cape-CBB-Serial-r01.dtbo.d
cape-CBB-Serial-r01.o: src/arm/cape-CBB-Serial-r01.dts \
 include/dt-bindings/board/am335x-bbw-bbb-base.h \
 include/dt-bindings/pinctrl/am33xx.h include/dt-bindings/pinctrl/omap.h
src/arm/cape-CBB-Serial-r01.dtbo: src/arm/.cape-CBB-Serial-r01.dtbo.dts.tmp
