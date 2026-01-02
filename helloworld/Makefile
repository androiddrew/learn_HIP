all:
	hipcc helloWorld.cpp -o helloWorld

clean:
	rm -rf helloWorld

profile:
	rocprofv3 --kernel-trace --stats --output-format csv -d ./profileResults -- ./helloWorld
