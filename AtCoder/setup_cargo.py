'''
setup_cargo.py
rust用のプロジェクトを生成する
'''
import argparse
import os
import shutil
import subprocess

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('contest', type=str, help='name of contest')
    parser.add_argument('problem_id', type=str,
                        help='number of problems')

    current_dir = os.getcwd()
    script_dir = os.path.dirname(os.path.abspath(__file__))

    args = parser.parse_args()
    problems = []
    try:
        num = int(args.problem_id)
        problems.extend(map(chr, range(ord('A'), ord('A')+num)))
    except:
        problems.append(args.problem_id)

    try:
        os.chdir(script_dir)
        subprocess.run(['cargo', 'init' if os.path.exists(f'./{args.contest}') else 'new', args.contest])

        crates = [
            'num', 'num-derive', 'ndarray', 'nalgebra', 'libm',
            'rand', 'rand_distr', 'petgraph', 'indexmap', 'regex',
            'lazy_static', 'ordered-float', 'ascii', 'permutohedron', 'superslice',
            'itertools', 'itertools-num', 'maplit',  'either', 'im-rc',
            'fixedbitset', 'bitset-fixed', 'proconio', 'text_io', 'whiteread',
            'rustc-hash', 'smallvec'
        ]

        os.chdir(os.path.join(script_dir, args.contest))
        subprocess.run(['cargo', 'add'] + crates)

        os.makedirs('src/bin', exist_ok=True)

        for id in problems:
            if not os.path.exists(f'src/bin/{id}.rs'):
                shutil.copy('src/main.rs', f'src/bin/{id}.rs')

        subprocess.run(['cargo', 'build'])
    finally:
        os.chdir(current_dir)
