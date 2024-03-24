import glob
import os
import time
import subprocess
from multiprocessing import Pool


def run(name: str) -> None:
    base_name, ext = os.path.splitext(os.path.basename(name))
    with open(name) as f:
        with open(f"./tools/out/{base_name}.txt", "w") as f2:
            cmd = "./target/release/main"
            subprocess.run(cmd, stdin=f, stdout=f2, stderr=subprocess.DEVNULL, shell=True)


def multi():
    t1 = time.time()
    p = Pool(32)
    p.map(run, glob.glob("./tools/in/*.txt"))
    t2 = time.time()
    print(t2 - t1)


def main():
    multi()


if __name__ == "__main__":
    main()
