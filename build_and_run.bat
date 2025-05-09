@echo off
REM === devOS build and QEMU run script ===

REM Set up environment (edit these paths if needed)
set CC=gcc
set NASM=nasm
set QEMU=qemu-system-i386
set CFLAGS=-ffreestanding -O2 -Wall -Wextra -Iinclude

REM Clean old build
if exist kernel.bin del kernel.bin

REM Assemble bootloader
%NASM% -f elf32 kernel/boot.s -o kernel/boot.o || goto :error

REM Compile kernel sources
%CC% %CFLAGS% -c kernel/kernel.c -o kernel/kernel.o || goto :error
%CC% %CFLAGS% -c kernel/scheduler.c -o kernel/scheduler.o || goto :error
%CC% %CFLAGS% -c kernel/syscall.c -o kernel/syscall.o || goto :error
%CC% %CFLAGS% -c kernel/process.c -o kernel/process.o || goto :error
%CC% %CFLAGS% -c kernel/memory.c -o kernel/memory.o || goto :error
%CC% %CFLAGS% -c kernel/timer.c -o kernel/timer.o || goto :error
%CC% %CFLAGS% -c shell/shell.c -o shell/shell.o || goto :error
%CC% %CFLAGS% -c shell/builtin.c -o shell/builtin.o || goto :error
%CC% %CFLAGS% -c shell/command.c -o shell/command.o || goto :error
%CC% %CFLAGS% -c wm/wm.c -o wm/wm.o || goto :error
%CC% %CFLAGS% -c wm/terminal.c -o wm/terminal.o || goto :error
%CC% %CFLAGS% -c drivers/keyboard.c -o drivers/keyboard.o || goto :error
%CC% %CFLAGS% -c drivers/screen.c -o drivers/screen.o || goto :error
%CC% %CFLAGS% -c drivers/vga.c -o drivers/vga.o || goto :error
%CC% %CFLAGS% -c utils/log.c -o utils/log.o || goto :error
%CC% %CFLAGS% -c utils/k_stdio.c -o utils/k_stdio.o || goto :error
%CC% %CFLAGS% -c utils/k_memory.c -o utils/k_memory.o || goto :error
%CC% %CFLAGS% -c utils/k_string.c -o utils/k_string.o || goto :error

REM Link kernel (use gcc as linker)
%CC% -ffreestanding -nostdlib -T kernel/linker.ld -Wl,--oformat=binary -o kernel.bin kernel/boot.o kernel/kernel.o kernel/scheduler.o kernel/syscall.o kernel/process.o kernel/memory.o kernel/timer.o shell/shell.o shell/builtin.o shell/command.o wm/wm.o wm/terminal.o drivers/keyboard.o drivers/screen.o drivers/vga.o utils/log.o utils/k_stdio.o utils/k_memory.o utils/k_string.o || goto :error

REM Copy kernel.bin to ISO boot folder
copy /Y kernel.bin iso\boot\kernel.bin || goto :error

REM Create ISO using grub-mkrescue
if not exist devos.iso del devos.iso
where grub-mkrescue >nul 2>&1
if errorlevel 1 (
    echo grub-mkrescue not found! Falling back to direct kernel boot.
    %QEMU% -kernel kernel.bin
    goto :eof
)
grub-mkrescue -o devos.iso iso || goto :error

REM Run in QEMU using the ISO
%QEMU% -cdrom devos.iso

goto :eof

REM Run in QEMU (no ISO, boot kernel directly)
%QEMU% -kernel kernel.bin

goto :eof
:error
echo Build failed!
pause