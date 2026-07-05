# 1 "main.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "main.c"







int main(void) {

    (*(volatile unsigned int *)(0x40023800 + 0x30)) |= (1 << 0);


    (*(volatile unsigned int *)(0x40020000 + 0x00)) |= (1 << 22);
    (*(volatile unsigned int *)(0x40020000 + 0x00)) &= ~(1 << 23);

    while (1) {

        (*(volatile unsigned int *)(0x40020000 + 0x14)) ^= (1 << 11);


        for(unsigned int i = 0; i <= 4194303; i++);;
    }
}
