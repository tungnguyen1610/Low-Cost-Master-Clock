cmd_src/arm/am33xx_pwm-00A0.dtbo = cpp -Wp,-MD,src/arm/.am33xx_pwm-00A0.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.am33xx_pwm-00A0.dtbo.dts.tmp src/arm/am33xx_pwm-00A0.dts ; dtc -O dtb -o src/arm/am33xx_pwm-00A0.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.am33xx_pwm-00A0.dtbo.d.dtc.tmp src/arm/.am33xx_pwm-00A0.dtbo.dts.tmp ; cat src/arm/.am33xx_pwm-00A0.dtbo.d.pre.tmp src/arm/.am33xx_pwm-00A0.dtbo.d.dtc.tmp > src/arm/.am33xx_pwm-00A0.dtbo.d
am33xx_pwm-00A0.o: src/arm/am33xx_pwm-00A0.dts
src/arm/am33xx_pwm-00A0.dtbo: src/arm/.am33xx_pwm-00A0.dtbo.dts.tmp