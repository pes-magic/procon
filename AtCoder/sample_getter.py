'''
sample_getter.py
入力されたコンテスト名から各問題のサンプルを得る
'''
import json
import os
import re
import sys
import requests
from bs4 import BeautifulSoup

def gen_login_info(session):
    '''
    ログイン処理
    Parameters
    -------
    session
        ログインに使うセッション
    '''
    res = {}
    # userdata.json にはログインに使うユーザ情報を以下の形式で入れておく
    # {
    #     "username": <username>,
    #     "password": <password>
    # }
    with open('userdata.json', 'r') as f:
        res = json.load(f)
    html = session.get('https://atcoder.jp/login')
    soup = BeautifulSoup(html.text, 'html.parser')
    token = soup.find(attrs={'name':'csrf_token'}).get('value')
    res['csrf_token'] = token
    return res

def log_in():
    '''
    ログイン処理
    Returns
    -------
    session
        ログイン済みセッション
    '''
    session = requests.session()
    session.post('https://atcoder.jp/login', data=gen_login_info(session))
    return session

def get_samples(session, contest_name, problem_id, problem_url):
    '''
    指定されたIDのサンプルをファイルに書き出す
    Parameters
    ----------
    session
        ログイン済みセッション
    contest_name : str
        コンテスト名(URL)
    problem_id : str
        問題ID
    problem_url : str
        問題URL
    '''
    html = session.get(problem_url)
    soup = BeautifulSoup(html.text, 'html.parser')
    if not os.path.isdir(contest_name):
        os.mkdir(contest_name)
    case_id = 0
    for tag in soup.find_all('section'):
        h3_tag = tag.find('h3', string=re.compile('入力例'))
        if h3_tag is None:
            continue
        with open(f'{contest_name}/{problem_id}-sample-{case_id:02d}.txt', 'w') as f:
            f.write(tag.find('pre').text.replace('\r', ''))
        case_id += 1

def search_problem(contest_name):
    '''
    指定されたコンテストの全問題のサンプルをファイルに書き出す
    Parameters
    ----------
    contest_name : str
        コンテスト名(URL)
    '''
    session = log_in()
    url = f'https://atcoder.jp/contests/{contest_name}/tasks'
    html = session.get(url)
    soup = BeautifulSoup(html.text, 'html.parser')
    for tag in soup.find_all('a', href=re.compile('/tasks/'))[0::2]:
        problem_id = tag.text
        problem_url = f'https://atcoder.jp{tag.get("href")}'
        get_samples(session, contest_name, problem_id, problem_url)

if __name__ == '__main__':
    if len(sys.argv) >= 2:
        search_problem(sys.argv[1])
    else:
        print('Usage: python ./sample_getter.py <contest-name>')
