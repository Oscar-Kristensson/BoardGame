import os
import shutil
import subprocess
import platform

BUILD_SYSTEM_DATA = [
    # Name, command, platforms
    ["VS2022", "Visual Studio 17 2022", "Windows"],
    ["MinGW", "MinGW Makefiles", "Windows"],
    ["Default cmake", None, "All platforms"]
]

IDE_BUILD_SYSTEMS = [0, 2]

BUILD_TYPES = ["Debug", "Release"]

def clearTerminal():
    if platform.system() == "Windows":
        os.system("cls")
    else:
        os.system("clear")

def addDividerInTerminal():
    print("\n"*2)
    print("-"*40)
    print("\n"*2)


def createACleanBuildDir():
    if os.path.exists("build"):
        print("Cleaning the build dir")
        shutil.rmtree("build")
    else:
        print("Creating build dir")

    os.mkdir("build")


def getConfirmedUserInput(prompt):
    while True:
        userInput = input(prompt + " (Use q to quit) ")
        if userInput == "q":
            quit()
        
        if input("Confirm (Y/n)") == "Y":
            return userInput
        
def createSelectUI(name = "a build system", max = 999):
    while True:
        userInput = input(f"Select {name} (q to quit): ")
        if userInput == "q":
            print("Exiting")
            quit()
        
        try:
            id = int(userInput)
        except ValueError:
            print("Input a valid integer")
            continue

        if id < 0 or id + 1 > max:
            print("Input a integer in the valid range")
            continue

        return id



def getBuildSystem():
    print()
    print("ID | Build system    | Platform")
    print("---|-----------------|---------")
    for i, buildSystem in enumerate(BUILD_SYSTEM_DATA):
        print(f"{str(i).ljust(3)}|{buildSystem[0].ljust(16)}| {buildSystem[2].ljust(16)}")
    
    print()
    return createSelectUI("a build system", len(BUILD_SYSTEM_DATA))


def getBuildType():
    print()
    print("ID | Build type")
    print("---|-----------")
    for i, buildType in enumerate(BUILD_TYPES):
        print(f"{str(i).ljust(3)}|{buildType}")
    
    print()
    return createSelectUI("a build type", len(BUILD_TYPES))

         
def generateBuildFiles(buildSystem, buildType = "Debug"):
    # Move in to the build dir
    os.chdir("build")
    command = ["cmake", ".."]
    
    if buildSystem not in IDE_BUILD_SYSTEMS or buildSystem == 2: # Add for default cmake
        print(f"Not an IDE -> generating {buildType} Makefiles")
        command.insert(1, f"-DCMAKE_BUILD_TYPE={buildType}")

    if BUILD_SYSTEM_DATA[buildSystem][1] is not None:
        command.insert(1, BUILD_SYSTEM_DATA[buildSystem][1])
        command.insert(1, "-G")


    print("Generating the project files\n")
    subprocess.run(command)
    os.chdir("..")

def buildTheProject(buildSystem, buildType):
    os.chdir("build")
    command = ["cmake", "--build", "."]
    
    if buildSystem in IDE_BUILD_SYSTEMS:
        print(f"IDE -> setting {buildType}")
        command.append("--config")
        command.append(buildType)

    print("Building the project\n")
    subprocess.run(command)
    os.chdir("..")

def createInformationPanelUI():
    print("------------------ Build information ------------------")
    buildSystem = getBuildSystem()
    buildType = BUILD_TYPES[getBuildType()]

    autoPackage = input("Do you want to package? (Y/n): ") == "Y"

    if autoPackage and buildType != "Release":
        print("Warning! Use the Release buildType inorder to package!")

    return {
        "system": buildSystem,
        "type": buildType,
        "package": autoPackage
    }



        
def build():
    # Gather information
    clearTerminal()
    info = createInformationPanelUI()

    if info["package"]:
        from package import package, CONFIG

    
    clearTerminal()
    buildInfoString = f"------- Build: -------\nType: {info['type']}\nSystem: {BUILD_SYSTEM_DATA[info['system']][0]}"
    if info['package']:
        buildInfoString += f"\nWill be packaged\nVersion: {CONFIG['version']}"



    print(buildInfoString)



    if input("\nConfirm with enter (stop with q): ") == "q": quit()

    # Run the build process
    clearTerminal()
    print("Cleaning/creating the build dir")
    createACleanBuildDir()

    print("Writing build information to build/info.txt")
    with open("build/info.txt", "w") as f:
        f.write(buildInfoString)

    addDividerInTerminal()
    generateBuildFiles(info["system"], info["type"])

    addDividerInTerminal()
    buildTheProject(info["system"], info["type"])


    if info["package"]:
        print("Packaging")
        addDividerInTerminal()
        package()




if __name__ == "__main__":
    build()
