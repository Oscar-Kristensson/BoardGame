import os
import shutil
import json
import tarfile
import hashlib
import sys


with open("scripts/packageConfig.json", "r") as f:
    CONFIG = json.load(f) 


print("Current working dir", os.getcwd())

if os.path.isdir("build/dist"):
    print("The build/dist dir already exists. Trying to auto remove it", end=": ")
    try:
        shutil.rmtree("build/dist")
        print("Success")
    except Exception as e:
        print(f"\nSomething went wrong: \n {e}")
        quit("Failed to package")

def getFileHash(file_path, returnDict = False):
    out = []
    for algorithm in [hashlib.sha256(), hashlib.sha1(), hashlib.sha512(), hashlib.md5()]:
        with open(file_path, 'rb') as f:
            for chunk in iter(lambda: f.read(8192), b''):
                algorithm.update(chunk)

        out.append(algorithm.hexdigest())
    
    if returnDict:
        return {
            "SHA256": out[0],
            "SHA1": out[1],
            "SHA512": out[2],
            "MD5": out[3]
        }

    return out

def compressFolder(folderPath, outputPath):
    with tarfile.open(outputPath, "w:xz") as tar:
        for item in os.listdir(folderPath):
            item_path = os.path.join(folderPath, item)
            tar.add(item_path, arcname=item)  # Add item directly at archive root


def userCheckAndCreateDir(path, auto = False):
    if auto:
        if not os.path.isdir(path):
            print("Creating folder", path)
            os.mkdir(path)
        return

    while(not os.path.isdir(path)):
        response = input(f"There is no {path} dir in current folder. Would you like to generate the folder (Y/n):")
        if response == "Y":
            os.mkdir(path)
        elif response == "n":
            quit("Failed to package")
        else:
            print("Did not understand the input, stop with n\n")

def copyFolder(path):
    try:
        print("Copying folder", path)
        shutil.copytree(path, f"build/{CONFIG['distDir']}/{path}")

    except Exception as e:
        print(f"Something went wrong when copying folder {path}: \n{e}")
        quit("Failed to package")


def installGame(name):
    if not os.path.exists(f"games/{name}"):
        print(f"Could not include game {name} because it was not found")
        return False
    
    copyFolder(f"games/{name}")

# Create the new dirs
userCheckAndCreateDir("build")
userCheckAndCreateDir(f"build/{CONFIG['distDir']}", True)
userCheckAndCreateDir(f"build/{CONFIG['distDir']}/games", True)
userCheckAndCreateDir(f"build/{CONFIG['outputDir']}", True)


# Copy executable
extension = ""
if sys.platform == "win32":
    extension = ".exe"


if not os.path.exists(f"{CONFIG['executable']}{extension}"):
    print(f"ERROR: The executable {CONFIG['executable']} could not be found. Check the it exists and works.")
    quit("Failed to package")

shutil.copyfile(f"{CONFIG['executable']}{extension}", f"build/{CONFIG['distDir']}/{CONFIG['executableOutput']}{extension}")



# Copy folders
copyFolder("assets")
copyFolder("licenses")

installedGames = []
for game in CONFIG["includeGames"]:
    print(f"Installing game {game}")
    if installGame(game):
        installedGames.append(game)



# Copy Windows files
if sys.platform == "win32":
    for scriptName in CONFIG["copyFiles"]["windowsScripts"]:
        shutil.copyfile(f"scripts/{scriptName}", f"build/{CONFIG['distDir']}/{scriptName}")


# Copy files
for fileName in CONFIG["copyFiles"]["all"]:
    if os.path.exists(fileName):
        print(f"Copying file {fileName}")
        shutil.copyfile(f"{fileName}", f"build/{CONFIG['distDir']}/{fileName}")
    else:
        print(f"Failed to copy {fileName} because the file does not exist")



# Compressing folders
print("Compressing folders")
compressFolder("build/dist", f"build/{CONFIG['outputDir']}/{CONFIG['programName']}.tar.xz")
shutil.make_archive(f"build/{CONFIG['outputDir']}/{CONFIG['programName']}", "zip", f"build/dist")


# Generating metadata
CHECKSUMS = {
    f"{CONFIG['programName']}.tar.xz": getFileHash(f"build/{CONFIG['outputDir']}/{CONFIG['programName']}.tar.xz", True),
    f"{CONFIG['programName']}.zip": getFileHash(f"build/{CONFIG['outputDir']}/{CONFIG['programName']}.zip", True)
}




# Generate CHECKSUM TEXT
string = ""
for key in CHECKSUMS:
    string += f"\n{key}:\n"
    for algorithm in CHECKSUMS[key]:
        string += f"{algorithm}: {CHECKSUMS[key][algorithm]}\n"

print(string)

with open(f"build/{CONFIG['outputDir']}/{CONFIG['checksumFile']}", "w") as f:
    f.write(string)



METADATA = {
    "checksums": CHECKSUMS,
    "version": CONFIG["version"]
}


with open(f"build/{CONFIG['outputDir']}/{CONFIG['metadataFile']}", "w") as f:
    json.dump(METADATA, f, indent=4)