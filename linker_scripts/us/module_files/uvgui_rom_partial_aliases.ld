/* Native GUI storage aliases for the partial relocatable link.
 * No allocation: preserve the six C pools and eight intervening import words.
 * These observed addresses do not assert historical object capacities. */
SECTIONS
{
    .bss 0 :
    {
        *(.bss)
        D_uvgui_rom_00407218 = sGuiVectorSlots + 0x2F8;
        D_uvgui_rom_0040721C = sGuiVectorSlots + 0x2FC;
        D_uvgui_rom_00407220 = sGuiVectorSlots + 0x300;
        D_uvgui_rom_00407224 = sGuiVectorSlots + 0x304;
        D_uvgui_rom_00407228 = sGuiVectorSlots + 0x308;
        D_uvgui_rom_0040722C = sGuiVectorSlots + 0x30C;
        D_uvgui_rom_00407234 = sGuiVectorSlots + 0x314;
        D_uvgui_rom_00407230 = sGuiVectorSlots + 0x310;
        D_uvgui_rom_00407238 = sGuiMenuItems + 0x0;
        D_uvgui_rom_00408A98 = sGuiMenus + 0x0;
        D_uvgui_rom_00408D78 = sGuiMenuOptions + 0x0;
        D_uvgui_rom_0040D558 = sGuiScalarSlots + 0x0;
        D_uvgui_rom_0040FB50 = sGuiValueSlots + 0x0;
        D_uvgui_rom_0040D576 = sGuiScalarSlots + 0x1E;
        D_uvgui_rom_0040FBAE = sGuiValueSlots + 0x5E;
        D_uvgui_rom_00406F20 = sGuiVectorSlots + 0x0;
        D_uvgui_rom_00406F3E = sGuiVectorSlots + 0x1E;
    }
}
