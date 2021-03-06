#include <stdio.h>
#include <stdlib.h>
#include <elf.h>
#include <inttypes.h>
#include "elf_analyze.h"

void analyze_32(FILE *fp);
void analyze_64(FILE *fp);
void parse_e_ident(unsigned char *e_ident);
void parse_type(Elf64_Half e_type);
void parse_machine(Elf64_Half e_machine);
void parse_header_meta(Elf64_Ehdr header);
void parse_section_headers(FILE *fp, Elf64_Ehdr header);
void parse_program_headers(FILE *fp, Elf64_Ehdr header);
void parse_section(FILE *fp, Elf64_Shdr section_header, Elf64_Off offset, Elf64_Word size);

void analyze_elf(FILE *fp)
{
	int class;

	class = getc(fp);

	// Check for architecture
	if(class == CLASS_32_BIT)
	{
		analyze_32(fp);
	}
	else if(class == CLASS_64_BIT)
	{
		analyze_64(fp);
	}
}


void analyze_32(FILE *fp)
{

}

void analyze_64(FILE *fp)
{
	// Reset fp to get entire header
	fseek(fp, 0, SEEK_SET);

	// ELF Header struct
	Elf64_Ehdr header;

	
	// Read the entire header (0x40 bytes) into the Elf64_Ehdr struct
	fread(&header, sizeof(header), 1, fp);

	printf("File is a 64 bit executable");
	
	parse_e_ident(header.e_ident);

	parse_type(header.e_type);

	parse_machine(header.e_type);

	parse_header_meta(header);

	parse_section_headers(fp, header);

	parse_program_headers(fp, header);

	/* Program header area */
}


void parse_e_ident(unsigned char *e_ident)
{
	switch(e_ident[EI_DATA])
	{

		case ELFDATANONE:
			printf(" and does not have a valid machine archetecture\n");
			break;
		case ELFDATA2LSB:
			printf(" in little endian 2's compiment.\n");
			break;
		case ELFDATA2MSB:
			printf(" in big endian 2's compliment.\n");
			break;
		case ELFDATANUM:
			printf(" and I need to look up 0x03 spec.\n");
			break;
	}

	if(e_ident[EI_VERSION] == 0x01)
	{
		printf("ELF Version 1.\n");
	}
	
	printf("Target operating system: ");

	switch(e_ident[EI_OSABI])
	{
		case ELFOSABI_NONE:
			printf("UNIX System V ABI.\n");
			break;
		case ELFOSABI_HPUX:
			printf("HP-UX.\n");
			break;
		case ELFOSABI_NETBSD:
			printf("NetBSD.\n");
			break;
		case ELFOSABI_GNU:
			printf("GNU/Linux.\n");
			break;
	 	case ELFOSABI_SOLARIS:
			printf("Sun Solaris.\n");
			break;
		case ELFOSABI_AIX:
			printf("IBM AIX.\n");
			break;
		case ELFOSABI_IRIX:
			printf("SGI Irix.\n");
			break;
		case ELFOSABI_FREEBSD:
			printf("FreeBSD.\n");
			break;
		case ELFOSABI_TRU64:
			printf("Compaq TRU64 UNIX.\n");
			break;
		case ELFOSABI_MODESTO:
			printf("Novell Modesto.\n");
			break;
		case ELFOSABI_OPENBSD:
			printf("OpenBSD.\n");
			break;
		case ELFOSABI_ARM_AEABI:
			printf("ARM EABI.\n");
			break;
		case ELFOSABI_ARM:
			printf("ARM.\n");
			break;
		case ELFOSABI_STANDALONE:
			printf("Stanalone (embedded) application.\n");
			break;
	}
}


void parse_type(Elf64_Half e_type)
{
	printf("File type: ");
	switch(e_type)
	{
		case ET_NONE:
			printf("No file type\n");
			break;
		case ET_REL:
			printf("Relocatable file\n");
			break;
		case ET_EXEC:
			printf("Executable file\n");
			break;
		case ET_DYN:
			printf("Shared object file\n");
			break;
		case ET_CORE:
			printf("Core file\n");
			break;
		// Include ofhters?

		default:
			printf("not found\n");
	}
}


