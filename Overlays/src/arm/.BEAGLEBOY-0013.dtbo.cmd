cmd_src/arm/BEAGLEBOY-0013.dtbo = cpp -Wp,-MD,src/arm/.BEAGLEBOY-0013.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.BEAGLEBOY-0013.dtbo.dts.tmp src/arm/BEAGLEBOY-0013.dts ; dtc -O dtb -o src/arm/BEAGLEBOY-0013.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.BEAGLEBOY-0013.dtbo.d.dtc.tmp src/arm/.BEAGLEBOY-0013.dtbo.dts.tmp ; cat src/arm/.BEAGLEBOY-0013.dtbo.d.pre.tmp src/arm/.BEAGLEBOY-0013.dtbo.d.dtc.tmp > src/arm/.BEAGLEBOY-0013.dtbo.d
BEAGLEBOY-0013.o: src/arm/BEAGLEBOY-0013.dts \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/pinctrl/am33xx.h \
 include/dt-bindings/pinctrl/omap.h \
 include/dt-bindings/board/am335x-bbw-bbb-base.h
src/arm/BEAGLEBOY-0013.dtbo: src/arm/.BEAGLEBOY-0013.dtbo.dts.tmp
