"""Tap vs hold and cooldown for game.spawn_weapons_on_back.

Compiles tools/tests/spawn_weapons_on_back_test.c against
source/game/spawn_weapons_on_back.h. Needs only a C compiler.

Usage: test_spawn_weapons_on_back.py [--cc clang]
"""

import argparse
import os
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent


def main():
	parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
	parser.add_argument("--cc", default=os.environ.get("CC", "cc"))
	arguments = parser.parse_args()
	with tempfile.TemporaryDirectory() as directory:
		program = Path(directory) / "spawn_weapons_on_back_test"
		subprocess.run(
			[
				arguments.cc,
				"-std=c11",
				"-Wall",
				"-Werror",
				"-g",
				"-I",
				str(ROOT / "source"),
				str(ROOT / "tools/tests/spawn_weapons_on_back_test.c"),
				"-o",
				str(program),
			],
			check=True,
		)
		result = subprocess.run([str(program)], check=True, capture_output=True, text=True)
		if result.stdout.strip() != "ok":
			sys.stderr.write(result.stdout)
			sys.stderr.write(result.stderr)
			sys.exit(1)
	print("ok   spawn_weapons_on_back")


if __name__ == "__main__":
	main()
