import os
import shutil
import pyzipper
from getpass import getpass


filename = 'C:\\Users\\kiril\\Desktop\\ИСОБ\\lab4-5\\django_project.zip'
target_dir = 'C:\\Users\\kiril\\Desktop\\ИСОБ\\lab4-5\\'


def main(filename: str):
    print("Enter install password:")
    password = getpass()

    unzip(filename, password)

    print('Install done')


def unzip(filename: str, password: str) -> str:
    try:
        with pyzipper.AESZipFile(filename, 'r') as z:
            z.setpassword(password.encode('UTF-8'))
            z.extractall(target_dir)

    except Exception as e:
        dir_delete = os.path.join(target_dir, "django_project")
        if (os.path.exists(dir_delete)):
            shutil.rmtree(dir_delete)
        print(e)
        exit(-1)


if __name__ == '__main__':
    main(filename)
