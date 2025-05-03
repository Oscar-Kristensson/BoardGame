import subprocess
import os



def renderSVGAssets(files = [], inputDir = "", outputDir = "", dpi = "180"):
    print("Current Working Directory:", os.getcwd())

    for file in files:
        print("Rendering", file)
        command = [
            "C:/Program Files/Inkscape/bin/inkscape.exe", # Inkscape path
            f"{inputDir}{file}.svg",
            "--export-type=png",
            f"--export-dpi={dpi}",
            f"--export-filename={outputDir}{file}.png"
        ]

        result = subprocess.run(command, capture_output=True, text=True)

        if result.returncode != 0:
            print(f"Error rendering {file}: {result.stderr}")
        else:
            print(f"Successfully rendered {file}")

if __name__ == "__main__":
    renderSVGAssets([
       "map"
    ],inputDir = "assets/raw/", outputDir = "assets/", dpi = "384")



