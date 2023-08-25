import random
import os
import shutil
import subprocess

for s in range(1, 31):
    # seeds.txtに1000行を出力
    unique_random_integers = random.sample(range(1, 1000000001), 1000)  # 1000個のユニークな乱数を生成
    with open("my_seeds.txt", "w") as file:
        for r in unique_random_integers:
            line = f"{r} 0 0 {s*s}\n"
            file.write(line)

    # # cargoコマンドを実行
    subprocess.run(["cargo", "run", "--release", "--bin", "gen", "my_seeds.txt"])

    # ディレクトリ名を作成
    dir_name = f"S{s:02d}"
    print(dir_name)

    # ディレクトリが存在しない場合、作成
    if not os.path.exists(dir_name):
        os.makedirs(dir_name)

    # inディレクトリの中身をすべて移動
    src_dir = "in"
    for filename in os.listdir(src_dir):
        src_path = os.path.join(src_dir, filename)
        dest_path = os.path.join(dir_name, filename)
        shutil.move(src_path, dest_path)

    print(f"Operation completed for s={s}")
