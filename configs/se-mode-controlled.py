import sys, os

from gem5.isas import ISA
from gem5.prebuilt.riscvmatched.riscvmatched_board import RISCVMatchedBoard
from gem5.simulate.simulator import Simulator
from gem5.utils.requires import requires
from m5.objects import Process, SEWorkload
import m5

from gem5.resources.resource import Resource, BinaryResource
from gem5.simulate.exit_event import ExitEvent



requires(isa_required=ISA.RISCV)

# instantiate the riscv matched board with default parameters
board = RISCVMatchedBoard()

# set the hello world riscv binary as the board workload
binary_path = os.path.join(
    os.path.dirname(os.path.realpath(__file__)),
    "..",
    sys.argv[1],
)

binary = BinaryResource(binary_path)
board.set_se_binary_workload(binary)

def on_work_begin():
    print("Work begin")
    m5.stats.reset()
    yield False

def on_work_end():
    m5.stats.dump()
    print("Work end")
    yield True

def on_exit():
    yield True

# run the simulation with the RISCV Matched board
simulator = Simulator(
    board=board, 
    full_system=False,
    on_exit_event={
        ExitEvent.EXIT: on_exit(),
        ExitEvent.WORKBEGIN: on_work_begin(),
        ExitEvent.WORKEND: on_work_end(),
    },
)
simulator.run()

print(
    "Exiting @ tick {} because {}.".format(
        simulator.get_current_tick(),
        simulator.get_last_exit_event_cause(),
    )
)
