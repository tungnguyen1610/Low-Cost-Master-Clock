cmd_src/arm/BBBLUE-GP0-SPI-00A0.dtbo = cpp -Wp,-MD,src/arm/.BBBLUE-GP0-SPI-00A0.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.BBBLUE-GP0-SPI-00A0.dtbo.dts.tmp src/arm/BBBLUE-GP0-SPI-00A0.dts ; dtc -O dtb -o src/arm/BBBLUE-GP0-SPI-00A0.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.BBBLUE-GP0-SPI-00A0.dtbo.d.dtc.tmp src/arm/.BBBLUE-GP0-SPI-00A0.dtbo.dts.tmp ; cat src/arm/.BBBLUE-GP0-SPI-00A0.dtbo.d.pre.tmp src/arm/.BBBLUE-GP0-SPI-00A0.dtbo.d.dtc.tmp > src/arm/.BBBLUE-GP0-SPI-00A0.dtbo.d
BBBLUE-GP0-SPI-00A0.o: src/arm/BBBLUE-GP0-SPI-00A0.dts
src/arm/BBBLUE-GP0-SPI-00A0.dtbo: src/arm/.BBBLUE-GP0-SPI-00A0.dtbo.dts.tmp