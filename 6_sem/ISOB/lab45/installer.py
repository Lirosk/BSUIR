import os
import sys
import shutil
import zipfile
import subprocess
from getpass import getpass


def main(filename: str):
    print("Enter install password:")
    password = getpass()

    target_dir = unzip(filename, password)
    install_requirements(target_dir)

    print('Install done')


def unzip(filename: str, password: str) -> str:
    target_dir = filename
    if target_dir.endswith(".zip") or target_dir.endswith(".rar"):
        target_dir = filename[:-4]

    try:
        with zipfile.ZipFile(filename) as zf:
            zf.extractall(pwd=bytes(password,'utf-8'))
        
        # with zipfile.ZipFile(filename) as z:
        #     z.setpassword(password.encode())
        #     z.extractall(target_dir)

        return target_dir
    except Exception as e:
        if (os.path.exists(target_dir)):
            shutil.rmtree(target_dir)
        print(e)
        exit(-1)


def install_requirements(dir: str):
    return
    file = os.path.join(dir, "requirements.txt")
    subprocess.Popen([f"pip install -r {file}"]).wait()

if __name__ == '__main__':
    DIR = os.getcwd()

    filename = 'data.zip'

    args = sys.argv
    if len(args) == 2:
        filename == args[1]

    filename = os.path.join(DIR, filename)

    main(filename)
