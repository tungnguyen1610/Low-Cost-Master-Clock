cmd_src/arm/GHI-DB-NH5C-00A0.dtbo = cpp -Wp,-MD,src/arm/.GHI-DB-NH5C-00A0.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.GHI-DB-NH5C-00A0.dtbo.dts.tmp src/arm/GHI-DB-NH5C-00A0.dts ; dtc -O dtb -o src/arm/GHI-DB-NH5C-00A0.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.GHI-DB-NH5C-00A0.dtbo.d.dtc.tmp src/arm/.GHI-DB-NH5C-00A0.dtbo.dts.tmp ; cat src/arm/.GHI-DB-NH5C-00A0.dtbo.d.pre.tmp src/arm/.GHI-DB-NH5C-00A0.dtbo.d.dtc.tmp > src/arm/.GHI-DB-NH5C-00A0.dtbo.d
GHI-DB-NH5C-00A0.o: src/arm/GHI-DB-NH5C-00A0.dts \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/pinctrl/am33xx.h \
 include/dt-bindings/pinctrl/omap.h \
 include/dt-bindings/board/am335x-bbw-bbb-base.h
src/arm/GHI-DB-NH5C-00A0.dtbo: src/arm/.GHI-DB-NH5C-00A0.dtbo.dts.tmp
