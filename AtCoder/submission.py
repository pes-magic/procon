"""
sample_getter.py
入力されたコンテスト名から各問題のサンプルを得る
"""

import json
import os
import re
import sys
import requests
from bs4 import BeautifulSoup


def gen_login_info(session):
    """
    ログイン処理
    Parameters
    -------
    session
        ログインに使うセッション
    """
    res = {}
    # userdata.json にはログインに使うユーザ情報を以下の形式で入れておく
    # {
    #     "username": <username>,
    #     "password": <password>
    # }
    with open("userdata.json", "r") as f:
        res = json.load(f)
    html = session.get("https://atcoder.jp/login")
    soup = BeautifulSoup(html.text, "html.parser")
    token = soup.find(attrs={"name": "csrf_token"}).get("value")
    res["csrf_token"] = token
    return res


def log_in():
    """
    ログイン処理
    Returns
    -------
    session
        ログイン済みセッション
    """
    session = requests.session()
    session.post("https://atcoder.jp/login", data=gen_login_info(session))
    return session


def submit_code(contest_name: str, source_path: str, problem_ids: list[str]):
    """
    指定されたファイルを提出する
    Parameters
    ----------
    contest_name : str
        コンテスト名(URL)
    source_path : str
        ソースコードのパス
    problem_ids : list[str]
        問題IDのリスト
    """
    session = log_in()
    with open(source_path) as f:
        source_code = f.read()
    for id in problem_ids:
        url = f"https://atcoder.jp/contests/{contest_name}/submit?taskScreenName={contest_name}_{id}"
        html = session.get(url)
        soup = BeautifulSoup(html.text, "html.parser")
        csrf_input = soup.find("input", {"name": "csrf_token"})
        csrf_token = csrf_input["value"]
        data = {
            "data.TaskScreenName": f"{contest_name}_{id}",
            "data.LanguageId": "5028",  # C++23 (gcc 12.2)
            "sourceCode": source_code,
            "csrf_token": csrf_token,
        }

        # 提出リクエストを送信
        session.post(url, data=data)


if __name__ == "__main__":
    if len(sys.argv) >= 4:
        submit_code(sys.argv[1], sys.argv[2], sys.argv[3:])
    else:
        print("Usage: python ./submission.py <contest-name> <source-code-path> <problem-ids>")
