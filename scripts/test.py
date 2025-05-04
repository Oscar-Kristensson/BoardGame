filePath = input("Input the path to the file")

with open(filePath, "r") as f:
    fileData = f.read()

# Removes spaces and splits in to lines
fileData = fileData.replace(" ", "")
fileData = fileData.replace("\n", "")
lines = fileData.split(";")

for line in lines:
    if line == "":
        continue

    arguments = line.split(",")

    instructionName = arguments[0]
    
    argumentDict = {}

    for i in range(1, len(arguments)):
        if not "=" in arguments[i]:
            print(arguments[i], "did not have a = sign")
            continue
        
        key, value = arguments[i].split("=")
        
        argumentDict[key] = value

    print(instructionName, argumentDict)
