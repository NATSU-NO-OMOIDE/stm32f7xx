/* エントリポイントの指定 */
ENTRY(Reset_Handler)

/*****************************************************************************************************/
/* メモリ定義 */
/*****************************************************************************************************/
MEMORY
{
    RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 0x20000          /* 0x20000000 から  128KB       */
    ROM (rx)    : ORIGIN = 0x08000000, LENGTH = 0x100000         /* 0x08000000 から 1024KB FLASH */
}

/*****************************************************************************************************/
/* ヒープサイズ */
/*****************************************************************************************************/
HEAP_SIZE = 0x100;    /* size: 256 bytes */

/*****************************************************************************************************/
/* 弱結合シンボル */
/* 他で定義されていなければ、この値でお願いします」というシンボル定義 */
/*****************************************************************************************************/
PROVIDE (__main_stack_start =    0x20020000);                    /* スタックサイズを設定 0x20020000から0x400 (1024 bytes) */
PROVIDE (_pvHeapStart = __main_stack_start - 0x400 - HEAP_SIZE); /* ヒープサイズを設定 */

/*****************************************************************************************************/
/* セクション定義 */
/*****************************************************************************************************/
SECTIONS
{
    /* The startup code into ROM memory */
    /* ベクターテーブル配置用のセクション */
    .isr_vector :
    {
        . = ALIGN(4);        /* ロケーションカウンタから4byteアラインする */
        KEEP(*(.isr_vector)) /* vectorテーブル */
                             /* ()外の*は「任意のファイル名」を意味する */
                             /* ()内の*は「任意のセクション名」を意味する */
                             /* KEEP()は、未使用のシンボルをガベージコレクションに入れることを許可しない。リンカによるリンク省略を避けるための対策 */
        . = ALIGN(4);        /* ロケーションカウンタから4byteアラインする */
    } >ROM                   /* ROMに配置 */

    /* プログラムコードおよびその他のデータをROMに配置する */
    .text :
    {
        . = ALIGN(4);        /* ロケーションカウンタから4byteアラインする */
        *(.text)             /* .text sections (code) */
        *(.text*)            /* .text* sections (code) */
        *(.glue_7)           /* glue arm to thumb code 実質宣言されていないセクション名？ */
        *(.glue_7t)          /* glue thumb to arm code 実質宣言されていないセクション名？ */
        *(.eh_frame)

        KEEP (*(.init))      /* どこかのファイルにある.initをここに配置 */
        KEEP (*(.fini))      /* どこかのファイルにある.finiをここに配置 */

        . = ALIGN(4);        /* ロケーションカウンタから4byteアラインする */

        _etext = .;          /* define a global symbols at end of code */
                             /* _etextというシンボルにロケーションカウンタのアドレス(絶対アドレス)を設定している */
                             /* つまりプログラムコードの最後に_etextを配置している */
    } >ROM

    /* 定数(const)を格納するためのセクションをROMに配置 */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)          /* .rodata sections (constants, strings, etc.) */
        *(.rodata*)         /* .rodata* sections (constants, strings, etc.) */
        . = ALIGN(4);
    } >ROM

    /* 例外テーブル(newlib) */
    .ARM.extab : 
    {
        . = ALIGN(4);
        *(.ARM.extab* .gnu.linkonce.armextab.*)
        . = ALIGN(4);
    } >ROM

    /* 例外インデックス(newlib) */
    .ARM : 
    {
        . = ALIGN(4);
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
        . = ALIGN(4);
    } >ROM

    /* 特殊セクション */
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
    /* C言語で使用したいため変数宣言している */
    _sidata = LOADADDR(.data);

    /* LOADADDR()は ROM（AT> ROM）のアドレスを返す */
    /* ADDR()は RAM （>RAM）のアドレスを返す */

    /* プログラムのうち初期値を持つ変数を格納するためのセクションをRAMに配置 */
    .data :
    {
        . = ALIGN(4);       /* ロケーションカウンタから4byteアラインする */

        _sdata = .;         /* create a global symbol at data start */
                            /* ロケーションカウンタに代入した場合、セクションブロックの先頭アドレスからのオフセット(相対アドレス) */
                            /* 変数にロケーションカウンタを代入した場合、絶対アドレスになる */

        *(.data)            /* .data sections */
        *(.data*)           /* .data* sections */

        . = ALIGN(4);       /* ロケーションカウンタから4byteアラインする */
        
        _edata = .;         /* define a global symbol at data end */
                            /* 初期化されたデータのセグメントの末尾の次のアドレス */
    } >RAM AT> ROM          /* 一旦ROMに配置してマイコン起動時にRAMにコピー */
                            /* バイナリとしては配置先はとりあえず AT > */
                            /* プログラム中の分岐等、アドレスを用いる値は > に配置 */

    /* Uninitialized data section into RAM memory */
    /* プログラムのうち、初期値を持たない変数を格納するためのセクションをRAMに配置 */
    . = ALIGN(4);           /* ロケーションカウンタから4byteアラインする */
    .bss :
    {
        /* This is used by the startup in order to initialize the .bss secion */
        _sbss = .;         /* define a global symbol at bss start */

        __bss_start__ = _sbss;

        *(.bss)
        *(.bss*)
        *(COMMON)         /* COMMONはコモンシンボル用の入力セクション */

        . = ALIGN(4);

        _ebss = .;         /* define a global symbol at bss end */

        __bss_end__ = _ebss;
    } >RAM

    /* 十分なRAMが残っていることを確認するために使用 */
    /* おそらくビルドに失敗したときはリンカエラーがでてヒープ領域を確保できないということがわかる・・・はず */
    /* 「NOLOAD」の指定があるため、オブジェクトの実体として出力されない */
    ._user_heap_stack _pvHeapStart(NOLOAD) :
    {
        . = ALIGN(8);

        PROVIDE ( end = . );
        PROVIDE ( _end = . );

        . = . + HEAP_SIZE;
        /* . = . + Min_Stack_Size */

        . = ALIGN(8);
    } >RAM

    /* ここに記述された オブジェクトセクションはリンクされない */
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

