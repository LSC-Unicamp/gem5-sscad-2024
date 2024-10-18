mkdir gem5
cd gem5
git clone https://github.com/gem5/gem5.git .
git checkout tags/v24.0.0.1
python -m venv .venv
source .venv/bin/activate
pip install -r requirements.txt
pre-commit install
pre-commit install -t prepare-commit-msg

scons build/RISCV/gem5.opt -j`nproc`