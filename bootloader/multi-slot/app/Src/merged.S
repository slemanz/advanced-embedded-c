.section .bootloader_section
    .incbin "../../bootloader/Build/bootloader.bin"

.section .factory_section
    .incbin "../../factory-app/Build/factory.bin"