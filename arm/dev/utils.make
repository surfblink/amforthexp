# Utilities that can be use across different boards/targets
# Assumptions:
# * build/ directory containing the various amforth.* files
# * CROSS variable with the architecture command prefix

# A detailed dump of ELF sections for debugging linker issues
sections: sec-type sec-addr sec-sum

sec-type:
	# SECTION TYPES:
	# Type:
	# 	PROGBITS: Program data (code, initialized constants).
	#	NOBITS: Occupies no space in the file (e.g., .bss, NOLOAD).
	#	SYMTAB / STRTAB: Symbol tables and string tables for debugging.
	# Flags:
	#	W (write): The processor is allowed to write to this memory address (RAM).
	#	A (alloc): This section is "allocated"—it exists in the memory map of the device at runtime.
	#	X (execute): This section contains code that the CPU can run.
	#	M (merge): The linker may merge duplicate data to save space (common in strings).
	#	S (strings): The section contains null-terminated strings.
	# ES - entry size for table sections (fixed sized elements)
	# Lk - index number of a linked section (relocations, symbol tables)
	# Inf - extra info (relo & symtables)
	# Al - section Addr alignment in bytes (must be 2^n)
	$(CROSS)readelf --sections build/amforth.elf

sec-addr:
	# SECTION ADDRESSES:
	# Flags: Name | Description [ Linker Script / ELF Equivalent ]
	# 	CONTENTS	The section has actual data stored in the file. [ SHT_PROGBITS ]
	#	ALLOC		Space must be reserved for this section in RAM/Flash at runtime. [ SHF_ALLOC (the A flag) ]
	#	LOAD		This section should be loaded into memory from the file. [ Not NOLOAD ]
	#	READONLY	The section cannot be modified at runtime (usually in Flash). [ Missing SHF_WRITE ]
	# 	CODE		Contains executable CPU instructions.	[ .text ]
	#	DATA		Contains initialized variables or constants.	[ .data, .rodata ]
	#	DEBUGGING	Contains DWARF or stabs info for GDB (not loaded).	[ .debug_info ]
	#	HAS_CONTENTS	Similar to CONTENTS; implies the section isn't empty.	[ Various ]
	$(CROSS)objdump -h build/amforth.elf

sec-sum:
	# SECTION SIZE SUMMARY:
	$(CROSS)size build/amforth.elf