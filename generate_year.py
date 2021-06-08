import argparse
import os
import shutil 


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--year', action="store", dest="year")

    args = parser.parse_args()

    if os.path.exists(args.year):
        shutil.rmtree(args.year)
    shutil.copytree("template", args.year) 

    files = []
    dirlist = [args.year]

    while len(dirlist) > 0:
        for (dirpath, dirnames, filenames) in os.walk(dirlist.pop()):
            # remove .DS_store files
            filenames = [i for i in filenames if not i.startswith('.')]

            dirlist.extend(dirnames)
            files.extend(map(lambda n: os.path.join(*n), zip([dirpath] * len(filenames), filenames)))

    for file in files:
        print(file)
        with open(file, "rt") as f:
            x = f.read()
            
        with open(file, "wt") as f:
            x = x.replace('XXXX', args.year)
            f.write(x)


if __name__ == "__main__":
    main()