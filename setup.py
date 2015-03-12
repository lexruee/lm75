# encoding: utf-8
from distutils.core import setup, Extension
setup(
	name="tentacle_pi.LM75", 
	version="1.0",
	url = "https://github.com/lexruee/tentacle_pi",
	author = "Alexander Rüedlinger",
	author_email = "a.rueedlinger@gmail.com",
	packages = ["tentacle_pi"],
	ext_modules = [
		Extension("tentacle_pi.LM75", 
			sources = ["src/lm75.c", "src/lm75_ext.c"])
	],
	license = "MIT"
)
