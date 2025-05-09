# devOS

A minimal, kernel-compatible operating system designed for learning and experimentation.

## Building

To build and run devOS, simply run:

```bash
build_and_run.bat
```

This script will:
1. Compile all kernel components
2. Link the kernel
3. Create an ISO (if GRUB tools are available)
4. Run the OS in QEMU

## Build Modes

The build system supports two modes:

1. **Direct Kernel Boot** (Default)
   - Uses QEMU's direct kernel loading
   - Requires no additional tools
   - Faster build and test cycle

2. **ISO Boot** (Optional)
   - Creates a bootable ISO using GRUB
   - Requires GRUB tools
   - More realistic boot experience

## Requirements

### Core Requirements (Required)
- GCC (MinGW on Windows)
- NASM
- QEMU
- GRUB tools (grub-mkrescue)

### Linux-Specific Setup

1. **Install Dependencies**
   ```bash
   sudo apt update
   sudo apt install build-essential nasm qemu-system-x86 xorriso
   ```

2. **Build and Run**
   ```bash
   # Build and run using the Windows script
   ./build_and_run.bat
   
   # Or build directly (for linux)
   gcc -ffreestanding -nostdlib -T kernel/linker.ld -o kernel.bin kernel/*.o shell/*.o wm/*.o drivers/*.o utils/*.o
   qemu-system-i386 -kernel kernel.bin
   ```

### Directory Structure

```
.
├── build_and_run.bat     # Build and run script
├── kernel/               # Kernel source
├── shell/               # Shell implementation
├── wm/                  # Window manager
├── fs/                  # File system
├── drivers/             # Hardware drivers
├── utils/              # Utility functions
├── include/            # Header files
└── iso/               # ISO build files
```

## Development Notes

1. All kernel code is free of standard library dependencies
2. Kernel-safe functions are prefixed with `k_`
3. Memory management is handled by kernel-safe functions
4. String operations use kernel-safe implementations

### Linux-Specific Notes

1. **Build System**
   - The Windows batch script works on Linux with Wine
   - Alternatively, use the provided Makefile
   - Direct GCC compilation is also supported

2. **Development Environment**
   - Use your favorite Linux IDE/editor
   - Debug with GDB
   - Test with QEMU
   - Build ISOs with GRUB tools

3. **Best Practices**
   - Use Linux-native tools for development
   - Test on both Windows and Linux
   - Maintain cross-platform compatibility
   - Document Linux-specific changes

## Troubleshooting

1. If build fails:
   - Ensure all required tools are installed
   - Check for compiler warnings
   - Verify linker script

2. If QEMU fails to boot:
   - Check kernel binary format
   - Verify bootloader configuration
   - Try both ISO and direct boot modes

## Contributing

Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Submit a pull request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Why Choose DevOS?

### Advantages Over Starting From Scratch

1. **Time-Saving Foundation**
   - Complete kernel structure
   - Working bootloader
   - Basic system services
   - Memory management
   - Process handling
   - File system basics

2. **Proven Architecture**
   - Tested kernel components
   - Working build system
   - Proper memory management
   - Correct system call handling
   - Proper process isolation

3. **Learning Curve**
   - Clear code organization
   - Well-documented components
   - Educational examples
   - Real-world implementations

### Why Fork Instead of Starting New?

1. **Immediate Productivity**
   - Start coding your features right away
   - No need to reinvent basic OS concepts
   - Focus on your specific goals

2. **Community Benefits**
   - Learn from existing implementations
   - Contribute back to the community
   - Get help from other developers
   - Share your improvements

3. **Risk Reduction**
   - Avoid common pitfalls
   - Learn from existing mistakes
   - Build on proven concepts
   - Faster iteration cycles

### What You Get When You Fork

1. **Complete Development Environment**
   - Working build system
   - Tested configurations
   - Proper toolchain setup
   - Virtualization support

2. **Educational Resources**
   - Well-commented code
   - Structured examples
   - Clear architecture
   - Development guidelines

3. **Modular Structure**
   - Easy to modify components
   - Clear separation of concerns
   - Independent modules
   - Simple integration points

### Development Philosophy

- **Minimalist**: Only essential features
- **Modular**: Easy to modify and extend
- **Educational**: Clear code structure
- **Practical**: Real-world OS concepts

### Getting Started Tips

1. **Start Small**
   - Begin with simple modifications
   - Understand the existing code
   - Build your knowledge gradually

2. **Focus on Your Goals**
   - Identify your specific needs
   - Modify relevant components
   - Test thoroughly
   - Document your changes

3. **Contribute Back**
   - Share your improvements
   - Help other developers
   - Enhance the community
   - Make DevOS better for everyone

---

*Note: This project is designed to be a starting point, not a complete OS. Feel free to modify, extend, and improve it to suit your needs.*

---

*devOS — made by Alex Andrew Roman.*
