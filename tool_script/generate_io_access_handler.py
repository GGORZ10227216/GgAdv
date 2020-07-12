fp = open("./IOmap", "r")
mapInfo = fp.readlines()
fp.close()


def mode_format(mode_name):
    for char in "\"/":
        mode_name = mode_name.replace(char, "")
    return mode_name


mapName = ""
enumContent = ""
wave_ram_declare = "\tconstexpr static IOReg_t<uint16_t, AccessMode::RW> WAVE_RAM{num}_{hl} = {{0x{addr:x}}};\n"
for i in range(len(mapInfo)):
    fields = mapInfo[i].split()
    if len(fields) == 0:
        if mapName != "" and enumContent != "":
            fp = open("../include/mmu/IO/" + mapName + ".h", "w+")
            fp.write("#include <ioreg_type.h>\n\n")
            fp.write("#ifndef CPU_" + mapName.upper() + "_H\n")
            fp.write("#define CPU_" + mapName.upper() + "_H\n\n")
            fp.write("namespace IO_Map {\n")
            fp.write(enumContent)
            fp.write("}\n\n")
            fp.write("#endif // CPU_" + mapName.upper() + "_H")
            fp.close()
            mapName = ""
            enumContent = ""
    elif len(fields) == 1:
        mapName = fields[0].lower()
    else:
        ignoredTag = ["-", "Not", "?", "(3DS)", "IR"]
        if fields[3] not in ignoredTag:
            if fields[3] == "WAVE_RAM":
                waveRamBaseAddr = int(fields[0][:-1], 16)
                print(waveRamBaseAddr)
                for ramNum in range(4):
                    baseAddr2 = waveRamBaseAddr + ramNum * 4
                    enumContent += wave_ram_declare.format(num=ramNum, hl='L', addr=baseAddr2)
                    enumContent += wave_ram_declare.format(num=ramNum, hl='H', addr=baseAddr2 + 2)
            else:
                enumContent += \
                    "\tconstexpr static IOReg_t<uint{size}_t, AccessMode::{mode}> {name} = {{0x{addr}}};\n".format(
                        size=("16" if fields[1] == "2" else "32"),
                        mode=mode_format(fields[2]),
                        name=fields[3],
                        addr=fields[0][:-1].lower()
                    )
