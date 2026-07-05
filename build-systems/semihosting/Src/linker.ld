ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx): ORIGIN =0x08000000, LENGTH =256K
    SRAM(rwx): ORIGIN =0x20000000, LENGTH =60K
}

_estack = ORIGIN(SRAM) + LENGTH(SRAM);

__max_heap_size = 0x400;
_Min_Stack_Size =  __max_heap_size;
__max_stack_size = 0x400;

/* Sections */
SECTIONS
{
    .text :
    {
        . = ALIGN(4);
        *(.isr_vector_tbl)  
        *(.text)            
        *(.rodata)          
        . = ALIGN(4);
        _etext = .;         
    } > FLASH


    _ldata = LOADADDR(.data);
    .data :
    {
        . = ALIGN(4);
        _sdata = .;         
        *(.data)            
        . = ALIGN(4);
        _edata = .;         
    } > SRAM AT> FLASH
    

    /*third section of output file*/
    .bss :
    {
        . = ALIGN(4);
        _sbss = .;          
        __bss_start__ = _sbss;          
        *(.bss)             
        . = ALIGN(4);
        _ebss = .;  
        __bss_end__ = _ebss;  

    } > SRAM AT> FLASH 

    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + __max_heap_size;
        . = . + __max_stack_size;
        . = ALIGN(8);
        end = .;
        __end__ = end;
    } >SRAM
}
