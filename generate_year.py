import argparse
import os
import shutil 


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--year', action="store", dest="year")
    parser.add_argument('--days', action="store", dest="days")

    args = parser.parse_args()

    if os.path.exists(args.year):
        shutil.rmtree(args.year)

    for day in range(1, int(args.days) + 1):
        path = os.path.join(args.year, "day" + str(day).zfill(2))
        shutil.copytree("template/dayYY", path) 

        files = []
        dirlist = [path]

        while len(dirlist) > 0:
            for (dirpath, dirnames, filenames) in os.walk(dirlist.pop()):
                # remove .DS_store files
                filenames = [i for i in filenames if not i.startswith('.')]

                dirlist.extend(dirnames)
                files.extend(map(lambda n: os.path.join(*n), zip([dirpath] * len(filenames), filenames)))

        for file in files:
            with open(file, "rt") as f:
                x = f.read()
                
            with open(file, "wt") as f:
                x = x.replace('XXXX', args.year).replace('YY', str(day).zfill(2))
                f.write(x)


if __name__ == "__main__":
    main()