void parse_machine(Elf64_Half e_machine)
{
	printf("Machine Archetecture: ");
	switch(e_machine)
	{
		case EM_NONE:
			printf("No machine\n");
			break;
		case EM_M32:
			printf("AT&T WE 32100\n");
			break;
		case EM_SPARC:
			printf("Sun SPARC\n");
			break;
		case EM_386:
			printf("Intel 80386\n");
			break;
		case EM_68K:
			printf("Motorola m68k family\n");
			break;
		case EM_88K:
			printf("Motorola m88k family\n");
			break;
		case EM_860:
			printf("Intel 80860\n");
			break;
		case EM_MIPS:
			printf("MIPS R3000 big-endian\n");
			break;
		case EM_S370:
			printf("IBM System/370\n");
			break;
		case EM_MIPS_RS3_LE:
			printf("MIPS R3000 little-endian\n");
			break;
		case EM_PARISC:
			printf("HPPA\n");
			break;
		case EM_VPP500:
			printf("Fujitsu VPP500\n");
			break;
		case EM_SPARC32PLUS:
			printf("Sun's \"v8plus\"\n");
			break;
		case EM_960:
			printf("Intel 80960\n");
			break;
		case EM_PPC:
			printf("PowerPC\n");
			break;
		case EM_PPC64:
			printf("PowerPC 64-bit\n");
			break;
		case EM_S390:
			printf("IBM S390\n");
			break;
		case EM_V800:
			printf("NEC V800 series\n");
			break;
		case EM_FR20:
			printf("Fujitsu FR20\n");
			break;
		case EM_RH32:
			printf("TRW RH-32\n");
			break;
		case EM_RCE:
			printf("Motorola RCE\n");
			break;
		case EM_ARM:
			printf("ARM\n");
			break;
		case EM_FAKE_ALPHA:
			printf("Digital Alpha\n");
			break;
		case EM_SH:
			printf("Hitachi SH\n");
			break;
		case EM_SPARCV9:
			printf("SPARC v9 64-bit\n");
			break;
		case EM_TRICORE:
			printf("Siemens Tricore\n");
			break;
		case EM_ARC:
			printf("Argonaut RISC Core\n");
			break;
		case EM_H8_300:
			printf("Hitachi H8/300\n");
			break;
		case EM_H8_300H:
			printf("Hitachi H8/300H\n");
			break;
		case EM_H8S:
			printf("Hitachi H8S\n");
			break;
		case EM_H8_500:
			printf("Hitachi H8/500\n");
			break;
		case EM_IA_64:
			printf("Intel Merced\n");
			break;
		case EM_MIPS_X:
			printf("Stanford MIPS-X\n");
			break;
		case EM_COLDFIRE:
			printf("Motorola Coldfire\n");
			break;
		case EM_68HC12:
			printf("Motorola M68HC12\n");
			break;
		case EM_MMA:
			printf("Fujitsu MMA Multimedia Accelerator*/\n");
			break;
		case EM_PCP:
			printf("Siemens PCP\n");
			break;
		case EM_NCPU:
			printf("Sony nCPU embeeded RISC\n");
			break;
		case EM_NDR1:
			printf("Denso NDR1 microprocessor\n");
			break;
		case EM_STARCORE:
			printf("Motorola Start*Core processor\n");
			break;
		case EM_ME16:
			printf("Toyota ME16 processor\n");
			break;
		case EM_ST100:
			printf("STMicroelectronic ST100 processor\n");
			break;
		case EM_TINYJ:
			printf("Advanced Logic Corp. Tinyj emb.fam*/\n");
			break;
		case EM_X86_64:
			printf("AMD x86-64 architecture\n");
			break;
		case EM_PDSP:
			printf("Sony DSP Processor\n");
			break;
		case EM_FX66:
			printf("Siemens FX66 microcontroller\n");
			break;
		case EM_ST9PLUS:
			printf("STMicroelectronics ST9+ 8/16 mc\n");
			break;
		case EM_ST7:
			printf("STmicroelectronics ST7 8 bit mc\n");
			break;
		case EM_68HC16:
			printf("Motorola MC68HC16 microcontroller\n");
			break;
		case EM_68HC11:
			printf("Motorola MC68HC11 microcontroller\n");
			break;
		case EM_68HC08:
			printf("Motorola MC68HC08 microcontroller\n");
			break;
		case EM_68HC05:
			printf("Motorola MC68HC05 microcontroller\n");
			break;
		case EM_SVX:
			printf("Silicon Graphics SVx\n");
			break;
		case EM_ST19:
			printf("STMicroelectronics ST19 8 bit mc\n");
			break;
		case EM_VAX:
			printf("Digital VAX\n");
			break;
		case EM_CRIS:
			printf("Axis Communications 32-bit embedded processor\n");
			break;
		case EM_JAVELIN:
			printf("Infineon Technologies 32-bit embedded processor\n");
			break;
		case EM_FIREPATH:
			printf("Element 14 64-bit DSP Processor\n");
			break;
		case EM_ZSP:
			printf("LSI Logic 16-bit DSP Processor\n");
			break;
		case EM_MMIX:
			printf("Donald Knuth's educational 64-bit processor\n");
			break;
		case EM_HUANY:
			printf("Harvard University machine-independent object files\n");
			break;
		case EM_PRISM:
			printf("SiTera Prism\n");
			break;
		case EM_AVR:
			printf("Atmel AVR 8-bit microcontroller\n");
			break;
		case EM_FR30:
			printf("Fujitsu FR30\n");
			break;
		case EM_D10V:
			printf("Mitsubishi D10V\n");
			break;
		case EM_D30V:
			printf("Mitsubishi D30V\n");
			break;
		case EM_V850:
			printf("NEC v850\n");
			break;
		case EM_M32R:
			printf("Mitsubishi M32R\n");
			break;
		case EM_MN10300:
			printf("Matsushita MN10300\n");
			break;
		case EM_MN10200:
			printf("Matsushita MN10200\n");
			break;
		case EM_PJ:
			printf("picoJava\n");
			break;
		case EM_OPENRISC:
			printf("OpenRISC 32-bit embedded processor\n");
			break;
		case EM_ARC_A5:
			printf("ARC Cores Tangent-A5\n");
			break;
		case EM_XTENSA:
			printf("Tensilica Xtensa Architecture\n");
			break;
		case EM_AARCH64:
			printf("ARM AARCH64\n");
			break;
		case EM_TILEPRO:
			printf("Tilera TILEPro\n");
			break;
		case EM_MICROBLAZE:
			printf("Xilinx MicroBlaze\n");
			break;
		case EM_TILEGX:
			printf("Tilera TILE-Gx\n");
			break;
		default:
			printf("not found\n");
	}
}


