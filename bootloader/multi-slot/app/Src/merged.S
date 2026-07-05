.section .bootloader_section
    .incbin "../../bootloader/Build/bootloader.bin"

.section .factory_section
    .incbin "../../factory_app/Build/factory.bin"