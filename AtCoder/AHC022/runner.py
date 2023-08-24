import glob
import json
import time
import subprocess
import sys
from multiprocessing import Pool
from multiprocessing import Process


def convert(name):
    # base_name, ext = os.path.splitext(os.path.basename(name))
    # cmd = f'tools/target/release/tester.exe {name} a.exe'
    # result = subprocess.run(cmd, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)
    # return int(result.stderr.decode().strip().split(' ')[2])
    # コマンドを定義
    cmd = ["./target/release/tester", "./target/release/solver"]

    # ファイル 'F.in' の内容を標準入力として使用
    with open(name, "rb") as file_input:
        result = subprocess.run(cmd, stdin=file_input, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)

    # エラー出力を取得
    error_output = result.stderr.decode().split()
    return int(error_output[-19]), int(error_output[-13])


def multi(s):
    folder = f"S{s:02d}" if s >= 1 else "in_default"
    t1 = time.time()
    p = Pool(30)
    a = p.map(convert, glob.glob(f"./{folder}/*.txt"))
    scores, errors = zip(*a)
    sum_score = sum(scores)
    sum_error = sum(errors)
    print(f"Result: {s}", file=sys.stderr)
    print(f"* Score: {sum_score}", file=sys.stderr)
    print(f"* Error: {sum_error}", file=sys.stderr)
    t2 = time.time()
    print(t2 - t1, file=sys.stderr)
    return {"score": sum_score, "error": sum_error}


def main():
    res = {s: multi(s) for s in range(1, 31)}
    print(json.dumps(res, indent=4))


if __name__ == "__main__":
    main()