void parse_header_meta(Elf64_Ehdr header)
{
	printf("Entry point: 0x%"PRIxFAST64"\n", (uint64_t) header.e_entry);

	printf("Program header: 0x%"PRIxFAST64"\n", (uint64_t) header.e_phoff);

	printf("Program header size: 0x%"PRIxLEAST16"\n", (uint16_t) header.e_phentsize);

	printf("Entries in program header: 0x%"PRIxLEAST16"\n", (uint16_t) header.e_phnum);

	printf("Section Header: 0x%"PRIxLEAST64"\n", (uint64_t) header.e_shoff);

	printf("Section header size: 0x%"PRIxLEAST16"\n", (uint16_t) header.e_shentsize);

	printf("Entires is section header: 0x%"PRIxLEAST16"\n", (uint16_t) header.e_shnum);

	printf("Section name index: 0x%"PRIxLEAST16"\n", (uint16_t) header.e_shstrndx);

	printf("Flags: 0x%"PRIxLEAST32"\n", (uint32_t) header.e_flags);

	printf("ELF header size: 0x%"PRIxLEAST16"\n", (uint16_t) header.e_ehsize);
}



void parse_section_headers(FILE *fp, Elf64_Ehdr header)
{	
	printf("================================================================================\n");
	
	Elf64_Half num_sections = header.e_shnum, section_index;
	Elf64_Shdr sh_list[num_sections];


	fseek(fp, header.e_shoff, 0);
	
	int data_sections = 0, ro_data_sections = 0;

	if(!fread(&sh_list, sizeof(Elf64_Shdr), num_sections, fp))
	{
		exit(-1);
	}


	for(section_index = 0; section_index < num_sections; section_index++)
	{

		printf("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");

		printf("Section number %d\n", section_index);
		
		
		printf("0x%"PRIxLEAST64"\n", (uint64_t) sh_list[section_index].sh_name);
	

		printf("Section header type: ");
		
		switch(sh_list[section_index].sh_type)
		{
			case SHT_NULL:
				printf("Section header table entry unused\n");
				break;
			case SHT_PROGBITS:
				switch(sh_list[section_index].sh_flags)
				{
					case 0x0:
						printf(".comment/.line/.debug\n");
						break;
					case SHF_ALLOC:
						ro_data_sections > 0 ? printf(".rodata%d\n", ro_data_sections) : printf(".rodata\n");
						break;
					case SHF_ALLOC + SHF_WRITE:
						data_sections > 0 ? printf(".data%d\n", data_sections) : printf(".data\n");
						break;
					case SHF_ALLOC + SHF_EXECINSTR:
						printf(".text\n");
						break;
					default:
						printf("Program data\n");
				}
				break;
			case SHT_SYMTAB:
				printf("Symbol table\n");
				// Do later
				break;
			case SHT_STRTAB:
				printf("String table\n");
				// Do later
				break;
			case SHT_RELA:
				printf("Relocation entries with addend\n");
				break;
			case SHT_HASH:
				if(sh_list[section_index].sh_flags == SHF_ALLOC)
				{
					printf(".hash\n");
				}
				else
				{
					printf("Hash\n");
				}
				break;
			case SHT_DYNAMIC:
				printf("Dynamic linking information\n");
				// do later
				break;
			case SHT_NOTE:
				printf(".note\n");
				break;
			case SHT_NOBITS:
				if(sh_list[section_index].sh_flags == (SHF_ALLOC + SHF_WRITE))
				{
					printf(".bss");
				}
				break;
			case SHT_REL:
				printf("Relocation entries, no addend\n");
				break;
			case SHT_SHLIB:
				printf("Reserved\n");
				break;
			case SHT_DYNSYM:
				printf("Dynamic linker symbol table\n");
				break;
			case SHT_INIT_ARRAY:
				printf("Array of constructor\n");
				break;
			case SHT_FINI_ARRAY:
				printf("Array of destructor\n");
				break;
			case SHT_PREINIT_ARRAY:
				printf("Array of pre-constructor\n");
				break;
			case SHT_GROUP:
				printf("Section group\n");
				break;
			case SHT_SYMTAB_SHNDX:
				printf("Extended section indeces\n");
				break;
			case SHT_NUM:
				printf("Number of defined types\n");
				break;
			case SHT_LOOS:
				printf("Start OS-specific\n");
				break;
			case SHT_GNU_ATTRIBUTES:
				printf("Object attributes\n");
				break;
			case SHT_GNU_HASH:
				printf("GNU-style hash table\n");
				break;
			case SHT_GNU_LIBLIST:
				printf("Prelink library list\n");
				break;
			case SHT_CHECKSUM:
				printf("Checksum for DSO content\n");
				break;
			case SHT_LOSUNW:
				printf("Sun-specific low bound\n");
				break;
			case SHT_GNU_verdef:
				printf("Version definition section\n");
				break;
			case SHT_GNU_verneed:
				printf("Version needs section\n");
				break;
			case SHT_GNU_versym:
				printf("Version symbol table\n");
				break;
			case SHT_LOPROC:
				printf("Start of processor-specific\n");
				break;
			case SHT_HIPROC:
				printf("End of processor-specific\n");
				break;
			case SHT_LOUSER:
				printf("Start of application-specific\n");
				break;
			case SHT_HIUSER:
				printf("End of application-specific\n");
				break;
		}
		
		if(sh_list[section_index].sh_flags | 0x0)
		{
			printf("Table attributes:\n");
		}
		if((sh_list[section_index].sh_flags & SHF_WRITE) == SHF_WRITE)
		{
			printf("\tWritable\n");
		}
		if((sh_list[section_index].sh_flags & SHF_ALLOC) == SHF_ALLOC)
		{
			printf("\tLoads to memory during execution\n");
		}
		if((sh_list[section_index].sh_flags & SHF_EXECINSTR) == SHF_EXECINSTR)
		{
			printf("\tExecutable\n");
		}
		if((sh_list[section_index].sh_flags & SHF_MERGE) == SHF_MERGE)
		{
			printf("\tMay be merged\n");
		}
		if((sh_list[section_index].sh_flags & SHF_STRINGS) == SHF_STRINGS)
		{
			printf("\tContains nul-terminated strings\n");
		}
		if((sh_list[section_index].sh_flags & SHF_INFO_LINK) == SHF_INFO_LINK)
		{
			printf("\t'sh_info' contains SHT index\n");
		}
		if((sh_list[section_index].sh_flags & SHF_LINK_ORDER) == SHF_LINK_ORDER)
		{
			printf("\tPreserve order after combining\n");
		}
		if((sh_list[section_index].sh_flags & SHF_OS_NONCONFORMING) == SHF_OS_NONCONFORMING)
		{
			printf("\tNon-standard OS specific handling required\n");
		}
		if((sh_list[section_index].sh_flags & SHF_GROUP) == SHF_GROUP)
		{
			printf("\tSection is member of a group\n");
		}
		if((sh_list[section_index].sh_flags & SHF_TLS) == SHF_TLS)
		{
			printf("\tSection holds thread-local data\n");
		}
		if((sh_list[section_index].sh_flags & SHF_ORDERED) == SHF_ORDERED)
		{
			printf("\tSpecial ordering requirement (Solaris)\n");
		}
		if((sh_list[section_index].sh_flags & SHF_EXCLUDE) == SHF_EXCLUDE)
		{
			printf("\tSection is excluded unless referenced or allocated (Solaris)\n");
		}

		if(sh_list[section_index].sh_addr)
		{
			printf("Section loads to 0x"PRIxLEAST64"\n", sh_list[section_index].sh_addr);
		}

		// Load section and analyze
		// parse_section(fp, sh_list[section_index], sh_list[section_index].sh_offset, sh_list[section_index].sh_size);

	}

}




