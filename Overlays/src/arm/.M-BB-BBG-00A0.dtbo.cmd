cmd_src/arm/M-BB-BBG-00A0.dtbo = cpp -Wp,-MD,src/arm/.M-BB-BBG-00A0.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.M-BB-BBG-00A0.dtbo.dts.tmp src/arm/M-BB-BBG-00A0.dts ; dtc -O dtb -o src/arm/M-BB-BBG-00A0.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.M-BB-BBG-00A0.dtbo.d.dtc.tmp src/arm/.M-BB-BBG-00A0.dtbo.dts.tmp ; cat src/arm/.M-BB-BBG-00A0.dtbo.d.pre.tmp src/arm/.M-BB-BBG-00A0.dtbo.d.dtc.tmp > src/arm/.M-BB-BBG-00A0.dtbo.d
M-BB-BBG-00A0.o: src/arm/M-BB-BBG-00A0.dts
src/arm/M-BB-BBG-00A0.dtbo: src/arm/.M-BB-BBG-00A0.dtbo.dts.tmp
