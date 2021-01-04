/* �G���g���|�C���g�̎w�� */
ENTRY(Reset_Handler)

/*****************************************************************************************************/
/* ��������` */
/*****************************************************************************************************/
MEMORY
{
    RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 0x20000          /* 0x20000000 ����  128KB       */
    ROM (rx)    : ORIGIN = 0x08000000, LENGTH = 0x100000         /* 0x08000000 ���� 1024KB FLASH */
}

/*****************************************************************************************************/
/* �q�[�v�T�C�Y */
/*****************************************************************************************************/
HEAP_SIZE = 0x100;    /* size: 256 bytes */

/*****************************************************************************************************/
/* �㌋���V���{�� */
/* ���Œ�`����Ă��Ȃ���΁A���̒l�ł��肢���܂��v�Ƃ����V���{����` */
/*****************************************************************************************************/
PROVIDE (__main_stack_start =    0x20020000);                    /* �X�^�b�N�T�C�Y��ݒ� 0x20020000����0x400 (1024 bytes) */
PROVIDE (_pvHeapStart = __main_stack_start - 0x400 - HEAP_SIZE); /* �q�[�v�T�C�Y��ݒ� */

/*****************************************************************************************************/
/* �Z�N�V������` */
/*****************************************************************************************************/
SECTIONS
{
    /* The startup code into ROM memory */
    /* �x�N�^�[�e�[�u���z�u�p�̃Z�N�V���� */
    .isr_vector :
    {
        . = ALIGN(4);        /* ���P�[�V�����J�E���^����4byte�A���C������ */
        KEEP(*(.isr_vector)) /* vector�e�[�u�� */
                             /* ()�O��*�́u�C�ӂ̃t�@�C�����v���Ӗ����� */
                             /* ()����*�́u�C�ӂ̃Z�N�V�������v���Ӗ����� */
                             /* KEEP()�́A���g�p�̃V���{�����K�x�[�W�R���N�V�����ɓ���邱�Ƃ������Ȃ��B�����J�ɂ�郊���N�ȗ�������邽�߂̑΍� */
        . = ALIGN(4);        /* ���P�[�V�����J�E���^����4byte�A���C������ */
    } >ROM                   /* ROM�ɔz�u */

    /* �v���O�����R�[�h����т��̑��̃f�[�^��ROM�ɔz�u���� */
    .text :
    {
        . = ALIGN(4);        /* ���P�[�V�����J�E���^����4byte�A���C������ */
        *(.text)             /* .text sections (code) */
        *(.text*)            /* .text* sections (code) */
        *(.glue_7)           /* glue arm to thumb code �����錾����Ă��Ȃ��Z�N�V�������H */
        *(.glue_7t)          /* glue thumb to arm code �����錾����Ă��Ȃ��Z�N�V�������H */
        *(.eh_frame)

        KEEP (*(.init))      /* �ǂ����̃t�@�C���ɂ���.init�������ɔz�u */
        KEEP (*(.fini))      /* �ǂ����̃t�@�C���ɂ���.fini�������ɔz�u */

        . = ALIGN(4);        /* ���P�[�V�����J�E���^����4byte�A���C������ */

        _etext = .;          /* define a global symbols at end of code */
                             /* _etext�Ƃ����V���{���Ƀ��P�[�V�����J�E���^�̃A�h���X(��΃A�h���X)��ݒ肵�Ă��� */
                             /* �܂�v���O�����R�[�h�̍Ō��_etext��z�u���Ă��� */
    } >ROM

    /* �萔(const)���i�[���邽�߂̃Z�N�V������ROM�ɔz�u */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)          /* .rodata sections (constants, strings, etc.) */
        *(.rodata*)         /* .rodata* sections (constants, strings, etc.) */
        . = ALIGN(4);
    } >ROM

    /* ��O�e�[�u��(newlib) */
    .ARM.extab : 
    {
        . = ALIGN(4);
        *(.ARM.extab* .gnu.linkonce.armextab.*)
        . = ALIGN(4);
    } >ROM

    /* ��O�C���f�b�N�X(newlib) */
    .ARM : 
    {
        . = ALIGN(4);
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
        . = ALIGN(4);
    } >ROM

    /* ����Z�N�V���� */
    .preinit_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        . = ALIGN(4);
    } >ROM

    .init_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
        . = ALIGN(4);
    } >ROM

    .fini_array :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
        . = ALIGN(4);
    } >ROM

    /* Used by the startup to initialize data */
    /* C����Ŏg�p���������ߕϐ��錾���Ă��� */
    _sidata = LOADADDR(.data);

    /* LOADADDR()�� ROM�iAT> ROM�j�̃A�h���X��Ԃ� */
    /* ADDR()�� RAM �i>RAM�j�̃A�h���X��Ԃ� */

    /* �v���O�����̂��������l�����ϐ����i�[���邽�߂̃Z�N�V������RAM�ɔz�u */
    .data :
    {
        . = ALIGN(4);       /* ���P�[�V�����J�E���^����4byte�A���C������ */

        _sdata = .;         /* create a global symbol at data start */
                            /* ���P�[�V�����J�E���^�ɑ�������ꍇ�A�Z�N�V�����u���b�N�̐擪�A�h���X����̃I�t�Z�b�g(���΃A�h���X) */
                            /* �ϐ��Ƀ��P�[�V�����J�E���^���������ꍇ�A��΃A�h���X�ɂȂ� */

        *(.data)            /* .data sections */
        *(.data*)           /* .data* sections */

        . = ALIGN(4);       /* ���P�[�V�����J�E���^����4byte�A���C������ */
        
        _edata = .;         /* define a global symbol at data end */
                            /* ���������ꂽ�f�[�^�̃Z�O�����g�̖����̎��̃A�h���X */
    } >RAM AT> ROM          /* ��UROM�ɔz�u���ă}�C�R���N������RAM�ɃR�s�[ */
                            /* �o�C�i���Ƃ��Ă͔z�u��͂Ƃ肠���� AT > */
                            /* �v���O�������̕��򓙁A�A�h���X��p����l�� > �ɔz�u */

    /* Uninitialized data section into RAM memory */
    /* �v���O�����̂����A�����l�������Ȃ��ϐ����i�[���邽�߂̃Z�N�V������RAM�ɔz�u */
    . = ALIGN(4);           /* ���P�[�V�����J�E���^����4byte�A���C������ */
    .bss :
    {
        /* This is used by the startup in order to initialize the .bss secion */
        _sbss = .;         /* define a global symbol at bss start */

        __bss_start__ = _sbss;

        *(.bss)
        *(.bss*)
        *(COMMON)         /* COMMON�̓R�����V���{���p�̓��̓Z�N�V���� */

        . = ALIGN(4);

        _ebss = .;         /* define a global symbol at bss end */

        __bss_end__ = _ebss;
    } >RAM

    /* �\����RAM���c���Ă��邱�Ƃ��m�F���邽�߂Ɏg�p */
    /* �����炭�r���h�Ɏ��s�����Ƃ��̓����J�G���[���łăq�[�v�̈���m�ۂł��Ȃ��Ƃ������Ƃ��킩��E�E�E�͂� */
    /* �uNOLOAD�v�̎w�肪���邽�߁A�I�u�W�F�N�g�̎��̂Ƃ��ďo�͂���Ȃ� */
    ._user_heap_stack _pvHeapStart(NOLOAD) :
    {
        . = ALIGN(8);

        PROVIDE ( end = . );
        PROVIDE ( _end = . );

        . = . + HEAP_SIZE;
        /* . = . + Min_Stack_Size */

        . = ALIGN(8);
    } >RAM

    /* �����ɋL�q���ꂽ �I�u�W�F�N�g�Z�N�V�����̓����N����Ȃ� */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }

    .ARM.attributes 0 : 
    {
        *(.ARM.attributes) 
    }
}
