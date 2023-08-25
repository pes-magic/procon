import optuna
import glob
import subprocess
from multiprocessing import Pool

def convert(name, dist, search, base_val, base_num):
    # base_name, ext = os.path.splitext(os.path.basename(name))
    # cmd = f'tools/target/release/tester.exe {name} a.exe'
    # result = subprocess.run(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)
    # return int(result.stderr.decode().strip().split(' ')[2])
    # コマンドを定義
    cmd = ["./target/release/tester", "./target/release/solver2", dist, search, base_val, base_num]

    # ファイル 'F.in' の内容を標準入力として使用
    with open(name, "rb") as file_input:
        result = subprocess.run(cmd, stdin=file_input, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)

    # エラー出力を取得
    error_output = result.stderr.decode().split()
    return int(error_output[-19])


def multi(s, dist, search, base_val, base_num):
    folder = f"S{s:02d}" if s >= 1 else "in_default"
    scores = 0
    for f in glob.glob(f"./{folder}/00*.txt"):
        scores += convert(f, dist, search, base_val, base_num)
    return scores

 
def run_study(s):
    study = optuna.create_study(study_name=f'study-s{s:02d}',
                                storage=f'sqlite:///study-s{s:02d}.db',
                                load_if_exists=True,
                                direction='maximize')
    cur_s = s
    dist_low = 1
    dist_high = 7
    search_low = 3
    search_high = 100
    base_val_low = s*s
    base_val_high = min([9*s*s, 1000])
    base_num_low = 2
    base_num_high = min([1000//base_val_low + 1, 12])
        
    def objective(trial):
        dist = trial.suggest_int("dist", dist_low, dist_high)
        search = trial.suggest_int("search", search_low, search_high)
        base_val = trial.suggest_int("base_val", base_val_low, base_val_high)
        base_num = trial.suggest_int("base_num", base_num_low, base_num_high)
        if base_val * (base_num-1) > 1000:
            return 0
        return multi(cur_s, str(dist), str(search), str(base_val), str(base_num))

    study.optimize(objective, n_trials=10, timeout=36000)
    print(study.best_trial)
    with open(f"bestparam_s{s:02d}.txt", "w") as f:
        print(study.best_trial, file=f)

import argparse

parser = argparse.ArgumentParser(description="整数1個を受け取ります")
parser.add_argument("number", type=int, help="整数の値")

args = parser.parse_args()

run_study(args.number)