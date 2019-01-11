arm-none-eabi-gcc -std=c11 -pedantic -c main.c -mthumb-interwork -mthumb -O2 -o main.o -lm
arm-none-eabi-gcc -std=c11 -pedantic main.o -mthumb-interwork -mthumb -specs=gba.specs -o main.elf -lm
arm-none-eabi-objcopy -v -O binary main.elf main.gba
gbafix main.gba