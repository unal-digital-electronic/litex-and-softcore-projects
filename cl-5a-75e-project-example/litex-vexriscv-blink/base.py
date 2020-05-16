#!/usr/bin/env python3

from migen import *

from migen.genlib.io import CRG

from litex.build.generic_platform import IOStandard, Subsignal, Pins
from litex_boards.platforms import colorlight_5a_75e

from litex.soc.integration.soc_core import *
from litex.soc.integration.builder import *

from ios import Led

# IOs ----------------------------------------------------------------------------------------------

_serial = [
    ("serial", 0,
        Subsignal("tx", Pins("F3")), # J1.1
        # Subsignal("rx", Pins("M13")), # J1.2
        Subsignal("rx", Pins("F1")), # J1.2
        IOStandard("LVCMOS33")
    ),
]

# BaseSoC -----------------------------------------------------------------------------------------

class BaseSoC(SoCCore):
    def __init__(self, revision):
        platform = colorlight_5a_75b.Platform(revision)
        sys_clk_freq = int(25e6)

        platform.add_extension(_serial)

        # SoC with CPU
        SoCCore.__init__(self, platform,
            cpu_type                 = "vexriscv",
            clk_freq                 = 25e6,
            ident                    = "LiteX CPU Test SoC 5A-75B", ident_version=True,
            integrated_rom_size      = 0x8000,
            integrated_main_ram_size = 0x4000)

        # Clock Reset Generation
        self.submodules.crg = CRG(platform.request("clk25"), ~platform.request("user_btn_n"))
        # self.submodules.crg = CRG(platform.request("clk25"), platform.request("user_btn_n"))

        # Led
        user_leds = Cat(*[platform.request("user_led_n", i) for i in range(1)])
        self.submodules.leds = Led(user_leds)
        self.add_csr("leds")


# Build --------------------------------------------------------------------------------------------

soc = BaseSoC(revision="7.0")

builder = Builder(soc, output_dir="build", csr_csv="test/csr.csv")
builder.build()
