cmd_src/arm/BB-GPIO-HCSR04.dtbo = cpp -Wp,-MD,src/arm/.BB-GPIO-HCSR04.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.BB-GPIO-HCSR04.dtbo.dts.tmp src/arm/BB-GPIO-HCSR04.dts ; dtc -O dtb -o src/arm/BB-GPIO-HCSR04.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.BB-GPIO-HCSR04.dtbo.d.dtc.tmp src/arm/.BB-GPIO-HCSR04.dtbo.dts.tmp ; cat src/arm/.BB-GPIO-HCSR04.dtbo.d.pre.tmp src/arm/.BB-GPIO-HCSR04.dtbo.d.dtc.tmp > src/arm/.BB-GPIO-HCSR04.dtbo.d
BB-GPIO-HCSR04.o: src/arm/BB-GPIO-HCSR04.dts
src/arm/BB-GPIO-HCSR04.dtbo: src/arm/.BB-GPIO-HCSR04.dtbo.dts.tmp
