'''
setup_cargo.py
rust用のプロジェクトを生成する
'''
import argparse
import os
import subprocess
import toml

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('problem_id', type=str,
                        help='number of problems')

    args = parser.parse_args()
    problems = []
    try:
        num = int(args.problem_id)
        problems.extend(map(chr, range(ord('A'), ord('A')+num)))
    except:
        problems.append(args.problem_id)

    for id in problems:
        if not os.path.exists(f'./{id}'):
            subprocess.run(f'cargo new {id}', shell=True)

    crates = [
        'num', 'num-derive', 'ndarray', 'nalgebra', 'libm',
        'rand', 'rand_distr', 'petgraph', 'indexmap', 'regex',
        'lazy_static', 'ordered-float', 'ascii', 'permutohedron', 'superslice',
        'itertools', 'itertools-num', 'maplit',  'either', 'im-rc',
        'fixedbitset', 'bitset-fixed', 'proconio', 'text_io', 'whiteread',
        'rustc-hash', 'smallvec'
    ]

    for id in problems:
        t = toml.load(open(f'./{id}/Cargo.toml'))
        t['package']['name'] = t['package']['name'].lower()
        for c in crates:
            t['dependencies'][c] = '*'
        toml.dump(t, open(f'./{id}/Cargo.toml', 'w'))

    for id in problems:
        os.chdir(f'./{id}')
        subprocess.run('cargo build', shell=True)
        os.chdir('../')

    # for i in range(args.problem_num):
    #     file_name = f'{args.folder_name}/{chr(ord("A")+i)}.cpp'
    #     if os.path.isfile(file_name):
    #         continue
    #     with open(file_name, 'w') as f:
    #         pass
