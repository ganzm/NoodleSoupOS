OBJECTS = src/loader.o src/kmain.o src/fb.o src/io.o src/serial.o src/debug.o src/string.o src/descriptor_table.o src/interrupt.o src/int_handler_base.o
CC = gcc
CFLAGS = -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs -Wall -Wextra -Werror -c
LDFLAGS = -T src/link.ld -melf_i386
AS = nasm
ASFLAGS = -f elf -g

all: NoodleSoupOS.iso

kernel.elf: $(OBJECTS)
	ld $(LDFLAGS) $(OBJECTS) -o kernel.elf

kernel.sym: kernel.elf
	nm kernel.elf | grep " T " | awk '{ print $$1" "$$3 }' > kernel.sym

NoodleSoupOS.iso: kernel.elf kernel.sym
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                      \
	    -b boot/grub/stage2_eltorito    \
	    -no-emul-boot                   \
	    -boot-load-size 4               \
	    -A os                           \
	    -input-charset utf8             \
	    -quiet                          \
	    -boot-info-table                \
	    -o NoodleSoupOS.iso             \
	    iso

run: NoodleSoupOS.iso
	bochs -f bochsrc.txt -q

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

clean:
	rm -rf src/*.o log/* kernel.elf kernel.sym NoodleSoupOS.iso
