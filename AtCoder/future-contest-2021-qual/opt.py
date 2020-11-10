import glob
import os
import subprocess
import sys
import optuna

def objective(trial):
    low_temp = trial.suggest_uniform('low_temp', 0, 5)
    high_temp = trial.suggest_uniform('high_temp', 0, 5)
    iter = trial.suggest_uniform('iter', 1, 100000)
    whole = 0
    for i in range(50):
        proc = subprocess.run(f'./a.out {low_temp} {high_temp} {move_temp} < testCase_{i}.txt', shell=True, stdout = subprocess.PIPE)
        res = proc.stdout.decode("utf8")
        cost = 0
        for c in res:
            if c not in "IO":
                cost += 1
        whole += cost

    return whole

study = optuna.create_study(study_name = 'future2021', storage='sqlite:///future2021.db', load_if_exists = True)
study.optimize(objective, n_trials=100)

print(study.best_params)
