# Pong-i386
![](https://i.imgur.com/VuXNthr.gif)
<br>Bare metal [Pong](https://en.wikipedia.org/wiki/Pong) on the Intel i386 architecture.

## Usage
### Quick Start
Install the latest [Pong-i386.iso](https://github.com/zeim839/Pong-i386/releases) from Github releases. Boot the file as a cdrom disk image on your system or preferred virtual machine. A minimal [qemu](https://www.qemu.org/download/) example is illustrated below:
```
qemu-system-i386 -cdrom Pong-i386.iso
```
### Building from source
Alternatively, a bootable image can be generated by building the project from source. However, since the compilation target system is different from that of your machine, an i386-specific toolchain needs to be configured (see [here](https://flint.cs.yale.edu/cs422/tools/index.html) or [here](https://wiki.osdev.org/GCC_Cross-Compiler) for instructions, I recommend doing this on a modern Linux distribution). Additionally, the `grub-mkrescue` tool and its respective dependencies will also need to be installed.
<br><br>
Begin by cloning and navigating to the project directory:
```
git clone https://github.com/zeim839/Pong-i386.git
cd Pong-i386
```
Next, export your toolchain path as variable P (replacing `../opt/cross/bin` with your own path):
```
export P=../opt/cross/bin
```
Then compile & create the iso image:
```
make && make image
```

Finally, run the .iso using qemu or your preferred virtual machine:
```
qemu-system-i386 -cdrom Pong-i386.iso
```

## License
[GNU General Public License](https://github.com/zeim839/Pong-i386/blob/main/LICENSE)
