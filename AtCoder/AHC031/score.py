import glob
import os
import time
import subprocess
from multiprocessing import Pool

def vis(name: str) -> int:
    base_name, ext = os.path.splitext(os.path.basename(name))
    cmd = ['tools/target/release/vis', name, f'./tools/out/{base_name}.txt']
    result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
    return int(result.stdout.decode().strip().split(' ')[2])

def multi():
	t1 = time.time()
	p = Pool(30)
	score = p.map(vis, glob.glob('./tools/in/*.txt'))
	for i, s in enumerate(score):
		print(f'{i}: {s}')
	print(sum(score))
	t2 = time.time()
	print(t2-t1)

def main():
	multi()

if __name__ == '__main__':
	main()

