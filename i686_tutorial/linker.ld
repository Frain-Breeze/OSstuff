ENTRY(_start) /* in the assembly, for it to jump to on start, where we make a stack and whatnot*/

SECTIONS
{
    . = 1M; /* this will start putting our sections in mem starting at 1MiB, which is conventional*/

    /* first put in the multiboot header, then some text*/
    .text BLOCK(4K) : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }

    /* read-only data*/
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /*read-write data (initialized)*/
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* read-write data (uninitialized) and stack*/
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }

}