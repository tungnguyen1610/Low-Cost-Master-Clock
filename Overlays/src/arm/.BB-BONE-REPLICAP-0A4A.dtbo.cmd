cmd_src/arm/BB-BONE-REPLICAP-0A4A.dtbo = cpp -Wp,-MD,src/arm/.BB-BONE-REPLICAP-0A4A.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.BB-BONE-REPLICAP-0A4A.dtbo.dts.tmp src/arm/BB-BONE-REPLICAP-0A4A.dts ; dtc -O dtb -o src/arm/BB-BONE-REPLICAP-0A4A.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.BB-BONE-REPLICAP-0A4A.dtbo.d.dtc.tmp src/arm/.BB-BONE-REPLICAP-0A4A.dtbo.dts.tmp ; cat src/arm/.BB-BONE-REPLICAP-0A4A.dtbo.d.pre.tmp src/arm/.BB-BONE-REPLICAP-0A4A.dtbo.d.dtc.tmp > src/arm/.BB-BONE-REPLICAP-0A4A.dtbo.d
BB-BONE-REPLICAP-0A4A.o: src/arm/BB-BONE-REPLICAP-0A4A.dts
src/arm/BB-BONE-REPLICAP-0A4A.dtbo: src/arm/.BB-BONE-REPLICAP-0A4A.dtbo.dts.tmp
