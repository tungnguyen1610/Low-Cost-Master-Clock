cmd_src/arm/EEPROM.dtbo = cpp -Wp,-MD,src/arm/.EEPROM.dtbo.d.pre.tmp -nostdinc -Iinclude -Isrc/arm -Isrc -Itestcase-data -undef -D__DTS__ -x assembler-with-cpp -o src/arm/.EEPROM.dtbo.dts.tmp src/arm/EEPROM.dts ; dtc -O dtb -o src/arm/EEPROM.dtbo -b 0 -@ -i src/arm -Wno-unit_address_vs_reg -Wno-chosen_node_is_root -Wno-alias_paths -d src/arm/.EEPROM.dtbo.d.dtc.tmp src/arm/.EEPROM.dtbo.dts.tmp ; cat src/arm/.EEPROM.dtbo.d.pre.tmp src/arm/.EEPROM.dtbo.d.dtc.tmp > src/arm/.EEPROM.dtbo.d
EEPROM.o: src/arm/EEPROM.dts
src/arm/EEPROM.dtbo: src/arm/.EEPROM.dtbo.dts.tmp
