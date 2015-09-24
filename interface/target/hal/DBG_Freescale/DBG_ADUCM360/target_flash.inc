/* CMSIS-DAP Interface Firmware
 * Copyright (c) 2009-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "target_flash.h"

const uint32_t flash_algo_blob[] = {
    0xE00ABE00, 0x062D780D, 0x24084068, 0xD3000040, 0x1E644058, 0x1C49D1FA, 0x2A001E52, 0x4770D1F2,
    0x4770ba40, 0x4770bac0, 0x4603b510, 0x4c4d2000, 0xf64f8020, 0x4c4c70ff, 0x1d248020, 0x20048020, 
    0x3c244c49, 0x20008020, 0x4601bd10, 0x4a462000, 0x80103a24, 0x48444770, 0x88003828, 0x4a422004, 
    0x80103a24, 0x4056f24f, 0x3a084a3f, 0xf24f8010, 0x80101023, 0x4a3c2003, 0x80103a20, 0x483abf00, 
    0x88013828, 0x0f04f011, 0xf011d0f9, 0xd0010f30, 0x47702001, 0xe7fc2000, 0x48334601, 0x88003828, 
    0x4b312004, 0x80183b24, 0x4056f24f, 0x3b084b2e, 0xf24f8018, 0x80181023, 0x3b184b2b, 0xf64f8019, 
    0xea0070ff, 0x1d1b4011, 0x20018018, 0x3b204b26, 0xbf008018, 0x38284824, 0xf0128802, 0xd0f90f04, 
    0x0f30f012, 0x2001d001, 0x20004770, 0xb5f8e7fc, 0x46154604, 0x462a4623, 0x4056f24f, 0x3f084f1a, 
    0xf24f8038, 0x80381023, 0x38284817, 0xe0248800, 0xd2182904, 0x37fff04f, 0x46689700, 0xd0092901, 
    0xd0042902, 0xd1082903, 0x70877897, 0x7857bf00, 0xbf007047, 0x70077817, 0xbf00e000, 0x9f00bf00, 
    0x2104c380, 0xca01e001, 0xbf00c301, 0x38284806, 0xf0168806, 0xd0f90f08, 0x29001f09, 0x2000d1d8, 
    0x0000bdf8, 0x40002588, 0x40002828, 0x00000000, 
};

static const TARGET_FLASH flash = {
    0x20000029, // Init
    0x2000004B, // UnInit
    0x20000057, // EraseChip
    0x20000099, // EraseSector
    0x200000EF, // ProgramPage
    // breakpoint = RAM start + 1
    // RSB : base address is address of Execution Region PrgData in map file
    //       to access global/static data
    // RSP : Initial stack pointer
    {
        0x20000001, // breakpoint instruction address
        0x20000000 + 0x20 + 0x300,  // static base register value (image start + header + static base offset)
        0x20001000  // initial stack pointer
    },

    0x20001500, // program_buffer, any valid RAM location with +512 bytes of headroom
    0x20000000, // algo_start, start of RAM
    sizeof(flash_algo_blob), // algo_size, size of array above
    flash_algo_blob,  // image, flash algo instruction array
    512        // ram_to_flash_bytes_to_be_written
};
