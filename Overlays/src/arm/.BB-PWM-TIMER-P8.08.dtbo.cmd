cmd_src/arm/BB-PWM-TIMER-P8.08.dtbo = cpp -Wp,-MD,src/arm/.BB-PWM-TIMER-P8.08.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.BB-PWM-TIMER-P8.08.dtbo.dts.tmp src/arm/BB-PWM-TIMER-P8.08.dts ; dtc -O dtb -o src/arm/BB-PWM-TIMER-P8.08.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.BB-PWM-TIMER-P8.08.dtbo.d.dtc.tmp src/arm/.BB-PWM-TIMER-P8.08.dtbo.dts.tmp ; cat src/arm/.BB-PWM-TIMER-P8.08.dtbo.d.pre.tmp src/arm/.BB-PWM-TIMER-P8.08.dtbo.d.dtc.tmp > src/arm/.BB-PWM-TIMER-P8.08.dtbo.d
BB-PWM-TIMER-P8.08.o: src/arm/BB-PWM-TIMER-P8.08.dts \
 include/dt-bindings/gpio/gpio.h include/dt-bindings/pinctrl/am33xx.h \
 include/dt-bindings/pinctrl/omap.h
src/arm/BB-PWM-TIMER-P8.08.dtbo: src/arm/.BB-PWM-TIMER-P8.08.dtbo.dts.tmp
