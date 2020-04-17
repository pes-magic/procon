'''
test_runner.py
指定された実行ファイルに対してサンプルを実行する
'''
import glob
import os
import subprocess
import sys


if __name__ == '__main__':
    if len(sys.argv) >= 3:
#        os.chdir(os.getcwd())
        executable = sys.argv[1]
        problem_id = sys.argv[2]
        samples = list(glob.glob(f'./{problem_id}-sample-*.txt'))
        samples.sort()
        for f in samples:
            subprocess.run(f'{executable} < {f}', shell=True)
    else:
        print('Usage: python ./test_runner.py <executable> <problem-id>')
