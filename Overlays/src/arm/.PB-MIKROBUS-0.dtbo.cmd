cmd_src/arm/PB-MIKROBUS-0.dtbo = cpp -Wp,-MD,src/arm/.PB-MIKROBUS-0.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.PB-MIKROBUS-0.dtbo.dts.tmp src/arm/PB-MIKROBUS-0.dts ; dtc -O dtb -o src/arm/PB-MIKROBUS-0.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.PB-MIKROBUS-0.dtbo.d.dtc.tmp src/arm/.PB-MIKROBUS-0.dtbo.dts.tmp ; cat src/arm/.PB-MIKROBUS-0.dtbo.d.pre.tmp src/arm/.PB-MIKROBUS-0.dtbo.d.dtc.tmp > src/arm/.PB-MIKROBUS-0.dtbo.d
PB-MIKROBUS-0.o: src/arm/PB-MIKROBUS-0.dts \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/pinctrl/am33xx.h \
 include/dt-bindings/pinctrl/omap.h
src/arm/PB-MIKROBUS-0.dtbo: src/arm/.PB-MIKROBUS-0.dtbo.dts.tmp