void parse_program_headers(FILE *fp, Elf64_Ehdr header)
{
	printf("================================================================================\n");
	Elf64_Phdr program_header;
	fseek(fp, header.e_phoff, 0);
	fread(&program_header, sizeof(program_header), 1, fp);

	printf("Program type: ");
	switch(program_header.p_type)
	{
		case PT_NULL:
			printf("Unused\n");
			break;
		case PT_LOAD:
			printf("Loadable program segment\n");
			break;
		case PT_DYNAMIC:
			printf("Dynamic linking information\n");
			break;
		case PT_INTERP:
			printf("Program interpreter\n");
			break;
		case PT_NOTE:
			printf("Auxiliary information\n");
			break;
		case PT_SHLIB:
			printf("Reserved\n");
			break;
		case PT_PHDR:
			printf("Entry for the header table\n");
			break;
		case PT_TLS:
			printf("Thread-local storage segment\n");
			break;
		case PT_NUM:
			printf("Number of defined types\n");
			break;
		case PT_GNU_EH_FRAME:
			printf("GCC .eh_frame_hdr segment");
			break;
		case PT_GNU_STACK:
			printf("Indicates stack executability");
			break;
		case PT_GNU_RELRO:
			printf("Read-only after relocation");
			break;
		case PT_SUNWBSS:
			printf("Sun Specific segment");
			break;
		case PT_SUNWSTACK:
			printf("Stack segment");
			break;
		case PT_HIOS:
			printf("End of OS-specific");
			break;
		case PT_LOPROC: 
			printf("Start of processor-specific");
			break;
		case PT_HIPROC:
			printf("End of processor-specific");
			break;
	}
}


void parse_section(FILE *fp, Elf64_Shdr section_header, Elf64_Off offset, Elf64_Word size)
{

}
