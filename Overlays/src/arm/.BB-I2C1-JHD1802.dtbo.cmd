cmd_src/arm/BB-I2C1-JHD1802.dtbo = cpp -Wp,-MD,src/arm/.BB-I2C1-JHD1802.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.BB-I2C1-JHD1802.dtbo.dts.tmp src/arm/BB-I2C1-JHD1802.dts ; dtc -O dtb -o src/arm/BB-I2C1-JHD1802.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.BB-I2C1-JHD1802.dtbo.d.dtc.tmp src/arm/.BB-I2C1-JHD1802.dtbo.dts.tmp ; cat src/arm/.BB-I2C1-JHD1802.dtbo.d.pre.tmp src/arm/.BB-I2C1-JHD1802.dtbo.d.dtc.tmp > src/arm/.BB-I2C1-JHD1802.dtbo.d
BB-I2C1-JHD1802.o: src/arm/BB-I2C1-JHD1802.dts
src/arm/BB-I2C1-JHD1802.dtbo: src/arm/.BB-I2C1-JHD1802.dtbo.dts.tmp
