import os

excutable = "cmake-build-debug/EX2"
n_thread = ["1", "2", "3", "4"]
imgInB = "img"
imgOutB = "imgO"

for imgNum in range(1,10):
	imgIn = imgInB + str(imgNum) + ".bmp"
	imgOut = imgOutB + str(imgNum) + ".bmp"
	for num in n_thread:
		command = excutable + " " + num + " " + imgIn + " " +imgOut
		for i in range(10):
			result = os.system(command)



	